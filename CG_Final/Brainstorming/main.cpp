#include <GL/freeglut.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>
#include <Windows.h>
#include <iostream>
#include<random>
#include <MMSystem.h> 
#include "obj.h"

#pragma comment(lib, "msimg32.lib")
#pragma comment(lib, "winmm.lib")
using namespace std;

GLvoid drawScene(GLvoid);
GLvoid KeyBoard(unsigned char, int, int);

random_device gen;
uniform_int_distribution<int> dist(0, 8);//block conflict

GLvoid main(int argc, char* argv[])
{
	PlaySound("inGame.wav", NULL, SND_ASYNC | SND_LOOP);//sound

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Brainstorming");//µÎ³ú Ç®°¡µ¿
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(KeyBoard);
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	cout << "µÎ³ú Ç®°¡µ¿!" << endl;
}

GLvoid KeyBoard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
		break;
	case 'w':
		break;
	case 'e':
		break;
	case 'a':
		break;
	case 's':
		break;
	case 'd':
		break;
	case 'z':
		break;
	case 'x':
		break;
	case 'c':
		break;
	case 'p':
		exit(-1);
		break;
	default:
		break;
	}
	glutPostRedisplay();
}