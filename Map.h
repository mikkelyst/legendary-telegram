#pragma once
#include <vector>
#include "Board.h"


class Map
{
private:
  std::vector<Board> mapTiles;
  unsigned mapIdx( unsigned x, unsigned y )
  {
    if ( x < mapSide && y < mapSide )
    {
      return mapSide * y + x;
    }
    else throw;
  }
public:
  static float ui_mapDisplayScale;
  unsigned mapSide;
  unsigned mapArea;
  Map( unsigned boardsizeX, unsigned boardsizeY, unsigned mapN = 1 )
  {
    mapSide = ( 2 * mapN + 1 );
    mapArea = mapSide*mapSide;
    for ( unsigned i = 1; i <= mapArea; i++ ) SimpleTexture2D::Texture(i)->Resize( boardsizeX, boardsizeY );
    mapTiles.assign( mapArea, Board( boardsizeX, boardsizeY ) );
  }
  ~Map()
  {
    mapTiles.clear();
  }
  
  float DisplayScaleX()
  {
    return ( ui_mapDisplayScale / mapSide ) * mapTiles.at( 0 ).cellsX;
  }
  float DisplayScaleY()
  {
    return ( ui_mapDisplayScale / mapSide ) * mapTiles.at( 0 ).cellsY;
  }

  void ReplaceTile( unsigned x, unsigned y, Board* tile )
  { 
    mapTiles.at( mapIdx( x, y ) ).ReplaceWith(tile);
  } 
  void* DrawTileAt( unsigned x, unsigned y )
  { 
    mapTiles.at( mapIdx( x, y ) ).DrawCellsToTexture( mapIdx( x, y ) + 1 );
    return SimpleTexture2D::Texture( mapIdx( x, y ) + 1 )->Render();
  }

};

float Map::ui_mapDisplayScale = 4.0f;