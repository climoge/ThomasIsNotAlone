#include "common.h"

ScreenSize SetScreenSize(int width, int height){
	ScreenSize size;
	size.w = width;
	size.h = height;
	return size;
}

Color3f SetColor(float R, float G, float B){
	Color3f color;
	color.R = R;
	color.G = G;
	color.B = B;
	return color;
}

void SetMenu(Menu *menu, int id, Menu *up, Menu *right, Menu *down, Menu *left){
	menu->id = id;
	menu->up = up;
	menu->right = right;
	menu->down = down;
	menu->left = left;
}
