#pragma once 

#include "pattern.hpp"


class Hopfield {
public:
    Hopfield(int size) : newrons{Pattern(size)}, N(size) {
        if (size <= 0) {
            throw std::invalid_argument("Size must be a positive integer.");
        }
        weights.resize(size, std::vector<int>(size, 0));
    }

    void train(const Pattern& pattern) {
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

    void initNewrons(const Pattern& pattern) {
        for (int i = 0; i < N; ++i) {
            newrons.data[i] = pattern.data[i];
        }
    }

    Pattern newrons;
    std::vector<std::vector<int>> weights;
    int N;
};