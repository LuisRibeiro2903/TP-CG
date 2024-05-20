#include "engine/color.hpp"

Color::Color(tuple<int, int, int> diffuse_tuple, tuple<int, int, int> specular_tuple, tuple<int, int, int> ambient_tuple, tuple<int, int, int> emissive_tuple, int shininess) {
    int r, g, b;
    tie(r, g, b) = diffuse_tuple;
    GLfloat * diffuse_color = new GLfloat[4]{static_cast<GLfloat>(r) / 255.0f, static_cast<GLfloat>(g) / 255.0f, static_cast<GLfloat>(b) / 255.0f, 1.0f};
    this->diffuse = diffuse_color;
    tie(r, g, b) = specular_tuple;
    GLfloat * specular_color = new GLfloat[4]{static_cast<GLfloat>(r) / 255.0f, static_cast<GLfloat>(g) / 255.0f, static_cast<GLfloat>(b) / 255.0f, 1.0f};
    this->specular = specular_color;
    tie(r, g, b) = ambient_tuple;
    GLfloat * ambient_color = new GLfloat[4]{static_cast<GLfloat>(r) / 255.0f, static_cast<GLfloat>(g) / 255.0f, static_cast<GLfloat>(b) / 255.0f, 1.0f};
    this->ambient = ambient_color;
    tie(r, g, b) = emissive_tuple;
    GLfloat * emissive_color = new GLfloat[4]{static_cast<GLfloat>(r) / 255.0f, static_cast<GLfloat>(g) / 255.0f, static_cast<GLfloat>(b) / 255.0f, 1.0f};
    this->emissive = emissive_color;
    this->shininess = shininess;
}

Color::Color() {
    this->diffuse = new GLfloat[4]{static_cast<GLfloat>(200) / 255.0f, static_cast<GLfloat>(200) / 255.0f, static_cast<GLfloat>(200) / 255.0f, 1.0f};
    this->ambient = new GLfloat[4]{static_cast<GLfloat>(50) / 255.0f, static_cast<GLfloat>(50) / 255.0f, static_cast<GLfloat>(50) / 255.0f, 1.0f};
    this->specular = new GLfloat[4]{static_cast<GLfloat>(0) / 255.0f, static_cast<GLfloat>(0) / 255.0f, static_cast<GLfloat>(0) / 255.0f, 1.0f};
    this->emissive = new GLfloat[4]{static_cast<GLfloat>(0) / 255.0f, static_cast<GLfloat>(0) / 255.0f, static_cast<GLfloat>(0) / 255.0f, 1.0f};
    this->shininess = 0;
}