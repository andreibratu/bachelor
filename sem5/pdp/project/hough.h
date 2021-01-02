//
// Created by Andrei Bratu on 26.12.2020.
//

#ifndef PROJECT_HOUGH_H
#define PROJECT_HOUGH_H

#include "unordered_map"
#include <boost/functional/hash.hpp>

#define WHITE 255
#define BLACK 0

using namespace cv;
using line_to_points_dict = std::unordered_map<std::pair<double, double>, std::unique_ptr<std::vector<std::pair<int, int>>>, boost::hash<std::pair<int, int>>>;

inline double euclidean_distance(int x_one, int y_one, int x_two, int y_two) {
    double v_one_d = x_one - x_two;
    double v_two_d = y_one - y_two;
    return std::sqrt(v_one_d * v_one_d + v_two_d * v_two_d);
}

inline bool point_on_line(int x, int y, double theta, double r) {
    double accepted_region = std::abs(x * std::cos(theta) + y * std::sin(theta) - r);
    return accepted_region < 1.7;
}

std::vector<double> calculate_theta_divisions(int count) {
    std::vector<double> thetas;
    thetas.reserve(count);
    double theta_gradient = 2 * M_PI / count;
    for (int i = 0; i <= count; i++) {
        thetas.push_back(theta_gradient * i);
    }
    return thetas;
}

std::vector<double> calculate_r_divisions(double count, double r_max) {
    double r_gradient = r_max / count;
    std::vector<double> rs;
    rs.reserve(count + 1);
    for(int i = 0; i <= count; i++) {
        rs.push_back(r_gradient * i);
    }
    return rs;
}

std::vector<std::pair<int, int>> collect_white_pixels(const Mat &image) {
    std::vector<std::pair<int, int>> collector;
    collector.reserve(image.rows * image.cols);
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            if (image.at<uchar>(i, j) == WHITE) {
                collector.emplace_back(i, j);
            }
        }
    }
    return collector;
}

line_to_points_dict
hough_line_bins(const Mat &image, const vector<std::pair<int, int>> &white_pixels, int theta_divisions,
                int r_divisions) {
    int max_y = image.rows - 1;
    int max_x = image.cols - 1;
    double r_max = euclidean_distance(0, 0, max_x, max_y);
    auto r_vector = calculate_r_divisions(r_divisions, r_max);
    auto theta_vector = calculate_theta_divisions(theta_divisions);

    line_to_points_dict count;
    for (int theta_idx = 0; theta_idx < theta_vector.size(); theta_idx++) {
        for (int r_idx = 0; r_idx <= r_vector.size(); r_idx++) {
            for (auto &p: white_pixels) {
                int y = p.first;
                int x = p.second;
                // Add a border region
                double theta = theta_vector[theta_idx];
                double r = r_vector[r_idx];
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

Mat process_image(const line_to_points_dict &dict, const std::vector<std::pair<int, int>> &white_pixels,
                  const Mat &original_image, int minimum_number_pixels) {
    RNG rng(42);
    Mat result(original_image.rows, original_image.cols, CV_8UC3, Scalar(0, 0, 0));
    for(auto &p: white_pixels) {
        auto &rgb_pixel = result.at<Vec3b>(p.first, p.second);
        rgb_pixel[0] = 255;
        rgb_pixel[1] = 255;
        rgb_pixel[2] = 255;
    }
    for(auto &line_points: dict) {
        if (line_points.second->size() < minimum_number_pixels) continue;
        // Generate random pixel color
        int random_color_r = rng.uniform(0, 255);
        int random_color_g = rng.uniform(0, 255);
        int random_color_b = rng.uniform(0, 255);
        // Set all pixels belonging to line to this color
        for(auto& p: (*line_points.second)) {
            auto &rgb_pixel = result.at<Vec3b>(p.first, p.second);
            rgb_pixel[0] = random_color_r;
            rgb_pixel[1] = random_color_g;
            rgb_pixel[2] = random_color_b;
        }
    }
    return result;
}

Mat hough_transform(const Mat& input, int theta_divisions, int r_divisions, int minimum_number_pixels) {
    auto white_pixels = collect_white_pixels(input);
    auto count = hough_line_bins(input, white_pixels, theta_divisions, r_divisions);
    return process_image(count, white_pixels, input, minimum_number_pixels);
}


#endif //PROJECT_HOUGH_H
