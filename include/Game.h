#ifndef GAME_H_
#define GAME_H_

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include "common.h"

#include "level/Level.h"
#include "player/Player.h"
#include "physic/Physic.h"
#include "drawer/Drawer.h"
#include "file/File.h"

int startGame(ScreenSize *size, const unsigned int FULL_WIDTH, const unsigned int FULL_HEIGHT);

#endif

