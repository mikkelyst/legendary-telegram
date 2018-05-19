#pragma once
#include <string>
#include <GLFW\glfw3.h>

#include "imgui\imgui.h"
#include "imgui\imgui_impl_glfw_gl3.h"  

#include "BoardTexture.h"
#include "CellGrid.h" 

const char *build_str = "Build date: " __DATE__ " " __TIME__;

typedef struct MapGenUIwindow
{
  bool show;
  const char* title;
  const char* menutitle;
};


class MapGenUI
{
private:
  GLFWwindow* system_window;
  ImVec4 clear_color = ImVec4( 0.45f, 0.55f, 0.60f, 1.00f );

  BoardTexture *boardImage;

  MapGenUIwindow w_board = { true, "Board Controls", "Show Window: Board Controls" };
  MapGenUIwindow w_cagen = { true, "Generator Parameters", "Show Window: Generator Parameters" };
  MapGenUIwindow w_image = { true, "Generated Map Tile", "Show Window: Generated Map Tile" };
  MapGenUIwindow w_imgui = { false, "ImGui Demo", "Show Window: ImGui Demo" };

  bool  is_program_terminated = false;
  int   boardSize[2] = { 64,64 };
  float boardImageScale = 5.0f;

  void MainMenu()
  {
    if ( ImGui::BeginMainMenuBar() )
    {
      if ( ImGui::BeginMenu( "System:" ) )
      {
        ImGui::MenuItem( "New map...", "CTRL+N", false, false );// Disabled item
        ImGui::MenuItem( "Quit", "ALT+F4", &is_program_terminated );
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
        ImGui::MenuItem( w_board.menutitle, NULL, &w_board.show, &w_board.show );
        ImGui::MenuItem( w_cagen.menutitle, NULL, &w_cagen.show, &w_cagen.show );
        ImGui::MenuItem( w_image.menutitle, NULL, &w_image.show, &w_image.show );
        ImGui::Separator();
        ImGui::MenuItem( w_imgui.menutitle, NULL, &w_imgui.show, &w_imgui.show );
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
  void WindowBoardControls( int x, int y )
  {
    if ( w_board.show )
    {
      ImGui::SetNextWindowPos( ImVec2( x, y ), ImGuiCond_FirstUseEver );
      if ( ImGui::Begin( w_board.title, &w_board.show, ImGuiWindowFlags_NoCollapse ) )
      {
        {
          ImGui::Text( build_str );
          ImGui::Text( "%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate );
        }
        ImGui::Separator();
        {
          ImGui::Text( "Board size:" );
          ImGui::SliderInt2( "width, height", boardSize, 4, 128 );
          if ( ImGui::Button( "construct new board" ) )
          {
            // TODO: call construct new board
            delete boardImage;
            boardImage = new BoardTexture( boardSize[0], boardSize[1] );
          }
        }
        ImGui::Separator();
        {
          ImGui::Text( "Board image display: " );
          ImGui::SliderFloat( "zoom/scale", &boardImageScale, 1.f, 12.f );
        }
        ImGui::Separator();
        {
          ImGui::Text( "Board clearing:" );
          if ( ImGui::Button( "clear: white" ) ) { boardImage->Clear( C_WHITE ); }
          ImGui::SameLine();
          if ( ImGui::Button( "clear: wlack" ) ) { boardImage->Clear( C_BLACK ); }
          ImGui::SameLine();
          if ( ImGui::Button( "clear: chessboard" ) ) { boardImage->ChessClear(); }
        }
        ImGui::Separator();
        {
          ImGui::Text( "Other options: " );
          ImGui::ColorEdit3( "Background clear color", (float*)&clear_color );
        }
        ImGui::Separator();

        // TODO : refactor into pixel editing with mouse
        {
          std::string text = "Cell (2,3) is ";
          static bool my_pixel = true;
          text += std::to_string( my_pixel );
          ImGui::Checkbox( text.c_str(), &my_pixel );
          if ( my_pixel ) boardImage->SetTexelColor( 2, 3, C_RED );
          else boardImage->SetTexelColor( 2, 3, C_GREEN );
        }
        ImGui::End();
      }
    }
  }
  void WindowMapTileImage( int x, int y )
  {
    if ( w_image.show )
    {
      ImGui::SetNextWindowPos( ImVec2( x, y ), ImGuiCond_FirstUseEver );
      if ( ImGui::Begin( w_image.title, &w_image.show, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize ) )
      {
        ImGui::Image(
          reinterpret_cast<void*>( boardImage->Update() ),
          ImVec2(
            boardImageScale*float( boardImage->SizeX() ),
            boardImageScale*float( boardImage->SizeY() )
          )
        );
        ImGui::Separator();
        static int selectedStep = 0;
        if ( ImGui::SliderInt( "CA Step", &selectedStep, 0, 10 ) )
        {
          // TODO: update board tex with current cellgrid
        }
        ImGui::End();
      }
    }
  }
  void WindowGenerationControls( int x, int y )
  {
    if ( w_cagen.show )
    { 
      ImGui::SetNextWindowPos( ImVec2( x, y ), ImGuiCond_FirstUseEver );
      if ( ImGui::Begin( w_cagen.title, &w_cagen.show, ImGuiWindowFlags_NoCollapse ) )
      {
        {
          ImGui::Text( "Cell Types: (unimplemented)" );
          ImGui::Text( "CELLTYPE1 : initial % on board " ); ImGui::SameLine(); ImGui::Button( "Remove type" );
          ImGui::Text( "CELLTYPE2 : initial % on board " ); ImGui::SameLine(); ImGui::Button( "Remove type" );
          ImGui::Text( "CELLTYPE3 : initial % on board " ); ImGui::SameLine(); ImGui::Button( "Remove type" );
          ImGui::Text( "<fields>" ); ImGui::SameLine(); ImGui::Button( "ADD TYPE" );
        }
        ImGui::Separator();
        {
          ImGui::Text( "Rules:" );
          ImGui::Text( "R1 : neighbors : condition : new cell" );
          ImGui::Text( "R2 : neighbors : condition : new cell" );
          ImGui::Text( "R3 : neighbors : condition : new cell" );
        }
        ImGui::Separator();
        ImGui::End();
      }
    }
  }
  void WindowImguiDemo( int x, int y )
  {
    if ( w_imgui.show )
    {
      ImGui::SetNextWindowPos( ImVec2( x, y ), ImGuiCond_FirstUseEver );
      ImGui::ShowDemoWindow( &w_imgui.show );
    }
  }

public:
  MapGenUI( GLFWwindow* window )
  {
    glfwFocusWindow( system_window = window );
    // Setup ImGui binding
    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init( system_window, true );
    ImGui::StyleColorsDark();
    // Setup default cell board texture for rendering
    boardImage = new BoardTexture();
  }

  ~MapGenUI()
  {
    // Cleanup
    delete boardImage;
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
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

  void Update()
  {
    ImGui_ImplGlfwGL3_NewFrame();
    { //// UI: 
      MainMenu(); // on top of system window, main menu.
      WindowBoardControls( 10, 10 ); // parameters for user to change
      WindowGenerationControls( 20, 20 );
      WindowMapTileImage( 300, 50 ); // displaying generated tiles
      WindowImguiDemo( 10, 150 ); // Imgui demo for reference to ImGui examples
    }
    if ( is_program_terminated ) glfwSetWindowShouldClose( system_window, GLFW_TRUE );
  }
};

