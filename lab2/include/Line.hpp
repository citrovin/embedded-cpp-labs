#ifndef LINE_HPP
#define LINE_HPP

#include "Point.hpp"

template <typename T>
class Line {
public:
    // Constructor with two Point objects as parameters
    Line(Point<T> p1, Point<T> p2);

    // Destructor
    ~Line();

    // Method to calculate the slope of the line
    T slope() const;

    // Method to calculate the y-intercept of the line
    T yIntercept() const;

    // Getters and setters for the two points
    Point<T> getP1() const { return p1; }
    Point<T> getP2() const { return p2; }
    void setP1(Point<T> p) { p1 = p; }
    void setP2(Point<T> p) { p2 = p; }

private:
    // First Point object
    Point<T> p1;

    // Second Point object
    Point<T> p2;
};

// Constructor implementation
template <typename T>
Line<T>::Line(Point<T> p1, Point<T> p2) : p1(p1), p2(p2) {}

// Destructor implementation
template <typename T>
Line<T>::~Line() {}

// slope implementation
template <typename T>
T Line<T>::slope() const {
    return (p2.getY() - p1.getY()) / (p2.getX() - p1.getX());
}

// yIntercept implementation
template <typename T>
T Line<T>::yIntercept() const {
    return p1.getY() - slope() * p1.getX();
}

#endif // LINE_HPP
