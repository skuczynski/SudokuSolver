#include "Reader.h"
#include <fstream>

Board Reader::read_file(const char* filename)
{
	unsigned board[9][9];
	std::ifstream sudoku_file(filename);

	std::string header;
	for(unsigned i=0; i<5; ++i)
		sudoku_file >> header;

	for(unsigned i=0; i<9; ++i)
		for(unsigned j=0; j<9; ++j)
			sudoku_file >> board[i][j];

	return Board(board);
}