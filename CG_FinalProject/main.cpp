#include "shaders.h"
#include "stdafx.h"

#include "camera.h"
#include "object.h"

// 좌표계
typedef class Coord : public Object
{
public:
    void init() override;
    void render(GLuint shaderProgramID) override;
} Coord;
Coord coord; // 좌표계 객체

// 바닥
typedef class Base : public Object
{
public:
    void init() override;
    void render(GLuint shaderProgramID) override;
} Base;
Base base; // 바닥 객체

// 벽 (플레이어가 이 벽을 피해야 함)
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
Wall wall; // 벽 객체 (플레이어가 피해야 하는 벽)

// 카메라
Camera camera;
void initCamera();

// 오브젝트
vector<Object*> objects;

// 초기화
void init();

// gl 변수
GLclampf g_color[4] = { 0.f, 0.f, 0.f, 1.f };
GLuint windowWidth = 800;
GLuint windowHeight = 800;

// gl 함수
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid keyboard(unsigned char key, int x, int y);

// shader 변수
GLuint shaderProgramID;
glm::mat4 model;
glm::mat4 view;
glm::mat4 projection;

void main(int argc , char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("CG_FinalProject");
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Unable to initialize GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
        std::cout << "GLEW Initialized" << std::endl;

    glEnable(GL_DEPTH_TEST);

    char vertexFile[] = "vertex.glsl";
    char fragmentFile[] = "fragment.glsl";
    shaderProgramID = initShader(vertexFile, fragmentFile);

    // 초기화
    init();

    glutDisplayFunc(drawScene);
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
}

GLvoid drawScene()
{
    glClearColor(g_color[0], g_color[1], g_color[2], g_color[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shaderProgramID);

    glViewport(0, 0, 800, 800);

    // Camera
    camera.setCamera(shaderProgramID, 0);

    // Object Draw
    for (int i = 0; i < objects.size(); ++i)
        (*objects[i]).render(shaderProgramID);

    glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
    glViewport(0, 0, 800, 800);
}

GLvoid keyboard(unsigned char key, int x, int y)
{ }

void init()
{
    initCamera();
    coord.init();
    base.init();
    wall.init();

    objects.push_back(&coord);
    objects.push_back(&base);
    objects.push_back(&wall);
}

void initCamera()
{
    camera.setFovy(45.0f);
    camera.setzNear(0.1f);
    camera.setzFar(50.0f);

    camera.setLeft(-2.0f);
    camera.setRight(2.0f);
    camera.setBottom(-2.0f);
    camera.setTop(2.0f);

    camera.setYaw(-90.f);
    camera.setPitch(-20.f);
    camera.setAngle(-45.f);
    camera.setEye(glm::vec3(0.f, 1.f, 2.f));
}

void Coord::init()
{
    const vector<float> coordVertices = {
        -1.f, 0.0f, 0.0f,
        1.f, 0.0f, 0.0f,

        0.0f, 0.0f, -1.f,
        0.0f, 0.0f, 1.f,

        0.0f, -1.f, 0.0f,
        0.0f, 1.f, 0.0f };

    const vector<float> coordColor = {
       0.f, 0.f, 1.f,
       0.f, 0.f, 1.f,
       0.f, 1.f, 0.f,
       0.f, 1.f, 0.f,
       1.f, 0.f, 0.f,
       1.f, 0.f, 0.f };

    initModel(coordVertices, coordColor);
    initPos();
    pos.y = 0.01f;
    scale = glm::vec3(0.5f, .5f, .5f);
    initBuffer();
}

void Coord::render(GLuint shaderProgramID)
{
    model = glm::mat4(1.f);
    model = glm::translate(model, pos);
    model = glm::scale(model, scale);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(vao);
    glDrawArrays(GL_LINES, 0, 6);
}

void Base::init()
{
    const vector<float> baseVertices = {
        -.5f, 0.f, -1.f,
        .4f, 0.f, -1.f,
        .4f, 0.f, 1.f,
        -.5f, 0.f, 1.f };
    const vector<float> baseColor = {
        0.f, 1.f, 0.f,
        1.f, 0.f, 0.f,
        0.f, 0.f, 1.f,
        1.f, .5f, 1.f };
    const vector<GLubyte> baseIndices = {
        0, 1, 2,
        0, 2, 3 };

    initModel(baseVertices, baseColor, baseIndices);
    initPos();
    initBuffer();
}

void Base::render(GLuint shaderProgramID)
{
    model = glm::mat4(1.f);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
}

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
    	- 0.5f , 0.3f , -1.f,
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

    vector<float> wallColors = {
       
        // Z
        1.f , 0.f , 1.f,
        1.f , 0.f , 1.f,
        1.f , 0.f , 1.f,
        1.f , 0.f , 1.f,
         1.f , 0.f , 1.f,
         1.f , 0.f , 1.f,
         1.f , 0.f , 1.f,
         1.f , 0.f , 1.f,
        // X
        1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
         1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,

        // C
        1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
         1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
        // A
        1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
         1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
        // S
        1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
         1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
        // D
        1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
         1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
        // Q
        1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
         1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
        // W
        1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
         1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
        // E
        1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
         1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,
        1.f , 0.f , 0.f,

    };

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
    pos.y = 0.f;
    scale = glm::vec3(1.0f);
}

