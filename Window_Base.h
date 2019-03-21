#pragma once

#include "imgui\imgui.h"
#include "imgui\imgui_impl_glfw_gl3.h"  

#include "TileGenerator.h"
#include "TextureAtlas.h"

class Window_Base
{
public:
  bool isVisible = true; 
  char* menutitle = "<...>";

  Window_Base() {}
  ~Window_Base() = default;
  void Update()
  {
    if ( isVisible )
    { 
      ImGui::SetNextWindowPos( ImVec2( x, y ), ImGuiCond_FirstUseEver );
      if ( ImGui::Begin( title, &isVisible, flags ) )
      {
        WindowElements(); 
        ImGui::End();
      } 
    }
  } 

protected:
  float x, y;
  char* title = "<...>";
  ImGuiWindowFlags flags; 
  virtual void WindowElements() {}
};  


class WindowBoardControls : public Window_Base
{
public:

  WindowBoardControls(float initialPositionX, float initialPositionY, ImVec4 *bgColor)
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
      ImGui::Text(build_str);
      ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }
    ImGui::Separator();
    {
      ImGui::Text("Display options: ");
      ImGui::ColorEdit3("Background clear color", reinterpret_cast<float*>(ccPtr));
      ImGui::SliderFloat("Board zoom/scale", &Board::ui_boardDisplayScale, 2.f, 20.f);
      ImGui::SliderFloat("Map zoom/scale", &Map::ui_mapDisplayScale, 2.f, 20.f);
    }
    ImGui::Separator();
    {
      ImGui::Text("Board parameters:");
      ImGui::SliderInt2("width, height", TileGenerator::ui_boardSize, 16, 256);
      ImGui::SliderInt("simulation step count", &TileGenerator::ui_stepCount, 10, 200);
      if (ImGui::Button("RECONSTUCT BOARD")) { TileGenerator::Reset(); }
    }
    ImGui::Separator();
    static int ruleChoice = int(TileGenerator::currentRules);
    ImGui::Text("Rulesets:");
    if (ImGui::RadioButton("Game of Life Rules (for tests)", &ruleChoice, 0))
    {
      TileGenerator::State()->ChangeRuleset(RULES_GAMEOFLIFE);
    }
    if (ImGui::RadioButton("Map Generator Rules", &ruleChoice, 1))
    {
      TileGenerator::State()->ChangeRuleset(RULES_MAPGEN);
    }
    ImGui::Separator();
  }
};

class WindowBoardImage : public Window_Base
{
public:
  WindowBoardImage(float initialPositionX, float initialPositionY)
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
      TileGenerator::State()->StepImage(),
      ImVec2(
        TileGenerator::State()->StepState()->DisplayScaleX(),
        TileGenerator::State()->StepState()->DisplayScaleY())
    );
    ImGui::Separator();
    {
      if (ImGui::SliderInt("Step Selector", &TileGenerator::ui_stepSelected, 0, TileGenerator::State()->StepCount() - 1)) {}
    }
    ImGui::Separator();
    {
      ImGui::Text("Precise selectors:");
      if (ImGui::Button("    0     ")) { TileGenerator::State()->StepSelect(0); } ImGui::SameLine();
      if (ImGui::Button("<<< 3 STEP")) { TileGenerator::State()->StepJump(-3); }  ImGui::SameLine();
      if (ImGui::Button("<<< 1 STEP")) { TileGenerator::State()->StepJump(-1); }  ImGui::SameLine();
      if (ImGui::Button("1 STEP >>>")) { TileGenerator::State()->StepJump(1); }   ImGui::SameLine();
      if (ImGui::Button("3 STEP >>>")) { TileGenerator::State()->StepJump(3); }   ImGui::SameLine();
      if (ImGui::Button("   END    ")) { TileGenerator::State()->StepJumpLast(); }
    }
    ImGui::Separator();
    {
      ImGui::Text("Random initial tile state:");
      if (ImGui::Button("GENERATE")) { TileGenerator::State()->RegenerateStepsFrom(CLEAR_RANDOM); }
    }
    ImGui::Separator();
  }
};


class WindowMapTileGrid : public Window_Base
{

public:
  WindowMapTileGrid(float initialPositionX, float initialPositionY)
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
    if (!mapMode)
    {
      ShowMapTiles(TileGenerator::State()->ConstructedMap());
      ImGui::Separator();
      ImGui::TextWrapped("Click on a map tile to replace it with current generated tile.");
      ImGui::Separator();
      if (ImGui::Button("Join tiles into map"))
      {
        mapMode = true;
        TileGenerator::State()->ConstructedMap()->TileJoinAll();
      }
      if (ImGui::Button("Clear map tiles"))
      {
        TileGenerator::State()->ConstructedMap()->TileClearAll();
      }
    }
    if (mapMode)
    {
      ShowMap(TileGenerator::State()->ConstructedMap());
      ImGui::Separator();
      if (ImGui::Button("Run one CA step on Map"))
      {
        TileGenerator::State()->ConstructedMap()->MapMergeTiles();
      }
      ImGui::SameLine();
      if (ImGui::Button("Go back to editing"))
      {
        mapMode = false;
      }
      if (ImGui::Button("Export map to file <?>"))
      {
        // TODO: export Map to image on disk
      }

    }
  }

private:
  void ShowMapTiles(Map* m)
  {
    for (int x = 0; x < m->mapSide; x++)
    {
      for (int y = 0; y < m->mapSide; y++)
      {
        if (ImGui::ImageButton(
          m->DrawTileAt(x, y),
          ImVec2(m->DisplayScaleX_tiles(), m->DisplayScaleY_tiles())
        ))
        {
          m->TileReplace(x, y, TileGenerator::State()->StepState());
        }
        if (y != m->mapSide - 1)ImGui::SameLine();
      }
    }
  }
  void ShowMap(Map* m)
  {
    ImGui::Image(
      m->DrawMap(),
      ImVec2(m->DisplayScaleX_map(), m->DisplayScaleY_map())
    );
  }
};