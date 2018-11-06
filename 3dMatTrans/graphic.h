#pragma once
#include "matrix_calculate.h"	//Included <stdlib.h>,<vector>,<stdio.h>,<windows.h>

#include <GL/glut.h>
#define TIMER 20
#define LOOP 30
int WIDTH = 1024;
int HEIGHT = 768;
int strSeq;
void SetupRC();
void RenderScene(void);
void ChangeSize(int w, int h);
void TimerFunction(int value);
void processNormalKeys(unsigned char key, int x, int y);
void processMouse(int button, int state, int x, int y);
void processMouseActiveMotion(int x, int y);

//Graphical Main
void render(int argc, char* argv[]) {
	init();
	checkData();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Univers Drawing");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutKeyboardFunc(processNormalKeys);
	glutTimerFunc(TIMER, TimerFunction, 1);
	SetupRC();
	glutMouseFunc(processMouse);
	glutMotionFunc(processMouseActiveMotion);
	glutMainLoop();
}
void SetupRC()
{
	//glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	//glEnable(GL_CULL_FACE);
	glClearColor(0, 0, 0, 1.0f);

	glEnable(GL_DEPTH_TEST);

	glDisable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);
}

void RenderScene(void)
{
	// 윈도우를 지정된 색으로 clear한다.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	static int seq = 0;
	// World Transfrom
	//push Drawing Matrix
	glPushMatrix();
	glRotated(45, 0.5, 1, 0.185);
	//glRotated(90, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	if (!strSeq && !isEqualSolid(sol, pSol)) {
		for (int i = 0, sizeI = sol.size(); i < sizeI; i++) {
			glPushMatrix();		//Push Surface Matrix
			glBegin(GL_POLYGON);
			glColor3d((i + 1) / 4, (i + 1) / 2 % 2, (i + 1) % 2);
			for (int j = 0, sizeJ = sol[i].size(); j < sizeJ; j++) {
				glVertex3d(sol[i][j]->x, sol[i][j]->y, sol[i][j]->z);
			}
			glEnd();
			glPopMatrix();		//Pop Surface Matrix
		}
	}
	else {
		//printf("%d\n", seq);
		for (int i = 0, sizeI = sol.size(); i < sizeI; i++) {
			glPushMatrix();		//PushSurfaceMatrix
			glBegin(GL_POLYGON);
			glColor3d((i + 1) / 4, (i + 1) / 2 % 2, (i + 1) % 2);
			for (int j = 0, sizeJ = sol[i].size(); j < sizeJ; j++) {
				double x = (double)(sol[i][j]->x - pSol[i][j]->x) / LOOP*seq + pSol[i][j]->x
					 , y = (double)(sol[i][j]->y - pSol[i][j]->y) / LOOP*seq + pSol[i][j]->y
					 , z = (double)(sol[i][j]->z - pSol[i][j]->z) / LOOP*seq + pSol[i][j]->z
					;
				glVertex3d(x,y,z);
				//printf("(%4.0f, %4.0f, %4.0f)   ", x, y, z);
			}
			//printf("\n");
			glEnd();
			glPopMatrix();
		}
		if (++seq == 30)
			seq = 0, strSeq = 0; 
	}
	//pop Drawing Matrix
	glPopMatrix();
	//Double Buffering
	glutSwapBuffers();
}
void ChangeSize(int w, int h)
{
	GLfloat nRange = 100.0f;
	// h가 0일 때
	if (h == 0)
		h = 1;
	WIDTH = w, HEIGHT = h;
	// 윈도우의 폭과 넓이 설정
	glViewport(0, 0, w, h);

	//원근투영 사용
	GLfloat fAspect;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	fAspect = (float)w / (float)h;
	gluPerspective(60.0, fAspect, 1.0, 3000.0);
	glTranslatef(0.0f, 0.0f, -1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutSwapBuffers();
}
void TimerFunction(int value)
{
	glutPostRedisplay();
	glutTimerFunc(TIMER, TimerFunction, 1);
}
void processNormalKeys(unsigned char key, int x, int y)
{
	if (key == 27)//esc
		exit(0);//프로그램 종료
	if (!strSeq) {
		if (key == '0') {
			strSeq = 1;
			setRandomData();
			printf("%d %d\n", strSeq, !isEqualSolid(sol, pSol));
			checkData();
		}
		else if (key == '1') {
			strSeq = 1;
			setLargerData();
			checkData();
		}
		else if (key == '2') {
			strSeq = 1;
			setSmallerData();
			checkData();
		}
		else if (key == '3') {
			strSeq = 1;
			setOriginData();
			checkData();
		}
		else if (key == '4') {
			strSeq = 1;
			setRotateData();
			checkData();
		}
	}
}
void processMouse(int button, int state, int x, int y)
{

}
void processMouseActiveMotion(int x, int y)
{

}