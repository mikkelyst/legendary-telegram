#pragma once
 
#include "Window_Base.h" 

#include "SimpleTexture.h" // TODO: remove

class WindowMapTileGrid : public Window_Base
{ 
public:
  WindowMapTileGrid( float initialPositionX, float initialPositionY )
  {
    x = initialPositionX;
    y = initialPositionY;
    title = "Map";
    menutitle = "Show Window: Map";
    flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize;
  }

  ~WindowMapTileGrid()
  {
  }

  void WindowElements()
  {
    ShowMap();
    ImGui::Separator();
  }

  void ShowMap()
  {
    for ( int i = 1; i < 10; i++ )
    {
      ImGui::Image(
        SimpleTexture2D::Texture()->Render(),
        ImVec2( Automaton::State()->DrawSizeX() / 3, Automaton::State()->DrawSizeY() / 3 )
      );
      if ( i % 3 != 0 ) ImGui::SameLine();
    }
  }
};

