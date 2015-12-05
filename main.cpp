#include <cstdio>
#include "Board.h"
#include "Solver.h"
#include "Reader.h"

int main(int arc, char** argv)
{
	Board board = Reader::read_file("test.sdk");
	Solver solver = Solver(board);
	solver.solve();
	solver.print();
	printf("WORKS!\n");
	return 0;
}
