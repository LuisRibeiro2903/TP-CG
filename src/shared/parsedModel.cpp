#include "parsedModel.hpp"

ParsedModel::ParsedModel(vector<Point> vertex, vector<Point> normals, vector<Point> textures) {
    this->vertex = vertex;
    this->normals = normals;
    this->textures = textures;
    this->size = vertex.size();
}

vector<Point> ParsedModel::getVertex() {
    return vertex;
}

vector<Point> ParsedModel::getNormals() {
    return normals;
}

vector<Point> ParsedModel::getTextures() {
    return textures;
}

int ParsedModel::getSize() {
    return size;
}