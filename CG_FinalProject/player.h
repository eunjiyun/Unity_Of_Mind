#pragma once
#include "object.h"

typedef class Player : public Object
{
private:

	glm::mat4 pModel; // player ��

	void drawP(GLuint shaderProgramID);
public:
	bool crashOnce{};

public :

	void init() override;
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
};
