#pragma once
#include <vector>
#include "Board.h"

class BoardAutomaton
{
private: 
  std::vector<Board> generations;

  void Age( Board *before, Board *after  )
  {
    
    // For every cell in grid excluding edges, call ApplyRule(r), set cell to cellstate from rule

    // nextGridState->SetCellAt (2, 3, ApplyRule (test));

    return;
  }
  //CELL ApplyRule( rule, neighbors )
  //{

  // Check Neighborhood, calculate rule value
  // Apply rule to cell
  //  switch ( rule )
  //  {
  //  case ALL_OFF:		return CELL_OFF; // Rule Zero: all cells are dead

  //  case CT:			return CELL_OFF;
  //  case CL:			return CELL_ON;
  //  case CM:			return CELL_OFF;
  //  case CR:			return CELL_OFF;
  //  case CB:			return CELL_ON;

  //  default:			return CELL_OFF;
  //  }
  //}
public:
  BoardAutomaton( unsigned int x = 16, unsigned int y = 16, unsigned int genCount = 10 )
  {
    generations.assign( genCount, Board( x, y ) );
    generations.at( 0 ).RandomState();  
    for ( unsigned int step = 1; step < genCount; step++ )
    {
      Age( &generations.at( step-1 ), &generations.at( step ) );
    }
  }
  ~BoardAutomaton() = default;
  void UpdateImage()
  {
    // TODO: call board image update
    // TODO: decouple BoardTex from MapGenUI
  }
  
};

