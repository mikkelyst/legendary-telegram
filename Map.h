#pragma once
#include <vector>
#include "Board.h"


class Map
{
private:
  Board* mapBoard;
  std::vector<Board> mapTiles;
  unsigned mapIdx( unsigned x, unsigned y )
  {
    if ( x < mapSide && y < mapSide )
    {
      return mapSide * x + y;
    }
    else throw;
  }
public:
  static float ui_mapDisplayScale;
  unsigned mapSide;
  unsigned mapArea;
  Map( unsigned boardsizeX, unsigned boardsizeY, unsigned mapN = 2 )
  {
    mapSide = ( 2 * mapN + 1 );
    mapArea = mapSide*mapSide;
    for ( unsigned i = 1; i <= mapArea; i++ ) SimpleTexture2D::Texture( i )->Resize( boardsizeX, boardsizeY );
    mapTiles.assign( mapArea, Board( boardsizeX, boardsizeY ) );
    mapBoard = new Board( mapSide*boardsizeX, mapSide*boardsizeY );
    SimpleTexture2D::Texture( mapArea + 1 )->Resize( mapSide*boardsizeX, mapSide*boardsizeY );
  }
  ~Map()
  {
    if (mapBoard) delete mapBoard;
    mapTiles.clear();
  }

  //// MAP DRAWING
  float DisplayScaleX_tiles()
  {
    return ( ui_mapDisplayScale / mapSide ) * mapTiles.at( 0 ).cellsX;
  }
  float DisplayScaleY_tiles()
  {
    return ( ui_mapDisplayScale / mapSide ) * mapTiles.at( 0 ).cellsY;
  }
  float DisplayScaleX_map()
  {
    return ( ui_mapDisplayScale / mapSide ) * mapBoard->cellsX;
  }
  float DisplayScaleY_map()
  {
    return ( ui_mapDisplayScale / mapSide ) * mapBoard->cellsY;
  }
  void* DrawTileAt( unsigned x, unsigned y )
  {
    mapTiles.at( mapIdx( x, y ) ).DrawCellsToTexture( mapIdx( x, y ) + 1 );
    return SimpleTexture2D::Texture( mapIdx( x, y ) + 1 )->Render();
  }
  void* DrawMap()
  {
    mapBoard->DrawCellsToTexture( mapArea + 1 );
    return SimpleTexture2D::Texture( mapArea + 1 )->Render();
  }

  //// MAP BUILDING
  void TileReplace( unsigned x, unsigned y, Board* tile )
  {
    mapTiles.at( mapIdx( x, y ) ).ReplaceWith( tile );
  }
  void TileJoinAll()
  {
    unsigned ct_x = mapTiles.at( 0 ).cellsX;
    unsigned ct_y = mapTiles.at( 0 ).cellsY;  

    for ( unsigned x = 0; x < mapSide*ct_x; x++ )
    {
      for ( unsigned y = 0; y < mapSide*ct_y; y++ )
      {
        mapBoard->SetCellAt( x, y, mapTiles.at( mapIdx( y / ct_y, x / ct_x ) ).CellAt( x % ct_x, y % ct_y ) );
      }
    }
  }
  void TileClearAll()
  {
    mapBoard->Clear( 0 );
  }
  void MapMergeTiles()
  { 
    Board* tempBoard = new Board( mapBoard->cellsX, mapBoard->cellsY );
    Ruleset::EvolveState( mapBoard, tempBoard );
    {
      // TODO: run algorithm to merge tile edges
    } 
    delete mapBoard;
    mapBoard = tempBoard; 
  }
};

float Map::ui_mapDisplayScale = 6.0f; 