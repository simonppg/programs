#ifndef _BOWLING_GAME_H_
#define _BOWLING_GAME_H_

struct Bowling_game_s;
typedef struct Bowling_game_s Bowling_game;

Bowling_game * bowling_game_create();
void bowling_game_destroy(Bowling_game * game);
void bowling_game_roll(Bowling_game * game, int pins);
int bowling_game_score(Bowling_game * game);

#endif
