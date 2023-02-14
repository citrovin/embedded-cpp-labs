#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include "Point.h"
#include "Line.h"
#include <filesystem>
#include <fstream>
#include <vector>
template <typename T>
class Interpolation {
public:
    // Constructor with a vector of Point objects
    Interpolation(std::vector<Point<T>> points);

    // Destructor
    ~Interpolation();

    // Get input points for the interpolation
    std::vector<Point<T>> getInputPoints() const {
        return this->points;
    }

    // Set the input points for the interpolation and recompute
    void setPoints(std::vector<Point<T>> points) {
        this->interpolated_points.clear();
        this->points = points;
    }

    // Get the resulting matrix of points from the interpolation
    std::vector<std::vector<Point<T>>> getInterpolatedPoints() const {
        return interpolated_points;
    }

    // Linear interpolation method with n samples. Call getInterPolatedPoints() to receive the output
    void linear(int n);

    // Print each point in the interpolation as (x,y), on a newline if passed true, default is false
    void printInterpolatedPoints(bool newLine = false) const;

    // Print each point in the interpolation as (x,y) between point p1 and point p2, but nicely
    void printPretty() const;

    // Method to write the input points and interpolated points to a file
    void dumpToFile(const std::string file_name);

    // Method to write only the input points to a file
    void dumpInputsToFile(const std::string file_name);

private:
    // Array of input Point objects
    std::vector<Point<T>> points;
    // Matrix of interpolated Point objects
    std::vector<std::vector<Point<T>>> interpolated_points;
};

// Constructor implementation
template <typename T>
Interpolation<T>::Interpolation(std::vector<Point<T>> points) : points(points) {}

// Destructor implementation
template <typename T>
Interpolation<T>::~Interpolation() {}

// Linear interpolation with n samples
template <typename T>
void Interpolation<T>::linear(int n) {
    // Iterate through all points (cannot be avoided)
    for (int i = 0; i < Interpolation<T>::points.size(); i++) {
        // Resize the interpolated_points matrix so we don't get a segmentation fault
        interpolated_points.resize(interpolated_points.size() + 1);

        // Instantiate the line made by point i and i+1
        Line<T> line(Interpolation<T>::points[i], Interpolation<T>::points[i+1]);

        // Get the slope and y-intercept for the line made by point i and i+1 so we can determine the Y coordinate
        T slope = line.slope();
        T yIntercept = line.yIntercept();

        // Get x1 and x2
        T x1 = line.getP1().getX();
        T x2 = line.getP2().getX();

        // Calculate increment to get n number of points between x of point i and x of point i+1
        auto increment = (-x1 + x2)/(n+1);

        // Check if increment is != 0, otherwise we have a vertical line and we need to assign points vertically
        // TODO: This if - else is messy, can be improved
        if (increment != 0) {
            // Compute each point and store it in vector
            for (int j = 1; j <= n; j++) {
                // Compute new x coordinate for interpolated point
                auto new_x = x1 + j*increment;

                // Compute new y coordinate for interpolated point and store it in the vector
                Point<T> point(new_x, yIntercept + slope*new_x);
                Interpolation<T>::interpolated_points[i].push_back(point);
            }
        } else {
            // Get y1 and y2
            T y1 = line.getP1().getY();
            T y2 = line.getP2().getY();

            // Calculate increment to get n number of points between y of point i and y of point i+1
            auto increment = (-y1 + y2)/(n+1);

            // Compute each point and store it in vector
            for (int j = 1; j <= n; j++) {
                // Compute new y coordinate for interpolated point
                auto new_y = y1 + j*increment;

                // Compute new y coordinate for interpolated point and store it in the vector
                Point<T> point((new_y - yIntercept)/slope, new_y);
                Interpolation<T>::interpolated_points[i].push_back(point);
            }
        }
    }
}

// Print each point in the interpolation as (x,y), on a newline if passed True
template<typename T>
void Interpolation<T>::printInterpolatedPoints(bool newLine) const {
    for (const auto& row : interpolated_points) {
        for (const auto& point : row) {
            point.print(newLine);
        }
        if (newLine) {
            std::cout << std::endl;
        }
    }
}

// Print each point in the interpolation as (x,y) between point p1 and point p2
template <typename T>
void Interpolation<T>::printPretty() const {
    for (unsigned int i = 0; i < interpolated_points.size() - 1; i++) {
        std::cout << "Interpolated points between point ";
        points[i].print();
        std::cout << " and ";
        points[i+1].print();
        std::cout << ":" << std::endl;
        for (const Point<T> &point : interpolated_points[i]) {
            point.print();
        }
        std::cout << std::endl;
    }
}

// Method to write the input points and interpolated points to a file
template <typename T>
void Interpolation<T>::dumpToFile(const std::string file_name) {
    if (!std::filesystem::exists("out")) {
        std::filesystem::create_directory("out");
    }
    std::ofstream file("out/" + file_name);

    // Loop through all the points in the vector except the last one
    for (int i = 0; i < Interpolation<T>::points.size() - 1; i++) {
        // Get the current point
        const Point<T>& point1 = Interpolation<T>::points[i];

        // Write the current point to the file
        file << point1.getX() << "," << point1.getY() << std::endl;

        // Loop through all the interpolated points
        for (const auto& interpolated_point : Interpolation<T>::interpolated_points[i]) {
            // Write the interpolated point to the file
            file << interpolated_point.getX() << "," << interpolated_point.getY() << std::endl;
        }
    }

    // Get the last point in the vector
    const Point<T>& last_point = Interpolation<T>::points.back();

    // Write the last point to the file
    file << last_point.getX() << "," << last_point.getY() << std::endl;

    // Close the output file stream
    file.close();
}





// Method to write only the input points to a file
template <typename T>
void Interpolation<T>::dumpInputsToFile(const std::string file_name) {
    if (!std::filesystem::exists("out")) {
        std::filesystem::create_directory("out");
    }
    std::ofstream file("out/" + file_name);
    for (const auto& input_point : Interpolation<T>::points) {
        file << input_point.getX() << "," << input_point.getY() << std::endl;
    }
    file.close();
}


#endif // INTERPOLATION_H