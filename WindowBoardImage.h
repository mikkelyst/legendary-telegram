#pragma once
#include "Window_Base.h"
class WindowBoardImage : public Window_Base
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
      Automaton::State()->CurrentBoardImage(),
      ImVec2( Automaton::State()->DrawSizeX(), Automaton::State()->DrawSizeY() )
    );
    ImGui::Separator();
    {
      if ( ImGui::SliderInt( "CA Step", &Automaton::ui_stepSelected, 0, Automaton::State()->StepLast() ) ) {}
    }
    ImGui::Separator();
    {
      if ( ImGui::Button( "    0     " ) ) { Automaton::State()->StepJumpZero(); } ImGui::SameLine();
      if ( ImGui::Button( "<<< 5 STEP" ) ) { Automaton::State()->StepJump( -5 ); } ImGui::SameLine();
      if ( ImGui::Button( "<<< 1 STEP" ) ) { Automaton::State()->StepJump( -1 ); } ImGui::SameLine();
      if ( ImGui::Button( "1 STEP >>>" ) ) { Automaton::State()->StepJump( 1 ); }  ImGui::SameLine();
      if ( ImGui::Button( "5 STEP >>>" ) ) { Automaton::State()->StepJump( 5 ); }  ImGui::SameLine();
      if ( ImGui::Button( "   END    " ) ) { Automaton::State()->StepJumpLast(); }
    } 
  }
};

