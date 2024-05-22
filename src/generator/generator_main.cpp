#include "generators.hpp"
#include "parsedModel.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void write3dFile(ParsedModel model, std::string output_file_name) {
  std::ofstream file(output_file_name);
  file << model.getVertex().size() << std::endl;
  std::vector<Point> vertices = model.getVertex();
  for (Point vertex : vertices) {
    file << vertex.x() << "," << vertex.y() << "," << vertex.z() << std::endl;
  }
  std::vector<Point> normals = model.getNormals();
  for (Point normal : normals) {
    file << normal.x() << "," << normal.y() << "," << normal.z() << std::endl;
  }
  std::vector<Point> textures = model.getTextures();
  for (Point texture : textures) {
    file << texture.x() << "," << texture.y() << "," << texture.z() << std::endl;
  }
  file.close();
}

int main(int argc, char *argv[]) {

  if (argc < 2) {
    std::cerr << "Usage: " << argv[0]
              << " <primitive> <arguments> <output_file_name.3d" << std::endl;
    return 1;
  }

  std::string primitive = argv[1];

  if (primitive == "plane") {
    if (argc != 5) {
      std::cerr << "Usage: " << argv[0]
                << " plane <length> <divisions> <output_file_name.3d"
                << std::endl;
      return 1;
    }
    float length = std::stof(argv[2]);
    int divisions = std::stoi(argv[3]);
    if (length <= 0 || divisions <= 0) {
      std::cerr << "Length and divisions must be greater than 0" << std::endl;
      return 1;
    }
    std::string output_file_name = argv[4];
    write3dFile(generatePlane(length, divisions), output_file_name);
  } else if (primitive == "sphere") {
    if (argc != 6) {
      std::cerr << "Usage: " << argv[0]
                << " sphere <radius> <slices> <stacks> <output_file_name.3d"
                << std::endl;
      return 1;
    }
    float radius = std::stof(argv[2]);
    int slices = std::stoi(argv[3]);
    int stacks = std::stoi(argv[4]);
    if (radius <= 0 || slices <= 0 || stacks <= 0) {
      std::cerr << "Radius, slices and stacks must be greater than 0"
                << std::endl;
      return 1;
    }
    std::string output_file_name = argv[5];
    write3dFile(generateSphere(radius, slices, stacks), output_file_name);
  } else if (primitive == "box") {
    if (argc != 5) {
      std::cerr << "Usage: " << argv[0]
                << " box <dimension> <divisions> <output_file_name.3d"
                << std::endl;
      return 1;
    }
    float dimension = std::stof(argv[2]);
    int divisions = std::stoi(argv[3]);
    if (dimension <= 0 || divisions <= 0) {
      std::cerr << "Dimension and divisions must be greater than 0"
                << std::endl;
      return 1;
    }
    std::string output_file_name = argv[4];
    write3dFile(generateBox(dimension, divisions), output_file_name);
  } else if (primitive == "cone") {
    if (argc != 7) {
      std::cerr
          << "Usage: " << argv[0]
          << " cone <radius> <height> <slices> <stacks> <output_file_name.3d"
          << std::endl;
      return 1;
    }
    float radius = std::stof(argv[2]);
    float height = std::stof(argv[3]);
    int slices = std::stoi(argv[4]);
    int stacks = std::stoi(argv[5]);
    if (radius <= 0 || height <= 0 || slices <= 0 || stacks <= 0) {
      std::cerr << "Radius, height, slices and stacks must be greater than 0"
                << std::endl;
      return 1;
    }
    std::string output_file_name = argv[6];
    write3dFile(generateCone(radius, height, slices, stacks), output_file_name);
  } else if (primitive == "cylinder") {
    if (argc != 6) {
      std::cerr << "Usage:" << argv[0]
                << "cylinder <radius> <height> <sides> <output_file_name.3d"
                << std::endl;
      return 1;
    }
    float radius = std::stof(argv[2]);
    float height = std::stof(argv[3]);
    int sides = std::stoi(argv[4]);
    std::string output_file_name = argv[5];
    write3dFile(generateCylinder(radius, height, sides), output_file_name);
  } else if (primitive == "patch") {
    if (argc != 5) {
      std::cerr
          << "Usage: " << argv[0]
          << " patch <patch_file> <tesselation_level> <output_file_name.3d"
          << std::endl;
      return 1;
    }
    std::string patch_file = argv[2];
    int tesselation_level = std::stoi(argv[3]);
    std::string output_file_name = argv[4];
    write3dFile(generatePatch(patch_file, tesselation_level), output_file_name);

  } else {
    std::cerr << "Unknown primitive: " << primitive << std::endl;
    return 1;
  }
}
