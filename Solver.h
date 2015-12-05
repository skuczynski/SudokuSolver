#ifndef SOLVER_H
#define SOLVER_H

#include "Board.h"
#include <set>

class Solver
{
public:
	Solver(const Board& board);
	void print();
	void solve();
private:
	void _one_cell_check(unsigned &solved_cells);
	void _one_3x3grid_check(unsigned &solved_cells);
	void _one_row_check(unsigned &solved_cells);
	void _one_column_check(unsigned &solved_cells);

	void _check_row(unsigned i, std::set<unsigned> &numbers);
	void _check_column(unsigned j, std::set<unsigned> &numbers);
	void _check_3x3grid(unsigned grid_i, unsigned grid_j, std::set<unsigned> &numbers);

	bool _is_element_in_row(unsigned i, unsigned number);
	bool _is_element_in_column(unsigned j, unsigned number);
	bool _is_element_in_3x3grid(unsigned grid_i, unsigned grid_j, unsigned number);
	
	void _delete_row(unsigned row, unsigned grid_copy[3][3]);
	void _delete_column(unsigned column, unsigned grid_copy[3][3]);

	Board _board;	
};

#endif
