#pragma once
#include "object.h"

class CImage : public Object
{
public:
    GLint object;
    vector<glm::vec3> vertices;
    vector<glm::vec3> normals;
    vector<glm::vec2> uvs;

    GLuint textureID;
    bool end{};
public:
    CImage();
    void render(GLuint shaderProgramID) /*override*/;
    void initTexture() /*override*/;
    void initBuffer() /*override*/;
};

