#include <fstream>
#include <iostream>
#include "parser.hpp"


vector<Point> parse3dFile (const char* filename) 
{
    vector<Point> vertices;

    std::ifstream file(filename);
    if (!file.good()) {
        std::cerr << "Error: file not found" << std::endl;
        exit(1);
    }

    std::string line;

    std::getline(file, line);

    unsigned int numVertices = std::stoi(line);
    vertices.reserve(numVertices);
    for(int i = 0; i < numVertices; i++)
    {
        std::getline(file, line);
        float x, y, z;
        if(sscanf(line.c_str(), "%f,%f,%f", &x, &y, &z) != 3)
        {
            std::cerr << "Error: invalid file format" << std::endl;
            exit(1);
        }
        vertices.emplace_back(x, y, z);
    }
    
    return vertices;
}
