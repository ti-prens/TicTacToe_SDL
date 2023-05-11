#include "renderer.h"


const char *table_path[3] = {"ress/game1.png", "ress/game2.png",
                             "ress/game3.png"};

void fill_rect(SDL_Rect *rect, int x, int y, int w, int h) {
  rect->x = x;
  rect->y = y;
  rect->w = w;
  rect->h = h;
}

err render_title(SDL_Renderer *ren, SDL_Texture *tex) {
  static int i = 0;
  char gif_dogo[100] = {0};

  /* Direct the draw commands to the target texture. */
  SDL_SetRenderTarget(ren, tex);

  sprintf(gif_dogo, "ress/gifs/title/frame_%03d.png", i);
  i = (i < 96) ? i + 1 : 0;
  SDL_Surface *gif = IMG_Load(gif_dogo);
  SDL_Texture *texture1 = SDL_CreateTextureFromSurface(ren, gif);
  /* Let's copy the other textures onto the target texture. */
  SDL_RenderCopy(ren, texture1, NULL, NULL);

  SDL_Surface *xoxo = IMG_Load("ress/xoxo.png");
  SDL_Texture *texture2 = SDL_CreateTextureFromSurface(ren, xoxo);
  /* Let's copy the other textures onto the target texture. */
  SDL_RenderCopy(ren, texture2, NULL, NULL);

  SDL_Surface *title = IMG_Load("ress/titile1.png");
  SDL_Texture *texture3 = SDL_CreateTextureFromSurface(ren, title);
  /* Let's copy the other textures onto the target texture. */
  SDL_RenderCopy(ren, texture3, NULL, NULL);

  /* Resetting to the default render target which is the frame buffer
     that gets displayed on screen. */
  SDL_SetRenderTarget(ren, NULL);

  return OK;
}


err print_to_screen(SDL_Renderer *ren, SDL_Texture *tex, game_t *GB, TTF_Font *font, const char * text) {

  SDL_Rect Rect_box;
  SDL_Color color = {0,0,0,255};
  /* Direct the draw commands to the target texture. */
  SDL_SetRenderTarget(ren, tex);
 
  fill_rect(&Rect_box, 105, 15,420 , but_h);
  SDL_SetRenderDrawColor(ren,255,255,255,255);
  SDL_RenderDrawRect(ren,&Rect_box);
  color.r = 0;color.b = 0;color.g = 0;color.a = 255; //white

  SDL_Surface *textSurf = TTF_RenderText_Solid( font, text, color );
  SDL_Texture *texture3 = SDL_CreateTextureFromSurface(ren, textSurf);
  /* Let's copy the other textures onto the target texture. */
  int max = (20*strlen(text) > 420) ? 420:20*strlen(text);
  fill_rect(&Rect_box, 105, 15,max , but_h);
  SDL_RenderCopy(ren, texture3, NULL, &Rect_box);
  /* Resetting to the default render target which is the frame buffer
     that gets displayed on screen. */
  SDL_SetRenderTarget(ren, NULL);

  return OK;
}

