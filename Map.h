#pragma once
#include <vector>
#include "Board.h"
class Map
{
public:
  std::vector<Board> mapTiles;
  const unsigned mapN = 1;
  const unsigned mapSide = ( 2 * mapN + 1 );
  const unsigned mapArea = mapSide*mapSide;
  Map( unsigned x, unsigned y )
  {
    mapTiles.assign( mapArea, Board( x, y ) );
  }
  ~Map()
  {
    mapTiles.clear();
  }

};