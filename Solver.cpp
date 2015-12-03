#include "Solver.h"
#include <cstdio>

Solver::Solver(const Board& board): _board(board)
{
}

void Solver::print()
{
	_board.print();
}

void Solver::solve()
{
	unsigned solved_cells(0);
	for(unsigned i=0; i<9; ++i)
	{
		for(unsigned j=0; j<9; ++j)
		{
			unsigned cell = _board.cell(i, j);
			if(cell>=1 && cell<=9)
			{
				++solved_cells;
			}
		}
	}

	unsigned current_solved_cells;
	do{
		current_solved_cells = solved_cells;
		_one_cell_check(solved_cells);
		_one_3x3grid_check(solved_cells);
	}while(solved_cells != 81 && current_solved_cells != solved_cells);

	printf("SOLVED!\n");
}

void Solver::_one_cell_check(unsigned& solved_cells)
{
	unsigned current_solved_cells;
	do{
		current_solved_cells = solved_cells;

		for(unsigned i=0; i<9; ++i)
		{
			for(unsigned j=0; j<9; ++j)
			{
				unsigned cell = _board.cell(i, j);
				if(cell == 0)
				{
					std::set<unsigned> numbers;
					for(unsigned k=1; k<=9; ++k)
						numbers.insert(k);

					_check_row(i, numbers);
					_check_column(j, numbers);
					_check_3x3grid(i/3, j/3, numbers);

					if(numbers.size() == 1)
						_board.cell(i, j) = *numbers.begin();
				}
			}
		}

	}while(solved_cells != 81 && current_solved_cells != solved_cells);
}


void Solver::_one_3x3grid_check(unsigned &solved_cells)
{
	unsigned current_solved_cells;
	do{
		current_solved_cells = solved_cells;

		for(unsigned grid_i=0; grid_i<3; ++grid_i)
		{
			for(unsigned grid_j=0; grid_j<3; ++grid_j)
			{
				std::set<unsigned> numbers;
				for(unsigned k=1; k<=9; ++k)
					numbers.insert(k);

				_check_3x3grid(grid_i, grid_j, numbers);

				for(std::set<unsigned>::iterator it = numbers.begin(); it != numbers.end(); ++it)
				{
					unsigned grid_copy[3][3];
					for(unsigned el_i=0; el_i<3; ++el_i)
						for(unsigned el_j=0; el_j<3; ++el_j)
							grid_copy[el_i][el_j] = _board.cell(grid_i*3 + el_i, grid_j*3 + el_j);

					for(unsigned row=0; row<3; ++row)
						if(_is_element_in_row(grid_i*3 + row, *it))
							_delete_row(row, grid_copy);

					for(unsigned column=0; column<3; ++column)
						if(_is_element_in_column(grid_j*3 + column, *it))
							_delete_column(column, grid_copy);

					unsigned number_of_zeros = 0;
					unsigned zero_el_i = 0;
					unsigned zero_el_j = 0 ;
					for(unsigned el_i=0; el_i<3; ++el_i)
					{
						for(unsigned el_j=0; el_j<3; ++el_j)
						{
							if(grid_copy[el_i][el_j] == 0)
							{
								++number_of_zeros;
								zero_el_i = el_i;
								zero_el_j = el_j;
							}
						}
					}

					if(number_of_zeros == 1)
					{
						_board.cell(grid_i*3 + zero_el_i, grid_j*3 + zero_el_j) = *it;
						numbers.erase(*it);
					}
				}
			}
		}

	}while(solved_cells != 81 && current_solved_cells != solved_cells);
}

void Solver::_check_row(unsigned i, std::set<unsigned> &numbers)
{
	for(unsigned j=0; j<9; ++j)
		numbers.erase(_board.cell(i, j));
}

void Solver::_check_column(unsigned j, std::set<unsigned> &numbers)
{
	for(unsigned i=0; i<9; ++i)
		numbers.erase(_board.cell(i, j));
}

void Solver::_check_3x3grid(unsigned grid_i, unsigned grid_j, std::set<unsigned> &numbers)
{
	for(unsigned el_i=0; el_i<3; ++el_i)
		for(unsigned el_j=0; el_j<3; ++el_j)
			numbers.erase(_board.cell(grid_i*3 + el_i, grid_j*3 + el_j));
}

bool Solver::_is_element_in_row(unsigned i, unsigned number)
{
	for(unsigned j=0; j<9; ++j)
		if(_board.cell(i, j) == number)
			return true;

	return false;
}

bool Solver::_is_element_in_column(unsigned j, unsigned number)
{
	for(unsigned i=0; i<9; ++i)
		if(_board.cell(i, j) == number)
			return true;

	return false;
}

void Solver::_delete_row(unsigned row, unsigned grid_copy[3][3])
{
	for(unsigned j=0; j<3; ++j)
		grid_copy[row][j] = -1;
}

void Solver::_delete_column(unsigned column, unsigned grid_copy[3][3])
{
	for(unsigned i=0; i<3; ++i)
		grid_copy[i][column] = -1;
}
