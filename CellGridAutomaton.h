#pragma once
#include <vector>
#include "CellGrid.h"

class CellGridAutomaton
{
private:
  std::vector<CellGrid*> steps;

public:
  CellGridAutomaton()
  {
    
  }
  ~CellGridAutomaton()
  {

  }
  void STEPS()
  {
    steps.at(0) = new CellGrid(16, 16);
    for (int it = 1; it < 10; it++)
    {
      steps.at(it) = steps.at(it - 1)->NextStep();
    }
    
  }
};

