#include "wall.h"
#define CUBE_INDEX_COUNT 36

void Wall::init()
{
    const vector<float> wallVertices = {

        // Z
        -0.5f, 0.f, -1.f,
        -0.2f, 0.f, -1.f,
        -0.5f , 0.3f , -1.f,
        -0.2f , 0.3f , -1.f,

         -0.5f, 0.f, -0.7f,
        -0.2f, 0.f, -.7f,
        -0.5f , 0.3f , -.7f,
        -0.2f , 0.3f , -.7f,

        // X
        -0.2f, 0.f, -1.f,
        0.1f, 0.f , -1.f,
        -0.2f , 0.3f , -1.f,
        0.1f , 0.3f , -1.f,

          -0.2f, 0.f, -0.7f,
        0.1f, 0.f , -.7f,
        -0.2f , 0.3f , -.7f,
        0.1f , 0.3f , -.7f,

        // C
        0.1f, 0.f , -1.f,
        0.4f, 0.f , -1.f,
         0.1f , 0.3f , -1.f,
        0.4f , 0.3f , -1.f,

           0.1f, 0.f , -.7f,
        0.4f, 0.f , -.7f,
         0.1f , 0.3f , -.7f,
        0.4f , 0.3f , -.7f,

        // A
        -0.5f , 0.3f , -1.f,
        -0.2f , 0.3f , -1.f,
        -0.5f , 0.6f , -1.f,
        -0.2f , 0.6f , -1.f,

        -0.5f , 0.3f , -0.7f,
        -0.2f , 0.3f , -.7f,
        -0.5f , 0.6f , -.7f,
        -0.2f , 0.6f , -.7f,

        // S
        -0.2f , 0.3f , -1.f,
        0.1f , 0.3f , -1.f,
         -0.2f , 0.6f , -1.f,
        0.1f , 0.6f , -1.f,

        -0.2f , 0.3f , -.7f,
        0.1f , 0.3f , -.7f,
         -0.2f , 0.6f , -.7f,
        0.1f , 0.6f , -.7f,

        // D
        0.1f , 0.3f , -1.f,
        0.4f , 0.3f , -1.f,
        0.1f , 0.6f , -1.f,
        0.4f , 0.6f , -1.f,

        0.1f , 0.3f , -.7f,
        0.4f , 0.3f , -.7f,
        0.1f , 0.6f , -.7f,
        0.4f , 0.6f , -.7f,

        // Q
        -0.5f , 0.6f , -1.f,
        -0.2f , 0.6f , -1.f,
         -0.5f , 0.9f , -1.f,
        -0.2f , 0.9f , -1.f,

          -0.5f , 0.6f , -.7f,
        -0.2f , 0.6f , -.7f,
         -0.5f , 0.9f , -.7f,
        -0.2f , 0.9f , -.7f,

        // W
         -0.2f , 0.6f , -1.f,
        0.1f , 0.6f , -1.f,
        -0.2f , 0.9f , -1.f,
        0.1f , 0.9f , -1.f,

         -0.2f , 0.6f , -.7f,
        0.1f , 0.6f , -.7f,
        -0.2f , 0.9f , -.7f,
        0.1f , 0.9f , -.7f,

        // E
          0.1f , 0.6f , -1.f,
        0.4f , 0.6f , -1.f,
         0.1f , 0.9f , -1.f,
        0.4f , 0.9f , -1.f,

           0.1f , 0.6f , -.7f,
        0.4f , 0.6f , -.7f,
         0.1f , 0.9f , -.7f,
        0.4f , 0.9f , -.7f
    };

    vector<float> wallColors;

    for (int i = 0; i < 8 * 9; i++)
    {
        wallColors.push_back(1.f);
        wallColors.push_back(0.f);
        wallColors.push_back(0.f);
    }

    const vector<GLubyte> wallIndices = {

        // Z
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

        // X
        12 , 13 , 15,
        15 , 14 , 12,
        9 , 8 , 11 ,
        8 , 10 , 11,
        9 , 13 , 12,
        12 , 8 , 9,
        11 , 10 , 14,
        14 , 15 , 11,
        9 , 11 , 15 ,
        15 , 13 , 9,
        14 , 10 , 8,
        8 , 12 , 14,

        // C
        20 , 21 , 23,
        23 , 22 , 20,
        17 , 16 , 19,
        16 , 18 , 19,
        17 , 21 , 20,
        20 , 16 , 17,
        19 , 18 , 22,
        22 , 23 , 19,
        17 , 19 , 23,
        23 , 21 , 17,
        22 , 18 , 16,
        16 , 20 , 22,

        // A
        28 , 29 , 31,
        31 , 30 , 28,
        25 , 24 , 27,
        24 , 26 , 27,
        25 , 29 , 28,
        28 , 24 , 25,
        27 , 26 , 30,
        30 , 31 , 27,
        25 , 27 , 31,
        31 , 29 , 25,
        30 , 26 , 24,
        24 , 28 , 30,

        // S
        36 , 37 , 39,
        39 , 38 , 36,
        33 , 32 , 35,
        32 , 34 , 35,
        33 , 37 , 36,
        36 , 32 , 33,
        35 , 34 , 38,
        38 , 39 , 35,
        33 , 35 , 39,
        39 , 37 , 33,
        38 , 34 , 32,
        32 , 36 , 38,

        // D
        44, 45, 47,
        47, 46, 44,
        41, 40, 43,
        40, 42, 43,
        41, 45, 44,
        44, 40, 41,
        43, 42, 46,
        46, 47, 43,
        41, 43, 47,
        47, 45, 41,
        46, 42, 40,
        40, 44, 46,

        // Q
        52, 53, 55,
        55, 54, 52,
        49, 48, 51,
        48, 50, 51,
        49, 53, 52,
        52, 48, 49,
        51, 50, 54,
        54, 55, 51,
        49, 51, 55,
        55, 53, 49,
        54, 50, 48,
        48, 52, 54,

        // W
        60, 61, 63,
        63, 62, 60,
        57, 56, 59,
        56, 58, 59,
        57, 61, 60,
        60, 56, 57,
        59, 58, 62,
        62, 63, 59,
        57, 59, 63,
        63, 61, 57,
        62, 58, 56,
        56, 60, 62,

        // E
        68, 69, 71,
        71, 70, 68,
        65, 64, 67,
        64, 66, 67,
        65, 69, 68,
        68, 64, 65,
        67, 66, 70,
        70, 71, 67,
        65, 67, 71,
        71, 69, 65,
        70, 66, 64,
        64, 68, 70,
    };

    initModel(wallVertices, wallColors, wallIndices);
    initBuffer();
}

