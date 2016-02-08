#include <stdbool.h>
#include <stdlib.h>

#include "bowling_game.h"

enum  { max_rolls = 21 };
struct Bowling_game_s {
	int rolls[max_rolls];
	int current_roll;
};

Bowling_game * bowling_game_create() {
	Bowling_game * game = malloc(sizeof(Bowling_game));
	for (int i=0; i<max_rolls; i++)
		game->rolls[i] = 0;
	game->current_roll = 0;
	return game;
}

void bowling_game_destroy(Bowling_game * game) {
	free(game);
}

void bowling_game_roll(Bowling_game * game, int pins) {
	game->rolls[game->current_roll++] = pins;
}

static bool is_spare(Bowling_game * game, int frame_index) {
	return game->rolls[frame_index] + game->rolls[frame_index+1] == 10;
}

static bool is_strke(Bowling_game * game, int frame_index) {
	return game->rolls[frame_index] == 10;
}

static int strike_score(Bowling_game * game, int frame_index) {
	return 10 + game->rolls[frame_index+1] + game->rolls[frame_index+2];
}

static int spare_score(Bowling_game * game, int frame_index) {
	return 10 + game->rolls[frame_index+2];
}

static int normal_score(Bowling_game * game, int frame_index) {
	return game->rolls[frame_index] + game->rolls[frame_index+1];
}

int bowling_game_score(Bowling_game * game)  {
	int score = 0;
	int frame_index = 0;
	for (int frame=0; frame<10; ++frame) {
		if ( is_strke(game, frame_index) ) {
			score += strike_score(game, frame_index);
			frame_index += 1;
		} else if ( is_spare(game, frame_index) ) {
			score += spare_score(game, frame_index);
			frame_index += 2;
		} else {
			score += normal_score(game, frame_index);
			frame_index += 2;
		}
	}
	return score;
}
