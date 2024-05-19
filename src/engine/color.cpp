#include "engine/color.hpp"

Color::Color(tuple<int, int, int> diffuse, tuple<int, int, int> specular, tuple<int, int, int> ambient, tuple<int, int, int> emissive, int shininess) {
    this->diffuse = diffuse;
    this->specular = specular;
    this->ambient = ambient;
    this->emissive = emissive;
    this->shininess = shininess;
}

Color::Color() {
    this->diffuse = make_tuple(200, 200, 200);
    this->ambient = make_tuple(50, 50, 50);
    this->specular = make_tuple(0, 0, 0);
    this->emissive = make_tuple(0, 0, 0);
    this->shininess = 0;
}