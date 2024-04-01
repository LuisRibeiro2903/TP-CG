#include "parser.hpp"
#include "tinyxml2.h"
#include "transforms.h"
#include <fstream>
#include <iostream>
#include <string>

ParsedWorld::ParsedWorld(std::array<Point, 3> &lookAt,
                         std::array<float, 3> &projection, int windowWidth,
                         int windowHeight, std::vector<std::string> &models,
                         std::vector<TransformNode> transforms)
    : _lookAt(lookAt), _projection(projection), _windowWidth(windowWidth),
      _windowHeight(windowHeight), _models(models) {}

vector<vector<Point>> parse3dFile(vector<string> models) {
  vector<vector<Point>> all_vertices;
  for (string model : models) {
    vector<Point> vertices;
    std::ifstream file(model);
    if (!file.is_open()) {
      std::cerr << "Error: file not found" << std::endl;
      exit(1);
    }
    int n_vertices;
    file >> n_vertices;
    for (int i = 0; i < n_vertices; i++) {
      float x, y, z;
      char comma;
      file >> x >> comma >> y >> comma >> z;
      vertices.push_back(Point(x, y, z));
    }
    all_vertices.push_back(vertices);
    file.close();
  }
  return all_vertices;
}

ParsedWorld worldParser(const char *filename) {
  std::array<Point, 3> lookAt;
  std::array<float, 3> projection;
  int windowWidth;
  int windowHeight;
  std::vector<std::string> models;

  tinyxml2::XMLDocument doc;
  if (doc.LoadFile(filename) != tinyxml2::XML_SUCCESS) {
    std::cerr << "Error: file not found" << std::endl;
    exit(1);
  }

  tinyxml2::XMLElement *root = doc.FirstChildElement("world");
  if (!root) {
    std::cerr << "Error: invalid file format (no 'world' element)" << std::endl;
    exit(1);
  }

  tinyxml2::XMLElement *windowElement = root->FirstChildElement("window");
  if (!windowElement) {
    std::cerr << "Error: invalid file format (no 'window' element)"
              << std::endl;
    exit(1);
  }
  windowElement->QueryIntAttribute("width", &windowWidth);
  windowElement->QueryIntAttribute("height", &windowHeight);

  tinyxml2::XMLElement *cameraElement = root->FirstChildElement("camera");
  if (cameraElement) {
    tinyxml2::XMLElement *positionElement =
        cameraElement->FirstChildElement("position");
    if (!positionElement) {
      std::cerr << "Error: invalid file format (no 'position' element of "
                   "parent 'camera')"
                << std::endl;
      exit(1);
    }
    float positionX, positionY, positionZ;
    positionElement->QueryFloatAttribute("x", &positionX);
    positionElement->QueryFloatAttribute("y", &positionY);
    positionElement->QueryFloatAttribute("z", &positionZ);
    lookAt[0] = Point(positionX, positionY, positionZ);
    tinyxml2::XMLElement *lookAtElement =
        cameraElement->FirstChildElement("lookAt");
    if (!lookAtElement) {
      std::cerr << "Error: invalid file format (no 'lookAt' element of parent "
                   "'camera')"
                << std::endl;
      exit(1);
    }
    float lookAtX, lookAtY, lookAtZ;
    lookAtElement->QueryFloatAttribute("x", &lookAtX);
    lookAtElement->QueryFloatAttribute("y", &lookAtY);
    lookAtElement->QueryFloatAttribute("z", &lookAtZ);
    lookAt[1] = Point(lookAtX, lookAtY, lookAtZ);
    tinyxml2::XMLElement *upElement = cameraElement->FirstChildElement("up");
    if (!upElement) {
      std::cerr
          << "Error: invalid file format (no 'up' element of parent 'camera')"
          << std::endl;
      exit(1);
    }
    float upX, upY, upZ;
    upElement->QueryFloatAttribute("x", &upX);
    upElement->QueryFloatAttribute("y", &upY);
    upElement->QueryFloatAttribute("z", &upZ);
    lookAt[2] = Point(upX, upY, upZ);
    tinyxml2::XMLElement *projectionElement =
        cameraElement->FirstChildElement("projection");
    if (!projectionElement) {
      std::cerr << "Error: invalid file format (no 'projection' element of "
                   "parent 'camera')"
                << std::endl;
      exit(1);
    }
    projectionElement->QueryFloatAttribute("fov", &projection[0]);
    projectionElement->QueryFloatAttribute("near", &projection[1]);
    projectionElement->QueryFloatAttribute("far", &projection[2]);
  } else {
    std::cerr << "Error: invalid file format (no 'camera' element)"
              << std::endl;
    exit(1);
  }
  tinyxml2::XMLElement *groupElement = root->FirstChildElement("group");
  if (groupElement) {
    tinyxml2::XMLElement *modelsElement =
        groupElement->FirstChildElement("models");
    if (modelsElement) {
      for (tinyxml2::XMLElement *model =
               modelsElement->FirstChildElement("model");
           model != nullptr; model = model->NextSiblingElement("model")) {
        const char *file = model->Attribute("file");
        models.push_back(file);
      }
    } else {
      std::cerr << "Error: invalid file format (no 'models' element of parent "
                   "'group')"
                << std::endl;
      exit(1);
    }
  } else {
    std::cerr << "Error: invalid file format (no 'group' element)" << std::endl;
    exit(1);
  }

  ParsedWorld world(lookAt, projection, windowWidth, windowHeight, models);
  return world;
}
