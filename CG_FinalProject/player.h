#pragma once
#include "object.h"
#include "FileIn.h"

typedef class Player : public Object
{
private:

	glm::mat4 pModel; // player ��

	void drawP(GLuint shaderProgramID);
public:
	bool crashOnce{};
	CFileIn in;

public:

	void init(int);
	void render(GLuint shaderProgramID) override;

	// �÷��̾� �̵�
	void moveLeft();
	void moveRight();

	//�÷��̾� �� ����
	void changeRed();
	void changeGreen();
	void changeBlue();

	// �÷��̾� ũ�� ����
	void changeSize();

	void initBuf();
};
