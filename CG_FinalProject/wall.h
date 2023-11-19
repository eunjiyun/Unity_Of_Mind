#pragma once
#include "object.h"

typedef class Wall : public Object
{

private:
    glm::mat4 zModel;
    glm::mat4 xModel;
    glm::mat4 cModel;
    glm::mat4 aModel;
    glm::mat4 sModel;
    glm::mat4 dModel;
    glm::mat4 qModel;
    glm::mat4 wModel;
    glm::mat4 eModel;

    glm::vec3 color_z;
    glm::vec3 color_x;
    glm::vec3 color_c;
    glm::vec3 color_a;
    glm::vec3 color_s;
    glm::vec3 color_d;
    glm::vec3 color_q;
    glm::vec3 color_w;
    glm::vec3 color_e;

    void drawZ(GLuint shaderProgramID);
    void drawX(GLuint shaderProgramID);
    void drawC(GLuint shaderProgramID);
    void drawA(GLuint shaderProgramID);
    void drawS(GLuint shaderProgramID);
    void drawD(GLuint shaderProgramID);
    void drawQ(GLuint shaderProgramID);
    void drawW(GLuint shaderProgramID);
    void drawE(GLuint shaderProgramID);

public:
    void init() override;
    void render(GLuint shaderProgramID) override;
    void reset();

    void moveWall();

} Wall;




