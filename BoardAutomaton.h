#pragma once
#include <vector>
#include "Board.h"
#include "BoardTexture.h"

class BoardAutomaton
{
private:
  std::vector<Board> generations;

  void Age( Board *before, Board *after )
  {
    // For every cell in grid excluding edges, ApplyRule(r), set cell
    for ( unsigned int x = 1; x < before->cellsX - 1; x++ )
    {
      for ( unsigned int y = 1; y < before->cellsY - 1; y++ )
      {
        int sum = 0;
        sum += before->CellAt( x - 1, y - 1 );
        sum += before->CellAt( x - 1, y + 0 );
        sum += before->CellAt( x - 1, y + 1 );
        sum += before->CellAt( x + 0, y - 1 );
        sum += before->CellAt( x + 0, y + 0 );
        sum += before->CellAt( x + 0, y + 1 );
        sum += before->CellAt( x + 1, y - 1 );
        sum += before->CellAt( x + 1, y + 0 );
        sum += before->CellAt( x + 1, y + 1 );
        after->SetCellAt( x, y, ApplyRule( sum ) );
      }
    }
    return;
  }
  CELL ApplyRule( unsigned int rule )
  {

    //// Check Neighborhood, calculate rule value
    //// Apply rule to cell
    switch ( rule )
    {
    case 3:
      return CELL_ON;
    case 4:
      return CELL_ON;
    default:
      return CELL_OFF;
    }
  }
public:
  BoardAutomaton( unsigned int x = 16, unsigned int y = 16, unsigned int genCount = 10 )
  {
    generations.assign( genCount, Board( x, y ) );
    generations.at( 0 ).RandomState();
    for ( unsigned int step = 1; step < genCount; step++ )
    {
      Age( &generations.at( step - 1 ), &generations.at( step ) );
    }
  }
  ~BoardAutomaton() = default;
  Board* Generation( unsigned int g )
  {
    return &generations.at( g % generations.size() );
  }
  unsigned int LastGenIndex()
  {
    return generations.size() - 1;
  }

};

