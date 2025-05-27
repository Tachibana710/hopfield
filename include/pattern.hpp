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
private:
    std::array<int8_t, N> data;
};