//
// Created by Andrei Bratu on 26.12.2020.
//

#ifndef PROJECT_HOUGH_H
#define PROJECT_HOUGH_H

#include "unordered_map"
#include "helper.h"

#define WHITE 255
#define BLACK 0

using namespace cv;

line_to_points_dict
hough_line_bins(const Mat &image, const vector<std::pair<int, int>> &white_pixels, int theta_divisions,
                int r_divisions) {
    int max_y = image.rows - 1;
    int max_x = image.cols - 1;
    double r_max = euclidean_distance(0, 0, max_x, max_y);
    auto r_vector = calculate_r_divisions(r_divisions, r_max);
    auto theta_vector = calculate_theta_divisions(theta_divisions);

    line_to_points_dict count;
    for (double theta : theta_vector) {
        for (double r : r_vector) {
            for (auto &p: white_pixels) {
                int y = p.first;
                int x = p.second;
                if (point_on_line(x, y, theta, r)) {
                    std::pair<double, double> key = {theta, r};
                    if (count[key] == nullptr) {
                        count[key] = std::make_unique<std::vector<std::pair<int, int>>>();
                    }
                    count[key]->push_back(p);
                }
            }
        }
    }
    return count;
}

Mat hough_transform(const Mat& input, int theta_divisions, int r_divisions, int minimum_number_pixels) {
    auto white_pixels = collect_white_pixels(input);
    auto count = hough_line_bins(input, white_pixels, theta_divisions, r_divisions);
    std::cout << "COUNT " << count.size() << '\n';
    return process_image(count, white_pixels, input, minimum_number_pixels);
}


#endif //PROJECT_HOUGH_H
