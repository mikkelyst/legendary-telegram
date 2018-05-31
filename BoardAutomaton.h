#pragma once
#include <vector>
#include <random> 
#include <chrono> // systime as random seed

#include "AutomatonRules.h"
#include "Board.h"
#include "SimpleTexture.h"

enum BoardInit_t
{
  CLEAR_RANDOM,
  CLEAR_CHESS,
  CLEAR_XYMOD,
  TEST_GLIDER
};

class BoardAutomaton
{
public:
  static int ui_boardSize[2];
  static int ui_stepCount;
  static int ui_stepSelected;
  static float ui_imageScale; 
  static BoardAutomaton* State()
  {
    if ( !single_instance )
      single_instance = new BoardAutomaton();
    return single_instance;
  }
  static BoardAutomaton* Reset()
  {
    delete single_instance;
    return single_instance = new BoardAutomaton();
  }
  ~BoardAutomaton()
  {
    delete boardImage;
    delete currentRuleset;
  } 

  unsigned int StepLast()
  {
    return generations.size() - 1;
  }
  int StepJump( unsigned int offset )
  {
    unsigned int stepUpdated = ui_stepSelected + offset;
    if ( 0 < stepUpdated && stepUpdated < StepLast() )
    {
      ui_stepSelected = stepUpdated;
      return stepUpdated;
    }
    else return ui_stepSelected;
  }
  int StepJumpZero()
  {
    return ui_stepSelected = 0;
  }
  int StepJumpLast()
  {
    return ui_stepSelected = StepLast();
  } 

  void  RegenerateStepsFrom( BoardInit_t initialBoard )
  {
    switch ( initialBoard )
    {
    case CLEAR_RANDOM:        InitGenAllRandom(); break; 
    case CLEAR_CHESS:   InitGenClearChess(); break;
    case CLEAR_XYMOD:   InitGenClearXYMOD(); break;
    case TEST_GLIDER:   InitGenTestGlider(); break;
    }
    GenerateSteps();
  }
  void  Ruleset( int ruleset )
  {
    delete currentRuleset;
    switch ( ruleset )
    {
    case 1:  currentRuleset = new AutomatonRules_MapGen();    break;
    default: currentRuleset = new AutomatonRules_GameOfLife(); break;
    }
    GenerateSteps();
  }

  void* DrawSelectedBoard()
  {
    if ( unsigned( ui_stepSelected ) < generations.size() ) generations.at( ui_stepSelected ).DrawCellsToImage( boardImage );
    return reinterpret_cast<void*>( boardImage->Render() );
  }
  float DrawSizeX()
  {
    return ui_imageScale * CellCountX();
  }
  float DrawSizeY()
  {
    return ui_imageScale * CellCountY();
  } 

private:
  static BoardAutomaton *single_instance;
  AutomatonRules *currentRuleset;
  SimpleTexture2D *boardImage;
  std::vector<Board> generations;

  BoardAutomaton()
  {
    boardImage = new SimpleTexture2D( ui_boardSize[0], ui_boardSize[1] );
    generations.assign( ui_stepCount, Board( ui_boardSize[0], ui_boardSize[1] ) );
    currentRuleset = new AutomatonRules_MapGen();
  }

  unsigned int CellCountX()
  {
    return generations.at( 0 ).cellsX;
  }
  unsigned int CellCountY()
  {
    return generations.at( 0 ).cellsY;
  }

  void BoardClear()
  {
    BoardClear( CELL_FLOOR );
  }
  void BoardClear( CELL_t state )
  {
    generations.clear();
    generations.assign( ui_stepCount, Board( ui_boardSize[0], ui_boardSize[1] ) );
  }
  
  void InitGenAllRandom()
  {
    BoardClear();
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator( seed );
    std::uniform_int_distribution<int> distribution( 1, 100 );
    distribution.reset();
    CELL_t c = CELL_OTHER;
    for ( unsigned int x = 0; x < CellCountX(); x++ )
    {
      for ( unsigned int y = 0; y < CellCountY(); y++ )
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
  void InitGenClearChess()
  {
    BoardClear();
    for ( unsigned int x = 0; x < CellCountX(); x++ )
    {
      for ( unsigned int y = 0; y < CellCountY(); y++ )
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
    BoardClear();
    for ( unsigned int x = 0; x < CellCountX(); x++ )
    {
      for ( unsigned int y = 0; y < CellCountY(); y++ )
      {
        if ( ( ( x * 17 ) % ( 1 + y * 8 ) ) % 3 )
          generations.at( 0 ).SetCellAt( x, y, CELL_WALL );
        else
          generations.at( 0 ).SetCellAt( x, y, CELL_FLOOR );
      }
    }
  }
  void InitGenTestGlider()
  {
    BoardClear();
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

  void GenerateSteps()
  {
    // TODO: we could try to implement this function in lazy evaluation manner. 
    // Challenge: we could also try rules where cellstate is dependent on states before the previous one
    for ( unsigned int step = 1; step < generations.size(); step++ )
    {
      currentRuleset->Evolve( &generations.at( step - 1 ), &generations.at( step ) );
    }
  }

};

int BoardAutomaton::ui_boardSize[2] = { 128, 128 };
int BoardAutomaton::ui_stepCount = 10;
int BoardAutomaton::ui_stepSelected = 0;
float BoardAutomaton::ui_imageScale = 4.0f;
BoardAutomaton* BoardAutomaton::single_instance = 0;