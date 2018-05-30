#pragma once

#include <vector>
#include "BoardTexture.h"

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
    return cells.at( cellsX * (y%cellsY) + (x%cellsX) );
  }
  void SetCellAt( unsigned int x, unsigned int y, CELL newState )
  {
    cells.at( cellsX * ( y%cellsY ) + ( x%cellsX ) ) = newState;
    return;
  }
  void Clear( CELL with )
  {
    cells.assign( ( cellsX*cellsY ), with );
  }
  void DrawCellsToImage( BoardTexture2D *image )
  {
    //  update board tex with current cellgrid 
    for ( unsigned int x = 0; x < cellsX; x++ )
    {
      for ( unsigned int y = 0; y < cellsY; y++ )
      {
        switch ( CellAt( x, y ) )
        {
        case CELL_FLOOR: image->SetTexelColor( x, y, color_BLACK ); break;
        case CELL_WALL:  image->SetTexelColor( x, y, color_WHITE ); break;
        case CELL_OTHER: image->SetTexelColor( x, y, color_GREEN ); break;
        default:
          // red cells should never be created if all is well         
          image->SetTexelColor( x, y, color_RED );
          break;
        }
      }
    }
  }

  // NeighborsOf(x,y){ return neighbors; }
};

