#include "parser.hpp"
#include "engine/transform/translate.hpp"
#include "engine/transform/rotate.hpp"
#include "engine/transform/scale.hpp"
#include "engine/transform/catmullrom.hpp"
#include "groups.hpp"
#include "tinyxml2.h"
#include <fstream>
#include <iostream>

ParsedWorld::ParsedWorld(std::array<Point, 3> &lookAt,
                         std::array<float, 3> &projection, int windowWidth,
                         int windowHeight, GroupNode * rootGroup)
    : lookAt(lookAt), projection(projection), windowWidth(windowWidth),
      windowHeight(windowHeight), rootGroup(rootGroup) {}

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

GroupNode * ParseGroupElement(tinyxml2::XMLElement* groupElement);

ParsedWorld * worldParser(const char *filename) {

  std::array<Point, 3> lookAt;
  std::array<float, 3> projection;
  int windowWidth;
  int windowHeight;

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

  
  GroupNode *rootGroup = nullptr;
  tinyxml2::XMLElement *primaryGroupElement = root->FirstChildElement("group");
  if (primaryGroupElement) {
    rootGroup = ParseGroupElement(primaryGroupElement);
  } else {
    std::cerr << "Error: invalid file format (no 'group' element, must have at least one)" << std::endl;
    exit(1);
  }

  return new ParsedWorld(lookAt, projection, windowWidth, windowHeight, rootGroup);
  

}

GroupNode * ParseGroupElement(tinyxml2::XMLElement* groupElement) {
  auto * group = new GroupNode();
  

  tinyxml2::XMLElement* transformElement = groupElement->FirstChildElement("transform");
  if (transformElement) {
    for (tinyxml2::XMLElement* child = transformElement->FirstChildElement(); child != nullptr; child = child->NextSiblingElement()) {
        string transformType = child->Value();
        float time = 0.0f;

        // Checking if the translate is a CatmullRom
        if (transformType == "translate" && child->QueryFloatAttribute("time", &time) == tinyxml2::XML_SUCCESS) {
          // Align bool
          const char* alignStr = child->Attribute("align");
          bool align = alignStr && strcmp(alignStr, "true") == 0;

          //Vector of points
          std::vector<Point> points;
          for(tinyxml2::XMLElement* pointElement = child->FirstChildElement("point"); pointElement != nullptr;  pointElement = pointElement->NextSiblingElement("point")) {
            float x = 0, y = 0, z = 0;
            pointElement->QueryFloatAttribute("x", &x);
            pointElement->QueryFloatAttribute("y", &y);
            pointElement->QueryFloatAttribute("z", &z);
            points.emplace_back(x, y, z);
          }
          group->addTransform(new CatmullROM(points, time, align));
        } else {
          float x = 0, y = 0, z = 0, angle = 0;
          
          child->QueryFloatAttribute("x", &x);
          child->QueryFloatAttribute("y", &y);
          child->QueryFloatAttribute("z", &z);

          if (transformType == "translate") {
              group->addTransform(new Translate(x, y, z));
          } else if (transformType == "rotate") {
            float angleOrTime = 0;
            bool isTime = false;
            if (child->QueryFloatAttribute("time", &time) == tinyxml2::XML_SUCCESS) {
              angleOrTime = time;
              isTime = true;
            } else {
              child->QueryFloatAttribute("angle", &angle);
              angleOrTime = angle;
            }
              group->addTransform(new Rotate(angleOrTime, x, y, z, isTime));
          } else if (transformType == "scale") {
              group->addTransform(new Scale(x, y, z));
          }
        }
    }
  }

  tinyxml2::XMLElement* colorElement = groupElement->FirstChildElement("color");
  if (colorElement) {
    float r = 0, g = 0, b = 0;
    colorElement->QueryFloatAttribute("r", &r);
    colorElement->QueryFloatAttribute("g", &g);
    colorElement->QueryFloatAttribute("b", &b);
    group->setColor(r, g, b);
  }

  tinyxml2::XMLElement* modelsElement = groupElement->FirstChildElement("models");
  if (modelsElement) {
    for (tinyxml2::XMLElement* model = modelsElement->FirstChildElement("model"); model != nullptr; model = model->NextSiblingElement("model")) {
      const char *file = model->Attribute("file");
      group->addModel(new string(file));
    }
  }

  tinyxml2::XMLElement* childGroup = groupElement->FirstChildElement("group");
  while(childGroup) {
    GroupNode * child = ParseGroupElement(childGroup);
    group->addSubNode(child);
    childGroup = childGroup->NextSiblingElement("group");
  }

  return group;
}
