//
// Created by Andrei Bratu on 26.12.2020.
//

#ifndef PROJECT_CANNY_H
#define PROJECT_CANNY_H

#include <highgui.h>

// Kudos @ https://github.com/hasanakg/Canny-Edge-Detector

#define WHITE 255
#define BLACK 0

using namespace cv;

typedef std::vector<std::vector<double>> filter;

std::vector<std::vector<double>> create_gaussian_filter(int rows, int columns, double sigmaIn) {
    filter filter;

    for (int i = 0; i < rows; i++) {
        std::vector<double> col;
        col.reserve(columns);
        for (int j = 0; j < columns; j++) {
            col.push_back(-1);
        }
        filter.push_back(col);
    }

    double coord_sum;
    double constant = 2.0 * sigmaIn * sigmaIn;

    // Sum is for normalization
    float sum = 0.0;

    for (int x = -rows / 2; x <= rows / 2; x++) {
        for (int y = -columns / 2; y <= columns / 2; y++) {
            coord_sum = (x * x + y * y);
            filter[x + rows / 2][y + columns / 2] = (exp(-(coord_sum) / constant)) / (M_PI * constant);
            sum += filter[x + rows / 2][y + columns / 2];
        }
    }

    // Normalize the filter
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            filter[i][j] /= sum;

    return filter;
}

Mat apply_gaussian_filter(Mat img_in, const filter &filter) {
    int size = (int) filter.size() / 2;
    Mat filtered_img = Mat(img_in.rows - 2 * size, img_in.cols - 2 * size, CV_8UC1);
    for (int i = size; i < img_in.rows - size; i++) {
        for (int j = size; j < img_in.cols - size; j++) {
            double sum = 0;

            for (int x = 0; x < filter.size(); x++)
                for (int y = 0; y < filter.size(); y++) {
                    sum += filter[x][y] * (double) (img_in.at<uchar>(i + x - size, j + y - size));
                }

            filtered_img.at<uchar>(i - size, j - size) = sum;
        }

    }
    return filtered_img;
}

std::pair<Mat, Mat> apply_sobel(Mat gaussian_filtered) {
    //Sobel X filter
    double x1[] = {-1.0, 0, 1.0};
    double x2[] = {-2.0, 0, 2.0};
    double x3[] = {-1.0, 0, 1.0};

    vector<vector<double>> xFilter(3);
    xFilter[0].assign(x1, x1 + 3);
    xFilter[1].assign(x2, x2 + 3);
    xFilter[2].assign(x3, x3 + 3);

    //Sobel Y filter
    double y1[] = {1.0, 2.0, 1.0};
    double y2[] = {0, 0, 0};
    double y3[] = {-1.0, -2.0, -1.0};

    vector<vector<double>> yFilter(3);
    yFilter[0].assign(y1, y1 + 3);
    yFilter[1].assign(y2, y2 + 3);
    yFilter[2].assign(y3, y3 + 3);

    //Limit Size
    int size = (int) xFilter.size() / 2;

    Mat filteredImg = Mat(gaussian_filtered.rows - 2 * size, gaussian_filtered.cols - 2 * size, CV_8UC1);

    Mat angles = Mat(gaussian_filtered.rows - 2 * size, gaussian_filtered.cols - 2 * size, CV_32FC1); //AngleMap

    for (int i = size; i < gaussian_filtered.rows - size; i++) {
        for (int j = size; j < gaussian_filtered.cols - size; j++) {
            double sumX = 0;
            double sumY = 0;

            for (int x = 0; x < xFilter.size(); x++)
                for (int y = 0; y < xFilter.size(); y++) {
                    sumX += xFilter[x][y] *
                            (double) (gaussian_filtered.at<uchar>(i + x - size, j + y - size)); //Sobel_X filter Value
                    sumY += yFilter[x][y] *
                            (double) (gaussian_filtered.at<uchar>(i + x - size, j + y - size)); //Sobel_Y filter Value
                }
            double sumXSquared = sumX * sumX;
            double sumYSquared = sumY * sumY;

            double sq2 = sqrt(sumXSquared + sumYSquared);

            if (sq2 > 255) //Unsigned Char Fix
                sq2 = 255;
            filteredImg.at<uchar>(i - size, j - size) = sq2;

            if (sumX == 0) //Arctan Fix
                angles.at<float>(i - size, j - size) = 90;
            else
                angles.at<float>(i - size, j - size) = atan(sumY / sumX);
        }
    }

    return {filteredImg, angles};
}

