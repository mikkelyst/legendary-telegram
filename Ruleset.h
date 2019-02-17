#pragma once

#include "Board.h"

enum Rules
{
  RULES_GAMEOFLIFE = 0,
  RULES_MAPGEN = 1
};
class Ruleset
{
public:
  static void EvolveState(Board * before, Board * after, Rules r = RULES_MAPGEN)
  {
    switch (r)
    {
    case RULES_GAMEOFLIFE: Rules_GameOfLife(before, after); break;
    case RULES_MAPGEN:     Rules_MapGen(before, after); break;
    default: break;
    }
  }
private:
  static void Rules_GameOfLife(Board *before, Board *after)
  {
    Board::isMarkingEnabled = false;
    for (unsigned int x = 0; x < before->cellsX; x++)
    {
      for (unsigned int y = 0; y < before->cellsY; y++)
      {
        switch (before->SumNeighbours(x, y, MOORE8))
        {
        case 2:  after->SetCellAt(x, y, before->CellAt(x, y)); break;
        case 3:  after->SetCellAt(x, y, 1);             break;
        default: after->SetCellAt(x, y, 0);             break;
        }
      }
    }
    return;
  }
  static void Rules_MapGen(Board *before, Board *after)
  {
    Board::isMarkingEnabled = true;
    for (unsigned int x = 0; x < before->cellsX; x++)
    {
      for (unsigned int y = 0; y < before->cellsY; y++)
      {
        unsigned int sum = before->SumNeighbours(x, y, MOORE8);
        if (sum < 5) after->SetCellAt(x, y, 1);
        if (sum > 5) after->SetCellAt(x, y, 0);
      }
    }
    return;
  }
  // TODO: with ruleset separated from automaton, maybe we could try rules where cellstate is dependent on states in the past, not just the previous one
};

