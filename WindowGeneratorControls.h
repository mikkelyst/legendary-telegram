#pragma once
#include "Window_Base.h"
class WindowGeneratorControls : public Window_Base
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
      if ( ImGui::Button( "Ruleset 1: Game of Life  " ) ) { Automaton::State()->ChangeRuleset( 0 ); }
      if ( ImGui::Button( "Ruleset 2: Map Generator " ) ) { Automaton::State()->ChangeRuleset( 1 ); } 
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