err render_win(SDL_Renderer *ren, SDL_Texture *tex, game_t *GB, TTF_Font *font) {
  static int i  = 0;
  char gif_path[100] = {0};
  SDL_Rect Rect_name_box;
  

  /* Direct the draw commands to the target texture. */
  SDL_SetRenderTarget(ren, tex);

  sprintf(gif_path, "ress/gifs/win/2/frame_%03d.png", i);
  i = (i < 166) ? i + 1 : 0;
  SDL_Surface *gif = IMG_Load(gif_path);
  SDL_Texture *texture1 = SDL_CreateTextureFromSurface(ren, gif);
  /* Let's copy the other textures onto the target texture. */
  SDL_RenderCopy(ren, texture1, NULL, NULL);

  SDL_Color color = { 0, 0, 0, 255 }; //black
  int k = ( GB->players[0]->score[0] > GB->players[1]->score[0] ) ? 0:1;

  SDL_Surface* winning_player = TTF_RenderText_Solid( font, GB->players[k]->name, color );
  SDL_Texture *texture2 = SDL_CreateTextureFromSurface(ren, winning_player);
  /* Let's copy the other textures onto the target texture. */
  fill_rect(&Rect_name_box, 65, 39, 230, 60);
  SDL_RenderCopyEx(ren, texture2, NULL, &Rect_name_box, -25,NULL,SDL_FLIP_NONE);

  color.r = 255;color.b = 255;color.g = 255;color.a = 255; //white
  winning_player = TTF_RenderText_Solid( font, GB->players[k]->name, color );
  texture2 = SDL_CreateTextureFromSurface(ren, winning_player);
  /* Let's copy the other textures onto the target texture. */
  fill_rect(&Rect_name_box, 65, 39, 240, 70);
  SDL_RenderCopyEx(ren, texture2, NULL, &Rect_name_box, -25,NULL,SDL_FLIP_NONE);

  SDL_Surface* won_text = TTF_RenderText_Solid( font, "WON", color );
  SDL_Texture *texture3 = SDL_CreateTextureFromSurface(ren, won_text);
  fill_rect(&Rect_name_box, 241, 176, 100, but_h);
  SDL_RenderCopy(ren, texture3, NULL, &Rect_name_box);

  SDL_Surface *replay = TTF_RenderText_Solid( font, "click to replay", color );
  SDL_Texture *texture4 = SDL_CreateTextureFromSurface(ren, replay);
  /* Let's copy the other textures onto the target texture. */
  fill_rect(&Rect_name_box, 236, 430, 160, but_h);
  SDL_RenderCopy(ren, texture4, NULL, &Rect_name_box);

  /* Resetting to the default render target which is the frame buffer
     that gets displayed on screen. */
  SDL_SetRenderTarget(ren, NULL);

  return OK;
}


err render_draw(SDL_Renderer *ren, SDL_Texture *tex, game_t *GB, TTF_Font *font) {
  static int i = 0;
  char gif_path[100] = {0};
  SDL_Rect Rect_box;

  /* Direct the draw commands to the target texture. */
  SDL_SetRenderTarget(ren, tex);

  sprintf(gif_path, "ress/gifs/draw/1/frame_%03d.png", i);
  i = (i < 34) ? i + 1 : 0;
  SDL_Surface *gif = IMG_Load(gif_path);
  SDL_Texture *texture1 = SDL_CreateTextureFromSurface(ren, gif);
  /* Let's copy the other textures onto the target texture. */
  SDL_RenderCopy(ren, texture1, NULL, NULL);

  SDL_Color color = { 255, 255, 255, 255 }; //white
  SDL_Surface *replay = TTF_RenderText_Solid( font, "click to replay", color );
  SDL_Texture *texture3 = SDL_CreateTextureFromSurface(ren, replay);
  /* Let's copy the other textures onto the target texture. */
  fill_rect(&Rect_box, 236, 14, 160, but_h);
  SDL_RenderCopy(ren, texture3, NULL, &Rect_box);

  /* Resetting to the default render target which is the frame buffer
     that gets displayed on screen. */
  SDL_SetRenderTarget(ren, NULL);

  return OK;
}

