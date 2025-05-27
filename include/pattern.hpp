#pragma once

#include <array>
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <random>


template <int N>
class Pattern {
public:
    Pattern(){
        std::generate(data.begin(), data.end(), []() {
            return (rand() % 2 == 0) ? 1 : -1;
        });
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