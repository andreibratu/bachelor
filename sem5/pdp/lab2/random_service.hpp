//
// Created by bratu on 10/20/2020.
//

#include <type_traits>
#include <random>

// A function to return a seeded random number generator.
inline std::mt19937& generator() {
    // the generator will only be seeded once (per thread) since it's static
    static thread_local std::mt19937 gen(std::random_device{}());
    return gen;
}

// A function to generate floats in the range [min, max)
template<typename T, std::enable_if_t<std::is_floating_point_v<T>>* = nullptr>
T my_rand(T min, T max) {
    std::uniform_real_distribution<T> dist(min, max);
    return dist(generator());
}
