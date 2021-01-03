#include <cv.h>
#include "canny.h"
#include "hough.h"
#include "iostream"
#include "hough_threaded.h"

int main() {
    Mat init = imread("/Users/andreibratu/bachelor/sem5/pdp/project/grey8.jpg", IMREAD_GRAYSCALE);
    Mat img;
    cv::resize(init, img, cv::Size(), 1, 1);
    if (img.empty()) {
        std::cout << "Could not read the image" << std::endl;
        return 1;
    }
    startWindowThread();
    filter gaussian_filter = create_gaussian_filter(3, 3, 1);
    img = apply_gaussian_filter(img, gaussian_filter);
    auto pair = apply_sobel(img);
    img = apply_non_max_suppresion(pair.first, pair.second);
    img = get_binary_canny_image(img, 10, 40);
//    img = hough_transform(img, 180, 200, 750);
    img = hough_transform_threaded(img, 180, 200, 750, 8);
    namedWindow("Lines", WINDOW_AUTOSIZE);
    resizeWindow("Lines", 500, 500);
    imshow("Lines", img);
    waitKey(0);
    destroyAllWindows();
    return 0;
}
