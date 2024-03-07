#include <iostream>
#include <vector>
#include <fstream>
#include "generators.hpp"

void write3dFile(std::vector<Point> vertices, std::string output_file_name)
{
    std::ofstream file (output_file_name);
    file << vertices.size() << std::endl;
    for (Point vertex : vertices)
    {
        file << vertex.x() << "," << vertex.y() << "," << vertex.z() << std::endl;
    }
    file.close();
}

int main (int argc, char *argv[]) {

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <primitive> <arguments> <output_file_name.3d" << std::endl;
        return 1;
    }
    
    std::string primitive = argv[1];

    if (primitive == "plane")
    {
        if (argc != 5) {
            std::cerr << "Usage: " << argv[0] << " plane <length> <divisions> <output_file_name.3d" << std::endl;
            return 1;
        }
        float length = std::stof(argv[2]);
        int divisions = std::stoi(argv[3]);
        std::string output_file_name = argv[4];
        write3dFile(generatePlane(length, divisions), output_file_name);
    }
    else if (primitive == "sphere")
    {
        if (argc != 6) {
            std::cerr << "Usage: " << argv[0] << " sphere <radius> <slices> <stacks> <output_file_name.3d" << std::endl;
            return 1;
        }
        float radius = std::stof(argv[2]);
        int slices = std::stoi(argv[3]);
        int stacks = std::stoi(argv[4]);
        std::string output_file_name = argv[5];
        write3dFile(generateSphere(radius, slices, stacks), output_file_name);
    }
    else if (primitive == "box")
    {
        if (argc != 5) {
            std::cerr << "Usage: " << argv[0] << " box <dimension> <divisions> <output_file_name.3d" << std::endl;
            return 1;
        }
        float dimension = std::stof(argv[2]);
        int divisions = std::stoi(argv[3]);
        std::string output_file_name = argv[4];
        write3dFile(generateBox(dimension, divisions), output_file_name);
    }
    else if(primitive == "cone")
    {
        if (argc!= 6) {
            std::cerr << "Usage: " << argv[0] << " cone <radius> <height> <slices> <stacks> <output_file_name.3d" << std::endl;
            return 1;
        }
        float radius = std::stof(argv[2]);
        float height = std::stof(argv[3]);
        int slices = std::stoi(argv[4]);
        int stacks = std::stoi(argv[5]);
        std::string output_file_name = argv[6];
        write3dFile(generateCone(radius, height, slices, stacks), output_file_name);
    }
    else {
        std::cerr << "Unknown primitive: " << primitive << std::endl;
        return 1;
    }
}