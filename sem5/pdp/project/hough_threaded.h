//
// Created by Andrei Bratu on 03.01.2021.
//

#ifndef PROJECT_HOUGH_THREADED_H
#define PROJECT_HOUGH_THREADED_H

#include "thread_pool.h"
#include "helper.h"

void hough_line_bins_parallel(
        const Mat &image, const vector <std::pair<int, int>> &white_pixels,
        const vector<double> &theta_divisions, const vector<double> &r_divisions, line_to_points_dict &count) {
    for (double theta : theta_divisions) {
        for (double r : r_divisions) {
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
}

Mat hough_transform_threaded(const Mat &input, int theta_divisions, int r_divisions, int minimum_number_pixels,
                             int num_workers) {
    int max_y = input.rows - 1;
    int max_x = input.cols - 1;
    double r_max = euclidean_distance(0, 0, max_x, max_y);
    std::vector<line_to_points_dict> dicts(num_workers);
    auto r_vector = calculate_r_divisions(r_divisions, r_max);
    auto theta_vector = calculate_theta_divisions(theta_divisions);
    auto white_pixels = collect_white_pixels(input);
    auto white_pixels_splits = split_vector(white_pixels, num_workers);
    ThreadPool tp{static_cast<size_t>(num_workers)};
    for (int i = 0; i < num_workers; i++) {
        tp.enqueue([&input, &white_pixels_splits, &dicts, &theta_vector, &r_vector, i]() {
            hough_line_bins_parallel(input, white_pixels_splits[i], theta_vector, r_vector, dicts[i]);
        });
    }
    tp.close();
    auto result = aggregate_dicts(dicts);
    return process_image(result, white_pixels, input, minimum_number_pixels);
}

#endif //PROJECT_HOUGH_THREADED_H
