#include "parser.hpp"
#include "engine/transform/translate.hpp"
#include "engine/transform/rotate.hpp"
#include "engine/transform/scale.hpp"
#include "engine/transform/catmullrom.hpp"
#include "engine/lights/light.hpp"
#include "engine/lights/lightDir.hpp"
#include "engine/lights/lightPoint.hpp"
#include "engine/lights/lightSpot.hpp"
#include "engine/color.hpp"
#include "groups.hpp"
#include "tinyxml2.h"
#include <fstream>
#include <iostream>
#include <tuple>

ParsedWorld::ParsedWorld(std::array<Point, 3> &lookAt,
                         std::array<float, 3> &projection, int windowWidth,
                         int windowHeight, GroupNode * rootGroup, vector<Light *> lights, int n_lights)
    : lookAt(lookAt), projection(projection), windowWidth(windowWidth),
      windowHeight(windowHeight), rootGroup(rootGroup), lights(lights), n_lights(n_lights) {}

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


  vector<Light *> lights;
  int lightId = 0;
  tinyxml2::XMLElement *lightsElement = root->FirstChildElement("lights");
  if(lightsElement) {
    for (tinyxml2::XMLElement *lightElement = lightsElement->FirstChildElement("light"); lightElement != nullptr; lightElement = lightElement->NextSiblingElement("light"), lightId++) {
      const char *lightType = lightElement->Attribute("type");
      lightElement->QueryStringAttribute("type", &lightType);
      switch (lightType[0]) {
        case 'd': {
          float dirX, dirY, dirZ;
          lightElement->QueryFloatAttribute("dirx", &dirX);
          lightElement->QueryFloatAttribute("diry", &dirY);
          lightElement->QueryFloatAttribute("dirz", &dirZ);
          LightDir * l = new LightDir(dirX, dirY, dirZ, lightId);
          lights.push_back(l);
          break;
        }
        case 'p': {
          float posX, posY, posZ;
          lightElement->QueryFloatAttribute("posx", &posX);
          lightElement->QueryFloatAttribute("posy", &posY);
          lightElement->QueryFloatAttribute("posz", &posZ);
          LightPoint * l = new LightPoint(posX, posY, posZ, lightId);
          lights.push_back(l);
          break;
        }
        case 's': {
          float posX, posY, posZ, dirX, dirY, dirZ, cutoff;
          lightElement->QueryFloatAttribute("posx", &posX);
          lightElement->QueryFloatAttribute("posy", &posY);
          lightElement->QueryFloatAttribute("posz", &posZ);
          lightElement->QueryFloatAttribute("dirx", &dirX);
          lightElement->QueryFloatAttribute("diry", &dirY);
          lightElement->QueryFloatAttribute("dirz", &dirZ);
          lightElement->QueryFloatAttribute("cutoff", &cutoff);
          LightSpot * l = new LightSpot(posX, posY, posZ, dirX, dirY, dirZ, cutoff, lightId);
          lights.push_back(l);
          break;
        }
      }
    }

  }

  
  GroupNode *rootGroup = nullptr;
  tinyxml2::XMLElement *primaryGroupElement = root->FirstChildElement("group");
  if (primaryGroupElement) {
    rootGroup = ParseGroupElement(primaryGroupElement);
  } else {
    std::cerr << "Error: invalid file format (no 'group' element, must have at least one)" << std::endl;
    exit(1);
  }

  return new ParsedWorld(lookAt, projection, windowWidth, windowHeight, rootGroup, lights, lights.size());
  

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

  tinyxml2::XMLElement* modelsElement = groupElement->FirstChildElement("models");
  if (modelsElement) {
    //TODO: One color for each model
    vector<Color *> colors;
    for (tinyxml2::XMLElement* model = modelsElement->FirstChildElement("model"); model != nullptr; model = model->NextSiblingElement("model")) {
      const char *file = model->Attribute("file");
      group->addModel(new string(file));
      tinyxml2::XMLElement* colorElement = model->FirstChildElement("color");
      if (colorElement) {
        std::tuple<int, int, int> diffuse = std::make_tuple(200, 200, 200);
        std::tuple<int, int, int> specular = std::make_tuple(0, 0, 0);
        std::tuple<int, int, int> ambient = std::make_tuple(50, 50, 50);
        std::tuple<int, int, int> emissive = std::make_tuple(0, 0, 0);
        int shininess = 0;
        tinyxml2::XMLElement* diffuseElement = colorElement->FirstChildElement("diffuse");
        if (diffuseElement) {
          float r = 0, g = 0, b = 0;
          diffuseElement->QueryFloatAttribute("R", &r);
          diffuseElement->QueryFloatAttribute("G", &g);
          diffuseElement->QueryFloatAttribute("B", &b);
          diffuse = std::make_tuple(r, g, b);
        }
        tinyxml2::XMLElement* specularElement = colorElement->FirstChildElement("specular");
        if (specularElement) {
          float r = 0, g = 0, b = 0;
          specularElement->QueryFloatAttribute("R", &r);
          specularElement->QueryFloatAttribute("G", &g);
          specularElement->QueryFloatAttribute("B", &b);
          specular = std::make_tuple(r, g, b);
        }
        tinyxml2::XMLElement* ambientElement = colorElement->FirstChildElement("ambient");
        if (ambientElement) {
          float r = 0, g = 0, b = 0;
          ambientElement->QueryFloatAttribute("R", &r);
          ambientElement->QueryFloatAttribute("G", &g);
          ambientElement->QueryFloatAttribute("B", &b);
          ambient = std::make_tuple(r, g, b);
        }
        tinyxml2::XMLElement* emissiveElement = colorElement->FirstChildElement("emissive");
        if (emissiveElement) {
          float r = 0, g = 0, b = 0;
          emissiveElement->QueryFloatAttribute("R", &r);
          emissiveElement->QueryFloatAttribute("G", &g);
          emissiveElement->QueryFloatAttribute("B", &b);
          emissive = std::make_tuple(r, g, b);
        }
        tinyxml2::XMLElement* shininessElement = colorElement->FirstChildElement("shininess");
        if (shininessElement) {
          shininessElement->QueryIntAttribute("value", &shininess);
        }
        colors.push_back(new Color(diffuse, specular, ambient, emissive, shininess));
      } else {
        colors.push_back(new Color());
      }
      group->addColor(colors);
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
