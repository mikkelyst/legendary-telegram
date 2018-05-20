#pragma once

#include <vector>

enum CELL
{
  // we may need to make a class Cell{} perhaps, but for now, just enum
  CELL_ON = 1,
  CELL_OFF = 0
}; 

class Board
{
private:
  std::vector<CELL> cells;
  unsigned int sizex;
  unsigned int sizey;

  CELL CellAt (unsigned int x, unsigned int y)
  {
    return cells.at (sizex * y + x);
  }

  void SetCellAt (unsigned int x, unsigned int y, CELL newState)
  {
    cells.at (sizex * y + x) = newState;
    return;
  }
public:
  Board (unsigned int width, unsigned int height)
  {
    sizex = width;
    sizey = height;
    cells.assign ((sizex*sizey), CELL_OFF);
  }
  Board (Board* previous)
  {
    sizex = previous->sizex;
    sizey = previous->sizey;
    cells = previous->cells;
  } 
  ~Board () = default;
  void RandomState()
  {

  }

  // NeighborsOf(x,y){ return neighbors; }
};

