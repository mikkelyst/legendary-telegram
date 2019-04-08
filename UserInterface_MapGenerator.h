#pragma once
#include <string>
#include <list>
#include <GLFW\glfw3.h>

#include "TileGenerator.h"
#include "UserInterface.h"

class UserInterface_MapGenerator
{
public:
  UserInterface_MapGenerator( GLFWwindow* window )
  {
    glfwFocusWindow( system_window = window );
    // Setup ImGui binding
    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init( system_window, true );
    ImGui::StyleColorsDark();
    // Setup ui elements
    UserInterfaceWindows.push_back( new WindowBoardControls( 10.f, 10.f, &clear_color ) ); 
    UserInterfaceWindows.push_back( new WindowBoardImage( 300.f, 150.f ) ); 
    UserInterfaceWindows.push_back( new WindowMapTileGrid( 500.f, 200.f ) );
    // Initialize automaton with default data 
    TileGenerator::State()->RegenerateStepsFrom( CLEAR_RANDOM );
  }
  ~UserInterface_MapGenerator()
  { 
    // Cleanup 
    UserInterfaceWindows.clear();
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
  } 
  void Update()
  {
    ImGui_ImplGlfwGL3_NewFrame();
    {
      // UI updates: 
      MainMenu(); 
      for ( Window_Base *w : UserInterfaceWindows ) w->Update();
      if ( isImguiDemoVisible ) 
      { 
        ImGui::SetNextWindowPos( ImVec2( 10, 150 ), ImGuiCond_FirstUseEver );
        ImGui::ShowDemoWindow( &isImguiDemoVisible ); // Imgui demo for reference to ImGui examples
      }
      if ( isImguiMetricsVisible )
      {
        ImGui::ShowMetricsWindow( &isImguiMetricsVisible );
      }
    }
    if ( isProgramTerminated ) glfwSetWindowShouldClose( system_window, GLFW_TRUE );
  }
  void Render()
  {
    // Rendering
    int display_w, display_h;
    glfwGetFramebufferSize( system_window, &display_w, &display_h );
    glViewport( 0, 0, display_w, display_h );
    glClearColor( clear_color.x, clear_color.y, clear_color.z, clear_color.w );
    glClear( GL_COLOR_BUFFER_BIT );
    // Render gui
    ImGui::Render();
    ImGui_ImplGlfwGL3_RenderDrawData( ImGui::GetDrawData() );
  }

private:
  bool isProgramTerminated = false;
  bool isImguiDemoVisible = false;
  bool isImguiMetricsVisible = false;
  GLFWwindow* system_window;
  ImVec4 clear_color = ImVec4( 0.45f, 0.55f, 0.60f, 1.00f );

  std::list<Window_Base*> UserInterfaceWindows; 

  void MainMenu()
  {
    if ( ImGui::BeginMainMenuBar() )
    {
      if ( ImGui::BeginMenu( "System:" ) )
      {
        ImGui::MenuItem( "New map...", "CTRL+N", false, false );// Disabled item
        ImGui::MenuItem( "Quit", "ALT+F4", &isProgramTerminated );
        ImGui::EndMenu();
      }
      if ( ImGui::BeginMenu( "Editing:" ) )
      {
        ImGui::MenuItem( "Undo", "CTRL+Z", false, false );  // Disabled item
        ImGui::MenuItem( "Redo", "CTRL+Y", false, false );  // Disabled item 
        ImGui::EndMenu();
      }
      if ( ImGui::BeginMenu( "View:" ) )
      {
        for ( Window_Base *w : UserInterfaceWindows )
        {
          ImGui::MenuItem( w->menutitle, NULL, &w->isVisible, &w->isVisible );
        } 
        ImGui::Separator();
        ImGui::MenuItem( "ImGui Demo Window", NULL, &isImguiDemoVisible, &isImguiDemoVisible );
        ImGui::MenuItem( "ImGui Metrics Window", NULL, &isImguiMetricsVisible, &isImguiMetricsVisible );
        ImGui::EndMenu();
      }
      if ( ImGui::BeginMenu( "About:" ) )
      {
        ImGui::MenuItem( "Author", NULL, false, false ); // Disabled item
        ImGui::MenuItem( "Used libraries", NULL, false, false );// Disabled item
        ImGui::EndMenu();
      }
      ImGui::EndMainMenuBar();
    }
  }
};

