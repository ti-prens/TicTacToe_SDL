#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include <stdbool.h>
#include <stdlib.h>

#define LIG 3
#define COL 3
#define FUL 9
#define NAME_MAX_LEN 20
#define HUMAN 1

#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

#define player1_symbole X
#define player2_symbole O

extern int win_cond[8][3];
extern int best_case_order[9];

typedef enum { OK = 1, NOT_OK = 0, WTF = -1 } err;

typedef enum { X = 0, O = 1, NIET = 45 } marks_t;

typedef enum {
  init = 0,
  running = 1,
  draw = 2,
  win_p1 = 3,
  win_p2 = 4,
  end = 5,
  stop = 6
} game_status_t;

typedef struct player_t {
  char name[NAME_MAX_LEN];

  size_t score[3]; //(win,lose,draw) in this match
  marks_t symbole;
  bool human;
} player_t;

typedef union board_t {
  marks_t board[LIG][COL];
  marks_t BOARD[FUL];
} board_t;

typedef struct game_t {
  board_t B;
  game_status_t status;
  player_t *players[2];
  int round_number;
  int round_current;
  bool turn;
} game_t;

err init_game(game_t *GB);
err init_menu(game_t *GB, game_t *MN);
err delete_game(game_t *GB);
err edit_game_board(board_t *B, board_t *edits);
err edit_player(player_t *player, char *name, marks_t sign, bool human);
err print_game(game_t *GB);
err play_move(game_t *GB, size_t move);
err update_game_state(game_t *GB);
game_status_t check_game_status(board_t *B);
int find_best_move(board_t *B, bool player1_turn);
err reset_board(game_t *GB);
err reset_player_turn(game_t *GB);
err reset_game_status(game_t *GB);
err reset_players_score(game_t *GB);
err reset_round(game_t *GB);
err replay_game(game_t *GB);
err new_round(game_t *GB); 

#endif
