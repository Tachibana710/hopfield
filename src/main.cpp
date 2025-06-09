#include "pattern.hpp"
#include "hopfield.hpp"
#include "hopfield_3d.hpp"

#include <iostream>
#include <fstream>



void run(int N, int PATTERN_NUM, double noise_rate = 0.5) {
    std::vector<Pattern> patterns;
    for (int i = 0; i < PATTERN_NUM; ++i) {
        patterns.push_back(Pattern(N));
    }

    Hopfield3D hopfield(N);
    hopfield.initNewrons(addNoise(patterns[0], noise_rate));
    for (const auto& pattern : patterns) {
        hopfield.train(pattern);
    }

    int current_energy = 0;
    int stop_count = 0;
    while (true) {
        static int i = 0;
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

        i++;
        // std::cout << "Energy: " << current_energy << std::endl;
        // std::cout << hopfield.newrons << std::endl;

    }

    bool success = false;
    for (const auto& pattern : patterns) {
        double sim = hopfield.newrons.similarity(pattern);
        // std::cout << "Similarity: " << sim << std::endl;
        if (sim == 1.0 || sim == -1.0) {
            success = true;
        }
    }

    std::string filename = "log.csv";
    std::ofstream ofs(filename, std::ios::app);
    if (!ofs) {
        std::cerr << "Error opening file: " << filename << std::endl;
    }
    ofs << N << "," << PATTERN_NUM << "," << (success ? 1 : 0) << "\n";
    ofs.close();
}

int main(int argc, char* argv[]){
    int N = std::atoi(argv[1]);
    int PATTERN_NUM = std::atoi(argv[2]);
    int TEST_NUM = std::atoi(argv[3]);
    double noise_rate = std::atof(argv[4]);
    for (int i = 0; i < TEST_NUM; ++i) {
        run(N, PATTERN_NUM, noise_rate);
    }
}