#include <cmath>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <point.hpp>
#include <cgmath.hpp>
#include "parsedModel.hpp"

using namespace std;

vector<vector<vector<Point>>> parsePatch (const string &patchfile) {
    ifstream file(patchfile);
    if (!file.is_open()) {
        cerr << "Error opening file: " << patchfile << endl;
        exit(1);
    }
    int n_patches;
    file >> n_patches;
    int indices[n_patches][16];
    for (int i = 0; i < n_patches; i++) {
        char comma;
        for (int j = 0; j < 16; j++) {
            file >> indices[i][j];
            if (j < 15) {
                file >> comma;
            }
        }
    }
    int n_controlPoints;
    file >> n_controlPoints;
    vector<Point> controlPoints;
    for (int i = 0; i < n_controlPoints; i++) {
        float x, y, z;
        char comma;
        file >> x >> comma >> y >> comma >> z;
        controlPoints.emplace_back(x, y, z);
    }
    file.close();

    vector<vector<vector<Point>>> patches;
    for (int i = 0; i < n_patches; i++) {
        vector<vector<Point>> patch;
        for (int j = 0; j < 4; j++) {
            vector<Point> curve;
            for (int k = 0; k < 4; k++) {
                curve.push_back(controlPoints[indices[i][j * 4 + k]]);
            }
            patch.push_back(curve);
        }
        patches.push_back(patch);
    }

    return patches;
}


ParsedModel generatePatch(string &patchfile, float tesselationLevel) {

    vector<vector<vector<Point>>> patches = parsePatch(patchfile);

    vector<Point> vertices;

    vector<vector<float>> bezierMatrix = {
        {-1, 3, -3, 1},
        {3, -6, 3, 0},
        {-3, 3, 0, 0},
        {1, 0, 0, 0}
    };

    for (vector<vector<Point>>patch : patches) {
        // Pre-calculation for the patch
        auto mp = MP(bezierMatrix, patch);
        auto pmt = PMtranspose(mp, bezierMatrix); // bezierMatrix is simetric, so M = Mt

        for (float u = 1; u <= tesselationLevel; u++) {
            float pu = (u - 1) / tesselationLevel;
            float uVector[4] = {pu * pu * pu, pu * pu, pu, 1};
            float next_pu = u / tesselationLevel;
            float next_uVector[4] = {next_pu * next_pu * next_pu, next_pu * next_pu, next_pu, 1};

            auto uvectorMPMt = uVectorMPMt(uVector, pmt);
            auto next_uvectorMPMt = uVectorMPMt(next_uVector, pmt);
            for (float v = 1; v <= tesselationLevel; v++) {
                float pv = (v - 1) / tesselationLevel;
                float vVector[4] = {pv * pv * pv, pv * pv, pv, 1};
                float next_pv = v / tesselationLevel;
                float next_vVector[4] = {next_pv * next_pv * next_pv, next_pv * next_pv, next_pv, 1};

                Point p1 = uVectorMPMtVVector(uvectorMPMt, vVector);
                Point p2 = uVectorMPMtVVector(uvectorMPMt, next_vVector);
                Point p3 = uVectorMPMtVVector(next_uvectorMPMt, vVector);
                Point p4 = uVectorMPMtVVector(next_uvectorMPMt, next_vVector);

                /*
                    p1 --- p3
                    | \    |
                    |  \   |            
                    |   \  |
                    |    \ |
                    |     \|
                    p2 --- p4
                */

                vertices.push_back(p1);
                vertices.push_back(p2);               
                vertices.push_back(p4);

                vertices.push_back(p1);
                vertices.push_back(p4);
                vertices.push_back(p3);

            }
        }
    }

    return ParsedModel(vertices, {}, {});

}
  