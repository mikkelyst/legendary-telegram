#pragma once
#include <string>
#include <GLFW\glfw3.h>

#include "imgui\imgui.h"
#include "imgui\imgui_impl_glfw_gl3.h"  

#include "BoardAutomaton.h"
#include "BoardTexture.h"

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
  bool  is_program_terminated = false;
  GLFWwindow* system_window;
  ImVec4 clear_color = ImVec4( 0.45f, 0.55f, 0.60f, 1.00f );
  BoardAutomaton *tileGenerator;

  MapGenUIwindow w_board = { true, "Board Controls", "Show Window: Board Controls" };
  MapGenUIwindow w_cagen = { true, "Generator Parameters", "Show Window: Generator Parameters" };
  MapGenUIwindow w_image = { true, "Generated Map Tile", "Show Window: Generated Map Tile" };
  MapGenUIwindow w_imgui = { false, "ImGui Demo", "Show Window: ImGui Demo" }; 

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
      ImGui::SetNextWindowPos( ImVec2( float( x ), float( y ) ), ImGuiCond_FirstUseEver );
      if ( ImGui::Begin( w_board.title, &w_board.show, ImGuiWindowFlags_NoCollapse ) )
      {
        {
          ImGui::Text( build_str );
          ImGui::Text( "%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate );
        }
        ImGui::Separator();
        {
          ImGui::Text( "Display options: " );
          ImGui::ColorEdit3( "Background clear color", (float*)&clear_color );
          ImGui::SliderFloat( "Board zoom/scale", &BoardAutomaton::ui_imageScale, 2.f, 20.f );
        }
        ImGui::Separator();
        {
          ImGui::Text( "Board parameters:" );
          ImGui::SliderInt2( "width, height", BoardAutomaton::ui_boardSize, 16, 256 );
          ImGui::SliderInt( "simulation step count", &BoardAutomaton::ui_stepCount, 10, 200 );
          if ( ImGui::Button( "RECONSTUCT BOARD" ) )
          {
            delete tileGenerator;
            tileGenerator = new BoardAutomaton( BoardAutomaton::ui_boardSize[0], BoardAutomaton::ui_boardSize[1], BoardAutomaton::ui_stepCount );
          }
        }
        ImGui::Separator();
        {
          ImGui::Text( "Board initializers:" );
          if ( ImGui::Button( "init : random    " ) ) { tileGenerator->RegenerateWith( CLEAR_RANDOM ); } 
          if ( ImGui::Button( "init : chessboard" ) ) { tileGenerator->RegenerateWith( CLEAR_CHESS ); }
          if ( ImGui::Button( "init : modxyboard" ) ) { tileGenerator->RegenerateWith( CLEAR_XYMOD ); }
          if ( ImGui::Button( "init : glidertest" ) ) { tileGenerator->RegenerateWith( TEST_GLIDER ); }

          ImGui::TextWrapped( "Note: these functions generate all board states at once. Calling them may take some time to finish, depending on board size and step count." );
        }
        ImGui::Separator();
        {
          ImGui::Text( "Cell Types:" );
          // TODO: stats of cell types in board. needs better cell implementation
          // for each celltype
          std::string cellStats; // + type name + count cells, etc

          ImGui::Text( "CELLTYPE1 :  % on board " ); ImGui::SameLine();  
          ImGui::Text( "CELLTYPE2 :  % on board " ); ImGui::SameLine();  
          ImGui::Text( "CELLTYPE3 :  % on board " ); ImGui::SameLine();   
        }
        ImGui::Separator();
        {
          ImGui::Text( "Other options: " );
          // TODO : (future work) enable/disable pixel editing with mouse
          ImGui::Text( "..." );
        }
        ImGui::Separator();
        ImGui::End();
      }
    }
  }
  void WindowMapTileImage( int x, int y )
  {
    if ( w_image.show )
    {
      ImGui::SetNextWindowPos( ImVec2( float( x ), float( y ) ), ImGuiCond_FirstUseEver );
      if ( ImGui::Begin( w_image.title, &w_image.show, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize ) )
      {
        ImGui::Image(
          tileGenerator->DrawSelectedBoard(),
          ImVec2( tileGenerator->DrawSizeX(), tileGenerator->DrawSizeY() )
        );
        ImGui::Separator();
        {
          if ( ImGui::SliderInt( "CA Step", &BoardAutomaton::ui_stepSelected, 0, tileGenerator->StepLast() ) ) {}
        }
        ImGui::Separator();
        {
          if ( ImGui::Button( "    0     " ) ) { tileGenerator->StepJumpZero(); } ImGui::SameLine();
          if ( ImGui::Button( "<<< 5 STEP" ) ) { tileGenerator->StepJump( -5 ); } ImGui::SameLine();
          if ( ImGui::Button( "<<< 1 STEP" ) ) { tileGenerator->StepJump( -1 ); } ImGui::SameLine();
          if ( ImGui::Button( "1 STEP >>>" ) ) { tileGenerator->StepJump( 1 ); }  ImGui::SameLine();
          if ( ImGui::Button( "5 STEP >>>" ) ) { tileGenerator->StepJump( 5 ); }  ImGui::SameLine();
          if ( ImGui::Button( "   END    " ) ) { tileGenerator->StepJumpLast(); } 
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
          ImGui::Text( "Rulesets:" );
          if ( ImGui::Button( "Ruleset 1: Game of Life  " ) ) { tileGenerator->SwitchRuleset( 0 ); }
          if ( ImGui::Button( "Ruleset 2: Map Generator " ) ) { tileGenerator->SwitchRuleset( 1 ); }
          if ( ImGui::Button( "Ruleset 3: <  ... ...  > " ) ) { tileGenerator->SwitchRuleset( 2 ); }
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
public:
  MapGenUI( GLFWwindow* window )
  {
    glfwFocusWindow( system_window = window );
    // Setup ImGui binding
    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init( system_window, true );
    ImGui::StyleColorsDark();
    // Initialize automaton with default data
    tileGenerator = new BoardAutomaton( BoardAutomaton::ui_boardSize[0], BoardAutomaton::ui_boardSize[1], BoardAutomaton::ui_stepCount );
    tileGenerator->RegenerateWith( CLEAR_RANDOM );
  }

  ~MapGenUI()
  {
    // Cleanup
    delete tileGenerator;
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
      WindowGenerationControls( 20, 200 );
      WindowMapTileImage( 300, 150 ); // displaying generated tiles
      if ( w_imgui.show ) // Imgui demo for reference to ImGui examples
      {
        ImGui::SetNextWindowPos( ImVec2( 10, 150 ), ImGuiCond_FirstUseEver );
        ImGui::ShowDemoWindow( &w_imgui.show );
      }
    }
    if ( is_program_terminated ) glfwSetWindowShouldClose( system_window, GLFW_TRUE );
  }
};

