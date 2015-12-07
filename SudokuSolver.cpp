#include "SudokuSolver.h"
#include "Board.h"
#include "Solver.h"
#include "Reader.h"
#include <cstdio>
#include <string>

int SudokuSolver::main(int argc, char **argv)
{
	if(argc == 1)
	{
		_show_help();
		return 0;
	}

	for(unsigned i=1; i<argc; ++i)
	{
		std::string help_abbreviation = "-h";
		std::string help = "--help";
		if(argv[i] == help || argv[i] == help_abbreviation)
		{
			_show_help();
			return 0;
		}
	}

	int return_value = 0;

	for(unsigned i=1; i<argc; ++i)
	{
		Board board = Reader::read_file(argv[i]);
		Solver solver = Solver(board);
		if(solver.solve())
		{
			printf("%s:\n", argv[i]);
			solver.print();
		}
		else
		{
			printf("%s: malformed sudoku board!\n", argv[i]);
			--return_value;
		}
	}
	return return_value;
}

void SudokuSolver::_show_help()
{
	printf("SudokuSolver 1.0\n\n"\
		"Usage: SudokuSolver [arguments][file]\n\n"\
		"Arguments:\n"\
		"	-h or --help		Show help.\n");
}