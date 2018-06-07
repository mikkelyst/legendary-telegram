#pragma once

#include <vector>
#include "SimpleTexture.h" 

enum CELL_t
{
  // TODO: we may need to make a class Cell{} perhaps, but for now, just enum
  CELL_FLOOR = 0,
  CELL_WALL = 1,
  CELL_OTHER = 2 
};

class Board
{
private:
  std::vector<CELL_t> cells;
  bool isBoardChanged = false;
  bool isCellMarked( unsigned x, unsigned y )
  {
    if ( !isBoardChanged ) return false;
    int s = Neighbors4_Sum( x, y );
    return ( s == 2 || s == 3 ) && isMarkingEnabled;
  }

public:
  static float ui_boardDisplayScale;
  static bool isMarkingEnabled;
  unsigned int cellsX;
  unsigned int cellsY;

  Board( unsigned int width, unsigned int height )
  {
    cellsX = width;
    cellsY = height;
    Clear( CELL_FLOOR );
  }
  ~Board() = default;

  // BOARD STATE
  CELL_t CellAt( unsigned int x, unsigned int y )
  {
    return cells.at( cellsX * ( y%cellsY ) + ( x%cellsX ) );
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

  // BOARD MODIFY
  void SetCellAt( unsigned int x, unsigned int y, CELL_t newState )
  {
    cells.at( cellsX * ( y%cellsY ) + ( x%cellsX ) ) = newState;
    isBoardChanged = true;
    return;
  }
  void ReplaceWith( const Board* boardToCopy )
  {
    cells.erase( cells.begin(), cells.end() );
    cells.assign( boardToCopy->cells.begin(), boardToCopy->cells.end() );
    isBoardChanged = true;
  }
  void Clear( CELL_t with )
  {
    cells.assign( ( cellsX*cellsY ), with );
    isBoardChanged = true;
  }

  // BOARD DRAWING
  float DisplayScaleX()
  {
    return ui_boardDisplayScale * cellsX;
  }
  float DisplayScaleY()
  {
    return ui_boardDisplayScale * cellsY;
  }
  void  DrawCellsToTexture( unsigned texIdx, bool forceDraw = false )
  {
    if ( isBoardChanged || forceDraw )
    {
      for ( unsigned int x = 0; x < cellsX; x++ )
      {
        for ( unsigned int y = 0; y < cellsY; y++ )
        {
          switch ( CellAt( x, y ) )
          {
          case CELL_FLOOR: SimpleTexture2D::Texture( texIdx )->SetTexelColor( x, y, color_BLACK ); break;
          case CELL_WALL:  SimpleTexture2D::Texture( texIdx )->SetTexelColor( x, y, color_GREEN ); break;
          case CELL_OTHER: SimpleTexture2D::Texture( texIdx )->SetTexelColor( x, y, color_WHITE ); break;
          default:         SimpleTexture2D::Texture( texIdx )->SetTexelColor( x, y, color_BLUE ); break;
          }
          if ( isCellMarked( x, y ) ) SimpleTexture2D::Texture( texIdx )->SetTexelColor( x, y, color_RED );
        }
      }
    }
    isBoardChanged = false;
  }
};

float Board::ui_boardDisplayScale = 4.0f;
bool Board::isMarkingEnabled = true;