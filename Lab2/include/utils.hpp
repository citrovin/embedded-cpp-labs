#ifndef XHRS_UTILS_HPP
#define XHRS_UTILS_HPP

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Point.hpp"

template <typename T>
std::vector<Point<T>> readPointsVectorFromFile(const std::string& file_path) {
    std::vector<Point<T>> pointz;

    std::ifstream file(file_path);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream line_stream(line);
            T x, y;
            char delimiter;
            line_stream >> x >> delimiter >> y;
            pointz.emplace_back(Point<T>(x, y));
        }
        file.close();
    } else {
        throw std::runtime_error("Unable to open file: " + file_path);
    }

    return pointz;
}


#endif