err render_menu(SDL_Renderer *ren, SDL_Texture *tex, game_t *GB, TTF_Font *font) {

  int pos_player[2][2] = {{45, 165}, {390, 150}};

  SDL_Rect player1, player2;
  fill_rect(&player1, pos_player[0][0], pos_player[0][1], 200, 200);
  fill_rect(&player2, pos_player[1][0], pos_player[1][1], 200, 200);

  SDL_Rect arrow[4];
  fill_rect(&arrow[0], 80, 100, 100, 60);
  fill_rect(&arrow[1], 84, 387, 100, 60);
  fill_rect(&arrow[2], 440, 100, 100, 60);
  fill_rect(&arrow[3], 442, 387, 100, 60);


  SDL_Rect Rect_menu_but;
  fill_rect(&Rect_menu_but, margin, margin, but_w, but_h);

  SDL_Rect Rect_name_box;
  fill_rect(&Rect_name_box, margin, margin, but_w, but_h);


  SDL_Surface *BaGr = IMG_Load("ress/chose_1bl.png");
  SDL_Surface *arr = IMG_Load("ress/arrow_bare.png");
  SDL_Surface *hooman = IMG_Load("ress/human_face.png");
  SDL_Surface *robot = IMG_Load("ress/robot_face.png");
  SDL_Surface *back = IMG_Load("ress/menu_ok.png");

  SDL_Color color = { 0, 0, 0, 255 }; //black
  SDL_Surface* player1_name = TTF_RenderText_Solid( font, GB->players[0]->name, color );
  SDL_Surface* player2_name = TTF_RenderText_Solid( font, GB->players[1]->name, color );

  SDL_Surface* bstof = TTF_RenderText_Solid( font, "best of", color );
  char rounds[10];
  sprintf(rounds,"%d",GB->round_number);
  SDL_Surface* nbrRounds = TTF_RenderText_Solid( font, rounds, color );

  SDL_Texture *texture0 = SDL_CreateTextureFromSurface(ren, BaGr);
  SDL_Texture *texture1 = SDL_CreateTextureFromSurface(ren, hooman);
  SDL_Texture *texture2 = SDL_CreateTextureFromSurface(ren, robot);
  SDL_Texture *texture3 = SDL_CreateTextureFromSurface(ren, arr);
  SDL_Texture *texture4 = SDL_CreateTextureFromSurface(ren, back);
  SDL_Texture *texture5 = SDL_CreateTextureFromSurface(ren, player1_name);
  SDL_Texture *texture6 = SDL_CreateTextureFromSurface(ren, player2_name);

  SDL_Texture *texture7 = SDL_CreateTextureFromSurface(ren, bstof);
  SDL_Texture *texture8 = SDL_CreateTextureFromSurface(ren, nbrRounds);
  
  /* Direct the draw commands to the target texture. */
  SDL_SetRenderTarget(ren, tex);

  SDL_SetRenderDrawColor(ren, 255, 255, 255, 255); // set white opaq
  SDL_RenderClear(ren);                            // clear with white

  /* Let's copy the other textures onto the target texture. */
  SDL_RenderCopy(ren, texture0, NULL, NULL);

  if (GB->players[0]->human) {
    SDL_RenderCopy(ren, texture1, NULL, &player1);
  } else {
    SDL_RenderCopy(ren, texture2, NULL, &player1);
  }

  if (GB->players[1]->human) {
    SDL_RenderCopy(ren, texture1, NULL, &player2);
  } else {
    SDL_RenderCopy(ren, texture2, NULL, &player2);
  }

  SDL_RenderCopy(ren, texture3, NULL, &arrow[0]);
  SDL_RenderCopyEx(ren, texture3, NULL, &arrow[1], 180, NULL, SDL_FLIP_NONE);
  SDL_RenderCopyEx(ren, texture3, NULL, &arrow[2], 0, NULL, SDL_FLIP_NONE);
  SDL_RenderCopyEx(ren, texture3, NULL, &arrow[3], 180, NULL, SDL_FLIP_NONE);

  SDL_RenderCopy(ren, texture4, NULL, &Rect_menu_but);


  fill_rect(&Rect_name_box, 90, 15, 120, but_h * 2);
  SDL_RenderCopy(ren, texture5, NULL, &Rect_name_box);

  fill_rect(&Rect_name_box, 435, 15, 120, but_h * 2);
  SDL_RenderCopy(ren, texture6, NULL, &Rect_name_box);


  fill_rect(&Rect_name_box, 269, 432, sizeof( "best of") *margin, but_h);
  SDL_RenderCopy(ren, texture7, NULL, &Rect_name_box);

  fill_rect(&Rect_name_box, 351, 380, margin *3 , but_h *3);
  SDL_RenderCopy(ren, texture8, NULL, &Rect_name_box);


  
  /* Resetting to the default render target which is the frame buffer
       that gets displayed on screen. */
  SDL_SetRenderTarget(ren, NULL);

  return OK;
}

