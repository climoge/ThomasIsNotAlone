#ifndef DRAWER_H_
#define DRAWER_H_

#define CAM_SPEED 20

#include <GL/gl.h>
#include <GL/glu.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "common.h"
#include "level/Level.h"
#include "player/Player.h"

typedef struct ListRectangle {
	ListRectangleLevel *level;
	ListRectanglePlayer *players;
}ListRectangle;

typedef struct CamPosition {
	float X;
	float Y;
} CamPosition;

void DrawMenu(ScreenSize *size, const unsigned int WIN_WIDTH, const unsigned int WIN_HEIGHT, const unsigned int FULL_WIDTH, const unsigned int FULL_HEIGHT, Menu *currentMenu, int menuState);

void DrawSquare(int filled);

void DrawTriangle();

void DrawRectangle(float width, float height, int filled);

ListRectangle *MergeListRectangle(ListRectangleLevel *listLevel, ListRectanglePlayer *listPlayer);

void DrawScene(ListRectangle *list, RectanglePlayer *currentPlayer, ListFinalPosition *listPositions);

void cameraPosition(CamPosition *actualPos, ScreenSize *size, float X, float Y, float angle);

void drawHUD(ScreenSize *size, ListRectanglePlayer *listPlayers, RectanglePlayer *focus);

#endif

