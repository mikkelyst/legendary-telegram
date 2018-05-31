#pragma once
#include "MapGenWindow.h"
class WindowBoardImage : public MapGenWindow
{
public: 
  WindowBoardImage( float initialPositionX, float initialPositionY )
  {
    x = initialPositionX;
    y = initialPositionY;
    title = "Generated Map Tile";
    menutitle = "Show Window: Generated Map Tile";
    flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize;
  }  
  void WindowElements()
  {
    ImGui::Image(
      BoardAutomaton::State()->DrawSelectedBoard(),
      ImVec2( BoardAutomaton::State()->DrawSizeX(), BoardAutomaton::State()->DrawSizeY() )
    );
    ImGui::Separator();
    {
      if ( ImGui::SliderInt( "CA Step", &BoardAutomaton::ui_stepSelected, 0, BoardAutomaton::State()->StepLast() ) ) {}
    }
    ImGui::Separator();
    {
      if ( ImGui::Button( "    0     " ) ) { BoardAutomaton::State()->StepJumpZero(); } ImGui::SameLine();
      if ( ImGui::Button( "<<< 5 STEP" ) ) { BoardAutomaton::State()->StepJump( -5 ); } ImGui::SameLine();
      if ( ImGui::Button( "<<< 1 STEP" ) ) { BoardAutomaton::State()->StepJump( -1 ); } ImGui::SameLine();
      if ( ImGui::Button( "1 STEP >>>" ) ) { BoardAutomaton::State()->StepJump( 1 ); }  ImGui::SameLine();
      if ( ImGui::Button( "5 STEP >>>" ) ) { BoardAutomaton::State()->StepJump( 5 ); }  ImGui::SameLine();
      if ( ImGui::Button( "   END    " ) ) { BoardAutomaton::State()->StepJumpLast(); }
    } 
  }
};

