#pragma once

#include <vector>

enum CELL
{
  // we may need to make a class Cell{} perhaps, but for now, just enum
  CELL_FLOOR = 0,
  CELL_WALL = 1,
  CELL_OTHER = 2
  
};

class Board
{
private:
  std::vector<CELL> cells;
public:
  unsigned int cellsX;
  unsigned int cellsY;
  Board( unsigned int width, unsigned int height )
  {
    cellsX = width;
    cellsY = height;
    cells.assign( ( cellsX*cellsY ), CELL_FLOOR );
  }
  Board( Board* other )
  {
    cellsX = other->cellsX;
    cellsY = other->cellsY;
    cells = other->cells; // copy cells from other board
  }
  ~Board() = default;
  CELL CellAt( unsigned int x, unsigned int y )
  {
    return cells.at( cellsX * y + x );
  }
  void SetCellAt( unsigned int x, unsigned int y, CELL newState )
  {
    cells.at( cellsX * y + x ) = newState;
    return;
  }
  

  // NeighborsOf(x,y){ return neighbors; }
};

