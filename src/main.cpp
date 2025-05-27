#include "pattern.hpp"
#include "hopfield.hpp"

#include <iostream>

#define N 10

int main(){
    Pattern<N> p1;
    Pattern<N> p2;

    Hopfield<N> hopfield;
    hopfield.train(p1);
    hopfield.train(p2);

    for (int i = 0; i < 1000; ++i) {
        hopfield.recall(i % N);
        std::cout << "Energy after recall " << i << ": " << hopfield.energy() << std::endl;
    }

    std::cout << "P1: " << hopfield.newrons.similarity(p1) << std::endl;
    std::cout << "P2: " << hopfield.newrons.similarity(p2) << std::endl;

    return 0;
}