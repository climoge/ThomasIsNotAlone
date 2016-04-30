#ifndef LEVEL_H_
#define LEVEL_H_

#include "common.h"

typedef struct RectangleLevel {
	float width;
	float height;
	float posX;
	float posY;
	struct RectangleLevel *next;
}ListRectangleLevel, RectangleLevel;

ListRectangleLevel *CreateLevelList();

void AddLevel(float width, float height, float posX, float posY, ListRectangleLevel **list);

#endif

