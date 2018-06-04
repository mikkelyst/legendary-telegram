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
    static bool mapMode = false;
    if ( !mapMode )
    {
      ShowMapTiles( TileGenerator::State()->ConstructedMap() );
      ImGui::Separator();
      ImGui::TextWrapped( "Click on a map tile to replace it with current generated tile." );
      ImGui::Separator();
      if ( ImGui::Button( "Join tiles into map" ) )
      {
        mapMode = true;
        TileGenerator::State()->ConstructedMap()->TileJoinAll();
      }
     
      if ( ImGui::Button( "Clear map tiles" ) )
      {
        // TODO: clear tiles Map::Clear
      }
    }
    if ( mapMode )
    {
      ShowMap( TileGenerator::State()->ConstructedMap() );
      ImGui::Separator();
      if ( ImGui::Button( "MAPIFY: MapMergeTiles()" ) )
      {
        // TODO: FIX MY TITLE
        TileGenerator::State()->ConstructedMap()->MapMergeTiles();
      }
      ImGui::SameLine();
      if ( ImGui::Button( "Go back to editing" ) )
      {
        mapMode = false; 
      }
      if ( ImGui::Button( "Export map to file <?>" ) )
      {
        // TODO: export Map to image on disk
      }
      
    }
  }
private:
  void ShowMapTiles( Map* m )
  {
    for ( int x = 0; x < m->mapSide; x++ )
    {
      for ( int y = 0; y < m->mapSide; y++ )
      {
        if ( ImGui::ImageButton(
          m->DrawTileAt( x, y ),
          ImVec2( m->DisplayScaleX_tiles(), m->DisplayScaleY_tiles() )
        ) )
        {
          m->TileReplace( x, y, TileGenerator::State()->SelectedStep() );
        }
        if ( y != m->mapSide - 1 )ImGui::SameLine();
      }
    }
  }
  void ShowMap( Map* m )
  {
    ImGui::Image(
      m->DrawMap(),
      ImVec2( m->DisplayScaleX_map(), m->DisplayScaleY_map() )
    );
  }
};
