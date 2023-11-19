#include "player.h"
#define CUBE_INDEX_COUNT 36

void Player::init()
{
    const vector<float> playerVertices = {
        -0.1f , 0.0f , 0.8f,
        0.0f , 0.0f , 0.8f,
        -0.1f , 0.1f , 0.8f,
        0.0f , 0.1f , 0.8f,

        -0.1f , 0.0f , 0.7f,
        0.0f , 0.0f , 0.7f,
        -0.1f , 0.1f , 0.7f,
        0.0f , 0.1f , 0.7f,
    };

    vector<float> playerColors;

    for (int i = 0; i < 8; i++)
    {
        playerColors.push_back(1.f);
        playerColors.push_back(0.f);
        playerColors.push_back(0.f);
    }

    const vector<GLubyte> playerIndices = {
       // ¾Õ¸é
       4 , 5 , 7,
       7 , 6 , 4,
       // µÞ¸é
       1 , 0 , 3,
       0 , 2 , 3,
       // ¹Ù´Ú¸é
       1 , 5 , 4,
       4 , 0 , 1,
       // À­¸é
       3 , 2 , 6,
       6 , 7 , 3,
       // ¿À¸¥ÂÊ¸é
       1 , 3 , 7,
       7 , 5 , 1,
       // ¿ÞÂÊ¸é
       6 , 2 , 0,
       0 , 4 , 6,
    };

    color = glm::vec3(1.0f, 0.0f, 0.0f);

    initModel(playerVertices, playerColors, playerIndices);
    initBuffer();
}

void Player::render(GLuint shaderProgramID)
{
    glBindVertexArray(vao);

    model = glm::mat4(1.f);
    model = glm::translate(model, pos);
    model = glm::scale(model, scale);

    drawP(shaderProgramID);
}

void Player::drawP(GLuint shaderProgramID)
{
    pModel = glm::mat4(1.f);
    pModel = glm::translate(pModel, glm::vec3(0.f, 0.f, 0.f));
    pModel = glm::scale(pModel, glm::vec3(scale.x , scale.y , scale.z));
    model = model * pModel;

    glUniform3f(glGetUniformLocation(shaderProgramID, "fColor"), color.r, color.g, color.b);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, CUBE_INDEX_COUNT, GL_UNSIGNED_BYTE, 0);
}

void Player::moveLeft()
{
    if(pos.x > -0.35f)
    {
        pos.x -= 0.05f;
    } 
}

void Player::moveRight()
{
    if (pos.x < 0.35f)
    {
        pos.x += 0.05f;
    }
}

void Player::changeRed()
{
    color.r = 1.0f;
    color.g = 0.0f;
    color.b = 0.0f;
}

void Player::changeGreen()
{
    color.r = 0.0f;
    color.g = 1.0f;
    color.b = 0.0f;
}

void Player::changeBlue()
{
    color.r = 0.0f;
    color.g = 0.0f;
    color.b = 1.0f;
}

void Player::changeSize()
{
    if(scale.x == 0.5f)
    {
        scale.x = 1.0f;
        scale.y = 1.0f;
    }
    else
    {
        scale.x = 0.5f;
        scale.y = 0.5f;
    }
}


