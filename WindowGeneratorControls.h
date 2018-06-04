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
      static int ruleChoice = int(TileGenerator::currentRules);
      ImGui::Text( "Rulesets:" );
      if ( ImGui::RadioButton( "Game of Life Rules (for tests)", &ruleChoice, 0 ) )
      {
        TileGenerator::State()->ChangeRuleset( RULES_GAMEOFLIFE ); 
      } 
      if ( ImGui::RadioButton( "Map Generator Rules", &ruleChoice, 1 ) )
      {
        TileGenerator::State()->ChangeRuleset( RULES_MAPGEN );
      }
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

