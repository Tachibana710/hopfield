#pragma once 

#include "pattern.hpp"


template <int N>
class Hopfield {
public:
    Hopfield() : weights{}, newrons{} {}

    void train(const Pattern<N>& pattern) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (i != j) {
                    weights[i][j] += pattern.data[i] * pattern.data[j];
                }
            }
        }
    }

    void recall(const int idx){
        int sum = 0;
        for (int i = 0; i < N; ++i) {
            if (i != idx) {
                sum += weights[idx][i] * newrons.data[i];
            }
        }
        newrons.data[idx] = (sum >= 0) ? 1 : -1;
    }

    int energy() const {
        int energy = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (i != j) {
                    energy -= weights[i][j] * newrons.data[i] * newrons.data[j] / 2.0;
                }
            }
        }
        return energy;
    }

    void initNewrons(const Pattern<N>& pattern) {
        for (int i = 0; i < N; ++i) {
            newrons.data[i] = pattern.data[i];
        }
    }

    Pattern<N> newrons;
    std::array<std::array<int8_t, N>, N> weights;
};