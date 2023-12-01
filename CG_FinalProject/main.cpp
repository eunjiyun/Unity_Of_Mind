#include "stdafx.h"
#include "shaders.h"
#include "camera.h"
#include "object.h"
#include "base.h"
#include "wall.h"
#include "player.h"
#include "Image.h"

// 카메라
Camera camera;
void initCamera();
CameraMode cameraMode = THIRD_PERSON;

// 바닥
Base base;

// 벽
Wall wall;

// 플레이어
Player player;

// 오브젝트들
vector<Object*> objects;

CImage ending;

// 초기화
void init();

// gl 변수
GLclampf g_color[4] = { 0.f, 0.f, 0.f, 1.f };
GLuint windowWidth = BACK_WIDTH;
GLuint windowHeight = BACK_HEIGHT;

// gl 함수
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid keyboard(unsigned char key, int x, int y);
GLvoid update(int value);

// shader 변수
GLuint shaderProgramID;
glm::mat4 model;
glm::mat4 view;
glm::mat4 projection;

// 벽 이동 함수
void wallUpdate();
int wallUpdateSpeed = 20;



void main(int argc, char** argv)
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

	// GLEW 초기화
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}

	glEnable(GL_DEPTH_TEST);

	char vertexFile[] = "vertex.glsl";
	char fragmentFile[] = "fragment.glsl";
	shaderProgramID = initShader(vertexFile, fragmentFile);

	// 초기화
	init();

	glutTimerFunc(wallUpdateSpeed, update, 50);
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

	glViewport(0, 0, BACK_WIDTH, BACK_HEIGHT);

	// Camera
	camera.setCamera(shaderProgramID, 0, cameraMode, player.getPos());

	ending.render(shaderProgramID);

	// Object Draw
	if(not ending.end)
		for (int i = 0; i < objects.size(); ++i)
			(*objects[i]).render(shaderProgramID);

	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, BACK_WIDTH, BACK_HEIGHT);
}

GLvoid keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a': // 왼쪽 이동
		player.moveLeft();

		if (FIRST_PERSON == cameraMode)
			camera.moveLeft();
		break;
	case 'd': // 오른쪽 이동
		player.moveRight();

		if (FIRST_PERSON == cameraMode)
			camera.moveRight();
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

	case '1':
		cameraMode = FIRST_PERSON;
		camera.setEye(glm::vec3(player.getPos().x,camera.getEye().y, camera.getEye().z));
		break;
	case '3':
		cameraMode = THIRD_PERSON;
		break;
	case 'q':
		exit(-1);
		break;

	case '[':
		if (not ending.end)
			ending.end = true;
		else
			ending.end = false;
		
		player.init();
		//player.setPos(vec3(0, 0, 0));
		camera.setCamera(shaderProgramID, 0, cameraMode, player.getPos());
		ending.initTexture();

		break;
	}

	glutPostRedisplay();
}


void init()
{
	initCamera();

	base.init();
	objects.push_back(&base);

	wall.init();
	objects.push_back(&wall);

	player.init();
	objects.push_back(&player);

	ending.initBuffer();
	ending.initTexture();
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

GLvoid update(int value)
{
	wallUpdate();
	glutTimerFunc(wallUpdateSpeed, update, value);
	glutPostRedisplay();
}

void wallUpdate()
{
	wall.moveWall();
}











