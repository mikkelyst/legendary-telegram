#pragma once
#include <vector>
#include <random> 
#include <chrono> // systime as random seed

#include "AutomatonRules.h"
#include "Board.h"
#include "BoardTexture.h"

enum BoardClearType
{
  RANDOM = 0,
  CLEAR_ALL_ON = 1,
  CLEAR_ALL_OFF = 2,
  CLEAR_CHESS = 3,
  TEST_GLIDER = 4,
  CLEAR_XYMOD = 5
};

class BoardAutomaton
{
private:
  AutomatonRules *currentRuleset;
  BoardTexture2D *boardImage;
  std::vector<Board> generations;

  void GenerateSteps()
  {
    // TODO: we could try to implement this function in lazy evaluation manner. 
    // Challenge: we could also try rules where cellstate is dependent on states before the previous one
    for ( unsigned int step = 1; step < generations.size(); step++ )
    {
      currentRuleset->Evolve( &generations.at( step - 1 ), &generations.at( step ) );
    }
  }
  void InitGenClearWall()
  {
    for ( unsigned int x = 0; x < SizeX(); x++ )
    {
      for ( unsigned int y = 0; y < SizeY(); y++ )
      {
        generations.at( 0 ).SetCellAt( x, y, CELL_WALL );
      }
    }
  }
  void InitGenClearFloor()
  {
    for ( unsigned int x = 0; x < SizeX(); x++ )
    {
      for ( unsigned int y = 0; y < SizeY(); y++ )
      {
        generations.at( 0 ).SetCellAt( x, y, CELL_FLOOR );
      }
    }
  }
  void InitGenClearChess()
  {
    InitialState( CLEAR_ALL_OFF );
    for ( unsigned int x = 0; x < SizeX(); x++ )
    {
      for ( unsigned int y = 0; y < SizeY(); y++ )
      {
        if ( ( x % 2 ) ^ ( y % 2 ) )
          generations.at( 0 ).SetCellAt( x, y, CELL_WALL );
        else
          generations.at( 0 ).SetCellAt( x, y, CELL_FLOOR );
      }
    }
  }
  void InitGenClearXYMOD()
  {
    InitialState( CLEAR_ALL_OFF );
    for ( unsigned int x = 0; x < SizeX(); x++ )
    {
      for ( unsigned int y = 0; y < SizeY(); y++ )
      {
        if ( ( ( x * 3 ) % ( y + 1 ) ) % 2 )
          generations.at( 0 ).SetCellAt( x, y, CELL_WALL );
        else
          generations.at( 0 ).SetCellAt( x, y, CELL_FLOOR );
      }
    }
  }
  void InitGenTestGlider()
  {
    InitialState( CLEAR_ALL_OFF );
    {
      unsigned int a = generations.at( 0 ).cellsX / 2;
      unsigned int b = generations.at( 0 ).cellsY / 2;
      generations.at( 0 ).SetCellAt( a - 1, b + 0, CELL_WALL );
      generations.at( 0 ).SetCellAt( a + 0, b + 1, CELL_WALL );
      generations.at( 0 ).SetCellAt( a + 1, b - 1, CELL_WALL );
      generations.at( 0 ).SetCellAt( a + 1, b + 0, CELL_WALL );
      generations.at( 0 ).SetCellAt( a + 1, b + 1, CELL_WALL );
    }
  }
  void InitGenAllRandom()
  {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator( seed );
    std::uniform_int_distribution<int> distribution( 1, 100 );
    distribution.reset();
    CELL c = CELL_OTHER;
    for ( unsigned int x = 0; x < SizeX(); x++ )
    {
      for ( unsigned int y = 0; y < SizeY(); y++ )
      {
        switch ( distribution( generator ) % 2 )
        {
        case 0: c = CELL_WALL; break;
        case 1: c = CELL_FLOOR; break;
          //case 2: c = CELL_OTHER; break;
        default:break;
        }
        generations.at( 0 ).SetCellAt( x, y, c );
      }
    }
    return;
  }

public:
  BoardAutomaton( unsigned int x = 16, unsigned int y = 16, unsigned int genCount = 10 )
  {
    boardImage = new BoardTexture2D( x, y );
    generations.assign( genCount, Board( x, y ) );
    currentRuleset = new AutomatonRules_GameOfLife();
  }
  ~BoardAutomaton()
  {
    delete boardImage;
    delete currentRuleset;
  }

  void  InitialState( BoardClearType clearMethod )
  {
    switch ( clearMethod )
    {
    case CLEAR_ALL_ON:  InitGenClearWall(); break;
    case CLEAR_ALL_OFF: InitGenClearFloor(); break;
    case CLEAR_CHESS:   InitGenClearChess(); break;
    case CLEAR_XYMOD:   InitGenClearXYMOD(); break;
    case TEST_GLIDER:   InitGenTestGlider(); break;
    case RANDOM:        InitGenAllRandom(); break;
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
          switch ( generations.at( step ).CellAt( x, y ) )
          {
          case CELL_FLOOR: boardImage->SetTexelColor( x, y, color_BLACK ); break;
          case CELL_WALL:  boardImage->SetTexelColor( x, y, color_WHITE ); break;
          case CELL_OTHER: boardImage->SetTexelColor( x, y, color_GREEN ); break;
          default:
            // red cells should never be created if all is well         
            boardImage->SetTexelColor( x, y, color_RED );
            break;
          }
        }
      }
    }
    return reinterpret_cast<void*>( boardImage->Render() );
  }
  void  ChangeRuleset( int ruleset )
  {
    delete currentRuleset;
    switch ( ruleset )
    {
    case 1:  currentRuleset = new AutomatonRules_MapGen();    break;
    default: currentRuleset = new AutomatonRules_GameOfLife(); break;
    }
    GenerateSteps();
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

};

