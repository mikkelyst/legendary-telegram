#pragma once

#include <vector>

enum CellState {
	CELL_ON = 1,
	CELL_OFF = 0
};

class CellGrid
{
private:
	std::vector<CellState> *cells;
	unsigned int sizex;
	unsigned int sizey;

public:

	CellGrid(unsigned int x, unsigned int y)
	{
		sizex = x;
		sizey = y;
		cells = new std::vector<CellState>(x*y);
	}

	~CellGrid() = default;


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
		CellGrid *next = new CellGrid(sizex, sizey);

		// For every cell in grid excluding edges
			// Check Neighborhood, calculate rule
			// Apply rule to cell

		return next;
	}
};

