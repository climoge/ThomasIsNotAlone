#ifndef PLAYER_H_
#define PLAYER_H_

#include <math.h>

#include "level/Level.h"
#include "common.h"

typedef struct RectanglePlayer {
	int id;
	Color3f color;
	/*int weight;*/
	int colTop;
	int colBottom;
	int colLeft;
	int colRight;
	struct RectanglePlayer *belowPlayer;
	int isFinalPosition;
	/*int splittable;
	int inv_gravity;*/
	float width;
	float height;
	float posX;
	float posY;
	float highJump;
	float speedX;
	float speedY;
	struct RectanglePlayer *next;
}RectanglePlayer, ListRectanglePlayer;

typedef struct FinalPosition {
	int id;
	float width;
	float height;
	float posX;
	float posY;
	struct FinalPosition *next;
}FinalPosition, ListFinalPosition;

ListRectanglePlayer *CreatePlayerList();
ListFinalPosition *CreatePositionList();
void AddPlayer(int id, Color3f color, float width, float height, float posX, float posY, float highJump, ListRectanglePlayer **list);
void AddFinalPosition(RectanglePlayer *player, float posX, float posY, ListFinalPosition **list);
int isPositionCollision(RectanglePlayer *player, FinalPosition *position);
void onFinalPosition(ListRectanglePlayer **listPlayers, ListFinalPosition *listPositions);
int isLevelComplete(ListRectanglePlayer *listPlayers);
#endif
