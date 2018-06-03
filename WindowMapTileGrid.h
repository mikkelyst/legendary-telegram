#pragma once

#include "Window_Base.h" 
#include "SimpleTexture.h"
#include "Map.h"

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
    ShowMap( Automaton::State()->ConstructedMap() );
    ImGui::Separator();
    ImGui::TextWrapped( "Click on a map tile to replace it with current generated tile." );

  }
private: 
  void ShowMap( Map* m )
  { 
    for ( int x = 0; x < m->mapSide; x++ )
    {
      for ( int y = 0; y < m->mapSide; y++ )
      {
        if ( ImGui::ImageButton(
          m->DrawTileAt( x, y ),
          ImVec2( m->DisplayScaleX(), m->DisplayScaleY() )
        ) )
        {
          m->ReplaceTile( x, y, Automaton::State()->SelectedStep() );
        }
        if ( y != m->mapSide - 1 )ImGui::SameLine();
      }
    } 
  }
};
 