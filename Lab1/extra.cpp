#include <iostream>
#include <random>
#include <fstream>

int main() {
    std::mt19937 gen(std::random_device{}());
    std::lognormal_distribution<double> dist(0.3, 0.5);

    std::ofstream file("extra.txt");
    for (int i = 0; i < 100000; ++i) {
        file << dist(gen)*1000 << '\n';
    }
    file.close();

    return 0;
}