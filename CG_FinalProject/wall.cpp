#include "wall.h"
#define CUBE_INDEX_COUNT 36

// 스테이지 단계
int stageLevel = 1;

// 지금까지 통과한 벽의 개수
int wallCount = 1;

// 랜덤 값
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> dis(1, 8);

// 1단계 패턴 - 비어있으면 : 검은색! 채워져 있으면 : 빨간색
glm::vec3 iamEmpty = glm::vec3(0.0f, 0.0f, 0.0f);

// 2단계 패턴 - 빨간색 , 초록색 , 파란색 vec3 변수
glm::vec3 iamRed = glm::vec3(1.0f, 0.0f, 0.0f);
glm::vec3 iamGreen = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 iamBlue = glm::vec3(0.0f, 0.0f, 1.0f);

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
        // 앞면
        4 , 5 , 7,
        7 , 6 , 4,
        // 뒷면
        1 , 0 , 3,
        0 , 2 , 3,
        // 바닥면
        1 , 5 , 4,
        4 , 0 , 1,
        // 윗면
        3 , 2 , 6,
        6 , 7 , 3,
        // 오른쪽면
        1 , 3 , 7,
        7 , 5 , 1,
        // 왼쪽면
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

    color_z = glm::vec3(0.0f , 0.0f , 0.0f);
    color_x = iamRed;
    color_c = iamRed;
    color_a = iamRed;
    color_s = iamRed;
    color_d = iamRed;
    color_q = iamRed;
    color_w = iamRed;
    color_e = iamRed;

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

    if(stageLevel == 1) // 스테이지 레벨 1 - 랜덤수가 짝수일 때 : 막힘 , 랜덤수가 홀수일 때 : 뚫림
    {
		   
    }
    else if(stageLevel == 2) // 스테이지 레벨 2 - 레벨 1 패턴 + r : 랜덤수 나머지 0 , g : 랜덤수 나머지 1 , b : 랜덤수 나머지 2
    {
	    
    }
    else if(stageLevel == 3) // 스테이지 레벨 3 - 레벨 1 , 2 패턴 + 랜덤수가 8일 때 : 축소 , 나머지 : 그냥 그대로
    {
	    
    }
    
}

void Wall::moveWall()
{
    if(pos.z >= 1.7f)
    {
        if(wallCount == 10)
        {
            stageLevel += 1;
            wallCount = 0;
        }
        else
        {
            ++wallCount;
        }

        reset();
    }

    pos.z += 0.01f;
}

void Wall::drawZ(GLuint shaderProgramID)
{
    zModel = glm::mat4(1.f);
    zModel = glm::translate(zModel, glm::vec3(0.f, 0.f, 0.f));
    model = model * zModel;

    glUniform3f(glGetUniformLocation(shaderProgramID, "fColor"), color_z.r, color_z.g, color_z.b);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, CUBE_INDEX_COUNT * 1, GL_UNSIGNED_BYTE, 0);
}

void Wall::drawX(GLuint shaderProgramID)
{
    xModel = glm::mat4(1.f);
    xModel = glm::translate(xModel, glm::vec3(0.f, 0.f, 0.f));
    model = model * xModel;

    glUniform3f(glGetUniformLocation(shaderProgramID, "fColor"), color_x.r, color_x.g, color_x.b);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, CUBE_INDEX_COUNT * 2, GL_UNSIGNED_BYTE, 0);
}

void Wall::drawC(GLuint shaderProgramID)
{
    cModel = glm::mat4(1.f);
    cModel = glm::translate(cModel, glm::vec3(0.f, 0.f, 0.f));
    model = model * cModel;

    glUniform3f(glGetUniformLocation(shaderProgramID, "fColor"), color_c.r, color_c.g, color_c.b);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, CUBE_INDEX_COUNT * 3, GL_UNSIGNED_BYTE, 0);
}

void Wall::drawA(GLuint shaderProgramID)
{
    aModel = glm::mat4(1.f);
    aModel = glm::translate(aModel, glm::vec3(0.f, 0.f, 0.f));
    model = model * aModel;

    glUniform3f(glGetUniformLocation(shaderProgramID, "fColor"), color_a.r, color_a.g, color_a.b);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, CUBE_INDEX_COUNT * 4, GL_UNSIGNED_BYTE, 0);
}

void Wall::drawS(GLuint shaderProgramID)
{
    sModel = glm::mat4(1.f);
    sModel = glm::translate(sModel, glm::vec3(0.f, 0.f, 0.f));
    model = model * sModel;

    glUniform3f(glGetUniformLocation(shaderProgramID, "fColor"), color_s.r, color_s.g, color_s.b);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, CUBE_INDEX_COUNT * 5, GL_UNSIGNED_BYTE, 0);
}

void Wall::drawD(GLuint shaderProgramID)
{
    dModel = glm::mat4(1.f);
    dModel = glm::translate(dModel, glm::vec3(0.f, 0.f, 0.f));
    model = model * dModel;

    glUniform3f(glGetUniformLocation(shaderProgramID, "fColor"), color_d.r, color_d.g, color_d.b);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, CUBE_INDEX_COUNT * 6, GL_UNSIGNED_BYTE, 0);
}

void Wall::drawQ(GLuint shaderProgramID)
{
    qModel = glm::mat4(1.f);
    qModel = glm::translate(qModel, glm::vec3(0.f, 0.f, 0.f));
    model = model * qModel;

    glUniform3f(glGetUniformLocation(shaderProgramID, "fColor"), color_q.r, color_q.g, color_q.b);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, CUBE_INDEX_COUNT * 7, GL_UNSIGNED_BYTE, 0);
}

void Wall::drawW(GLuint shaderProgramID)
{
    wModel = glm::mat4(1.f);
    wModel = glm::translate(wModel, glm::vec3(0.f, 0.f, 0.f));
    model = model * wModel;

    glUniform3f(glGetUniformLocation(shaderProgramID, "fColor"), color_w.r, color_w.g, color_w.b);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, CUBE_INDEX_COUNT * 8, GL_UNSIGNED_BYTE, 0);
}

void Wall::drawE(GLuint shaderProgramID)
{
    eModel = glm::mat4(1.f);
    eModel = glm::translate(eModel, glm::vec3(0.f, 0.f, 0.f));
    model = model * eModel;

    glUniform3f(glGetUniformLocation(shaderProgramID, "fColor"), color_e.r, color_e.g, color_e.b);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, CUBE_INDEX_COUNT * 9, GL_UNSIGNED_BYTE, 0);
}
