#pragma once
#include "./Game.h"
#include <cassert>
#include <iostream>
void testGameBot()
{
	Game game(3,3);
	game.makeMove(Move{0,0},1);
	game.makeMove(Move{ 0,1 }, 1);
	Move move = game.findBestMove();
	assert(move.i == 0);
	assert(move.j == 2);
}