//
// Created by Andrei Bratu on 03.01.2021.
//

#ifndef PROJECT_HELPER_H
#define PROJECT_HELPER_H

#include <boost/functional/hash.hpp>

using line_to_points_dict = std::unordered_map<std::pair<double, double>, std::unique_ptr<std::vector<std::pair<int, int>>>, boost::hash<std::pair<int, int>>>;

inline double euclidean_distance(int x_one, int y_one, int x_two, int y_two) {
    double v_one_d = x_one - x_two;
    double v_two_d = y_one - y_two;
    return std::sqrt(v_one_d * v_one_d + v_two_d * v_two_d);
}

inline bool point_on_line(int x, int y, double theta, double r) {
    double accepted_region = std::abs(x * std::cos(theta) + y * std::sin(theta) - r);
    return accepted_region < 1.75;
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
    for (int i = 0; i <= count; i++) {
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

Mat process_image(const line_to_points_dict &dict, const std::vector<std::pair<int, int>> &white_pixels,
                  const Mat &original_image, int minimum_number_pixels) {
    RNG rng(42);
    Mat result(original_image.rows, original_image.cols, CV_8UC3, Scalar(0, 0, 0));
    for (auto &p: white_pixels) {
        auto &rgb_pixel = result.at<Vec3b>(p.first, p.second);
        rgb_pixel[0] = 255;
        rgb_pixel[1] = 255;
        rgb_pixel[2] = 255;
    }
    for (auto &line_points: dict) {
        if (line_points.second->size() < minimum_number_pixels) continue;
        // Generate random pixel color
        int random_color_r = rng.uniform(0, 255);
        int random_color_g = rng.uniform(0, 255);
        int random_color_b = rng.uniform(0, 255);
        // Set all pixels belonging to line to this color
        for (auto &p: (*line_points.second)) {
            auto &rgb_pixel = result.at<Vec3b>(p.first, p.second);
            rgb_pixel[0] = random_color_r;
            rgb_pixel[1] = random_color_g;
            rgb_pixel[2] = random_color_b;
        }
    }
    return result;
}

template<class T>
std::vector<std::vector<T>> split_vector(std::vector<T> &vec, int parts) {
    int part_size = vec.size() / parts;
    std::vector<std::vector<T>> result(parts);
    int i = 0;
    for (int p = 0; p < parts; p++) {
        int start_i = i;
        for (; i < start_i + part_size; i++) {
            result[p].push_back(vec[i]);
        }
    }
    int remainder_idx = 0;
    while (i < vec.size()) {
        result[remainder_idx].push_back(vec[i]);
        i++;
        remainder_idx++;
    }
    return result;
}

line_to_points_dict aggregate_dicts(const std::vector<line_to_points_dict> &dicts) {
    line_to_points_dict aggregate;
    for (auto &dict : dicts) {
        for (auto &kv_pair : dict) {
            if (aggregate.find(kv_pair.first) == aggregate.end())
                aggregate[kv_pair.first] = std::make_unique<std::vector<std::pair<int, int>>>(*kv_pair.second);
            else {
                for(auto &v : *kv_pair.second) {
                    aggregate[kv_pair.first]->push_back(v);
                }
            }
        }
    }
    return aggregate;
}

#endif //PROJECT_HELPER_H
