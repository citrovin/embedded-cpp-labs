#ifndef POINT_H
#define POINT_H

template <typename T>
class Point {
public:
    // Constructor with optional x and y parameters, initialized to T()
    Point(T x = T(), T y = T());

    // Destructor
    ~Point();

    // Getters for x and y
    T getX() const;
    T getY() const;

    // Setters for x and y
    void setX(T x);
    void setY(T y);

    // Overloaded operators for adding, subtracting, multiplying, and dividing points
    Point<T> operator+(const Point<T>& p) const;
    Point<T> operator-(const Point<T>& p) const;
    Point<T> operator*(T s) const;
    Point<T> operator/(T s) const;

    // Print the point as (x,y) on a new line if true, default is false
    void print(bool newline = false) const;

private:
    // x and y coordinates
    T x;
    T y;
};

// Constructor implementation
template <typename T>
Point<T>::Point(T x, T y) : x(x), y(y) {}

// Destructor implementation
template <typename T>
Point<T>::~Point() {}

// getX implementation
template <typename T>
T Point<T>::getX() const {
    return x;
}

// getY implementation
template <typename T>
T Point<T>::getY() const {
    return y;
}

// setX implementation
template <typename T>
void Point<T>::setX(T x) {
    this->x = x;
}

// setY implementation
template <typename T>
void Point<T>::setY(T y) {
    this->y = y;
}

// Overloaded operator+ implementation
template <typename T>
Point<T> Point<T>::operator+(const Point<T>& p) const {
    return Point<T>(x + p.x, y + p.y);
}

// Overloaded operator- implementation
template <typename T>
Point<T> Point<T>::operator-(const Point<T>& p) const {
    return Point<T>(x - p.x, y - p.y);
}

// Overloaded operator* implementation
template <typename T>
Point<T> Point<T>::operator*(T s) const {
    return Point<T>(x * s, y * s);
}

// Overloaded operator/ implementation
template <typename T>
Point<T> Point<T>::operator/(T s) const {
    return Point<T>(x / s, y / s);
}

// Print the point as (x,y) on a new line if true, default is false
template <typename T>
void Point<T>::print(bool newline) const {
    if (newline) {
        std::cout << std::endl;
    }
    std::cout << "(" << x << ", " << y << ")";
}

#endif // POINT_H
