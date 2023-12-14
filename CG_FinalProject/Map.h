#pragma once
#include "stdafx.h"
#include "object.h"
#include "FileIn.h"

class CMap :public Object
{
public:
	
	CFileIn in;

	glm::mat4 pModel; // player ¸ðµ¨
	vector<glm::vec2> uvs;
	GLuint texId;
	glm::vec3  pos{ glm::vec3(0.0f, 0.0f, 0.0f) };

public:
	void drawS(GLuint shaderProgramID);
	void init() override;
	void render(GLuint shaderProgramID) override;

	void initBuf();
	void initTexture();
};

