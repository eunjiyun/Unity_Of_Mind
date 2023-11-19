#include "stdafx.h"
#include "shaders.h"

#include "camera.h"
#include "object.h"
#include "base.h"
#include "wall.h"
#include "player.h"

// 카메라
Camera camera;
void initCamera();

// 바닥
Base base;

// 벽
Wall wall;

// 플레이어
Player player;

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
    PlaySound("inGame.wav", NULL, SND_ASYNC | SND_LOOP);//sound

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Unity of Mind");
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Unable to initialize GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
        std::cout << "Game Start!" << std::endl;

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
{
    switch (key)
    {
    case 'a': // 왼쪽 이동
        player.moveLeft();
        break;
    case 'd': // 오른쪽 이동
        player.moveRight();
        break;

    case 'r': // 플레이어 빨간색 변경
        player.changeRed();
        break;
    case 'g': // 플레이어 초록색 변경
        player.changeGreen();
        break;
    case 'b': // 플레이어 파란색 변경
        player.changeBlue();
        break;
    case 's': // 플레이어 축소 / 확대
        player.changeSize();
        break;
    }

    glutPostRedisplay();
}


void init()
{
    initCamera();
    base.init();
    wall.init();
    player.init();

    objects.push_back(&base);
    objects.push_back(&wall);
    objects.push_back(&player);
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






