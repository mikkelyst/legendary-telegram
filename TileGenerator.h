#pragma once
#include <vector>
#include <random> 
#include <chrono> // systime as random seed

#include "Ruleset.h"
#include "Board.h"
#include "TextureAtlas.h"
#include "Map.h"

enum BoardInit_t
{
  CLEAR_RANDOM,
  CLEAR_CHESS,
  CLEAR_XYMOD,
  TEST_GLIDER
};

class TileGenerator
{
public:
  static int ui_boardSize[2];
  static int ui_stepCount;
  static int ui_stepSelected;
  static float ui_stepProgress;
  static Rules currentRules;

  static TileGenerator* State()
  {
    if ( !single_instance )
      single_instance = new TileGenerator();
    return single_instance;
  }
  static TileGenerator* Reset()
  {
    delete single_instance;
    return single_instance = new TileGenerator();
  }
  ~TileGenerator()
  {
    delete map;
  }


  // STEP SELECTORS 
  void StepSelect( unsigned step )
  {
    ui_stepSelected = step % StepCount();
  }
  void StepJump( unsigned int offset )
  {
    StepSelect( ui_stepSelected + offset );
  }
  void StepJumpLast()
  {
    StepSelect( StepCount() - 1 );
  }

  // STEP USAGE
  unsigned int StepCount()
  {
    return generations.size();
  }
  Board* StepState()
  { 
    return ui_stepSelected < int(generations.size()) ?
      &generations.at( ui_stepSelected ) :
      &generations.at( 0 );
  }
  void* StepImage()
  {
    if (ui_stepSelected < int(generations.size()))
    {
      generations.at( ui_stepSelected ).DrawCellsToTexture( 0, true );
    }
    return SimpleTexture2D::Texture( 0 )->Render();
  }

  // STEP GENERATION
  void  RegenerateStepsFrom( BoardInit_t initialBoard )
  {
    InitGenAllRandom();
    GenerateSteps();
  }
  void ChangeRuleset( Rules r )
  {
    currentRules = r;
    GenerateSteps();
  }

  // MAP USAGE
  Map* ConstructedMap()
  {
    return map;
  }

private:
  static TileGenerator *single_instance;
  std::vector<Board> generations;
  Map* map;

  TileGenerator()
  {
    SimpleTexture2D::Texture( 0 )->Resize( ui_boardSize[0], ui_boardSize[1] );
    generations.assign( ui_stepCount, Board( ui_boardSize[0], ui_boardSize[1] ) );
    currentRules = RULES_MAPGEN;
    map = new Map( ui_boardSize[0], ui_boardSize[1] );
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
    BoardClear( 0 );
  }
  void BoardClear( CELL_t state )
  {
    generations.clear();
    generations.assign( ui_stepCount, Board( ui_boardSize[0], ui_boardSize[1] ) );
  }

  void InitGenAllRandom()
  {
    BoardClear();
    unsigned seed = unsigned( std::chrono::system_clock::now().time_since_epoch().count() );
    std::mt19937 randomizer( seed );
    std::uniform_int_distribution<int> distribution( 1, 100 );
    distribution.reset();
    CELL_t c = 2;
    for ( unsigned int x = 0; x < CellCountX(); x++ )
    {
      for ( unsigned int y = 0; y < CellCountY(); y++ )
      {
        switch ( distribution( randomizer ) % 2 )
        {
        case 0: c = 1; break;
        case 1: c = 0; break;
          //case 2: c = 2; break;
        default:break;
        }
        generations.at( 0 ).SetCellAt( x, y, c );
      }
    }
    return;
  } 
  void InitGenTestGlider()
  {
    BoardClear();
    {
      unsigned int a = generations.at( 0 ).cellsX / 2;
      unsigned int b = generations.at( 0 ).cellsY / 2;
      generations.at( 0 ).SetCellAt( a - 1, b + 0, 1 );
      generations.at( 0 ).SetCellAt( a + 0, b + 1, 1 );
      generations.at( 0 ).SetCellAt( a + 1, b - 1, 1 );
      generations.at( 0 ).SetCellAt( a + 1, b + 0, 1 );
      generations.at( 0 ).SetCellAt( a + 1, b + 1, 1 );
    }
  }

  void GenerateSteps()
  {
    // TODO: we could try to implement this function in lazy evaluation manner. 
    // ui_stepProgress = 0.f; 
    // ui_stepProgress = step / generations.size();
    for ( unsigned int step = 1; step < generations.size(); step++ )
    {
      Ruleset::EvolveState( &generations.at( step - 1 ), &generations.at( step ), currentRules );
    }
  }

};

int TileGenerator::ui_boardSize[2] = { 64, 64 };
int TileGenerator::ui_stepCount = 16; 
int TileGenerator::ui_stepSelected = 0;
float TileGenerator::ui_stepProgress = 0.f;
Rules TileGenerator::currentRules = RULES_MAPGEN;

TileGenerator* TileGenerator::single_instance = 0;