const int glDrawElements_constNum = 36;

void Wall::drawZ(GLuint shaderProgramID)
{
    zModel = glm::mat4(1.f);
    zModel = glm::translate(zModel, glm::vec3(0.f, 0.f, 0.f));
    model = model * zModel;
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, glDrawElements_constNum * 1, GL_UNSIGNED_BYTE, 0);
}

void Wall::drawX(GLuint shaderProgramID)
{
    xModel = glm::mat4(1.f);
    xModel = glm::translate(xModel, glm::vec3(0.f, 0.f, 0.f));
    model = model * xModel;
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, glDrawElements_constNum * 2, GL_UNSIGNED_BYTE, 0);
}

void Wall::drawC(GLuint shaderProgramID)
{
    cModel = glm::mat4(1.f);
    cModel = glm::translate(xModel, glm::vec3(0.f, 0.f, 0.f));
    model = model * cModel;
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, glDrawElements_constNum * 3, GL_UNSIGNED_BYTE, 0);
}

void Wall::drawA(GLuint shaderProgramID)
{
    aModel = glm::mat4(1.f);
    aModel = glm::translate(aModel, glm::vec3(0.f, 0.f, 0.f));
    model = model * aModel;
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, glDrawElements_constNum * 4, GL_UNSIGNED_BYTE, 0);
}

void Wall::drawS(GLuint shaderProgramID)
{
    sModel = glm::mat4(1.f);
    sModel = glm::translate(sModel, glm::vec3(0.f, 0.f, 0.f));
    model = model * sModel;
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, glDrawElements_constNum * 5, GL_UNSIGNED_BYTE, 0);
}

void Wall::drawD(GLuint shaderProgramID)
{
    dModel = glm::mat4(1.f);
    dModel = glm::translate(dModel, glm::vec3(0.f, 0.f, 0.f));
    model = model * dModel;
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, glDrawElements_constNum * 6, GL_UNSIGNED_BYTE, 0);
}

void Wall::drawQ(GLuint shaderProgramID)
{
    qModel = glm::mat4(1.f);
    qModel = glm::translate(qModel, glm::vec3(0.f, 0.f, 0.f));
    model = model * qModel;
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, glDrawElements_constNum * 7, GL_UNSIGNED_BYTE, 0);
}

void Wall::drawW(GLuint shaderProgramID)
{
    wModel = glm::mat4(1.f);
    wModel = glm::translate(wModel, glm::vec3(0.f, 0.f, 0.f));
    model = model * wModel;
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, glDrawElements_constNum * 8, GL_UNSIGNED_BYTE, 0);
}

void Wall::drawE(GLuint shaderProgramID)
{
    eModel = glm::mat4(1.f);
    eModel = glm::translate(eModel, glm::vec3(0.f, 0.f, 0.f));
    model = model * eModel;
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, glDrawElements_constNum * 9, GL_UNSIGNED_BYTE, 0);
}







