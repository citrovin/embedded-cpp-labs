#include <iostream>
#include <vector>
#include <string>
#include "include/Point.hpp"
#include "include/Line.hpp"
#include "include/Interpolation.hpp"
// System commands
#include <cstdlib>
// Command line arguments parsing
#include "include/program_options.h"
#include "include/program_options.cpp"
// For some utils to unclutter my main files
#include "include/utils.hpp"

int main(int argc, char *argv[]) {

    // // Generate 5 random numbers if unspecified
    // program_options::num_points = 5;
    // // Set samples to 3 if unspecified
    // program_options::samples = 3;

    // Vector to store the points
    std::vector<Point<double>> points;

    // Parse arg list
    try {
        program_options::parse(argc, argv);
    } catch (const std::exception &x) {
        std::cerr << x.what() << '\n';
        std::cerr << "usage: [-n] [-s] <input_file> ...\n";
        return EXIT_FAILURE;
    }

    // Parse input files from arg list
    for (const auto &file_name : program_options::input_files()) {
        std::ifstream input_file(file_name.data(), std::ios::in);
        if (!input_file.is_open()) {
            std::cerr << "Could not open input file '" << file_name << "'!\n";
            return EXIT_FAILURE;
        }

        std::string line;
        int         line_count = 1;
        while (std::getline(input_file, line)) {
            if (program_options::show_line_numbers()) {
                std::cout << std::setw(6) << std::setfill(' ') << line_count++ << "  ";
            }

            if (program_options::show_ends()) {
                std::cout << '$';
            }

            std::cout << '\n';
        }
    }

    if ( program_options::num_points != -1) {
        // Generate n random points
        for (int i = 0; i < program_options::num_points; i++) {
            points.push_back(Point<double>(rand() % 10, rand() % 10));
        }
    } else {
        const auto input_files = program_options::input_files();
        
        if(!input_files.empty()) {
            // for (const auto& file : input_files) {
            //     points = readPointsVectorFromFile(file);
            // }

            // for (auto it = input_files.begin(); it != input_files.end(); ++it) {
            //     points = readPointsVectorFromFile(*it);
            // }
            for (const auto& file_path : input_files){
                try {
                    // std::string file_path = "data/input.dat";
                    points = readPointsVectorFromFile<double>(file_path);
                } catch (const std::exception& e) {
                    std::cerr << e.what() << std::endl;
                    return 1;
                }
            }
        }
    }

    // Create interpolation object
    Interpolation<double> interp(points);

    if (program_options::method == "linear") {
        // Interpolate the points with s samples
        interp.linear(program_options::samples);
    } else if (program_options::method == "spline") {
        interp.spline(program_options::samples);
    } else {
        std::cerr << "\nNo such method as " << program_options::method;
    }
    // Print the interpolated points between each input point
    interp.printPretty();

    // Handle file errors
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