err render_game(SDL_Renderer *ren, SDL_Texture *tex, game_t *GB) {

  draw_table(ren, tex);
  draw_menu_but(ren, tex, 0);
  draw_reset(ren, tex);
  draw_score(ren,tex,GB);
  
  //draw_info(ren, tex, 0);

  // Read the contents of the texture into a buffer
  // Uint32* pixels = malloc(SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
  // SDL_RenderReadPixels(ren, NULL, SDL_PIXELFORMAT_RGBA8888, pixels,
  // SCREEN_WIDTH * sizeof(Uint32));
  return OK;
}


err draw_existing_mv( SDL_Renderer *ren, SDL_Texture *tex,game_t *GB){
  for (int i =0; i < 9; i++) {
    if(GB->B.BOARD[i] == X){
      draw_move(i, X,ren, tex, 9);
      printf("je reconnais un coup : mv %d - %d \n",i,GB->B.BOARD[i]);
    }else  if(GB->B.BOARD[i] == O){
      draw_move(i, O,ren, tex, 9);
      printf("je reconnais un coup : mv %d - %d \n",i,GB->B.BOARD[i]);
    }
    
  }
  return OK;
}

err draw_BG(SDL_Renderer *ren) {

  SDL_SetRenderDrawColor(ren, 255, 255, 255, 255); // set white opaq
  SDL_RenderClear(ren);                            // clear with white
  SDL_RenderPresent(ren);

  return OK;
}

err draw_table(SDL_Renderer *ren, SDL_Texture *tex) {

  // int i = rand() % 3;
  int i = 0;
  SDL_Surface *BG_surf = IMG_Load(table_path[i]);

  SDL_Texture *texture1 = SDL_CreateTextureFromSurface(ren, BG_surf);

  /* Direct the draw commands to the target texture. */
  SDL_SetRenderTarget(ren, tex);

  /* Let's copy the other textures onto the target texture. */
  SDL_RenderCopy(ren, texture1, NULL, NULL);
  SDL_SetRenderTarget(ren, NULL);

  SDL_RenderPresent(ren);
  return OK;
}

err draw_move(size_t mv, marks_t sym, SDL_Renderer *ren, SDL_Texture *tex, size_t start) {

  char symbole[2] = {'X', 'O'};
  char asset[100] = {0};
  int pos[9][2] = {{100, 95}, {246, 100}, {398, 90},  
                   {103, 211}, {249, 205}, {398, 206},
                   {96, 341}, {228, 325}, {392, 310}};

  SDL_Rect rect;
  rect.x = pos[mv][0];
  rect.y = pos[mv][1];
  rect.h = 80;
  rect.w = 80;


  int i = 0;
  for (i = (start <= 9) ? start:0; i <= 10; i++) {
    sprintf(asset, "ress/%c%d.png", symbole[sym], i);
    SDL_Surface *play = IMG_Load(asset);
    SDL_Texture *texture1 = SDL_CreateTextureFromSurface(ren, play);
    /* Let's copy the other textures onto the target texture. */
    SDL_RenderCopy(ren, texture1, NULL, &rect);

    /* Resetting to the default render target which is the frame buffer
       that gets displayed on screen. */
    SDL_SetRenderTarget(ren, NULL);
    SDL_RenderPresent(ren);
    SDL_Delay(50);
  }

  return OK;
}

err draw_menu_but(SDL_Renderer *ren, SDL_Texture *tex, bool clicked) {

  SDL_Rect Rect_menu_but;
  Rect_menu_but.x = margin;
  Rect_menu_but.y = margin;
  Rect_menu_but.w = but_w;
  Rect_menu_but.h = but_h;

  SDL_Surface *menu_icon;

  if (clicked) {
    menu_icon = IMG_Load("ress/menu_clicked.png");
  } else {
    menu_icon = IMG_Load("ress/menu.png");
  }

  SDL_Texture *texture1 = SDL_CreateTextureFromSurface(ren, menu_icon);

  /* Direct the draw commands to the target texture. */
  SDL_SetRenderTarget(ren, tex);
  /* Let's copy the other textures onto the target texture. */
  SDL_RenderCopy(ren, texture1, NULL, &Rect_menu_but);

  /* Resetting to the default render target which is the frame buffer
       that gets displayed on screen. */
  SDL_SetRenderTarget(ren, NULL);

  SDL_RenderPresent(ren);
  return OK;
}

