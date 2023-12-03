#pragma once
#include "object.h"

class CImage : public Object
{
public:
    GLint object;
    vector<vec3> vertices;
    vector<vec3> normals;
    vector<vec2> uvs;

    GLuint textureID;
    int status{0};

public:
    CImage();
    void render(GLuint) ;
    void initTexture() ;
    void initBuffer() ;
};

