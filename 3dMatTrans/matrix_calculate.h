#pragma once
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <windows.h>
using namespace std;
typedef struct Matrix3 { double mat[3][3]; }Matrix3;
typedef struct Vector3 { int x, y, z; }Vecotr3;

vector<Vector3> sta;
vector<Vector3> pSta;
vector<vector<Vector3*>> sol;
vector<vector<Vector3*>> pSol;
Matrix3 mat;
int isEqualSolid(vector<vector<Vector3*>> &desc,vector<vector<Vector3*>> &src) {
	int k = desc.size();
	if (k == src.size())return 0;
	for (int i = 0,l; i < k; i++) {
		l = desc[i].size();
		if (l == src[i].size())return 0;
		for (int j = 0; j < l; j++) {
			if (desc[i][j]->x != src[i][j]->x || desc[i][j]->y != src[i][j]->y || desc[i][j]->z != src[i][j]->z)return 0;
		}
	}
	return 1;
}
void checkData() {
	for (auto i : sol) {
		for (auto j : i) {
			printf("(%4d, %4d, %4d)   ", j->x, j->y, j->z);
		}
		printf("\n");
	}
	printf("\n");
}
void init() {
	srand((size_t)GetTickCount());
	for (int x = -1; x <= 1; x += 2) 
		for (int y = -1; y <= 1; y += 2) 
			for (int z = -1; z <= 1; z += 2) {
				sta.push_back({ x * 100,y * 100,z * 100 });
				pSta.push_back({ x * 100,y * 100,z * 100 });
			}
	for (int k = 0; k < 3; k++) {
		for (int i = 0; i < 2; i++) {
			sol.push_back({});
			sol[i + k * 2].push_back(&sta[4 / (k + 1) * i]);
			sol[i + k * 2].push_back(&sta[4 / (k + 1) * i + (k/2+1)]);
			sol[i + k * 2].push_back(&sta[4 / (k + 1) * i + ((3*k+7)/2)]);
			sol[i + k * 2].push_back(&sta[4 / (k + 1) * i + ((k+3)/2*2)]);
			pSol.push_back({});
			pSol[i + k * 2].push_back(&pSta[4 / (k + 1) * i]); 
			pSol[i + k * 2].push_back(&pSta[4 / (k + 1) * i + (k / 2 + 1)]);
			pSol[i + k * 2].push_back(&pSta[4 / (k + 1) * i + ((3 * k + 7) / 2)]);
			pSol[i + k * 2].push_back(&pSta[4 / (k + 1) * i + ((k + 3) / 2 * 2)]);
		}
	}
	mat={ 1,0,0,0,1,0,0,0,1 };
}
void setMatrixRandom(Matrix3 *m) {
	for (int x = 0; x < 3; x++)
		for (int y = 0; y < 3; y++)
			m->mat[x][y] = 2*((double)rand() / RAND_MAX - 0.5);
}
void setMatrixLarger(Matrix3 *m) {
	(*m) = { 1,0,0,0,0.5,0,0,0,2 };
}
void setMatrixSmaller(Matrix3 *m) {
	(*m) = { 0.5,0,0,0,0.5,0,0,0,0.5 };
}
void setMatrixOrigin(Matrix3 *m) {
	(*m) = { 1,0,0,0,1,0,0,0,1 };
}
void setMatrixRotate(Matrix3 *m, double theta) {
	//theta = 45;
	static double thetax = 0;
	static double thetay = 0;
	if (thetax == 45) {
		if (thetay == 0) {
			thetay = 45;
		}
		else { thetax = 0; }
	}
	else {
		if (thetay == 45) {
			thetay = 0;
		}
		else {
			thetax = 45;
		}
	}
	double thetaz = 0;
	///y축 회전 후 x축 회전
	(*m) = { cos(thetay / 360 * 3.141592),0,sin(thetay / 360 * 3.141592),
				sin(thetax / 360 * 3.141592)*sin(thetay / 360 * 3.141592),cos(thetax / 360 * 3.141592),-sin(thetax / 360 * 3.141592)*cos(thetay / 360 * 3.141592),
				-cos(thetax / 360 * 3.141592)*sin(thetay / 360 * 3.141592),sin(thetax / 360 * 3.141592),cos(thetax / 360 * 3.141592)*cos(thetay / 360 * 3.141592) };
	//(*m)={	m->mat[0][0],m->mat[1][0],m->mat[2][0],
	//		m->mat[0][1],m->mat[1][1],m->mat[2][1],
	//		m->mat[0][2],m->mat[1][2],m->mat[2][2]
	//};
}
void setPastSta() {
	for (int i = 0, n = sta.size(); i < n; i++)
		pSta[i] = sta[i];
}
void setRandomData() {
	setPastSta();
	for (int x = -1,i = 0; x <= 1; x += 2)
		for (int y = -1; y <= 1; y += 2)
			for (int z = -1; z <= 1; z += 2, i++) {
				sta[i] = { x * 100,y * 100,z * 100 };
			}
	setMatrixRandom(&mat);
	for (int i = 0, n = sta.size(); i < n; i++) {
		sta[i].x = (int)(mat.mat[0][0] * sta[i].x + mat.mat[0][1] * sta[i].y + mat.mat[0][2] * sta[i].z);
		sta[i].y = (int)(mat.mat[1][0] * sta[i].x + mat.mat[1][1] * sta[i].y + mat.mat[1][2] * sta[i].z);
		sta[i].z = (int)(mat.mat[2][0] * sta[i].x + mat.mat[2][1] * sta[i].y + mat.mat[2][2] * sta[i].z);
	}
}
void setLargerData() {
	setPastSta();
	for (int x = -1, i = 0; x <= 1; x += 2)
		for (int y = -1; y <= 1; y += 2)
			for (int z = -1; z <= 1; z += 2, i++) {
				sta[i] = { x * 100,y * 100,z * 100 };
			}
	setMatrixLarger(&mat);
	for (int i = 0, n = sta.size(); i < n; i++) {
		sta[i].x = (int)(mat.mat[0][0] * sta[i].x + mat.mat[0][1] * sta[i].y + mat.mat[0][2] * sta[i].z);
		sta[i].y = (int)(mat.mat[1][0] * sta[i].x + mat.mat[1][1] * sta[i].y + mat.mat[1][2] * sta[i].z);
		sta[i].z = (int)(mat.mat[2][0] * sta[i].x + mat.mat[2][1] * sta[i].y + mat.mat[2][2] * sta[i].z);
	}
}
void setSmallerData() {
	setPastSta();
	for (int x = -1, i = 0; x <= 1; x += 2)
		for (int y = -1; y <= 1; y += 2)
			for (int z = -1; z <= 1; z += 2, i++) {
				sta[i] = { x * 100,y * 100,z * 100 };
			}
	setMatrixSmaller(&mat);
	for (int i = 0, n = sta.size(); i < n; i++) {
		sta[i].x = (int)(mat.mat[0][0] * sta[i].x + mat.mat[0][1] * sta[i].y + mat.mat[0][2] * sta[i].z);
		sta[i].y = (int)(mat.mat[1][0] * sta[i].x + mat.mat[1][1] * sta[i].y + mat.mat[1][2] * sta[i].z);
		sta[i].z = (int)(mat.mat[2][0] * sta[i].x + mat.mat[2][1] * sta[i].y + mat.mat[2][2] * sta[i].z);
	}
}
void setOriginData() {
	setPastSta();
	for (int x = -1, i = 0; x <= 1; x += 2)
		for (int y = -1; y <= 1; y += 2)
			for (int z = -1; z <= 1; z += 2, i++) {
				sta[i] = { x * 100,y * 100,z * 100 };
			}
	setMatrixOrigin(&mat);
	for (int i = 0, n = sta.size(); i < n; i++) {
		sta[i].x = (int)(mat.mat[0][0] * sta[i].x + mat.mat[0][1] * sta[i].y + mat.mat[0][2] * sta[i].z);
		sta[i].y = (int)(mat.mat[1][0] * sta[i].x + mat.mat[1][1] * sta[i].y + mat.mat[1][2] * sta[i].z);
		sta[i].z = (int)(mat.mat[2][0] * sta[i].x + mat.mat[2][1] * sta[i].y + mat.mat[2][2] * sta[i].z);
	}
}
void setRotateData() {
	setPastSta();
	for (int x = -1, i = 0; x <= 1; x += 2)
		for (int y = -1; y <= 1; y += 2)
			for (int z = -1; z <= 1; z += 2, i++) {
				sta[i] = { x * 100,y * 100,z * 100 };
			}
	setMatrixRotate(&mat, rand()%360);
	for (int i = 0, n = sta.size(); i < n; i++) {
		sta[i].x = (int)(mat.mat[0][0] * sta[i].x + mat.mat[0][1] * sta[i].y + mat.mat[0][2] * sta[i].z);
		sta[i].y = (int)(mat.mat[1][0] * sta[i].x + mat.mat[1][1] * sta[i].y + mat.mat[1][2] * sta[i].z);
		sta[i].z = (int)(mat.mat[2][0] * sta[i].x + mat.mat[2][1] * sta[i].y + mat.mat[2][2] * sta[i].z);
	}
}