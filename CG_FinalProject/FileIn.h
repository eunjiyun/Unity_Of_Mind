#pragma once
#include "stdafx.h"


class CFileIn
{
public:

    vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    vector<vec3> temp_vertices;
    vector<vec2> temp_uvs;
    vector<vec3> temp_normals;

    vector<vec3> out_vertices, out_normals;
    vector<vec2> out_uvs;

    float sumX{ 0.0 }, sumY{ 0.0 }, sumZ{ 0.0 };
    float aveX, aveY, aveZ;
    float scaleX, scaleY, scaleZ;
    float minX{ 0.0 }, minY{ 0.0 }, minZ{ 0.0 };
    float maxX{ 0.0 }, maxY{ 0.0 }, maxZ{ 0.0 };
    float scaleAll;

    float sizeX, sizeY, sizeZ;

public:
    int loadObj(const char* );
};

