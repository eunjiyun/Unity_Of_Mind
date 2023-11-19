<<<<<<< HEAD
#pragma once
=======
#ifndef WALL_H
#define WALL_H

//#include "stdafx.h"
>>>>>>> 0bfbbac86e898931a4569528486f4e2a2d56dc02
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

} Wall;
<<<<<<< HEAD
=======

>>>>>>> 0bfbbac86e898931a4569528486f4e2a2d56dc02



