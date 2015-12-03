#include <cstdio>
#include "Board.h"
#include "Solver.h"

int main(int arc, char** argv)
{
/*	unsigned test_board[9][9] = {{1,2,3,4,5,6,7,8,9},
								{4,5,6,7,8,9,1,2,3},
								{7,8,9,1,2,3,4,5,6},
								{2,3,4,5,6,7,8,9,1},
								{5,6,7,8,9,1,2,3,4},
								{8,9,1,2,3,4,5,6,7},
								{3,4,5,6,7,8,9,1,2},
								{6,7,8,9,1,2,3,4,5},
								{9,1,2,3,4,5,6,7,8}};*/

	unsigned test_board[9][9] = {{0,0,0,0,0,8,5,0,0},
								{0,0,0,2,7,0,0,0,0},
								{0,0,6,5,0,0,1,0,0},
								{3,0,0,0,0,0,4,5,0},
								{5,0,7,0,2,0,9,0,1},
								{0,8,4,0,0,0,0,0,7},
								{0,0,8,0,0,4,3,0,0},
								{0,0,0,0,1,7,0,0,0},
								{0,0,1,9,0,0,0,0,0}};
	Board board; 
	board.fill(test_board);
	Solver solver = Solver(board);
	solver.print();
	solver.solve();
	solver.print();
	printf("WORKS!\n");
	return 0;
}