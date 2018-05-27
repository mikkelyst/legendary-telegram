#pragma once

#include "Board.h"

class AutomatonRules
{
public:
  virtual void Evolve( Board * before, Board * after ) = 0;
};

class AutomatonRules_GameOfLife : public AutomatonRules
{
public:
  void Evolve( Board *before, Board *after )
  {
    for ( unsigned int x = 1; x < before->cellsX - 1; x++ )
    {
      for ( unsigned int y = 1; y < before->cellsY - 1; y++ )
      {
        // Check neighbors
        int sum = 0;
        sum += before->CellAt( x - 1, y - 1 );
        sum += before->CellAt( x - 1, y + 0 );
        sum += before->CellAt( x - 1, y + 1 );
        sum += before->CellAt( x + 0, y - 1 );
        //sum += before->CellAt( x + 0, y + 0 );
        sum += before->CellAt( x + 0, y + 1 );
        sum += before->CellAt( x + 1, y - 1 );
        sum += before->CellAt( x + 1, y + 0 );
        sum += before->CellAt( x + 1, y + 1 );

        // Apply rules
        switch ( sum )
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

class AutomatonRules_MapGen : public AutomatonRules
{
public:
  void Evolve( Board *before, Board *after )
  {
    for ( unsigned int x = 1; x < before->cellsX - 1; x++ )
    {
      for ( unsigned int y = 1; y < before->cellsY - 1; y++ )
      {
        // Check neighbors
        int sum = 0;
        sum += before->CellAt( x - 1, y - 1 );
        sum += before->CellAt( x - 1, y + 0 );
        sum += before->CellAt( x - 1, y + 1 );
        sum += before->CellAt( x + 0, y - 1 );
        //sum += before->CellAt( x + 0, y + 0 );
        sum += before->CellAt( x + 0, y + 1 );
        sum += before->CellAt( x + 1, y - 1 );
        sum += before->CellAt( x + 1, y + 0 );
        sum += before->CellAt( x + 1, y + 1 );

        if ( sum < 5 ) after->SetCellAt( x, y, CELL_WALL );
        if ( sum > 5 ) after->SetCellAt( x, y, CELL_FLOOR );
      }
    }
    return;
  }
};