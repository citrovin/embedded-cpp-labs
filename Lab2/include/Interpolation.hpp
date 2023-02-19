#ifndef INTERPOLATION_HPP
#define INTERPOLATION_HPP

#include "Point.hpp"
#include "Line.hpp"
#include <filesystem>
#include <fstream>
#include <vector>
#include <Eigen/Dense>

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

    // Method to clear the currently interpolated points
    void clearInterpolatedPoints();

    // Spline interpolation method (cubic).
    void spline(int n);

    // Sort input points
    void sort();

private:
    // Array of input Point objects
    std::vector<Point<T>> points;
    // Backup of the unsorted input Points
    std::vector<Point<T>> backup_points;
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
    // Iterate through all points
    for (int i = 0; i < points.size(); i++) {
        // Resize the interpolated_points matrix so we don't get a segmentation fault
        Interpolation<T>::interpolated_points.resize(Interpolation<T>::interpolated_points.size() + 1, std::vector<Point<T>>(0));

        // Instantiate the line made by point i and i+1
        Line<T> line(Interpolation<T>::points[i], Interpolation<T>::points[i+1]);

        // Get the slope and y-intercept for the line made by point i and i+1 so we can determine the Y coordinate
        T slope = line.slope();
        T yIntercept = line.yIntercept();

        // Get x1 and x2
        T x1 = line.getP1().getX();
        T x2 = line.getP2().getX();

        // Calculate increment to get n number of points between x of point i and x of point i+1
        auto increment = (x2 - x1)/(n+1);

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
            auto increment = (y2 - y1)/(n+1);

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

// Spline interpolation unoptimized algorithm with n samples
template <typename T>
void Interpolation<T>::spline(int n) {
    // Clear our current points before interpolating again
    Interpolation<T>::clearInterpolatedPoints();

    // Sort our input points
    Interpolation<T>::sort();
    
    // Define the size of the input array
    int nr_input_points = Interpolation<T>::points.size();

    // Cycle through input points
    for (int i = 0; i < nr_input_points; i++) {
        // Resize the interpolated_points matrix so we don't get a segmentation fault
        Interpolation<T>::interpolated_points.resize(Interpolation<T>::interpolated_points.size() + 2, std::vector<Point<T>>(0));

        // Get x1, x2, y1, and y2 for notation convenience
        T x1 = Interpolation<T>::points[i].getX();
        T x2 = Interpolation<T>::points[i+1].getX();
        T x3 = Interpolation<T>::points[i+2].getX();
        T y1 = Interpolation<T>::points[i].getY();
        T y2 = Interpolation<T>::points[i+1].getY();
        T y3 = Interpolation<T>::points[i+2].getY();

        // Define tridimensional matrix
        Eigen::Matrix3d A;

        double dx21 = x2 - x1;
        double dx32 = x3 - x2;

        double dy21 = y2-y1;
        double dy32 = y3-y2;

        double a11 = 2/dx21;
        double a12 = 1/dx21;
        double a21 = 1/dx21;
        double a22 = 2*((1/dx21)+(1/dx32));
        double a23 = 1/dx32;
        double a32 = 1/dx32;
        double a33 = 2/dx32;

        double _b1 = 3*(dy21/pow(dx21,2));
        double _b2 = 3*((dy21/pow(dx21,2))+(dy32/pow(dx32,2)));
        double _b3 = 3*(dy32/pow(dx32,2));

        Eigen::Vector3d B(_b1,_b2,_b3);

        A << a11, a12, 0,
            a21, a22, a23,
            0, a32, a33;

        Eigen::VectorXd K = A.colPivHouseholderQr().solve(B);

        auto k1 = K(0);
        auto k2 = K(1);
        auto k3 = K(2);

        auto a1 = (k1*(dx21))-dy21;
        auto b1 = ((-k2)*(dx21))+dy21;
        auto a2 = ((k2*dx32)-dy32);
        auto b2 = (((-k3)*dx32)+dy32);



        for (int j = 0; j < n; j++) {
            auto new_x1 = x1 + ((x2-x1)/(n))*j;
            // auto new_x2 = x2 + ((x3-x2)/(n+1))*j;

            // Compute t(x)
            auto t = (new_x1 - x1)/(x2 - x1);
            // auto t_2 = (new_x2 - x2)/(x3 - x2);

            // Compute y = q(x)
            auto new_y1 = (1-t)*y1 + t*y2 + t*(1-t)*((1-t)*a1 + t*b1);
            // auto new_y2 = (1-t_2)*y2 + t_2*y3 + t_2*(1-t_2)*((1-t_2)*a2 + t_2*b2);

            // Define a new point
            Point<T> point1(new_x1, new_y1);

            // Add the new point to our interpolation
            Interpolation<T>::interpolated_points[i].push_back(point1);
        }
    }
}

template <typename T>
void Interpolation<T>::clearInterpolatedPoints() {
    Interpolation<T>::interpolated_points.clear();
}

template <typename T>
void Interpolation<T>::sort() {
    // Save our initial input points if we need them later
    backup_points = points;

    // Define a lambda to compare x
    auto comparePoints = [](const Point<T>& a, const Point<T>& b) { return a.getX() < b.getX(); };

    // Sort the points ascending
    std::sort(points.begin(), points.end(), comparePoints);
}


#endif // INTERPOLATION_HPP