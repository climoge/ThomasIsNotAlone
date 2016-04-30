#ifndef PHYSIC_H_
#define PHYSIC_H_

#include "player/Player.h"

void Gravity(RectanglePlayer *player);

void Moves(ListRectanglePlayer *playerList);

void Jump (RectanglePlayer *player);

int isCollision(float R1X, float R1Y, float R1W, float R1H, float R2X, float R2Y, float R2W, float R2H);

void Collision(RectanglePlayer **playerList, RectangleLevel **colliderList);

#endif
