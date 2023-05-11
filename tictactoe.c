#include "tictactoe.h"

#define APP_NAME "Drawn TicTacToe"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *texture = NULL;
Mix_Music *music = NULL;
Mix_Chunk *sound = NULL;
TTF_Font *font;

game_t GAME_BOARD = {0};
game_state_t GAME_STATE;

int key_input(SDL_KeyCode code) {
  switch (code) {
  case SDLK_q:
    return 0;
  case SDLK_w:
    return 1;
  case SDLK_e:
    return 2;
  case SDLK_a:
    return 3;
  case SDLK_s:
    return 4;
  case SDLK_d:
    return 5;
  case SDLK_z:
    return 6;
  case SDLK_x:
    return 7;
  case SDLK_c:
    return 8;
  default:
    return NOT_OK;
  }
}

int main() {

  printf("Program succesfully started\n");

  init_game(&GAME_BOARD);
  printf("the default type is : %d \n", GAME_BOARD.players[0]->human);
  init_interface();
  GAME_STATE = switch_state(TITLE);

  game_loop();

  kill_everything();

  return EXIT_SUCCESS;
}

bool init_interface() {

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "Could not initialize sdl2: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  // Initialize SDL_ttf
  if (TTF_Init() < 0) {
    fprintf(stderr, "Error intializing SDL_ttf:  %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  // Load font
  font = TTF_OpenFont("ress/jrhand.ttf", 72);
  if (!font) {
    fprintf(stderr, "Error loading font:  %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  window =
      SDL_CreateWindow(APP_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

  if (window == NULL) {
    fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  SDL_Surface *ico = IMG_Load("ress/ico.png");
  SDL_SetWindowIcon(window, ico);

  renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (renderer == NULL) {
    SDL_DestroyWindow(window);
    fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  // Start sending SDL_TextInput? events
  SDL_StartTextInput();
  return true;
}

void game_loop() {

  SDL_Event e;
  Uint32 start_time = 0, end_time = 0;

  while (GAME_BOARD.status != stop) {

    start_time = SDL_GetTicks();
    end_time = 0;

    while (SDL_PollEvent(&e)) {

      switch (e.type) {
      case SDL_QUIT:
        GAME_BOARD.status = stop;
        break;
      case SDL_MOUSEBUTTONDOWN:
        clicked_on(&GAME_BOARD, &GAME_STATE, e.button.x, e.button.y);
        break;
      case SDL_KEYDOWN:
        if (GAME_STATE == GAME_PLAY) {
          int move = key_input(e.key.keysym.sym);
          if (move < 0) {
            break;
          }
          if (!(GAME_BOARD.players[GAME_BOARD.turn]->human)) {
            printf("you are not a robot ... dumbass ^^ \n");
                    // print_to_screen(renderer, texture ,&GAME_BOARD, font, "you are not a robot ... dumbass ^^") ;

          } else if (GAME_BOARD.status != running &&
                     GAME_BOARD.status != init) {
            printf("reset the game ... dumbass ^^ \n");
            // print_to_screen(renderer, texture ,&GAME_BOARD, font, "reset the game ... dumbass ^^") ;
          } else if (play_move(&GAME_BOARD, move) == OK) {

            draw_move(move, (marks_t) !(GAME_BOARD.turn), renderer, texture, 0);
            update_game_state(&GAME_BOARD);
            printf("after update status is %d \n", GAME_BOARD.status);
            render_game(renderer, texture, &GAME_BOARD);
          }
          if (GAME_BOARD.status == end) {
            SDL_Delay(500);
            if (GAME_BOARD.players[0]->score[0] >
                GAME_BOARD.players[0]->score[1]) { // player 1 won
              GAME_STATE = switch_state(WIN);
            } else if (GAME_BOARD.players[0]->score[0] <
                       GAME_BOARD.players[0]->score[1]) { // player 2 won
              // *GS = switch_state(LOSE);
              GAME_STATE = switch_state(WIN);
              render_win(renderer, texture, &GAME_BOARD, font);

            } else {
              GAME_STATE = switch_state(DRAW);
              render_draw(renderer, texture, &GAME_BOARD, font);
            }
          }
        }

      default: {
      }
      }
    }
    animation_active_scene(&GAME_STATE, &GAME_BOARD);
    end_time = SDL_GetTicks();

    if (end_time - start_time < 30) {
      // printf("%d %d %d \n", start_time, end_time, end_time - start_time);
      SDL_Delay(30 - (end_time - start_time));
    }
    SDL_RenderPresent(renderer);
  }
}

void kill_everything() {

  SDL_StopTextInput();

  TTF_CloseFont(font);
  font = NULL;

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  window = NULL;
  renderer = NULL;

  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

err clicked_on(game_t *GB, game_state_t *GS, int32_t x, int32_t y) {
  printf("cliked detected at %d %d\n", x, y);

  switch (*GS) {
  case TITLE:
    *GS = switch_state(GAME_PLAY);
    render_game(renderer, texture, GB);

    break;

  case GAME_PLAY:

    // go to menu
    if (dotInBox(x, y, 0, 0, margin + pading + but_w,
                 margin + pading + but_h)) {
      *GS = switch_state(MENU);
      render_menu(renderer, texture, GB, font);
      break;
    }

    // reset curent game
    if (dotInBox(x, y, SCREEN_WIDTH - (but_w + margin + pading), 0,
                 SCREEN_WIDTH, but_w + margin + pading)) {
      new_round(GB);
      draw_BG(renderer);
      render_game(renderer, texture, GB);
      printf("BOARD CLEARED \n");
      break;
    }

    // wait for move

    int move = valid_move(x, y);
    if (move < 0) {
      printf("dumbass ^^ \n");
      print_to_screen(renderer, texture ,GB, font, "dumbass ^^" ) ;
    } else {
      if (!(GB->players[GB->turn]->human)) {
        printf("you are not a robot ... dumbass ^^ \n");
        print_to_screen(renderer, texture ,GB, font, "you are not a robot ... dumbass ^^") ;
      } else if (GB->status != running && GB->status != init) {
        printf("reset the game ... dumbass ^^ \n");
        print_to_screen(renderer, texture ,GB, font, "reset the game ... dumbass ^^" ) ;

      } else if (play_move(GB, move) == OK) {

        draw_move(move, (marks_t) !(GB->turn), renderer, texture, 0);
        update_game_state(GB);
        printf("after update status is %d \n", GB->status);
        render_game(renderer, texture, GB);
      }
      if (GB->status == end) {
        SDL_Delay(500);
        if (GB->players[0]->score[0] >
            GB->players[0]->score[1]) { // player 1 won
          *GS = switch_state(WIN);
        } else if (GB->players[0]->score[0] <
                   GB->players[0]->score[1]) { // player 2 won
          // *GS = switch_state(LOSE);
          *GS = switch_state(WIN);
          render_win(renderer, texture, GB, font);

        } else {
          *GS = switch_state(DRAW);
          render_draw(renderer, texture, GB, font);
        }
      }
    }

    break;

  case MENU:;
    static int no_modif = 1;
    int pl = 0;
    // return to game (running or new)
    if (dotInBox(x, y, 0, 0, margin + pading + but_w,
                 margin + pading + but_h)) {

      if (no_modif == 1) {
        *GS = switch_state(GAME_PLAY);
        render_game(renderer, texture, GB);
        draw_existing_mv(renderer, texture, GB);
      } else {
        no_modif = 1;
        replay_game(GB);
        *GS = switch_state(GAME_PLAY);
        render_game(renderer, texture, GB);
        printf("SCORE CLEARED \n");
      }
    }

    // change players nature/type
    if (dotInBox(x, y, 78, 98, 185, 160) || dotInBox(x, y, 80, 380, 182, 444)) {
      no_modif = 0;
      GB->players[0]->human ^= 1;
      render_menu(renderer, texture, GB, font);
    }

    if (dotInBox(x, y, 421, 103, 539, 160) ||
        dotInBox(x, y, 436, 390, 541, 439)) {
      no_modif = 0;
      GB->players[1]->human ^= 1;
      render_menu(renderer, texture, GB, font);
    }

    // change player's name

    if (dotInBox(x, y, 91, 34, 189, 90)) {
      no_modif = 0;
      pl = 1;
    }
    if (dotInBox(x, y, 440, 33, 533, 90)) {
      no_modif = 0;
      pl = 2;
    }
    if (pl > 0) {

      // // Start sending SDL_TextInput events
      // SDL_StartTextInput();
      SDL_Event e;
      int done = 0;
      char new_name[NAME_MAX_LEN] = {0};

      while (GB->status != stop && !done) {

        while (SDL_PollEvent(&e)) {

          switch (e.type) {
          case SDL_QUIT:
            GB->status = stop;
            break;
          case SDL_MOUSEBUTTONDOWN:
            done = 1;
            break;
          case SDL_TEXTINPUT:

            if (strlen(new_name) < NAME_MAX_LEN - 1) {
              strcat(new_name, e.text.text);
            }

            if (strlen(new_name) > 0) {

              // printf("inputed : %s - full name : %s -lenght =
              // %d\n",e.text.text,new_name,strlen(new_name) );
              strncpy_s(GB->players[pl - 1]->name, NAME_MAX_LEN, new_name,
                        strlen(new_name));

              render_menu(renderer, texture, GB, font);
              SDL_RenderPresent(renderer);
              printf("--> inputed : %s - full name : %s - received pl name %s "
                     "-lenght = %lld\n",
                     e.text.text, new_name, GB->players[pl - 1]->name,
                     strlen(new_name));
            }
            break;
          case SDL_KEYDOWN:
            if (e.key.keysym.sym == SDLK_BACKSPACE && strlen(new_name) > 0) {
              new_name[strlen(new_name) - 1] = '\0';
            } else if (e.key.keysym.sym == SDLK_RETURN &&
                       strlen(new_name) > 0) {
              done = 1;
            } else if (e.key.keysym.sym == SDLK_ESCAPE) {
              char player_def_name[NAME_MAX_LEN];
              sprintf(player_def_name, "Player %d", pl);

              strncpy_s(new_name, NAME_MAX_LEN, player_def_name, NAME_MAX_LEN);
              done = 1;
            }
            if (strlen(new_name) > 0) {

              // printf("inputed : %s - full name : %s -lenght =
              // %d\n",e.text.text,new_name,strlen(new_name) );
              strncpy_s(GB->players[pl - 1]->name, NAME_MAX_LEN, new_name,
                        strlen(new_name));

              render_menu(renderer, texture, GB, font);
              SDL_RenderPresent(renderer);
              // printf("--> inputed : %s - full name : %s - received pl name %s
              // "
              //        "-lenght = %lld\n",
              //        e.text.text, new_name, GB->players[pl - 1]->name,
              //        strlen(new_name));
            }
            break;
          default: {
          }
          }
        }
      }
    }

    // edit number of rounds
    else if (dotInBox(x, y, 271, 415, 376, 480)) {
      no_modif = 0;
      GB->round_number = (GB->round_number < 10) ? GB->round_number + 1 : 1;
      render_menu(renderer, texture, GB, font);
    }
    break;

  case WIN:
    replay_game(GB);
    *GS = switch_state(GAME_PLAY);
    render_game(renderer, texture, GB);

    break;

  case LOSE:
    replay_game(GB);
    *GS = switch_state(GAME_PLAY);
    render_game(renderer, texture, GB);

    break;

  case DRAW:
    replay_game(GB);
    *GS = switch_state(GAME_PLAY);
    render_game(renderer, texture, GB);

    break;
  default:
    printf("something went wrong");
  }

  return OK;
}

void animation_active_scene(game_state_t *GS, game_t *GB) {
  switch (*GS) {
  case TITLE:
    render_title(renderer, texture);
    break;
  case WIN:
    render_win(renderer, texture, GB, font);
    break;
  case LOSE:
    break;
  case DRAW:
    render_draw(renderer, texture, GB, font);
    break;
  case GAME_PLAY:
    if (GB->players[GB->turn]->human == 0 && (GB->status == init || GB->status == running )) {
      SDL_Delay(750);
      int move = find_best_move(&(GB->B), GB->turn);
      if (play_move(GB, move) == OK) {
        draw_move(move, (marks_t) !(GB->turn), renderer, texture, 0);
        update_game_state(GB);
        printf("after update status is %d \n", GB->status);
        render_game(renderer, texture, GB);

        if (GB->status == end) {
          SDL_Delay(500);
          if (GB->players[0]->score[0] >
              GB->players[0]->score[1]) { // player 1 won
            *GS = switch_state(WIN);
          } else if (GB->players[0]->score[0] <
                     GB->players[0]->score[1]) { // player 2 won
            // *GS = switch_state(LOSE);
            *GS = switch_state(WIN);
            render_win(renderer, texture, GB, font);

          } else {
            *GS = switch_state(DRAW);
            render_draw(renderer, texture, GB, font);
          }
        }
      }
    }
    break;
  default:
    break;
  }
}

game_state_t switch_state(game_state_t new_state) {
  draw_BG(renderer);
  printf("switched scene to %d\n", new_state);
  return new_state;
}

bool dotInBox(int dotx, int doty, int x1, int y1, int x2, int y2) {
  printf("%d %d %d %d %d %d \n", dotx, doty, x1, y1, x2, y2);
  if (dotx >= x1 && dotx <= x2) {
    if (doty >= y1 && doty <= y2) {
      return true;
    }
  }
  return false;
}

int valid_move(int posx, int posy) {
  int cases[9][4] = {
      {85, 91, 192, 172},  {217, 91, 352, 171},  {372, 89, 510, 162},
      {74, 205, 180, 297}, {206, 195, 351, 281}, {368, 195, 515, 286},
      {67, 328, 170, 399}, {196, 314, 333, 393}, {360, 300, 477, 400}};
  for (int i = 0; i < 9; i++) {
    if (dotInBox(posx, posy, cases[i][0], cases[i][1], cases[i][2],
                 cases[i][3]))
      return i;
  }
  return -1;
}