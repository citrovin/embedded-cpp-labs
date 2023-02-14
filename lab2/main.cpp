#include <iostream>
#include <vector>
#include "Point.h"
#include "Line.h"
#include "Interpolation.h"

int main() {
    int num_points = 5;
    std::vector<Point<double>> points;

    // Generate 5 random points
    for (int i = 0; i < num_points; i++) {
    points.push_back(Point<double>(rand() % 10, rand() % 10));
    }

    Interpolation<double> interp(points);

    // Interpolate the points
    interp.linear(2);

    // Print the interpolated points between each input point
    interp.printPretty();

    return 0;
}
