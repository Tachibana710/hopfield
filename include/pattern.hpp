#pragma once

#include <vector>
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <random>
#include <chrono>
#include <stdexcept>


class Pattern {
public:
    Pattern(int size) : N(size) {
        data.resize(N);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 1);
        for (int i = 0; i < N; ++i) {
            data[i] = (dis(gen) == 0) ? -1 : 1; // -1 or 1
        }
    }

    Pattern(std::vector<int8_t> input_data) : data(input_data), N(input_data.size()) {
        if (data.size() != N) {
            throw std::invalid_argument("Input data size does not match the specified size.");
        }
    }

    double similarity(const Pattern& other) const {
        if (N != other.N) {
            throw std::invalid_argument("Patterns must have the same size for similarity calculation.");
        }
        int dot_product = 0;
        for (int i = 0; i < N; ++i) {
            dot_product += data[i] * other.data[i];
        }
        return static_cast<double>(dot_product) / N;
    }

    std::vector<int8_t> data;
    int N;
};

#include <iostream>

std::ostream& operator<<(std::ostream& os, const Pattern& pattern) {
    for (int i = 0; i < pattern.N; ++i) {
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