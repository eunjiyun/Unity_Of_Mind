#pragma once
#include "stdafx.h"


class CFileIn
{
public:

    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;

    std::vector<glm::vec3> out_vertices, out_normals;
    std::vector<glm::vec2> out_uvs;

    float sumX = 0.0, sumY = 0.0, sumZ = 0.0;
    float aveX, aveY, aveZ;
    float scaleX, scaleY, scaleZ;
    float minX = 0.0, minY = 0.0, minZ = 0.0;
    float maxX = 0.0, maxY = 0.0, maxZ = 0.0;
    float scaleAll;

    float sizeX, sizeY, sizeZ;

    int loadObj(const char* fileName);
};

