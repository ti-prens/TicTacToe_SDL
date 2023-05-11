#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SDL_MAIN_HANDLED // to use main() without the arguments

#include "SDL2\SDL.h"
#include "SDL2\SDL_image.h"
#include "SDL2\SDL_mixer.h"
#include "SDL2\SDL_ttf.h"

#include "game_model.h"
#include "renderer.h"

typedef  enum  {TITLE, GAME_PLAY, INFO, MENU, WIN, LOSE, DRAW } game_state_t;

bool init_interface();
bool load_interface();
void game_loop();
void kill_everything();

extern SDL_Window *window     ;// = NULL;
extern SDL_Renderer *renderer ;// = NULL;
extern SDL_Texture *texture   ;// = NULL;
extern Mix_Music *music       ;// = NULL;
extern Mix_Chunk *sound       ;// = NULL;
extern game_t GAME_BOARD      ;// = NULL;
extern game_state_t GAME_STATE;


bool init_interface();
bool load_interface();
void game_loop();
void kill_everything();
game_state_t switch_state(game_state_t new_state);
bool dotInBox(int dotx, int doty, int x1, int y1,int x2, int y2 );
void animation_active_scene(game_state_t *GS, game_t * GB);
int valid_move(int posx, int posy);
err clicked_on(game_t *GB, game_state_t *GS, int32_t x,
               int32_t y);

#endif