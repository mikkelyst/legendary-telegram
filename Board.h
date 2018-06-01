#pragma once

#include <vector>
#include "SimpleTexture.h"

enum CELL_t
{
  // TODO: we may need to make a class Cell{} perhaps, but for now, just enum
  CELL_FLOOR = 0,
  CELL_WALL = 1,
  CELL_OTHER = 2,
  CELL_MARK = 7
};

class Board
{
private:
  std::vector<CELL_t> cells;
  bool IsMarked( unsigned x, unsigned y )
  {
    int s = Neighbors4_Sum( x, y );
    return ( s == 2 || s == 3 );
  }
public:
  bool isMarkingEnabled = true;
  unsigned int cellsX;
  unsigned int cellsY;
  Board( unsigned int width, unsigned int height )
  {
    cellsX = width;
    cellsY = height;
    cells.assign( ( cellsX*cellsY ), CELL_FLOOR );
  }
  Board( Board* copyFrom )
  {
    cellsX = copyFrom->cellsX;
    cellsY = copyFrom->cellsY;
    cells = copyFrom->cells; // copy cells from other board
  }
  ~Board() = default;
  CELL_t CellAt( unsigned int x, unsigned int y )
  {
    return cells.at( cellsX * ( y%cellsY ) + ( x%cellsX ) );
  }
  void SetCellAt( unsigned int x, unsigned int y, CELL_t newState )
  {
    cells.at( cellsX * ( y%cellsY ) + ( x%cellsX ) ) = newState;
    return;
  }
  void Clear( CELL_t with )
  {
    cells.assign( ( cellsX*cellsY ), with );
  }
  void DrawCellsToImage( SimpleTexture2D *image )
  {
    //  update board tex with current cellgrid 
    for ( unsigned int x = 0; x < cellsX; x++ )
    {
      for ( unsigned int y = 0; y < cellsY; y++ )
      {
        if ( isMarkingEnabled && IsMarked( x, y ) ) SetCellAt( x, y, CELL_MARK );
        switch ( CellAt( x, y ) )
        {
        case CELL_FLOOR: image->SetTexelColor( x, y, color_GREEN ); break;
        case CELL_WALL:  image->SetTexelColor( x, y, color_BLACK ); break;
        case CELL_MARK:  image->SetTexelColor( x, y, color_RED ); break;
        default:
          image->SetTexelColor( x, y, color_RED );
          break;
        }
      }
    }
  }

  unsigned int Neighbors4_Sum( unsigned int x, unsigned int y )
  {
    unsigned int sum = 0;
    //sum += CellAt( x - 1, y - 1 );
    sum += CellAt( x - 1, y + 0 );
    //sum += CellAt( x - 1, y + 1 );
    sum += CellAt( x + 0, y - 1 );
    //sum += CellAt( x + 0, y + 0 );
    sum += CellAt( x + 0, y + 1 );
    //sum += CellAt( x + 1, y - 1 );
    sum += CellAt( x + 1, y + 0 );
    //sum += CellAt( x + 1, y + 1 );
    return sum;
  }
  unsigned int Neighbors5_Sum( unsigned int x, unsigned int y )
  {
    unsigned int sum = 0;
    //sum += CellAt( x - 1, y - 1 );
    sum += CellAt( x - 1, y + 0 );
    //sum += CellAt( x - 1, y + 1 );
    sum += CellAt( x + 0, y - 1 );
    sum += CellAt( x + 0, y + 0 );
    sum += CellAt( x + 0, y + 1 );
    //sum += CellAt( x + 1, y - 1 );
    sum += CellAt( x + 1, y + 0 );
    //sum += CellAt( x + 1, y + 1 );
    return sum;
  }
  unsigned int Neighbors8_Sum( unsigned int x, unsigned int y )
  {
    unsigned int sum = 0;
    sum += CellAt( x - 1, y - 1 );
    sum += CellAt( x - 1, y + 0 );
    sum += CellAt( x - 1, y + 1 );
    sum += CellAt( x + 0, y - 1 );
    //sum += CellAt( x + 0, y + 0 );
    sum += CellAt( x + 0, y + 1 );
    sum += CellAt( x + 1, y - 1 );
    sum += CellAt( x + 1, y + 0 );
    sum += CellAt( x + 1, y + 1 );
    return sum;
  }
  unsigned int Neighbors9_Sum( unsigned int x, unsigned int y )
  {
    unsigned int sum = 0;
    sum += CellAt( x - 1, y - 1 );
    sum += CellAt( x - 1, y + 0 );
    sum += CellAt( x - 1, y + 1 );
    sum += CellAt( x + 0, y - 1 );
    sum += CellAt( x + 0, y + 0 );
    sum += CellAt( x + 0, y + 1 );
    sum += CellAt( x + 1, y - 1 );
    sum += CellAt( x + 1, y + 0 );
    sum += CellAt( x + 1, y + 1 );
    return sum;
  }

   
};

