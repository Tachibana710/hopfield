#include "pattern.hpp"
#include "hopfield.hpp"
#include "hopfield_3d.hpp"

#include <iostream>
#include <fstream>



void run(int N, int PATTERN_NUM, double noise_rate = 0.5) {
    std::vector<Pattern> patterns;
    for (int i = 0; i < PATTERN_NUM; ++i) {
        patterns.push_back(Pattern(N));
        // std::cout << "Pattern " << i << ": " << patterns[i] << std::endl;
    }

    Hopfield3D hopfield(N);
    auto init = addNoise(patterns[0], noise_rate);
    // std::cout << "Initial noisy pattern: " << init << std::endl;
    hopfield.initNewrons(init);
    for (const auto& pattern : patterns) {
        hopfield.train(pattern);
    }

    int current_energy = 0;
    int stop_count = 0;
    double mean_similarity = 0.0;
    int i = 0;
    while (true) {
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
        mean_similarity += hopfield.newrons.similarity(patterns[0]);
        i++;
        // std::cout << "Energy: " << current_energy << std::endl;
        // std::cout << hopfield.newrons << std::endl;

    }
    mean_similarity /= i;

    bool success = false;
    // for (const auto& pattern : patterns) {
    //     double sim = hopfield.newrons.similarity(pattern);
    //     // std::cout << "Similarity: " << sim << std::endl;
    //     if (sim == 1.0 || sim == -1.0) {
    //         success = true;
    //     }
    // }
    if (hopfield.newrons.similarity(patterns[0]) == 1.0 || hopfield.newrons.similarity(patterns[0]) == -1.0) {
        success = true;
    }

    std::string filename = "log.csv";
    std::ofstream ofs(filename, std::ios::app);
    if (!ofs) {
        std::cerr << "Error opening file: " << filename << std::endl;
    }
    ofs << N << "," << PATTERN_NUM << "," << (success ? 1 : 0) << "," << mean_similarity << "," << noise_rate << "\n";
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

// int main(){

//     double attractor_num_2d, attractor_num_3d;    
    
//     constexpr size_t N = 25; // 5x5 grid
//     constexpr size_t total = 1ULL << N; // 2^N
//     Hopfield hopfield(N);
//     Hopfield3D hopfield3d(N);
//     for (int i =0; i < 50; ++i) {
//         Pattern p(N);
//         hopfield.train(p);
//         hopfield3d.train(p);
//     }
//     for (size_t i = 0; i < total; ++i) {
//         std::cout << i << " / " << total << ", " << (i * 100.0 / total) << "%\r";
//         std::vector<int8_t> data(N);
//         for (size_t j = 0; j < N; ++j) {
//             data[j] = (i & (1ULL << j)) ? 1 : -1;
//         }
//         Pattern pattern(data);
//         hopfield.initNewrons(pattern);
//         bool is_attractor = true;
//         for (size_t j = 0; j < N; ++j) {
//             hopfield.recall(j);
//             if (hopfield.newrons.data[j] != pattern.data[j]) {
//                 is_attractor = false;
//                 break;
//             }
//         }
//         if (is_attractor) {
//             attractor_num_2d++;
//         }
//         hopfield3d.initNewrons(pattern);
//         is_attractor = true;
//         for (size_t j = 0; j < N; ++j) {
//             hopfield3d.recall(j);
//             if (hopfield3d.newrons.data[j] != pattern.data[j]) {
//                 is_attractor = false;
//                 break;
//             }
//         }
//         if (is_attractor) {
//             attractor_num_3d++;
//         }
//     }
//     std::cout << std::endl;
//     std::cout << std::endl;
   
//     std::cout << "2D Attractor Count: " << attractor_num_2d << std::endl;
//     std::cout << "3D Attractor Count: " << attractor_num_3d << std::endl;
// }