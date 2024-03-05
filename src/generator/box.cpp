#include <vector>
#include "point.hpp"


std::vector<Point>generatePlaneXZ(float dimension,int divisions)
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

            // Lower triangle
            vertices.emplace_back(x0, 0.0f, z0);
            vertices.emplace_back(x1, 0.0f, z0);
            vertices.emplace_back(x0, 0.0f, z1);

            // Upper triangle
            vertices.emplace_back(x1, 0.0f, z0);
            vertices.emplace_back(x1, 0.0f, z1);
            vertices.emplace_back(x0, 0.0f, z1);
        }
    }
    return vertices;
}

std::vector<Point> generatePlaneXY(float dimension, int divisions){
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
            vertices.emplace_back(x0, y0, 0.0f);
            vertices.emplace_back(x1, y0, 0.0f);
            vertices.emplace_back(x0, y1, 0.0f);

            // Upper triangle
            vertices.emplace_back(x1, y0, 0.0f);
            vertices.emplace_back(x1, y1, 0.0f);
            vertices.emplace_back(x0, y1, 0.0f);
        }
    }

    return vertices;
}

std::vector<Point> generatePlaneYZ(float dimension, int divisions){
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

            // Lower triangle
            vertices.emplace_back(0.0f, y0, z0);
            vertices.emplace_back(0.0f, y0, z1);
            vertices.emplace_back(0.0f, y1, z0);

            // Upper triangle
            vertices.emplace_back(0.0f, y0, z1);
            vertices.emplace_back(0.0f, y1, z1);
            vertices.emplace_back(0.0f, y1, z0);
        }
    }

    return vertices;
}

std::vector<Point>generateBox(float dimension, int divisions){
    std::vector<Point>box;

    //Topo e base
    auto topFace = generatePlaneXZ(dimension, divisions);
    auto bottomFace = generatePlaneXZ(dimension, divisions);
    for (auto &p : topFace) 
        p.setY(p.y() + dimension / 2.0f);

    for (auto &p : bottomFace) 
        p.setY(p.y() - dimension / 2.0f);

    box.insert(box.end(), topFace.begin(), topFace.end()); 
    box.insert(box.end(), bottomFace.begin(), bottomFace.end());

    //Lados
    auto leftFace = generatePlaneYZ(dimension, divisions);
    auto rightFace = generatePlaneYZ(dimension, divisions);
    for (auto &p : leftFace)
        p.setX(p.x() - dimension / 2.0f);

    for (auto &p : rightFace)
        p.setX(p.x() + dimension / 2.0f);

    box.insert(box.end(), leftFace.begin(), leftFace.end());
    box.insert(box.end(), rightFace.begin(), rightFace.end());

    // Frente e trás
    auto frontFace = generatePlaneXY(dimension, divisions);
    auto backFace = generatePlaneXY(dimension, divisions);
    for (auto &p : frontFace)
        p.setZ(p.z() + dimension / 2.0f);

    for (auto &p : backFace)
        p.setZ(p.z() - dimension / 2.0f);

    box.insert(box.end(), frontFace.begin(), frontFace.end());
    box.insert(box.end(), backFace.begin(), backFace.end());

    return box;
}