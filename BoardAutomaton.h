#pragma once
#include <vector>
#include "Board.h"
#include "BoardTexture.h"

enum BoardClears
{
  CLEAR_ALL_ON = 1,
  CLEAR_ALL_OFF = 2,
  CLEAR_CHESS = 3,
  TEST_GLIDER = 4
};

class BoardAutomaton
{
private:
  BoardTexture2D *boardImage;
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
        //sum += before->CellAt( x + 0, y + 0 );
        sum += before->CellAt( x + 0, y + 1 );
        sum += before->CellAt( x + 1, y - 1 );
        sum += before->CellAt( x + 1, y + 0 );
        sum += before->CellAt( x + 1, y + 1 );
        after->SetCellAt( x, y, ApplyRule( sum, before->CellAt( x, y ) ) );
      }
    }
    return;
  }
  CELL ApplyRule( unsigned int rule, CELL previous )
  { 
    switch ( rule )
    {
    case 2:
      return previous;
    case 3:
      return CELL_ON;
    default:
      return CELL_OFF;
    }
  }
  void GenerateSteps()
  {
    for ( unsigned int step = 1; step < generations.size(); step++ )
    {
      Age( &generations.at( step - 1 ), &generations.at( step ) );
    }
  }
public:
  BoardAutomaton( unsigned int x = 16, unsigned int y = 16, unsigned int genCount = 10 )
  {
    boardImage = new BoardTexture2D( x, y );
    generations.assign( genCount, Board( x, y ) );
    InitialState( TEST_GLIDER ); 
  }
  ~BoardAutomaton()
  {
    delete boardImage;
  }

  unsigned int SizeX()
  {
    return generations.at( 0 ).cellsX;
  }
  unsigned int SizeY()
  {
    return generations.at( 0 ).cellsY;
  }
  unsigned int LastGenIndex()
  {
    return generations.size() - 1;
  } 
  void InitialState( BoardClears chosenBoardClear )
  {
    switch ( chosenBoardClear )
    {
    case CLEAR_ALL_ON:
      for ( unsigned int x = 0; x < SizeX(); x++ )
      {
        for ( unsigned int y = 0; y < SizeY(); y++ )
        {
          generations.at( 0 ).SetCellAt( x, y, CELL_ON );
        }
      }
      break;
    case CLEAR_ALL_OFF:
      for ( unsigned int x = 0; x < SizeX(); x++ )
      {
        for ( unsigned int y = 0; y < SizeY(); y++ )
        {
          generations.at( 0 ).SetCellAt( x, y, CELL_OFF );
        }
      }
      break;
    case CLEAR_CHESS:
      InitialState( CLEAR_ALL_OFF );
      for ( unsigned int x = 0; x < SizeX(); x++ )
      {
        for ( unsigned int y = 0; y < SizeY(); y++ )
        {
          if ( ( x % 2 ) ^ ( y % 2 ) )
            generations.at( 0 ).SetCellAt( x, y, CELL_ON );
          else
            generations.at( 0 ).SetCellAt( x, y, CELL_OFF );
        }
      }
      break;
    case TEST_GLIDER:
      InitialState( CLEAR_ALL_OFF );
      {
        unsigned int a = generations.at( 0 ).cellsX / 2;
        unsigned int b = generations.at( 0 ).cellsY / 2;
        generations.at( 0 ).SetCellAt( a - 1, b + 0, CELL_ON );
        generations.at( 0 ).SetCellAt( a + 0, b + 1, CELL_ON );
        generations.at( 0 ).SetCellAt( a + 1, b - 1, CELL_ON );
        generations.at( 0 ).SetCellAt( a + 1, b + 0, CELL_ON );
        generations.at( 0 ).SetCellAt( a + 1, b + 1, CELL_ON );
      } 
      break;
    default:
      break;
    }
    GenerateSteps();
  }
  void* DrawBoardAtStep( unsigned int step )
  {
    if ( step < generations.size() )
    {
      //  update board tex with current cellgrid 
      for ( unsigned int x = 0; x < SizeX(); x++ )
      {
        for ( unsigned int y = 0; y < SizeY(); y++ )
        {
          if ( generations.at( step ).CellAt( x, y ) == CELL_OFF )
            boardImage->SetTexelColor( x, y, color_BLACK );
          else
            boardImage->SetTexelColor( x, y, color_WHITE );
        }
      }
    }
    return reinterpret_cast<void*>( boardImage->Render() );
  }


};

