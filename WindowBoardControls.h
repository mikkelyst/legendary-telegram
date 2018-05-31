#pragma once
#include "MapGenWindow.h"
class WindowBoardControls : public MapGenWindow
{
public:

  WindowBoardControls( float initialPositionX, float initialPositionY, ImVec4 *bgColor )
  {
    x = initialPositionX;
    y = initialPositionY;
    title = "Board Controls";
    menutitle = "Show Window: Board Controls";
    flags = ImGuiWindowFlags_NoCollapse;
    ccPtr = bgColor;
  } 
  const char *build_str = "Build date: " __DATE__ " " __TIME__;
  ImVec4 *ccPtr;
  void WindowElements()
  {
    {
      ImGui::Text( build_str );
      ImGui::Text( "%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate );
    }
    ImGui::Separator();
    {
      ImGui::Text( "Display options: " );
      ImGui::ColorEdit3( "Background clear color", reinterpret_cast<float*>( ccPtr ) );
      ImGui::SliderFloat( "Board zoom/scale", &Automaton::ui_imageScale, 2.f, 20.f );
    }
    ImGui::Separator();
    {
      ImGui::Text( "Board parameters:" );
      ImGui::SliderInt2( "width, height", Automaton::ui_boardSize, 16, 256 );
      ImGui::SliderInt( "simulation step count", &Automaton::ui_stepCount, 10, 200 );
      if ( ImGui::Button( "RECONSTUCT BOARD" ) ) { Automaton::Reset(); }
    }
    ImGui::Separator();
    {
      ImGui::Text( "Board initializers:" );
      if ( ImGui::Button( "init : random    " ) ) { Automaton::State()->RegenerateStepsFrom( CLEAR_RANDOM ); }
      if ( ImGui::Button( "init : chessboard" ) ) { Automaton::State()->RegenerateStepsFrom( CLEAR_CHESS ); }
      if ( ImGui::Button( "init : modxyboard" ) ) { Automaton::State()->RegenerateStepsFrom( CLEAR_XYMOD ); }
      if ( ImGui::Button( "init : glidertest" ) ) { Automaton::State()->RegenerateStepsFrom( TEST_GLIDER ); }

      ImGui::TextWrapped( "Note: these functions generate all board states at once. Calling them may take some time to finish, depending on board size and step count." );
    }
    ImGui::Separator();
    {
      ImGui::Text( "Cell Types:" );
      // TODO: stats of cell types in board. needs better cell implementation
      // for each celltype
      std::string cellStats; // + type name + count cells, etc

      ImGui::Text( "CELLTYPE1 : %% on board " );
      ImGui::Text( "CELLTYPE2 : %% on board " );
      ImGui::Text( "CELLTYPE3 : %% on board " );
    }
    ImGui::Separator();
    {
      ImGui::Text( "Other options: " );
      // TODO : (future work) enable/disable pixel editing with mouse
      ImGui::Text( "..." );
    }
    ImGui::Separator();
  }
};