Mat apply_non_max_suppresion(Mat sobel_filtered, Mat angles) {
    Mat nonMaxSupped = Mat(sobel_filtered.rows - 2, sobel_filtered.cols - 2, CV_8UC1);
    for (int i = 1; i < sobel_filtered.rows - 1; i++) {
        for (int j = 1; j < sobel_filtered.cols - 1; j++) {
            float Tangent = angles.at<float>(i, j);

            nonMaxSupped.at<uchar>(i - 1, j - 1) = sobel_filtered.at<uchar>(i, j);
            //Horizontal Edge
            if (((-22.5 < Tangent) && (Tangent <= 22.5)) || ((157.5 < Tangent) && (Tangent <= -157.5))) {
                if ((sobel_filtered.at<uchar>(i, j) < sobel_filtered.at<uchar>(i, j + 1)) ||
                    (sobel_filtered.at<uchar>(i, j) < sobel_filtered.at<uchar>(i, j - 1)))
                    nonMaxSupped.at<uchar>(i - 1, j - 1) = 0;
            }
            //Vertical Edge
            if (((-112.5 < Tangent) && (Tangent <= -67.5)) || ((67.5 < Tangent) && (Tangent <= 112.5))) {
                if ((sobel_filtered.at<uchar>(i, j) < sobel_filtered.at<uchar>(i + 1, j)) ||
                    (sobel_filtered.at<uchar>(i, j) < sobel_filtered.at<uchar>(i - 1, j)))
                    nonMaxSupped.at<uchar>(i - 1, j - 1) = 0;
            }

            //-45 Degree Edge
            if (((-67.5 < Tangent) && (Tangent <= -22.5)) || ((112.5 < Tangent) && (Tangent <= 157.5))) {
                if ((sobel_filtered.at<uchar>(i, j) < sobel_filtered.at<uchar>(i - 1, j + 1)) ||
                    (sobel_filtered.at<uchar>(i, j) < sobel_filtered.at<uchar>(i + 1, j - 1)))
                    nonMaxSupped.at<uchar>(i - 1, j - 1) = 0;
            }

            //45 Degree Edge
            if (((-157.5 < Tangent) && (Tangent <= -112.5)) || ((22.5 < Tangent) && (Tangent <= 67.5))) {
                if ((sobel_filtered.at<uchar>(i, j) < sobel_filtered.at<uchar>(i + 1, j + 1)) ||
                    (sobel_filtered.at<uchar>(i, j) < sobel_filtered.at<uchar>(i - 1, j - 1)))
                    nonMaxSupped.at<uchar>(i - 1, j - 1) = 0;
            }
        }
    }
    return nonMaxSupped;
}

Mat get_binary_canny_image(Mat image, int low, int high) {
    low = std::min(low, 255);
    high = std::min(high, 255);
    Mat edgeMat = Mat(image.rows, image.cols, image.type());

    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            edgeMat.at<uchar>(i, j) = image.at<uchar>(i, j);
            if (edgeMat.at<uchar>(i, j) > high)
                edgeMat.at<uchar>(i, j) = WHITE;
            else if (edgeMat.at<uchar>(i, j) < low)
                edgeMat.at<uchar>(i, j) = BLACK;
            else {
                bool anyHigh = false;
                bool anyBetween = false;
                for (int x = i - 1; x < i + 2; x++) {
                    for (int y = j - 1; y < j + 2; y++) {
                        if (x <= 0 || y <= 0 || edgeMat.rows || y > edgeMat.cols) //Out of bounds
                            continue;
                        else {
                            if (edgeMat.at<uchar>(x, y) > high) {
                                edgeMat.at<uchar>(i, j) = WHITE;
                                anyHigh = true;
                                break;
                            } else if (edgeMat.at<uchar>(x, y) <= high && edgeMat.at<uchar>(x, y) >= low)
                                anyBetween = true;
                        }
                    }
                    if (anyHigh)
                        break;
                }
                if (!anyHigh && anyBetween)
                    for (int x = i - 2; x < i + 3; x++) {
                        for (int y = j - 1; y < j + 3; y++) {
                            if (x < 0 || y < 0 || x > edgeMat.rows || y > edgeMat.cols) //Out of bounds
                                continue;
                            else {
                                if (edgeMat.at<uchar>(x, y) > high) {
                                    edgeMat.at<uchar>(i, j) = WHITE;
                                    anyHigh = true;
                                    break;
                                }
                            }
                        }
                        if (anyHigh)
                            break;
                    }
                if (!anyHigh)
                    edgeMat.at<uchar>(i, j) = BLACK;
            }
        }
    }
    return edgeMat;
}


#endif //PROJECT_CANNY_H
