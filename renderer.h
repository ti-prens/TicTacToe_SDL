#ifndef RENDER_H
#define RENDER_H

#include "SDL2\SDL.h"
#include "SDL2\SDL_image.h"
#include "SDL2\SDL_mixer.h"
#include "SDL2\SDL_ttf.h"
#include <stdio.h>

#include "game_model.h"

#define SCREEN_WIDTH 640.0
#define SCREEN_HEIGHT 480.0


#define but_w 53
#define but_h 46
#define margin 10
#define pading 5



err render_title(SDL_Renderer *ren, SDL_Texture *tex);
err render_menu(SDL_Renderer *ren, SDL_Texture *tex,game_t *GB, TTF_Font *font);
err render_win(SDL_Renderer *ren, SDL_Texture *tex,game_t *GB, TTF_Font *font);
err render_draw(SDL_Renderer *ren, SDL_Texture *tex,game_t *GB, TTF_Font *font);
// err render_info(SDL_Renderer *ren, SDL_Texture *tex,game_t *GB);
err render_game(SDL_Renderer *ren, SDL_Texture *tex, game_t *GB);
err print_to_screen(SDL_Renderer *ren, SDL_Texture *tex, game_t *GB, TTF_Font *font, const char * text);

err draw_move(size_t mv, marks_t sym, SDL_Renderer *ren, SDL_Texture *tex, size_t start);
err draw_BG(SDL_Renderer *ren);
err draw_table(SDL_Renderer *ren, SDL_Texture *tex);
err draw_menu_but(SDL_Renderer *ren, SDL_Texture *tex, bool clicked);
err draw_info(SDL_Renderer *ren, SDL_Texture *tex, bool clicked);
err draw_existing_mv( SDL_Renderer *ren, SDL_Texture *tex,game_t *GB);
err draw_reset(SDL_Renderer *ren, SDL_Texture *tex);
err draw_score(SDL_Renderer *ren, SDL_Texture *tex,game_t *GB);



#endif