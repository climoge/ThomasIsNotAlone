#ifndef FILE_H_
#define FILE_H_

#include <string.h>

#include "player/Player.h"
#include "level/Level.h"

#include "common.h"

void initialiseFromFile(char *path, ListRectanglePlayer **listPlayers, ListRectangleLevel **listLevel, ListFinalPosition **listPositions);

#endif
