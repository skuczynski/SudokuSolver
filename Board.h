#ifndef BOARD_H
#define BOARD_H

class Board
{
public:
	Board();
	Board(const Board& board);
	Board(const unsigned board[9][9]);
	unsigned& cell(unsigned i, unsigned j);
	void print();
private:
	unsigned _board[9][9];
	void _fill(const unsigned board[9][9]);	
};
#endif
