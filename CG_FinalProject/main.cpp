#include "shaders.h"
#include "stdafx.h"

// ��ǥ��
typedef class Coord : public Object
{
public:
    void init() override;
    void render(GLuint shaderProgramID) override;
} Coord;
Coord coord; // ��ǥ�� ��ü

// �ٴ�
typedef class Base : public Object
{
public:
    void init() override;
    void render(GLuint shaderProgramID) override;
} Base;
Base base; // �ٴ� ��ü

// ī�޶�
Camera camera;
void initCamera();

// ��ü
vector<Object*> objects;

// �ʱ�ȭ
void init();

// gl ����
GLclampf g_color[4] = { 0.f, 0.f, 0.f, 1.f };
GLuint windowWidth = 800;
GLuint windowHeight = 800;

// gl �Լ�
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid keyboard(unsigned char key, int x, int y);

// shader ����
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

    // �ʱ�ȭ
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

    objects.push_back(&coord);
    objects.push_back(&base);
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
    camera.setAngle(0.f);
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
        .5f, 0.f, -1.f,
        .5f, 0.f, 1.f,
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


