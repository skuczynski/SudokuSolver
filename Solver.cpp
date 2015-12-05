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
		_one_row_check(solved_cells);
		_one_column_check(solved_cells);
	}while(solved_cells != 81 && current_solved_cells != solved_cells);

	if(solved_cells != 81)
	{
		std::set<unsigned> numbers;
		std::pair<unsigned, unsigned> best_cell = _find_best_cell(numbers);

		for(std::set<unsigned>::iterator it = numbers.begin(); it != numbers.end(); ++it)
		{
			Solver recursive_solver(_board);
			recursive_solver._board.cell(best_cell.first, best_cell.second) = *it;
			recursive_solver.solve();
			if(recursive_solver._validate())
			{
				_board = recursive_solver._board;
				break;
			}
		}
	}
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
					{
						_board.cell(i, j) = *numbers.begin();

						++solved_cells;
					}
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

						++solved_cells;
					}
				}
			}
		}
	}while(solved_cells != 81 && current_solved_cells != solved_cells);
}


void Solver::_one_row_check(unsigned &solved_cells)
{
	unsigned current_solved_cells;
	do{
		current_solved_cells = solved_cells;
		for(unsigned i=0; i<9; ++i)
		{
			std::set<unsigned> numbers;
			for(unsigned k=1; k<=9; ++k)
				numbers.insert(k);

			_check_row(i, numbers);

			unsigned row_copy[9];
			for(std::set<unsigned>::iterator it = numbers.begin(); it != numbers.end(); ++it)
			{
				for(unsigned j=0; j<9; ++j)
					row_copy[j] = _board.cell(i, j);

				for(unsigned j=0; j<9; ++j)
					if(_is_element_in_column(j, *it))
						row_copy[j] = -1;

				for(unsigned grid_j=0; grid_j<3; ++grid_j)
				{
					if(_is_element_in_3x3grid(i/3, grid_j, *it))
					{
						row_copy[grid_j*3] = -1;
						row_copy[grid_j*3 + 1] = -1;
						row_copy[grid_j*3 + 2] = -1;
					}
				}
				unsigned number_of_zeros = 0;
				unsigned zero_j = 0;

				for(unsigned j=0; j<9; ++j)
				{
					if(row_copy[j] == 0)
					{
						++number_of_zeros;
						zero_j = j;
					}
				}
				if(number_of_zeros == 1)
				{
					_board.cell(i, zero_j) = *it;

					++solved_cells;
				}
			}
		}
	}while(solved_cells != 81 && current_solved_cells != solved_cells);
}

void Solver::_one_column_check(unsigned &solved_cells)
{
	unsigned current_solved_cells;
	do{
		current_solved_cells = solved_cells;
		for(unsigned j=0; j<9; ++j)
		{
			std::set<unsigned> numbers;
			for(unsigned k=1; k<=9; ++k)
				numbers.insert(k);

			_check_column(j, numbers);

			unsigned column_copy[9];
			for(std::set<unsigned>::iterator it = numbers.begin(); it != numbers.end(); ++it)
			{
				for(unsigned i=0; i<9; ++i)
					column_copy[i] = _board.cell(i, j);

				for(unsigned i=0; i<9; ++i)
					if(_is_element_in_row(i, *it))
						column_copy[i] = -1;

				for(unsigned grid_i=0; grid_i<3; ++grid_i)
				{
					if(_is_element_in_3x3grid(grid_i, j/3, *it))
					{
						column_copy[grid_i*3] = -1;
						column_copy[grid_i*3 + 1] = -1;
						column_copy[grid_i*3 + 2] = -1;
					}
				}
				unsigned number_of_zeros = 0;
				unsigned zero_i = 0;

				for(unsigned i=0; i<9; ++i)
				{
					if(column_copy[i] == 0)
					{
						++number_of_zeros;
						zero_i = i;
					}
				}
				if(number_of_zeros == 1)
				{
					_board.cell(zero_i, j) = *it;

					++solved_cells;
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

bool Solver::_is_element_in_3x3grid(unsigned grid_i, unsigned grid_j, unsigned number)
{
	for(unsigned el_i=0; el_i<3; ++el_i)
		for(unsigned el_j=0; el_j<3; ++el_j)
			if((_board.cell(grid_i*3 + el_i, grid_j*3 + el_j)) == number)
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

bool Solver::_validate()
{
	std::set<unsigned> numbers;
	for(unsigned k=1; k<=9; ++k)
		numbers.insert(k);

	std::set<unsigned> check_numbers;

	for(unsigned i=0; i<9; ++i)
	{
		check_numbers = numbers;
		_check_row(i, check_numbers);
		if(!check_numbers.empty())
			return false;
	}

	for(unsigned j=0; j<9; ++j)
	{
		check_numbers = numbers;
		_check_column(j, check_numbers);
		if(!check_numbers.empty())
			return false;
	}

	for(unsigned grid_i=0; grid_i<3; ++grid_i)
	{
		for(unsigned grid_j=0; grid_j<3; ++grid_j)
		{
			check_numbers = numbers;
			_check_3x3grid(grid_i, grid_j, check_numbers);
			if(!check_numbers.empty())
				return false;
		}
	}
	return true;
}

std::pair<unsigned, unsigned> Solver::_find_best_cell(std::set<unsigned> &numbers)
{
	std::pair<unsigned, unsigned> best_cell_coordinates;
	unsigned best_cell = 9;
	for(unsigned i=0; i<9; ++i)
	{
		for (unsigned j=0; j<9; ++j)
		{
			unsigned cell = _board.cell(i, j);
			if(cell == 0)
			{
				std::set<unsigned> cell_numbers;
				for(unsigned k=1; k<=9; ++k)
					cell_numbers.insert(k);

				_check_row(i, cell_numbers);
				_check_column(j, cell_numbers);
				_check_3x3grid(i/3, j/3, cell_numbers);

				if(cell_numbers.size() < best_cell)
				{
					best_cell = cell_numbers.size();
					best_cell_coordinates.first = i;
					best_cell_coordinates.second = j;
					numbers.clear();
					numbers = cell_numbers;
				}
			}
		}
	}
	return best_cell_coordinates;
}
