#pragma once

#include <vector>

enum CellState {
  CELL_ON = 1,
  CELL_OFF = 0
};

enum Neighborhood5 {
  ALL_OFF = 0,
  CT = 1, // top cell
  CL = 2, // left cell
  CM = 4, // mid cell, center
  CR = 8, // right cell
  CB = 16 // bottom cell
};

class CellGrid
{
private:
  std::vector<CellState> cells;
  unsigned int sizex;
  unsigned int sizey;

  CellState CellAt(unsigned int x, unsigned int y)
  {
    return cells.at(sizex * y + x);
  }

  void SetCellAt(unsigned int x, unsigned int y, CellState newState)
  {
    cells.at(sizex * y + x) = newState;
    return;
  }

  CellState ApplyRule(unsigned int rule)
  {
    switch (rule) {
    case ALL_OFF:		return CELL_OFF; // Rule Zero: all cells are dead

    case CT:			return CELL_OFF;
    case CL:			return CELL_ON;
    case CM:			return CELL_OFF;
    case CR:			return CELL_OFF;
    case CB:			return CELL_ON;

    default:			return CELL_OFF;
    }
  }

public:

  CellGrid(unsigned int width, unsigned int height)
  {
    sizex = width;
    sizey = height;
    cells.assign((sizex*sizey), CELL_OFF);
  }

  CellGrid(CellGrid* previous)
  {
    sizex = previous->sizex;
    sizey = previous->sizey;
    cells = previous->cells;
  }

  ~CellGrid() = default;

  CellGrid* NextStep()
  {
    CellGrid* nextGridState = new CellGrid(this);

    // For every cell in grid excluding edges
        // Check Neighborhood, calculate rule value
        // Apply rule to cell
    unsigned int neighbors = CT | CB | CT | CM;
    unsigned int test = CL;
    nextGridState->SetCellAt(2, 3, ApplyRule(test));

    return nextGridState;
  }
};

