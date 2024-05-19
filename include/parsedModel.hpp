#ifndef PARSEDMODEL_HPP
#define PARSEDMODEL_HPP

#include "point.hpp"
#include <GL/glew.h>
#include <vector>

using namespace std;

class ParsedModel {
        
    private:
        vector<Point> vertex;
        vector<Point> normals;
        vector<Point> textures;
        int size;

    public:
        ParsedModel(vector<Point> vertex, vector<Point> normals, vector<Point> textures);

        vector<Point> getVertex();
        vector<Point> getNormals();
        vector<Point> getTextures();
        int getSize();
};

#endif