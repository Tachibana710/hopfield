#pragma once
#include "pattern.hpp"
#include <tuple>

class Hopfield3D {
public:
    Hopfield3D(int size) : newrons{Pattern(size)}, N(size) {
        if (size <= 0) {
            throw std::invalid_argument("Size must be a positive integer.");
        }
        weights.resize(size, std::vector<std::vector<int>>(size, std::vector<int>(size, 0)));
    }

    void train(const Pattern& pattern) {
        for (int i = 0; i < N; ++i) {
            for (int j = i+1; j < N; ++j) {
                for (int k = j+1; k < N; ++k) {
                    weights[i][j][k] += pattern.data[i] * pattern.data[j] * pattern.data[k];
                }
            }
        }
    }

    void recall(const int idx) {
        int sum = 0;
        for (int j = 0; j < N; ++j) {
            if (j == idx) continue;
            for (int k = j+1; k < N; ++k) {
                if (k == idx) continue;
                int idx1 = idx, idx2 = j, idx3 = k;
                if (idx1 > idx2) std::swap(idx1, idx2);
                if (idx1 > idx3) std::swap(idx1, idx3);
                if (idx2 > idx3) std::swap(idx2, idx3);
                sum += weights[idx1][idx2][idx3] * newrons.data[j] * newrons.data[k];
            }
        }
        if (sum == 0) return;
        newrons.data[idx] = (sum < 0 ? -1 : +1);
    }

    int energy() const {
        int energy = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = i+1; j < N; ++j) {
                for (int k = j+1; k < N; ++k) {
                    energy -= weights[i][j][k] * newrons.data[i] * newrons.data[j] * newrons.data[k];
                }
            }
        }
        return energy;
    }

    void initNewrons(Pattern& pattern) {
        for (int i = 0; i < N; ++i) {
            newrons.data[i] = pattern.data[i];
        }
    }

    Pattern newrons;
    std::vector<std::vector<std::vector<int>>> weights;
    int N;
};