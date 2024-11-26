

#include <iostream>
#include <fstream>
#include<cmath>
#include<math.h>
#include<stdio.h>
using namespace std;

#include "Vector3.hpp"



const unsigned int width = 250;
const unsigned int height = 250 ;

using color = vec3; //color is a type alias for vec3, representing RGB color components (factors) [0,1]
                        //vec3 has the purpose of storing RGB values for each pixel


//pixel is our array and each array cell(position) can contain two integers(x,y) and a vec3(alias color) type
struct pixel {
    unsigned int x;
    unsigned int y;
    color color;
};
// x is the x-position of the pixel
// y is the y-position of the pixel
// color contains values between 0.0 and 1.0 for each of RGB


void printHeader(std::ofstream& ppmFile, const unsigned int width, const unsigned int height) {
    ppmFile << "P3" << std::endl; // Magic Number, we're doing a pixelmap here
    ppmFile << width << " " << height << std::endl;   // We need to specify width/height
    ppmFile << "255" << std::endl;    // Maximum value
}



void setColor(pixel* screen, const unsigned int x, const unsigned int y, vec3 color) {
    screen[width*y + x].color = color; // sets the color of a specific pixel on the screen at coordinates (x, y).
            // only the factors(between[0,1]) are being inserted here in screen array positions
            //these factors can have upto 3 decimal places
}

void write_color(std::ostream& out, const color& pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    //these pixel_color.x/y/z above were still all in factors [0,1] ; below it will be translated into proper RGB values
     // in the byte range [0,255], from float factors to proper int RGB values
    //It's always a good practice to clamp the final RGB values to the [0, 1] range before
     //converting them to the [0, 255] range to ensure no overflow beyond 255.
    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    // Write out the proper pixel color components inside the(locally out) ppmFile that was passed inside write_color function
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';

}


//This printScreenToPPMFile is able to write all the screen[].color to the PPM file
//by first calling printHeader only once and then writing all the RGB triplets for every pixel using write_color inside a loop.

void printScreenToPPMFile(const pixel* screen, std::ofstream& ppmFile) {
    printHeader(ppmFile, width ,height);
    for( int y = 0; y < height; y++) {
        for( int x = 0; x < width; x++) {
            write_color(ppmFile, screen[width*y + x].color);
        }
        //  It's a good idea to remove this newline below to avoid extra newline to avoid bug which could break the format
        ppmFile << "\n";
    }
}



int main() {


    struct pixel screen[width*height];
    // A screen array for pixels is created,
     // and each pixel is initialized with x, y positions and a user defined default color (here, dark blue) (0, 0, 100)  &
     // these things will be initially set using the first loop below


    for(int i = 0; i < width*height; i++) {
        screen[i].x = i % width; //basically x positions increase from 0 to 255 then resets again
        screen[i].y = i / width; //each time x position resets to 0, y position increases by 1, until y goes from 0 to 255
        screen[i].color = vec3(0, 0, 100); //initially the color for all pixels is set to blue (0,0,100)
    }


    vec3 observer_position = vec3(0, 0, 0); //The observer's position is assumed to be at (0, 0, 0).


    for(unsigned int i = 0; i < height; i++) {
        for(unsigned int j = 0; j < width; j++) {

            // Compute the pixel position in world space
            vec3 pixel_position = vec3(j-width/2.0, i-height/2.0, 100);

            // Compute the direction vector from the observer to the pixel
            vec3 direction = unit_vector(pixel_position - observer_position);

            direction = (direction + vec3(1,1, 1))/2.0; //to make the negative factors positive



            setColor(screen, j, i, direction);
            //The program then iterates over each pixel's coordinates,
            //calculates the "direction" vector from the observer (camera) to the pixel's position,
            //and normalizes this direction. The result is adjusted to ensure the RGB values are in the [0, 1] range.
        }
    }


    //so far we only set the RGB color factors in our array, so we did not create the PPM until now.

    std::ofstream ppmFile("output.ppm");
    //debugging
    if (!ppmFile) {
        std::cerr << "Error: Could not open output.ppm for writing!" << std::endl;
        return 1;
    } else {
        std::cout << "PPM file successfully opened for writing!" << std::endl;
    }


    printScreenToPPMFile(screen, ppmFile); // the PPM file actually takes in all the header and RGB triplet values
                                                //only by calling this one function in main.
    ppmFile.close();




    cout << "Vector Function Testing area: " << endl;

    /* test used this function below:
    double vec3::operator[](int i) const {
    return elements[i];
    }
    */
    vec3 testvec1=vec3{11,25,33};
    std::cout << testvec1[0]<<std::endl;  // " operator [] (int i) " is the highlight of this function
                                            // meaning operator [] is used along with a sent argument of int type

    /*
    double vec3::x() const {
    return elements[0];
    }
    */
    vec3 testvec2=vec3{11,25,33};
    std::cout << testvec2.y()<<std::endl; // " x() " is the highlight of this function


    vec3 testvec3=vec3{1,2,3}+=vec3{5,5,5};
    cout<<"addition of two vectors using += : "<< testvec3 <<endl;

    /*
    *vec3 operator/(const vec3& v, double t) {
    return vec3(v.elements[0] / t, v.elements[1] / t, v.elements[2] / t);
    }
    */

    vec3 testvec4=vec3{18,18,18}/3;
    std::cout <<"divide a vector by a number: "<< testvec4<<std::endl;

    /*
     double dot(const vec3& u, const vec3& v) {
        return u.elements[0] * v.elements[0] + u.elements[1] * v.elements[1] + u.elements[2] * v.elements[2];
    }
    */
    vec3 testvec5=vec3{1,2,3};
    vec3 testvec6=vec3{5,5,5};
    double testvec7=dot(testvec5,testvec6);
    cout<<"dot product of two vectors : "<< testvec7 <<endl;


    //also,
    /*
    std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.elements[0] << ' ' << v.elements[1] << ' ' << v.elements[2];
    }
    */

    //ppmFile<< testvec5; // will insert 1, 2& 3 (testvec5={1,2,3}) as another RGB triplet inside ppmFile



    /* Using std::vector is the most portable and future-proof solution for the stack overflow error. It would look like:

    #include <vector>
    std::vector<pixel> screen(width * height);

    // Access like this:
    screen[width * y + x].color = vec3(...);

     */



    return 0;





}



