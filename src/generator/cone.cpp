#include "point.hpp"
#include "parsedModel.hpp"
#include "cgmath.hpp"
#include <vector>
#include <math.h>

ParsedModel generateCone(float radius, float height, int slices, int stacks) {
    std::vector<Point> vertices;
    std::vector<Point> normals;
    float coneAngle = atan(radius / height);

    // Vertice para o "corpo" do cone
    for (int i = 0; i < slices; i++) {
        float angle = 2 * M_PI * i / slices;
        float nextAngle = 2 * M_PI * (i + 1) / slices;

        // Base
        vertices.emplace_back(0, 0, 0);
        normals.emplace_back(0, -1, 0);
        vertices.emplace_back(radius * cos(angle), 0, radius * sin(angle));
        normals.emplace_back(0, -1, 0);
        vertices.emplace_back(radius * cos(nextAngle), 0, radius * sin(nextAngle));
        normals.emplace_back(0, -1, 0);

        // Corpo do cone
        for (int j = 0; j < stacks; j++) {
            float currentHeight = height * j / stacks;
            float nextHeight = height * (j + 1) / stacks;
            float currentRadius = radius * (1 - (float)j / stacks);
            float nextRadius = radius * (1 - (float)(j + 1) / stacks);


            /*
            p1 --- p3
            | \    |
            |  \   |            
            |   \  |
            |    \ |
            |     \|
            p2 --- p4
            */    

            Point p1(currentRadius * cos(angle), currentHeight, currentRadius * sin(angle));
            Point p2(nextRadius * cos(angle), nextHeight, nextRadius * sin(angle));
            Point p3(currentRadius * cos(nextAngle), currentHeight, currentRadius * sin(nextAngle));
            Point p4(nextRadius * cos(nextAngle), nextHeight, nextRadius * sin(nextAngle));

            Point n1(cos(angle) * cos(coneAngle), sin(coneAngle), sin(angle) * cos(coneAngle));
            Point n2(cos(angle) * cos(coneAngle), sin(coneAngle), sin(angle) * cos(coneAngle));
            Point n3(cos(nextAngle) * cos(coneAngle), sin(coneAngle), sin(nextAngle) * cos(coneAngle));
            Point n4(cos(nextAngle) * cos(coneAngle), sin(coneAngle), sin(nextAngle) * cos(coneAngle));

            

            // Triângulos que compõem cada fatia do cone
            vertices.push_back(p1);
            normals.push_back(n1);
            vertices.push_back(p2);
            normals.push_back(n2);
            vertices.push_back(p4);
            normals.push_back(n4);

            vertices.push_back(p1);
            normals.push_back(n1);
            vertices.push_back(p4);
            normals.push_back(n4);
            vertices.push_back(p3);
            normals.push_back(n3);  
        }
    }

    return ParsedModel(vertices, normals, {});
}
