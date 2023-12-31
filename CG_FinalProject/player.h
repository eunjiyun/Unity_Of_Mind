#pragma once
#include "object.h"
#include "FileIn.h"

typedef class Player : public Object
{
private:

	glm::mat4 pModel; // player 모델

	void drawP(GLuint shaderProgramID);
public:
	bool crashOnce{};
	CFileIn in;

public:

	void init() override;
	void render(GLuint shaderProgramID) override;

	// 플레이어 이동
	void moveLeft();
	void moveRight();

	//플레이어 색 변경
	void changeRed();
	void changeGreen();
	void changeBlue();

	// 플레이어 크기 변경
	void changeSize();

	void initBuf();
};
