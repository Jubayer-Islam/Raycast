
#include "Vector3.hpp"
#include <cmath>
#include <iostream>
#include<fstream>

using namespace std;

//This implementation assumes you want a simple 3D vector class for use in computations like ray tracing,
 //and provides basic vector operations like addition, subtraction, dot/cross product, normalization, etc.


//These first two constructors below initializes a vector either with default values (0, 0, 0) or
 //with specific values provided for x, y, and z.

// Default constructor (initializes vector to (0, 0, 0))
vec3::vec3() {
    vec3{0,0,0};
}


// Constructor with given x, y, z values
vec3::vec3(double x, double y, double z) {
    elements[0] = x;
    elements[1] = y;
    elements[2] = z;
    //elements[3] = 1; we could give this vector more elements if we needed
}


// Accessor functions for x, y, z components
double vec3::x() const {
    return elements[0];
}

double vec3::y() const {
    return elements[1];
}
double vec3::z() const {
    return elements[2];
}


//// Unary negation (flips sign of each component)
// " operator - () " is the highlight of this function
// meaning operator - is used but no argument can be sent along with it

vec3 vec3::operator-() const {
    return vec3(-elements[0], -elements[1], -elements[2]);
}

//// return the i-th element of the elements vector
// Access the i-th component (const version)
// " operator [] (int i) " is the highlight of this function
// meaning operator [] is used along with a sent argument of int type

double vec3::operator[](int i) const {
    return elements[i];
}

// Access the i-th component (non-const version)
double& vec3::operator[](int i) {
    return elements[i];
}

//// Addition assignment operator (adds components of another vector to the current vector)
// example: vec3{1,2,3}+=vec3{5,5,5} will return vec3{6,7,8}

vec3& vec3::operator+=(const vec3& v) {
    elements[0] += v.elements[0];
    elements[1] += v.elements[1];
    elements[2] += v.elements[2];
    return *this;
}


// Scalar multiplication assignment (to multiply current vector by a scalar)
vec3& vec3::operator*=(double t) {
    elements[0] *= t;
    elements[1] *= t;
    elements[2] *= t;
    return *this;
    //this is a pointer to the current object( which stays on the left side of +=)
    //*this dereferences that pointer, giving the object itself.
}

// Scalar division assignment (to divide current vector by a scalar), scales the vector
vec3& vec3::operator/=(double t) {
    elements[0] /= t;
    elements[1] /= t;
    elements[2] /= t;
    return *this;
}

// Returns the length of the vector  (magnitude)
double vec3::length() const {
    return sqrt((elements[0] * elements[0]) + (elements[1] * elements[1]) + (elements[2] * elements[2]));
    //return std::sqrt(length_squared());
}

// Return the length but squared
double vec3::length_squared() const {
    return (elements[0] * elements[0] + elements[1] * elements[1] + elements[2] * elements[2]);
}

// Stream output operator to print the vector components
std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.elements[0] << ' ' << v.elements[1] << ' ' << v.elements[2];
}


// Vector addition (component-wise)
vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.elements[0] + v.elements[0], u.elements[1] + v.elements[1], u.elements[2] + v.elements[2]);
    //return vec3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z()); //also works but not entirely accurate syntax
}


// Vector subtraction (component-wise)
vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.elements[0] - v.elements[0], u.elements[1] - v.elements[1], u.elements[2] - v.elements[2]);
   // return vec3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
}

// Vector multiplication (component-wise, element-wise multiplication)
vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.elements[0] * v.elements[0], u.elements[1] * v.elements[1], u.elements[2] * v.elements[2]);
}

// To scale a number with a vector
vec3 operator*(double t, const vec3& v) {
    return vec3(v.elements[0] * t, v.elements[1] * t, v.elements[2] * t);
}

// To scale a vector with a number
vec3 operator*(const vec3& v, double t) {
    return vec3(v.elements[0] * t, v.elements[1] * t, v.elements[2] * t);
}

// To divide a vector by a number
vec3 operator/(const vec3& v, double t) {
    return vec3(v.elements[0] / t, v.elements[1] / t, v.elements[2] / t);

}

// Dot product (scalar result of component-wise multiplication)

 double dot(const vec3& u, const vec3& v) {
    return u.elements[0] * v.elements[0] + u.elements[1] * v.elements[1] + u.elements[2] * v.elements[2];
}

// Cross product (vector result of the cross-product)
vec3 cross(const vec3& u, const vec3& v) {
    return vec3(
        u.elements[1] * v.elements[2] - u.elements[2] * v.elements[1], // x-component
        u.elements[2] * v.elements[0] - u.elements[0] * v.elements[2], // y-component
        u.elements[0] * v.elements[1] - u.elements[1] * v.elements[0]  // z-component
    );
}


// To normalize a vector such that it has a length of 1, we need to divide a vector by its length
vec3 unit_vector(const vec3& v) {
    return vec3(v / sqrt((v.elements[0] * v.elements[0]) + (v.elements[1] * v.elements[1]) + (v.elements[2] * v.elements[2])));
    //efficient way would be: return v/v.length();
}
