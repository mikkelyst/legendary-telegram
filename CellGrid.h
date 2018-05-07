#pragma once

#include <vector>

enum CellState {
	CELL_ON = 1,
	CELL_OFF = 0
};

enum Neighborhood5 {
	CELL_ALL_OFF   = 0,
	CELL_NORTH_ON  = 1, 
	CELL_WEST_ON   = 2,
	CELL_MID_ON    = 4,
	CELL_EAST_ON   = 8,
	CELL_SOUTH_ON  = 16
};

class CellGrid
{
private:
	std::vector<CellState> *cells;
	unsigned int sizex;
	unsigned int sizey;

public:

	CellGrid(unsigned int width, unsigned int height)
	{
		sizex = width;
		sizey = height;
		cells = new std::vector<CellState>(sizex*sizey);
	}

	CellGrid(CellGrid* previous)
	{
		sizex = previous->sizex;
		sizey = previous->sizey;
		*cells = *previous->cells;
	}

	~CellGrid() = default;

	CellState CellAt(unsigned int col, unsigned int row) 
	{
		return cells->at(sizex * row + col);
	}


	void ApplyRule(unsigned int rule)
	{
		switch (rule) {
		case 1: 
			// Rule 1 is 0 000 1
			break;
		case 2: 
			// Rule 2 is 0 001 0
			break;
		default: //Error!
		}
	}

	CellGrid* NextStep() 
	{
		CellGrid *next = new CellGrid(this);

		// For every cell in grid excluding edges
			// Check Neighborhood, calculate rule
			// Apply rule to cell

		return next;
	}
};

