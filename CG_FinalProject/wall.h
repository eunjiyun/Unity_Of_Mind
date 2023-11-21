#pragma once
#include "object.h"

typedef class Cube : public Object
{
private:
    glm::mat4 cModel;
    glm::vec3 color;

public:
    void init() override;
    void render(GLuint shaderProgramID) override;
    void drawCube(GLuint shaderProgramID);
    void reset();
    bool moveCube();

    void changeEmpty();

    void changeRed();
    void changeGreen();
    void changeBlue();

    void change_SmallSize();

} Cube;

typedef class Wall : public Cube
{
private :
    Cube cube[3][3];
    int	random_num[36][3];

public :
    void init();
    void render(GLuint shaderProgramID) override;
    Cube getCube(int i , int j);

    void moveWall();
    void makeWall(int i , int j , int cur_idx);

}Wall;



