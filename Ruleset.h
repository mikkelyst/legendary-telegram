#pragma once

#include "Board.h"

class Ruleset
{
public:
  virtual void Evolve( Board * before, Board * after ) = 0;
};

class Rules_GameOfLife : public Ruleset
{
public:
  void Evolve( Board *before, Board *after )
  {
    for ( unsigned int x = 0; x < before->cellsX; x++ )
    {
      for ( unsigned int y = 0; y < before->cellsY; y++ )
      {
        switch ( before->Neighbors8_Sum( x, y ) )
        {
        case 2:  after->SetCellAt( x, y, before->CellAt( x, y ) ); break;
        case 3:  after->SetCellAt( x, y, CELL_WALL );              break;
        default: after->SetCellAt( x, y, CELL_FLOOR );             break;
        }
      }
    }
    return;
  }
};

class Rules_MapGen : public Ruleset
{
public:
  void Evolve( Board *before, Board *after )
  {
    for ( unsigned int x = 0; x < before->cellsX; x++ )
    {
      for ( unsigned int y = 0; y < before->cellsY; y++ )
      { 
        unsigned int sum = before->Neighbors8_Sum( x, y );  
        if ( sum < 5 ) after->SetCellAt( x, y, CELL_WALL );
        if ( sum > 5 ) after->SetCellAt( x, y, CELL_FLOOR );
      }
    }
    return;
  }
};