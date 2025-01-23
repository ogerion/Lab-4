#pragma once
#include "./sequence/LinkedListSequence.h"
#include "UnorderedMap.h"
#include <string>
#include <cstdio>
#include <iostream>
#include <UnorderedMapGraph.h>
struct Move
{
    int i;
    int j;
};

class Game
{
private:
    UnorderedMapGraph<std::string> memo;
    
	int size;
    int winCond;
	int ** field;

    std::string getFieldString()
    {
        std::string state;
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                state += std::to_string(field[i][j]);
            }
            state += "\n";
        }
        return state;
    }

    bool neighbours(int c, int r)
    {
        for (int i = c - 1; i <= c + 1;i++)
        {
            for (int j = r - 1; j <= r + 1; j++)
            {
                if (i >= 0 && i < size && j >= 0 && j < size && (i != c || j != r) && field[i][j] !=0)
                {
                    return true;
                }
            }
        }
        return false;
    }

    int checkDirection(int x, int y) {
        char player = field[x][y];

        if (checkCount(x, y, 1, 0, player) ||
            checkCount(x, y, 0, 1, player) ||
            checkCount(x, y, 1, 1, player) ||
            checkCount(x, y, 1, -1, player)
            ) {
            return (player == 2) ? 2 : 1;
        }
        return 0;
    }

    bool checkCount(int x, int y, int dx, int dy, char player) {
        int count = 0;
        for (int i = 0; i < winCond; ++i) {
            int newX = x + i * dx;
            int newY = y + i * dy;
            if (newX >= 0 && newX < size && newY >= 0 && newY < size && field[newX][newY] == player) {
                count++;
            }
            else {
                break;
            }
        }
        return count == winCond;
    }

    float minimax(int depth, bool isMaximizing, std::string prev) {
        int status = checkGameStatus();
        std::string now = getFieldString();
        memo.addVertex(std::string(now));

        if (status == 2) { memo.addEdge(prev, now, 10.0); return 10.0 - depth*10; }
        if (status == 1) { memo.addEdge(prev, now, -100.0); return -100.0 + depth*10; }
        if (status == -1) { memo.addEdge(prev, now, -2.0); return -2.0; }

        if (depth >= 4)
        {
            memo.addEdge(prev, now, 0.0);
            return 0;
        }

        if (isMaximizing)
        {
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    if (field[i][j] == 0 && neighbours(i, j))
                    {
                        field[i][j] = 2;
                        minimax(depth + 1, false, now);
                        field[i][j] = 0;
                    }
                }
            }
        }
        else
        {
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    if (field[i][j] == 0 && neighbours(i, j))
                    {
                        field[i][j] = 1;
                        minimax(depth + 1, true, now);
                        field[i][j] = 0;
                    }
                }
            }
        }
        float res = 0;
        std::vector<std::pair<std::string, float>> result(memo.getNeigbours(now));
        for (int i = 0; i < result.size(); i++)
        {
            res += result[i].second;
        }
        res = res / result.size();
        memo.addEdge(prev, now, res);
        return res;
    
}
public:

	Game(size_t size, int winCond)
	{
		this->size = size;
		this->field = new int * [size];
        this->winCond = winCond;
		for (size_t i = 0; i < size; i++)
		{
			field[i] = new int[size];
			for (size_t j = 0; j < size; j++)
			{
                field[i][j]=0;
			}
		}
        memo = UnorderedMapGraph<std::string>();
	}

	bool makeMove(Move move, int player)
	{
		if (field[move.i][move.j] != 0 || move.i<0 || move.j<0 || move.i >= size || move.j >= size)
		{
			return false;
		}
		field[move.i][move.j] = player;
		return true;
	}

    int checkGameStatus() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (field[i][j] != 0) {
                    int result = checkDirection(i, j);
                    if (result != 0) {
                        return result;
                    }
                }
            }
        }

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (field[i][j] == 0) {
                    return 0;
                }
            }
        }

        return -1; 
    }

    Move findBestMove() 
    {
        Move bestMove = {-1, -1};
        float bestScore = -100000.0;
        std::string now = getFieldString();
        memo.addVertex(now);
        minimax(0, true, now);
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (field[i][j] == 0 && neighbours(i, j))
                {
                    field[i][j] = 2;
                    std::string next = getFieldString();                    
                    float score = memo.getEdgeWeight(now, next);
                    if (score > bestScore)
                    {
                        bestScore = score;
                        bestMove.i = i;
                        bestMove.j = j;
                    }
                    field[i][j] = 0;
                }
            }
        }
        return bestMove;
    }

    int getCell(int i, int j)
    {
        return field[i][j];
    }

    ~Game()
    {
        for (int i = 0; i < size; i++)
        {
            delete[] field[i];
        }
        delete[] field;
    }
};