err draw_info(SDL_Renderer *ren, SDL_Texture *tex, bool clicked) {

  SDL_Rect Rect_info_but;

  Rect_info_but.x = SCREEN_WIDTH - but_w - margin;
  Rect_info_but.y = margin;
  Rect_info_but.w = but_w;
  Rect_info_but.h = but_h;

  SDL_Surface *info_icon;

  if (clicked) {
    info_icon = IMG_Load("ress/info_clicked_1.png");
  } else {
    info_icon = IMG_Load("ress/info_min.png");
  }

  SDL_Texture *texture1 = SDL_CreateTextureFromSurface(ren, info_icon);

  /* Direct the draw commands to the target texture. */
  SDL_SetRenderTarget(ren, tex);
  /* Let's copy the other textures onto the target texture. */
  SDL_RenderCopy(ren, texture1, NULL, &Rect_info_but);

  /* Resetting to the default render target which is the frame buffer
       that gets displayed on screen. */
  SDL_SetRenderTarget(ren, NULL);

  SDL_RenderPresent(ren);
  return OK;
}


err draw_reset(SDL_Renderer *ren, SDL_Texture *tex) {

  SDL_Rect Rect_reset_but;
  fill_rect(&Rect_reset_but,SCREEN_WIDTH - but_w - pading, margin,but_w ,but_h);


  SDL_Surface *reset_icon;
  
  reset_icon = IMG_Load("ress/restart.png");


  SDL_Texture *texture1 = SDL_CreateTextureFromSurface(ren, reset_icon);

  /* Direct the draw commands to the target texture. */
  SDL_SetRenderTarget(ren, tex);
  /* Let's copy the other textures onto the target texture. */
  SDL_RenderCopy(ren, texture1, NULL, &Rect_reset_but);

  /* Resetting to the default render target which is the frame buffer
       that gets displayed on screen. */
  SDL_SetRenderTarget(ren, NULL);

  SDL_RenderPresent(ren);

  return OK;
}


err draw_score(SDL_Renderer *ren, SDL_Texture *tex,game_t *GB){

  SDL_Rect Rect_score;

  SDL_Surface *bar_slim;
  
  bar_slim = IMG_Load("ress/bar_slim.png");


  SDL_Texture *texture1 = SDL_CreateTextureFromSurface(ren, bar_slim);

  /* Direct the draw commands to the target texture. */
  SDL_SetRenderTarget(ren, tex);
  /* Let's copy the other textures onto the target texture. */
  for(size_t i = 1;i<=GB->players[0]->score[0];i++){
    if(i == 5 ){
      fill_rect(&Rect_score,47 , 423,10 , 65);
      SDL_RenderCopyEx(ren, texture1, NULL, &Rect_score, 135, NULL, SDL_FLIP_NONE);
    }else if (i == 10){
      fill_rect(&Rect_score,98 , 423,10 ,67);
      SDL_RenderCopyEx(ren, texture1, NULL, &Rect_score, 135, NULL, SDL_FLIP_NONE);
    }else{
      fill_rect(&Rect_score,30 + 10 * (i-1), 433,10 ,40);
      SDL_RenderCopy(ren, texture1, NULL, &Rect_score);
    }
    
    
  }


  for(size_t i = 1;i<=GB->players[1]->score[0];i++){
    if(i == 5 ){
      fill_rect(&Rect_score,488 , 423,10 ,64);
      SDL_RenderCopyEx(ren, texture1, NULL, &Rect_score, 135, NULL, SDL_FLIP_NONE);
    }else if (i == 10){
      fill_rect(&Rect_score,540 , 423,10 ,68);
      SDL_RenderCopyEx(ren, texture1, NULL, &Rect_score, 135, NULL, SDL_FLIP_NONE);
    }else{
      fill_rect(&Rect_score,469 + 10 * (i-1), 433,10 ,40);
      SDL_RenderCopy(ren, texture1, NULL, &Rect_score);
    }
    
    
  }


  /* Resetting to the default render target which is the frame buffer
       that gets displayed on screen. */
  SDL_SetRenderTarget(ren, NULL);

  SDL_RenderPresent(ren);
  return OK;


}