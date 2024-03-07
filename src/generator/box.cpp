#include <vector>
#include "point.hpp"


std::vector<Point>generatePlanesXZ(float dimension,int divisions)
{
    std::vector<Point>vertices;

    float step = dimension / divisions;
    float halfDimension = dimension / 2.0f;

        for (int i = 0; i < divisions; i++) {
            for (int j = 0; j < divisions; j++) {
            
            // Calculate vertices for the current square
            float x0 = -halfDimension + j * step;
            float z0 = -halfDimension + i * step;
            float x1 = x0 + step;
            float z1 = z0 + step;

            // Lower triangle Top Face
            vertices.emplace_back(x0, halfDimension, z0);
            vertices.emplace_back(x1, halfDimension, z1);
            vertices.emplace_back(x1, halfDimension, z0);

            // Upper triangle Top Face
            vertices.emplace_back(x0, halfDimension, z1);
            vertices.emplace_back(x1, halfDimension, z1);
            vertices.emplace_back(x0, halfDimension, z0);

            // Upper triangle Bottom Face
            vertices.emplace_back(x0, -halfDimension, z0);
            vertices.emplace_back(x1, -halfDimension, z0);
            vertices.emplace_back(x0, -halfDimension, z1);

            // Lower triangle Bottom Face
            vertices.emplace_back(x0, -halfDimension, z1);
            vertices.emplace_back(x1, -halfDimension, z0);
            vertices.emplace_back(x1, -halfDimension, z1);

        }
    }
    return vertices;
}

std::vector<Point> generatePlanesXY(float dimension, int divisions){
    std::vector<Point> vertices;

    float step = dimension / divisions;
    float halfDimension = dimension / 2.0f;

    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
            
            // Calculate vertices for the current square
            float x0 = -halfDimension + j * step;
            float y0 = -halfDimension + i * step;
            float x1 = x0 + step;
            float y1 = y0 + step;

            // Lower triangle
            vertices.emplace_back(x0, y0, halfDimension);
            vertices.emplace_back(x1, y0, halfDimension);
            vertices.emplace_back(x0, y1, halfDimension);

            // Upper triangle
            vertices.emplace_back(x1, y0, halfDimension);
            vertices.emplace_back(x1, y1, halfDimension);
            vertices.emplace_back(x0, y1, halfDimension);

            // Lower triangle
            vertices.emplace_back(x0, y0, -halfDimension);
            vertices.emplace_back(x1, y1, -halfDimension);
            vertices.emplace_back(x1, y0, -halfDimension);

            // Upper triangle
            vertices.emplace_back(x1, y1, -halfDimension);
            vertices.emplace_back(x0, y0, -halfDimension);
            vertices.emplace_back(x0, y1, -halfDimension);
        }
    }

    return vertices;
}

std::vector<Point> generatePlanesYZ(float dimension, int divisions){
    std::vector<Point> vertices;

    float step = dimension / divisions;
    float halfDimension = dimension / 2.0f;

    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
            
            // Calculate vertices for the current square
            float y0 = -halfDimension + j * step;
            float z0 = -halfDimension + i * step;
            float y1 = y0 + step;
            float z1 = z0 + step;

            // Lower triangle Front Face
            vertices.emplace_back(halfDimension, y0, z0);
            vertices.emplace_back(halfDimension, y1, z0);
            vertices.emplace_back(halfDimension, y1, z1);

            // Upper triangle Front Face
            vertices.emplace_back(halfDimension, y0, z0);
            vertices.emplace_back(halfDimension, y1, z1);
            vertices.emplace_back(halfDimension, y0, z1);

            // Lower triangle Back Face
            vertices.emplace_back(-halfDimension, y0, z0);
            vertices.emplace_back(-halfDimension, y0, z1);
            vertices.emplace_back(-halfDimension, y1, z0);

            // Upper triangle Back Face
            vertices.emplace_back(-halfDimension, y1, z1);
            vertices.emplace_back(-halfDimension, y1, z0);
            vertices.emplace_back(-halfDimension, y0, z1);

            
        }
    }

    return vertices;
}

std::vector<Point>generateBox(float dimension, int divisions){
    std::vector<Point>box;

    //Topo e base
    auto XZFaces = generatePlanesXZ(dimension, divisions);

    box.insert(box.end(), XZFaces.begin(), XZFaces.end()); 

    //Lados
    auto YZFaces = generatePlanesYZ(dimension, divisions);
    box.insert(box.end(), YZFaces.begin(), YZFaces.end());

    // Frente e trás
    auto XYFaces = generatePlanesXY(dimension, divisions);
    box.insert(box.end(), XYFaces.begin(), XYFaces.end());

    return box;
}