#pragma once
#include "pattern.hpp"

class weight_element {
public:
    int get_weight(int val_j_arg, int val_k_arg) const {
        if (val_j_arg == 1 && val_k_arg == 1) {
            return w_tt;
        } else if (val_j_arg == 1 && val_k_arg == -1) {
            return w_tf;
        } else if (val_j_arg == -1 && val_k_arg == 1) {
            return w_ft;
        } else if (val_j_arg == -1 && val_k_arg == -1) {
            return w_ff;
        } else {
            throw std::invalid_argument("Invalid values for j and k. Must be either 1 or -1.");
        }
    }

    void add_weight(int val_i_arg, int val_j_arg, int val_k_arg) {
        if (val_j_arg == 1 && val_k_arg == 1) {
            w_tt += val_i_arg;
        } else if (val_j_arg == 1 && val_k_arg == -1) {
            w_tf += val_i_arg;
        } else if (val_j_arg == -1 && val_k_arg == 1) {
            w_ft += val_i_arg;
        } else if (val_j_arg == -1 && val_k_arg == -1) {
            w_ff += val_i_arg;
        } else {
            throw std::invalid_argument("Invalid values for j and k. Must be either 1 or -1.");
        }
    }

    weight_element() :  w_ff(0), w_ft(0), w_tf(0), w_tt(0) {}

    int w_ff;
    int w_ft;
    int w_tf;
    int w_tt;
};

class Hopfield3D {
public:
    Hopfield3D(int size) : newrons{Pattern(size)}, N(size) {
        if (size <= 0) {
            throw std::invalid_argument("Size must be a positive integer.");
        }
        weights.resize(size, std::vector<std::vector<weight_element>>(size, std::vector<weight_element>(size, weight_element())));
    }

    void train(const Pattern& pattern) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < i; ++j) {
                for (int k = 0; k < j; ++k) {
                    if (i != j && j != k && i != k) {
                        weights[i][j][k].add_weight(pattern.data[i], pattern.data[j], pattern.data[k]);
                        weights[i][k][j].add_weight(pattern.data[i], pattern.data[k], pattern.data[j]);
                        weights[j][i][k].add_weight(pattern.data[j], pattern.data[i], pattern.data[k]);
                        weights[j][k][i].add_weight(pattern.data[j], pattern.data[k], pattern.data[i]);
                        weights[k][i][j].add_weight(pattern.data[k], pattern.data[i], pattern.data[j]);
                        weights[k][j][i].add_weight(pattern.data[k], pattern.data[j], pattern.data[i]);
                    }
                }
            }
        }
    }

    void recall(const int idx) {
        int sum = 0;
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                if (j != idx && k != idx && j != k) {
                    sum += weights[idx][j][k].get_weight(newrons.data[j], newrons.data[k]);
                }
            }
        }
        if (sum == 0) {
            return;
        } else if (sum < 0) {
            newrons.data[idx] = -1;
        } else {
            newrons.data[idx] = 1;
        }
    }

    int energy() const {
        int energy = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                for (int k = 0; k < N; ++k) {
                    if (i != j && j != k && i != k) {
                        energy -= weights[i][j][k].get_weight(newrons.data[j], newrons.data[k]) * newrons.data[i];
                        energy -= weights[i][k][j].get_weight(newrons.data[k], newrons.data[j]) * newrons.data[i];
                        energy -= weights[j][i][k].get_weight(newrons.data[i], newrons.data[k]) * newrons.data[j];
                        energy -= weights[j][k][i].get_weight(newrons.data[k], newrons.data[i]) * newrons.data[j];
                        energy -= weights[k][i][j].get_weight(newrons.data[i], newrons.data[j]) * newrons.data[k];
                        energy -= weights[k][j][i].get_weight(newrons.data[j], newrons.data[i]) * newrons.data[k];
                    }
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
    std::vector<std::vector<std::vector<weight_element>>> weights;
    int N;
};