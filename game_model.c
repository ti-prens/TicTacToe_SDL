#include "game_model.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// win condition table
int win_cond[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6},
                      {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};
int best_case_order[9] = {4, 0, 2, 6, 8, 1, 3, 5, 7};

err init_game(game_t *GB) {

  char player_def_name[NAME_MAX_LEN];

  reset_board(GB);

  marks_t sym = X;
  for (int i = 0; i < 2; i++) {
    GB->players[i] = (player_t *)malloc(sizeof(player_t));
    sprintf(player_def_name, "Player %d", i + 1);
    edit_player(GB->players[i], player_def_name, sym, HUMAN);
    sym = O;
  }
  reset_game_status(GB);
  reset_player_turn(GB);
  GB->round_number = 1;
  GB->round_current = 1;
  return OK;
}
err replay_game(game_t *GB) {
  reset_board(GB);
  reset_player_turn(GB);
  reset_game_status(GB);
  reset_players_score(GB);
  reset_round(GB);
  return OK;
}
err new_round(game_t *GB) {
  reset_board(GB);
  reset_player_turn(GB);
  reset_game_status(GB);
  return OK;
}
err reset_board(game_t *GB) {
  for (int i = 0; i < 9; i++) {
    GB->B.BOARD[i] = NIET;
  }
  return OK;
}

err reset_round(game_t *GB) {

  GB->round_current = 1;

  return OK;
}

err reset_player_turn(game_t *GB) {
  GB->turn = 0;
  return OK;
}

err reset_game_status(game_t *GB) {
  GB->status = init;
  return OK;
}

err reset_players_score(game_t *GB) {
  for (int i = 0; i < 3; i++) {
    GB->players[0]->score[i] = 0;
    GB->players[1]->score[i] = 0;
  }
  return OK;
}

err edit_game_board(board_t *B, board_t *edits) {

  int offset = 0;
  for (int lig = 0; lig < LIG; lig++) {

    for (int col = 0; col < COL; col++) {
      B->board[lig][col] = edits->BOARD[lig + col + offset];
    }
    offset += 2;
  }
  return OK;
}

err print_game(game_t *GB) {

  for (int ligne = 0; ligne < LIG; ligne++) {
    for (int col = 0; col < COL; col++) {
      printf(" %d ", GB->B.board[ligne][col]);
    }
    printf("\n");
  }

  for (int i = 0; i < 10; i++) {
    printf("---");
  }
  printf("\n");
  printf("%s", GB->players[0]->name);
  printf(" ---- | ---- ");
  printf("%s", GB->players[1]->name);
  printf("\n");
  printf("(W -> %lld, L -> %lld, D ->%lld)", GB->players[0]->score[0],
         GB->players[0]->score[1], GB->players[0]->score[2]);
  printf("---");
  printf("(W -> %lld, L -> %lld, D ->%lld)", GB->players[1]->score[0],
         GB->players[1]->score[1], GB->players[1]->score[2]);
  printf("\n");
  printf("\n");

  return OK;
}

err edit_player(player_t *player, char *name, marks_t sign, bool human) {

  char default_name[NAME_MAX_LEN] = "Player U";

  if (name == NULL || strcmp(name, "") == 0) {
    strcpy(player->name, default_name);
  } else {
    strcpy(player->name, name);
  }

  for (int i = 0; i < 3; i++) {
    player->score[i] = 0;
  }

  player->symbole = sign;
  player->human = human;

  return OK;
}

err play_move(game_t *GB, size_t move) {
  if (move >= 9 || GB->B.BOARD[move] != NIET) {
    return NOT_OK;
  }

  GB->B.BOARD[move] = GB->players[GB->turn]->symbole;
  GB->turn ^= 1;
  return OK;
}

err update_game_state(game_t *GB) {

  switch (GB->status) {
  case init:
    GB->status = running;
    break;
  case running:
    GB->status = check_game_status(&(GB->B));
    if (GB->status != running) {
      update_game_state(GB); // update score
      if (GB->round_current < GB->round_number) {
        GB->round_current++;
      } else {
        GB->status = end;
      }
    }
    break;
  case draw:
    GB->players[0]->score[2]++; // +1 draw
    GB->players[1]->score[2]++; // +1 draw
    break;
  case win_p1:
    GB->players[0]->score[0]++; // +1 win
    GB->players[1]->score[1]++; // +1 lose
    break;
  case win_p2:
    GB->players[0]->score[1]++; // +1 lose
    GB->players[1]->score[0]++; // +1 win
    break;

  case end:
  
    break;
  case stop:

    break;
  default:
    return WTF;
  }

  return OK;
}

game_status_t check_game_status(board_t *B) {

  int nt = 0;
  int pl1 = 0;
  int opp = 0;
  int nule = 0;

  // todo: check for a win
  // todo: check for opp win
  // todo: calculate eval (check for most possibility of tictactoe)

  for (int j = 0; j < 8; j++) {
    for (int i = 0; i < 3; i++) {

      if ((B->BOARD[win_cond[j][i]]) == NIET) {
        nt++;
      } else if ((B->BOARD[win_cond[j][i]]) == player1_symbole) {
        pl1++;
      } else {
        opp++;
      }
    }
    if (pl1 == 3) {
      return win_p1;
    } else if (opp == 3) {
      return win_p2;
    }
    nule += nt;
    nt = 0;
    pl1 = 0;
    opp = 0;
  }

  return (nule == 0) ? draw : running;
}

int find_best_move(board_t *B, bool turn) {
  bool player1_turn = !turn;
  marks_t myMark = (marks_t)turn;
  int best_mv = 0;
  board_t tp_B = {0};
  memcpy(&tp_B, B, sizeof(board_t));

  game_status_t tp_status = running;

  // find winning move
  for (best_mv = 0; best_mv < 9; best_mv++) {
    if (tp_B.BOARD[best_mv] == NIET) {
      tp_B.BOARD[best_mv] = (player1_turn) ? player1_symbole : player2_symbole;
      tp_status = check_game_status(&tp_B);
      if (tp_status == win_p1 || tp_status == win_p2) {
        return best_mv;
      }
      tp_B.BOARD[best_mv] = NIET;
    }
  }
  // avoid losing move
  for (best_mv = 0; best_mv < 9; best_mv++) {
    if (tp_B.BOARD[best_mv] == NIET) {
      tp_B.BOARD[best_mv] = (player1_turn) ? player2_symbole : player1_symbole;
      tp_status = check_game_status(&tp_B);
      if (tp_status == win_p2 || tp_status == win_p1) {
        return best_mv;
      }
      tp_B.BOARD[best_mv] = NIET;
    }
  }
  // stop double win
  if ((tp_B.BOARD[0] == !myMark && tp_B.BOARD[8] == !myMark) ||
      (tp_B.BOARD[2] == !myMark && tp_B.BOARD[6] == !myMark) ) {
    for (int i = 5; i < 9; i++) {
      best_mv = best_case_order[i];
      if (tp_B.BOARD[best_mv] == NIET) {
        return best_mv;
      }
    }
  }
  if ((tp_B.BOARD[5] == !myMark && tp_B.BOARD[7] == !myMark) ) {
      best_mv = 8;
      if (tp_B.BOARD[best_mv] == NIET) {
        return best_mv;
      }
  }
  // find best move by hardcoded best cases
  for (int i = 0; i < 9; i++) {
    best_mv = best_case_order[i];
    if (tp_B.BOARD[best_mv] == NIET) {
      return best_mv;
    }
  }
  return WTF;
}