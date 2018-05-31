#pragma once

#include "imgui\imgui.h"
#include "imgui\imgui_impl_glfw_gl3.h"  

#include "BoardAutomaton.h"
#include "SimpleTexture.h"

class MapGenWindow
{
public:
  bool isVisible = true; 
  char* menutitle = "<...>";

  MapGenWindow() {}
  ~MapGenWindow() = default;
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

#include "WindowBoardControls.h"
#include "WindowBoardImage.h"
#include "WindowGeneratorControls.h"
