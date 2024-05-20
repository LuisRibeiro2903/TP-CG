#include <vector>
#include <tuple>
#include "point.hpp"
#include "parsedModel.hpp"


std::tuple<std::vector<Point>, std::vector<Point>> generatePlanesXZ(float dimension,int divisions)
{
    std::vector<Point>vertices;
    std::vector<Point>normals;

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
            normals.emplace_back(0, 1, 0);
            vertices.emplace_back(x1, halfDimension, z1);
            normals.emplace_back(0, 1, 0);
            vertices.emplace_back(x1, halfDimension, z0);   
            normals.emplace_back(0, 1, 0);

            // Upper triangle Top Face
            vertices.emplace_back(x0, halfDimension, z1);
            normals.emplace_back(0, 1, 0);
            vertices.emplace_back(x1, halfDimension, z1);
            normals.emplace_back(0, 1, 0);
            vertices.emplace_back(x0, halfDimension, z0);
            normals.emplace_back(0, 1, 0);

            // Upper triangle Bottom Face
            vertices.emplace_back(x0, -halfDimension, z0);
            normals.emplace_back(0, -1, 0);
            vertices.emplace_back(x1, -halfDimension, z0);  
            normals.emplace_back(0, -1, 0);
            vertices.emplace_back(x0, -halfDimension, z1);
            normals.emplace_back(0, -1, 0);

            // Lower triangle Bottom Face
            vertices.emplace_back(x0, -halfDimension, z1);
            normals.emplace_back(0, -1, 0);
            vertices.emplace_back(x1, -halfDimension, z0);
            normals.emplace_back(0, -1, 0);
            vertices.emplace_back(x1, -halfDimension, z1);
            normals.emplace_back(0, -1, 0);

        }
    }
    return make_tuple(vertices, normals);
}

std::tuple<std::vector<Point>, std::vector<Point>> generatePlanesXY(float dimension, int divisions){
    std::vector<Point> vertices;
    std::vector<Point> normals;

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
            normals.emplace_back(0, 0, 1);
            vertices.emplace_back(x1, y0, halfDimension);
            normals.emplace_back(0, 0, 1);
            vertices.emplace_back(x0, y1, halfDimension);
            normals.emplace_back(0, 0, 1);

            // Upper triangle
            vertices.emplace_back(x1, y0, halfDimension);
            normals.emplace_back(0, 0, 1);
            vertices.emplace_back(x1, y1, halfDimension);
            normals.emplace_back(0, 0, 1);
            vertices.emplace_back(x0, y1, halfDimension);
            normals.emplace_back(0, 0, 1);

            // Lower triangle
            vertices.emplace_back(x0, y0, -halfDimension);
            normals.emplace_back(0, 0, -1);
            vertices.emplace_back(x1, y1, -halfDimension);
            normals.emplace_back(0, 0, -1);
            vertices.emplace_back(x1, y0, -halfDimension);
            normals.emplace_back(0, 0, -1);

            // Upper triangle
            vertices.emplace_back(x1, y1, -halfDimension);
            normals.emplace_back(0, 0, -1);
            vertices.emplace_back(x0, y0, -halfDimension);
            normals.emplace_back(0, 0, -1);
            vertices.emplace_back(x0, y1, -halfDimension);
            normals.emplace_back(0, 0, -1);
        }
    }

    return make_tuple(vertices, normals);
}

std::tuple<std::vector<Point>, std::vector<Point>> generatePlanesYZ(float dimension, int divisions){

    std::vector<Point> vertices;
    std::vector<Point> normals;

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
            normals.emplace_back(1, 0, 0);
            vertices.emplace_back(halfDimension, y1, z0);
            normals.emplace_back(1, 0, 0);
            vertices.emplace_back(halfDimension, y1, z1);
            normals.emplace_back(1, 0, 0);

            // Upper triangle Front Face
            vertices.emplace_back(halfDimension, y0, z0);
            normals.emplace_back(1, 0, 0);
            vertices.emplace_back(halfDimension, y1, z1);
            normals.emplace_back(1, 0, 0);
            vertices.emplace_back(halfDimension, y0, z1);
            normals.emplace_back(1, 0, 0);

            // Lower triangle Back Face
            vertices.emplace_back(-halfDimension, y0, z0);
            normals.emplace_back(-1, 0, 0);
            vertices.emplace_back(-halfDimension, y0, z1);
            normals.emplace_back(-1, 0, 0);
            vertices.emplace_back(-halfDimension, y1, z0);
            normals.emplace_back(-1, 0, 0);

            // Upper triangle Back Face
            vertices.emplace_back(-halfDimension, y1, z1);
            normals.emplace_back(-1, 0, 0);
            vertices.emplace_back(-halfDimension, y1, z0);
            normals.emplace_back(-1, 0, 0);
            vertices.emplace_back(-halfDimension, y0, z1);
            normals.emplace_back(-1, 0, 0);

            
        }
    }

    return make_tuple(vertices, normals);
}

ParsedModel generateBox(float dimension, int divisions){
    std::vector<Point>box;
    std::vector<Point>normals;


    //Topo e base
    auto XZFaces = generatePlanesXZ(dimension, divisions);

    box.insert(box.end(), get<0>(XZFaces).begin(), get<0>(XZFaces).end()); 
    normals.insert(normals.end(), get<1>(XZFaces).begin(), get<1>(XZFaces).end());

    //Lados
    auto YZFaces = generatePlanesYZ(dimension, divisions);
    box.insert(box.end(), get<0>(YZFaces).begin(), get<0>(YZFaces).end());
    normals.insert(normals.end(), get<1>(YZFaces).begin(), get<1>(YZFaces).end());

    // Frente e trás
    auto XYFaces = generatePlanesXY(dimension, divisions);
    box.insert(box.end(), get<0>(XYFaces).begin(), get<0>(XYFaces).end());
    normals.insert(normals.end(), get<1>(XYFaces).begin(), get<1>(XYFaces).end());

    return ParsedModel(box, normals, {});
}