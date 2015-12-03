#ifndef BOARD_H
#define BOARD_H

class Board
{
public:
	Board();
	Board(const Board& board);
	unsigned& cell(unsigned i, unsigned j);
	void fill(const unsigned board[9][9]);
	void print();
private:
	unsigned _board[9][9];	
};
#endif
