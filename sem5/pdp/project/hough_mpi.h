//
// Created by Andrei Bratu on 11.01.2021.
//

#ifndef PROJECT_HOUGH_MPI_H
#define PROJECT_HOUGH_MPI_H

#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/collectives.hpp>
#include <boost/mpi/operations.hpp>
#include "helper.h"

namespace mpi = boost::mpi;

// using line_to_points_dict = std::unordered_map<
// std::pair<double, double>,
// std::unique_ptr<std::vector<std::pair<int, int>>>,
// boost::hash<std::pair<int, int>>
// >;

void send_count_dict(const mpi::communicator &comms, const line_to_points_dict &count) {
    int ok;
    int how_many = count.size();
    comms.send(0, 0, how_many);
    comms.recv(0, 0, ok);
    for(auto& p: count) {
        comms.send(0, 0, p.first.first);
        comms.recv(0, 0, ok);
        comms.send(0, 0, p.first.second);
        comms.recv(0, 0, ok);
        comms.send(0, 0, *p.second);
        comms.recv(0, 0, ok);
    }
}

line_to_points_dict reconstruct_count_dict(const mpi::communicator &comms, int worker) {
    line_to_points_dict dict;
    int how_many;
    double value_one;
    double value_two;
    comms.recv(worker, 0, how_many);
    comms.send(worker, 0, 1);
    std::pair<double, double> key;
    std::vector<std::pair<int, int>> value;
    for(int i = 0; i < how_many; i++) {
        comms.recv(worker, 0, value_one);
        comms.send(worker, 0, 1);
        comms.recv(worker, 0, value_two);
        comms.send(worker, 0, 1);
        key = {value_one, value_two};
        comms.recv(worker, 0, value);
        dict[key] = std::make_unique<std::vector<std::pair<int, int>>>(value);
        comms.send(worker, 0, 1);
    }
    return dict;
}

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

Mat hough_transform_mpi(const mpi::communicator &comm_world,const Mat &input, int theta_divisions, int r_divisions, int minimum_number_pixels) {
    if (comm_world.rank() == 0) {
        int num_workers = comm_world.size() - 1;
        int max_y = input.rows - 1;
        int max_x = input.cols - 1;
        double r_max = euclidean_distance(0, 0, max_x, max_y);
        auto r_vector = calculate_r_divisions(r_divisions, r_max);
        auto theta_vector = calculate_theta_divisions(theta_divisions);
        auto white_pixels = collect_white_pixels(input);
        auto white_pixels_splits = split_vector(white_pixels, num_workers);
        int ok;
        for (int i = 0; i < white_pixels_splits.size(); i++) {
            comm_world.send(i+1, 0, white_pixels_splits[i]);
            comm_world.recv(i+1, 0, ok);
            comm_world.send(i+1, 0, theta_vector);
            comm_world.recv(i+1, 0, ok);
            comm_world.send(i+1, 0, r_vector);
            comm_world.recv(i+1, 0, ok);
        }
        std::vector<line_to_points_dict> dicts(num_workers);
        for (int i = 0; i < white_pixels_splits.size(); i++) {
            dicts[i] = reconstruct_count_dict(comm_world, i + 1);
        }
        auto final_dict = aggregate_dicts(dicts);
        return process_image(final_dict, white_pixels, input, minimum_number_pixels);
    } else {
        Mat image = imread("/Users/andreibratu/bachelor/sem5/pdp/project/grey8.jpg", IMREAD_GRAYSCALE);
        std::vector<std::pair<int, int>> white_pixels;
        std::vector<double> r_vector;
        std::vector<double> theta_vector;
        comm_world.recv(0, 0, white_pixels);
        comm_world.send(0, 0, 0);
        comm_world.recv(0, 0, theta_vector);
        comm_world.send(0, 0, 0);
        comm_world.recv(0, 0, r_vector);
        comm_world.send(0, 0, 0);
        line_to_points_dict count;
        hough_line_bins_parallel(image, white_pixels, theta_vector, r_vector, count);
        send_count_dict(comm_world, count);
        return image; // Dummy return
    }
}

#endif //PROJECT_HOUGH_MPI_H
