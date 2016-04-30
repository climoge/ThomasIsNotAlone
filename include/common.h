#ifndef COMMON_H_
#define COMMON_H_

#include <stdlib.h>
#include <stdio.h>

#define GRAVITY -0.9f
#define PLAYER_SPEED 8;

typedef struct ScreenSize{
	int w;
	int h;
}ScreenSize;

typedef struct Menu{
	int id;
	struct Menu* up;
	struct Menu* right;
	struct Menu* down;
	struct Menu* left;
}Menu;

typedef struct Color3f {
	float R;
	float G;
	float B;
}Color3f;

ScreenSize SetScreenSize(int width, int height);
Color3f SetColor(float R, float G, float B);
void SetMenu(Menu *menu, int id, Menu *up, Menu *right, Menu *down, Menu *left);

#endif
