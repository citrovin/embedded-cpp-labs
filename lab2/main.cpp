#include <iostream>
#include <vector>
#include "Point.hpp"
#include "Line.hpp"
#include "Interpolation.hpp"
#include <cstdlib> // System commands

int main(int argc, char *argv[]) {
    int num_points = 5;
    std::vector<Point<double>> points;

    // Check if the number of points was specified in the command-line
    if (argc > 1) {
        num_points = std::stoi(argv[1]);
    }

    // Generate 5 random points
    for (int i = 0; i < num_points; i++) {
    points.push_back(Point<double>(rand() % 10, rand() % 10));
    }

    Interpolation<double> interp(points);

    // Interpolate the points
    interp.linear(5);

    // Print the interpolated points between each input point
    interp.printPretty();

    // Handle filer errors
    try {
        interp.dumpToFile("interpolation.dat");
        interp.dumpInputsToFile("input.dat");
    } catch (std::exception e) {
        std::cerr << "Files failed to write with error: " << e.what() << std::endl;
    }

    // Handle system errors from python sub-launch
    try {
        std::string command = "python plot_interpolation.py out/input.dat out/interpolation.dat";
        int result = std::system(command.c_str());
        if (result == 0) {
            std::cout << "Script executed successfully." << std::endl;
        } else {
            std::cout << "Script execution failed." << std::endl;
        }
    } catch (std::exception e) {
        std::cerr << "Interpolation visualization failed with error: " << e.what() << std::endl;
    }

    return 0;
}
