#pragma once

#include <vector>
#include "TextureAtlas.h" 

typedef unsigned int CELL_t;

enum Neighbourhood_t {
  VONNEUMANN4,
  VONNEUMANN5,
  MOORE8,
  MOORE9
};

class Board
{
private:
  std::vector<CELL_t> cells;
  bool isBoardChanged = false;
  bool isCellMarked(unsigned x, unsigned y)
  {
    if (!isBoardChanged) return false;
    int s = SumNeighbours(x, y, MOORE8);
    return (s > 2 && s < 6) && isMarkingEnabled;
  }


public:
  static float ui_boardDisplayScale;
  static bool isMarkingEnabled;
  unsigned int cellsX;
  unsigned int cellsY;

  Board(unsigned int width, unsigned int height)
  {
    cellsX = width;
    cellsY = height;
    Clear(0);
  }
  ~Board() = default;

  // BOARD STATE
  CELL_t CellAt(unsigned int x, unsigned int y)
  {
    return cells.at(cellsX * (y%cellsY) + (x%cellsX));
  }

  unsigned int SumNeighbours(unsigned int x, unsigned int y, Neighbourhood_t nht)
  {
    unsigned int sum = 0;
    sum += CellAt(x - 1, y + 0);
    sum += CellAt(x + 0, y - 1);
    sum += CellAt(x + 0, y + 1);
    sum += CellAt(x + 1, y + 0);
    if (nht == MOORE9 || nht == MOORE8) {
      sum += CellAt(x - 1, y - 1);
      sum += CellAt(x - 1, y + 1);
      sum += CellAt(x + 1, y - 1);
      sum += CellAt(x + 1, y + 1);
    }
    if (nht == MOORE9 || nht == VONNEUMANN5) sum += CellAt(x + 0, y + 0);
    return sum;
  }

  // BOARD MODIFY
  void SetCellAt(unsigned int x, unsigned int y, CELL_t newState)
  {
    cells.at(cellsX * (y%cellsY) + (x%cellsX)) = newState;
    isBoardChanged = true;
    return;
  }
  void ReplaceWith(const Board* boardToCopy)
  {
    cells.erase(cells.begin(), cells.end());
    cells.assign(boardToCopy->cells.begin(), boardToCopy->cells.end());
    isBoardChanged = true;
  }
  void Clear(CELL_t with)
  {
    cells.assign((cellsX*cellsY), with);
    isBoardChanged = true;
  }

  // BOARD DRAWING
  float DisplayScaleX()
  {
    return ui_boardDisplayScale * cellsX;
  }
  float DisplayScaleY()
  {
    return ui_boardDisplayScale * cellsY;
  }
  void  DrawCellsToTexture(unsigned texIdx, bool forceDraw = false)
  {
    if (isBoardChanged || forceDraw)
    {
      for (unsigned int x = 0; x < cellsX; x++)
      {
        for (unsigned int y = 0; y < cellsY; y++)
        {
          switch (CellAt(x, y))
          {
          case 0:   SimpleTexture2D::Texture(texIdx)->SetTexelColor(x, y, color_WHITE); break;
          case 1:   SimpleTexture2D::Texture(texIdx)->SetTexelColor(x, y, color_BLACK); break;
          case 2:   SimpleTexture2D::Texture(texIdx)->SetTexelColor(x, y, color_GREEN); break;
          default:  SimpleTexture2D::Texture(texIdx)->SetTexelColor(x, y, color_RED); break;
          }
          if (isCellMarked(x, y)) SimpleTexture2D::Texture(texIdx)->SetTexelColor(x, y, color_RED);
        }
      }
    }
    isBoardChanged = false;
  }
};

float Board::ui_boardDisplayScale = 4.0f;
bool Board::isMarkingEnabled = true;