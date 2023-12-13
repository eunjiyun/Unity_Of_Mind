#pragma once
#include "stdafx.h"
#include "object.h"
#include "FileIn.h"

class CMap :public Object
{
public:
	
	CFileIn in;

	glm::mat4 pModel; // player ¸ðµ¨

	

public:
	void drawS(GLuint shaderProgramID);
	void init() override;
	void render(GLuint shaderProgramID) override;

	void initBuf();
};

