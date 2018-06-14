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
    // ImGui::ProgressBar( TileGenerator::ui_stepProgress, ImVec2( 0.0f, 0.0f ) );
    ImGui::Separator();
    ImGui::Image(
      TileGenerator::State()->SelectedStepImage(),
      ImVec2(
        TileGenerator::State()->SelectedStep()->DisplayScaleX(),
        TileGenerator::State()->SelectedStep()->DisplayScaleY() )
    );
    ImGui::Separator();
    {
      if ( ImGui::SliderInt( "Step Selector", &TileGenerator::ui_stepSelected, 0, TileGenerator::State()->StepCount()-1 ) ) {}
    }
    ImGui::Separator();
    {
      ImGui::Text( "Precise selectors:" );
      if ( ImGui::Button( "    0     " ) ) { TileGenerator::State()->StepSelect( 0 ); } ImGui::SameLine();
      if ( ImGui::Button( "<<< 3 STEP" ) ) { TileGenerator::State()->StepJump( -3 ); }  ImGui::SameLine();
      if ( ImGui::Button( "<<< 1 STEP" ) ) { TileGenerator::State()->StepJump( -1 ); }  ImGui::SameLine();
      if ( ImGui::Button( "1 STEP >>>" ) ) { TileGenerator::State()->StepJump( 1 ); }   ImGui::SameLine();
      if ( ImGui::Button( "3 STEP >>>" ) ) { TileGenerator::State()->StepJump( 3 ); }   ImGui::SameLine();
      if ( ImGui::Button( "   END    " ) ) { TileGenerator::State()->StepJumpLast(); }
    }
  }
};