void Wall::render(GLuint shaderProgramID)
{
    glBindVertexArray(vao);

    model = glm::mat4(1.f);
    model = glm::translate(model, pos);
    model = glm::scale(model, scale);

    drawZ(shaderProgramID);
    drawX(shaderProgramID);
    drawC(shaderProgramID);
    drawA(shaderProgramID);
    drawS(shaderProgramID);
    drawD(shaderProgramID);
    drawQ(shaderProgramID);
    drawW(shaderProgramID);
    drawE(shaderProgramID);
}

void Wall::reset()
{
    initPos();
    pos.z = 0.f;
    scale = glm::vec3(1.0f);
}

void Wall::drawZ(GLuint shaderProgramID)
{
    zModel = glm::mat4(1.f);
    zModel = glm::translate(zModel, glm::vec3(0.f, 0.f, 0.f));
    model = model * zModel;

    glUniform3f(glGetUniformLocation(shaderProgramID, "fColor"), 1.0f, 0.5f, 0.5f);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, CUBE_INDEX_COUNT * 1, GL_UNSIGNED_BYTE, 0);
}

void Wall::drawX(GLuint shaderProgramID)
{
    xModel = glm::mat4(1.f);
    xModel = glm::translate(xModel, glm::vec3(0.f, 0.f, 0.f));
    model = model * xModel;

    glUniform3f(glGetUniformLocation(shaderProgramID, "fColor"), 1.0f, 0.5f, 0.5f);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, CUBE_INDEX_COUNT * 2, GL_UNSIGNED_BYTE, 0);
}

void Wall::drawC(GLuint shaderProgramID)
{
    cModel = glm::mat4(1.f);
    cModel = glm::translate(xModel, glm::vec3(0.f, 0.f, 0.f));
    model = model * cModel;

    glUniform3f(glGetUniformLocation(shaderProgramID, "fColor"), 1.0f, 0.5f, 0.5f);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, CUBE_INDEX_COUNT * 3, GL_UNSIGNED_BYTE, 0);
}

void Wall::drawA(GLuint shaderProgramID)
{
    aModel = glm::mat4(1.f);
    aModel = glm::translate(aModel, glm::vec3(0.f, 0.f, 0.f));
    model = model * aModel;

    glUniform3f(glGetUniformLocation(shaderProgramID, "fColor"), 1.0f, 0.5f, 0.5f);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, CUBE_INDEX_COUNT * 4, GL_UNSIGNED_BYTE, 0);
}

void Wall::drawS(GLuint shaderProgramID)
{
    sModel = glm::mat4(1.f);
    sModel = glm::translate(sModel, glm::vec3(0.f, 0.f, 0.f));
    model = model * sModel;

    glUniform3f(glGetUniformLocation(shaderProgramID, "fColor"), 1.0f, 0.5f, 0.5f);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, CUBE_INDEX_COUNT * 5, GL_UNSIGNED_BYTE, 0);
}

void Wall::drawD(GLuint shaderProgramID)
{
    dModel = glm::mat4(1.f);
    dModel = glm::translate(dModel, glm::vec3(0.f, 0.f, 0.f));
    model = model * dModel;

    glUniform3f(glGetUniformLocation(shaderProgramID, "fColor"), 1.0f, 0.5f, 0.5f);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, CUBE_INDEX_COUNT * 6, GL_UNSIGNED_BYTE, 0);
}

void Wall::drawQ(GLuint shaderProgramID)
{
    qModel = glm::mat4(1.f);
    qModel = glm::translate(qModel, glm::vec3(0.f, 0.f, 0.f));
    model = model * qModel;

    glUniform3f(glGetUniformLocation(shaderProgramID, "fColor"), 1.0f, 0.5f, 0.5f);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, CUBE_INDEX_COUNT * 7, GL_UNSIGNED_BYTE, 0);
}

void Wall::drawW(GLuint shaderProgramID)
{
    wModel = glm::mat4(1.f);
    wModel = glm::translate(wModel, glm::vec3(0.f, 0.f, 0.f));
    model = model * wModel;

    glUniform3f(glGetUniformLocation(shaderProgramID, "fColor"), 1.0f, 0.5f, 0.5f);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, CUBE_INDEX_COUNT * 8, GL_UNSIGNED_BYTE, 0);
}

void Wall::drawE(GLuint shaderProgramID)
{
    eModel = glm::mat4(1.f);
    eModel = glm::translate(eModel, glm::vec3(0.f, 0.f, 0.f));
    model = model * eModel;

    glUniform3f(glGetUniformLocation(shaderProgramID, "fColor"), 1.0f, 0.5f, 0.5f);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, CUBE_INDEX_COUNT * 9, GL_UNSIGNED_BYTE, 0);
}
