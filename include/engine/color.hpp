#ifndef COLOR_HPP
#define COLOR_HPP

#include <tuple>

using namespace std;

class Color {
    public:
        tuple<int, int, int> diffuse;
        tuple<int, int, int> specular;
        tuple<int, int, int> ambient;
        tuple<int, int, int> emissive;
        int shininess;

        Color(tuple<int, int, int> diffuse, tuple<int, int, int> specular, tuple<int, int, int> ambient, tuple<int, int, int> emissive, int shininess);
        Color();
        
};

#endif