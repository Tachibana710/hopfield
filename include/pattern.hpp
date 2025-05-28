#pragma once

#include <array>
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <random>
#include <chrono>
#include <stdexcept>


template <int N>
class Pattern {
public:
    Pattern(){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 1);
        for (int i = 0; i < N; ++i) {
            data[i] = (dis(gen) == 0) ? -1 : 1; // -1 or 1
        }
    }

    Pattern(std::array<int8_t, N>& arr) : data(arr) {}

    double similarity(const Pattern<N>& other) const {
        int dot_product = 0;
        for (int i = 0; i < N; ++i) {
            dot_product += data[i] * other.data[i];
        }
        return static_cast<double>(dot_product) / N;
    }

    std::array<int8_t, N> data;
};

#include <iostream>

template <int N>
std::ostream& operator<<(std::ostream& os, const Pattern<N>& pattern) {
    for (int i = 0; i < N; ++i) {
        if (pattern.data[i] == 1) {
            os << "■ ";
        } else {
            os << "□ ";
        }
        if ((i + 1) % 20 == 0) { // 改行
            os << std::endl;
        }
    }
    return os;
}