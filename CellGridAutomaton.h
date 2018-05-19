#pragma once
#include <vector>
#include "CellGrid.h"

class BoardAutomaton
{
private:
  std::vector<Board*> steps;

public:
  BoardAutomaton ()
  {
  }
  ~BoardAutomaton ()
  {

  }
  void STEPS ()
  {
    steps.at (0) = new Board (16, 16);
    for ( int it = 1; it < 10; it++ )
    {
      steps.at (it) = steps.at (it - 1)->NextStep ();
    }

  }
};

