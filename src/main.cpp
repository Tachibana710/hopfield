#include "pattern.hpp"
#include "hopfield.hpp"

#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    int N = std::atoi(argv[1]);
    int PATTERN_NUM = std::atoi(argv[2]);
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

    bool success = false;
    for (const auto& pattern : patterns) {
        double sim = hopfield.newrons.similarity(pattern);
        std::cout << "Similarity: " << sim << std::endl;
        if (sim == 1.0 || sim == -1.0) {
            success = true;
        }
    }

    std::string filename = "log.csv";
    std::ofstream ofs(filename, std::ios::app);
    if (!ofs) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }
    ofs << N << "," << PATTERN_NUM << "," << (success ? 1 : 0) << "\n";

    return 0;
}