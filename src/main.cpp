#include "pattern.hpp"
#include "hopfield.hpp"

#include <iostream>

#define N 500
#define PATTERN_NUM 10

int main(){
    std::vector<Pattern> patterns;
    for (int i = 0; i < PATTERN_NUM; ++i) {
        patterns.push_back(Pattern(N));
    }

    Hopfield hopfield(N);
    for (const auto& pattern : patterns) {
        hopfield.train(pattern);
    }

    int current_energy = 0;
    int stop_count = 0;
    for (int i = 0; i < 10000; ++i) {
        hopfield.recall(i % N);
        int prev_energy = current_energy;
        current_energy = hopfield.energy();

        // 収束判定
        if (current_energy == prev_energy) {
            stop_count++;
        } else {
            stop_count = 0;
        }
        if (stop_count > N) {
            break;
        }

        std::cout << "Energy: " << current_energy << std::endl;
        std::cout << "Newrons: " << std::endl << hopfield.newrons << std::endl;

    }

    for (const auto& pattern : patterns) {
        std::cout << "Similarity: " << hopfield.newrons.similarity(pattern) << std::endl;
    }

    return 0;
}