#pragma once
#include "MapGenWindow.h"
class WindowGeneratorControls : public MapGenWindow
{
public:  
  WindowGeneratorControls( float initialPositionX, float initialPositionY )
  {
    x = initialPositionX;
    y = initialPositionY;
    title = "Generator Controls";
    menutitle = "Show Window: Generator Controls";
    flags = ImGuiWindowFlags_NoCollapse;
  } 
  void WindowElements()
  {
    {
      ImGui::Text( "Rulesets:" );
      if ( ImGui::Button( "Ruleset 1: Game of Life  " ) ) { BoardAutomaton::State()->Ruleset( 0 ); }
      if ( ImGui::Button( "Ruleset 2: Map Generator " ) ) { BoardAutomaton::State()->Ruleset( 1 ); }
      if ( ImGui::Button( "Ruleset 3: <  ... ...  > " ) ) { BoardAutomaton::State()->Ruleset( 2 ); }
    }
    ImGui::Separator(); 
    {
      ImGui::Text( "Rules:" );
      ImGui::Text( "R1 : neighbors : condition : new cell" );
      ImGui::Text( "R2 : neighbors : condition : new cell" );
      ImGui::Text( "R3 : neighbors : condition : new cell" );
    }
    ImGui::Separator();
  } 
};

