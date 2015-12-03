#include "Board.h"
#include <cstdio>

Board::Board()
{
}

Board::Board(const Board& board)
{
	fill(board._board);
}

unsigned& Board::cell(unsigned i, unsigned j)
{
	return _board[i][j];
}

void Board::fill(const unsigned board[9][9])
{
	for(unsigned i=0; i<9; ++i)
	{
		for(unsigned j=0; j<9; ++j)
		{
			if(board[i][j] >= 1 && board[i][j] <= 9)
				_board[i][j] = board[i][j];
			else
				_board[i][j] = 0;
		}
	}
}

void Board::print()
{
	for(unsigned i=0; i<9; ++i)
	{
		for(unsigned j=0; j<9; ++j)
		{
			if(_board[i][j] >= 1 && _board[i][j] <= 9)
				printf("%u ", _board[i][j]);
			else
				printf("X ");

			if(j == 2 || j == 5)
				printf("|");
		}
		printf("\n");

		if(i == 2 || i == 5)
			printf("— — —  — — —  — — —\n");
	}
}
