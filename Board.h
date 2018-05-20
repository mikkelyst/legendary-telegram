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
public:
  unsigned int cellsX;
  unsigned int cellsY;
  Board( unsigned int width, unsigned int height )
  {
    cellsX = width;
    cellsY = height;
    cells.assign( ( cellsX*cellsY ), CELL_OFF );
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
  void RandomState()
  {
    int a = cellsX / 2;
    int b = cellsY / 2;
    SetCellAt( a + 0, b + 2, CELL_ON );
    SetCellAt( a + 1, b + 2, CELL_ON );
    SetCellAt( a + 2, b + 0, CELL_ON );
    SetCellAt( a + 2, b + 1, CELL_ON );
    SetCellAt( a + 2, b + 2, CELL_ON );
  }

  // NeighborsOf(x,y){ return neighbors; }
};

