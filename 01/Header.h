#ifndef HEADER_H_
#define HEADER_H_

#include <vector>
#include <windows.h>
#include <string>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

//Screen
static int SCREEN_WIDTH = 960;
static int SCREEN_HEIGHT = 640;
static int RENDER_DRAW_COLOR = 0xff;

//Img
static int COLOR_KEY_R = 167;
static int COLOR_KEY_G = 175;
static int COLOR_KEY_B = 180;

//Menu
const int NUM_SELECTION_MENU = 2;
const int NUM_SELECTION_PAUSE = 3;

//Map
static int TILE_SIZE = 32;

//Player
static int PLAYER_SPEED = 6;
static int GRAVITY_SPEED = 2;
static int MAX_FALL_SPEED = 16;
static int JUMP_PLAYER_VAR = 22;
const int NUM_FRAME_IDLE = 4;
const int NUM_FRAME_MOVE = 6;
const int NUM_FRAME_JUMP = 1;

//FPS
const int FRAME_PER_SECOND = 30;

#endif
