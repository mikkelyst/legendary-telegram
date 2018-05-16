#pragma once
#include <string>
#include <GLFW\glfw3.h>

#include "imgui\imgui.h"
#include "imgui\imgui_impl_glfw_gl3.h"  

#include "BoardTexture.h"
#include "CellGrid.h" 

const char *build_str = "Build date: " __DATE__ " " __TIME__;

class MapGenUI
{
private:
  GLFWwindow* system_window;
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  BoardTexture *cellGridTex;

  bool show_control_window = true;
  bool show_ca_texture_window = true;
  bool show_imgui_demo_window = false;
  bool is_program_terminated = false;
  int boardsize[2] = { 0,0 };

  void MainMenu()
  {
    if (ImGui::BeginMainMenuBar())
    {
      if (ImGui::BeginMenu("System:"))
      {
        ImGui::MenuItem("New map...", "CTRL+N", false, false);// Disabled item
        ImGui::MenuItem("Quit", "ALT+F4", &is_program_terminated);
        ImGui::EndMenu();
      }
      if (ImGui::BeginMenu("Editing:"))
      {
        ImGui::MenuItem("Undo", "CTRL+Z", false, false);  // Disabled item
        ImGui::MenuItem("Redo", "CTRL+Y", false, false);  // Disabled item 
        ImGui::EndMenu();
      }
      if (ImGui::BeginMenu("View:"))
      {
        ImGui::MenuItem("Window: Parameters Control", NULL, &show_control_window, &show_control_window);
        ImGui::MenuItem("Window: Generated Map Tile", NULL, &show_ca_texture_window, &show_ca_texture_window);
        ImGui::Separator();
        ImGui::MenuItem("Window: ImGui Demo", NULL, &show_imgui_demo_window, &show_imgui_demo_window);
        ImGui::EndMenu();
      }
      if (ImGui::BeginMenu("About:"))
      {
        ImGui::MenuItem("Author", NULL, false, false); // Disabled item
        ImGui::MenuItem("Used libraries", NULL, false, false);// Disabled item
        ImGui::EndMenu();
      }
      ImGui::EndMainMenuBar();
    }
  }
  void ControlWindow(int x, int y)
  {
    if (show_control_window)
    {
      ImGui::SetNextWindowPos(ImVec2(x, y), ImGuiCond_FirstUseEver);
      if (ImGui::Begin("Generation Parameters Control", &show_control_window))
      {
        ImGui::Text(build_str);
        ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Separator();


        // remove this later
        std::string text = "Cell (2,3) is ";
        static bool my_pixel = true;
        text += std::to_string(my_pixel);
        ImGui::Checkbox(text.c_str(), &my_pixel);
        if (my_pixel) cellGridTex->SetTexelColor(2, 3, C_RED);
        else cellGridTex->SetTexelColor(2, 3, C_GREEN);
        ImGui::Separator();
        //
        ImGui::Text("Board Controls:"); 
        ImGui::SliderInt2("Int2", boardsize, 1, 10);
        if (ImGui::Button("Draw a chessboard")) { cellGridTex->Test(); }
        if (ImGui::Button("Clear: White")) { cellGridTex->Clear(C_WHITE); }
        ImGui::SameLine();
        if (ImGui::Button("Clear: Black")) { cellGridTex->Clear(C_BLACK); }
        ImGui::Separator();

        ImGui::End();
      }
    }
  }
  void TilePresentationWindow(int x, int y)
  {
    if (show_ca_texture_window)
    {
      ImGui::SetNextWindowPos(ImVec2(x, y), ImGuiCond_FirstUseEver);
      if (ImGui::Begin("Generated Map Tile", &show_ca_texture_window,
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
      {
        ImGui::Image(reinterpret_cast<void*>(cellGridTex->Update()), ImVec2(600.f, 600.f));
        ImGui::Separator();
        static int selectedStep = 5;
        if (ImGui::SliderInt("Step", &selectedStep, 1, 10)) {
          // update board tex with current cellgrid
        }
        ImGui::End();
      }
    }
  }
  void ImguiDemoWindow(int x, int y)
  {
    if (show_imgui_demo_window)
    {
      ImGui::SetNextWindowPos(ImVec2(x, y), ImGuiCond_FirstUseEver);
      ImGui::ShowDemoWindow(&show_imgui_demo_window);
    }
  }

public: 
  MapGenUI(GLFWwindow* window)
  {
    glfwFocusWindow(system_window = window);
    // Setup ImGui binding
    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(system_window, true);
    ImGui::StyleColorsDark();
    // Setup default cell board texture for rendering
    cellGridTex = new BoardTexture();
  }

  ~MapGenUI()
  {
    // Cleanup
    delete cellGridTex;
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
  }

  void Render() {
    // Rendering
    int display_w, display_h;
    glfwGetFramebufferSize(system_window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    // Render gui
    ImGui::Render();
    ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
  }

  void Update() {
    ImGui_ImplGlfwGL3_NewFrame();
    {
      ImGui::ColorEdit3(" background clear color", (float*)&clear_color);
    } 
    { //// UI: 
      MainMenu(); // on top of system window, main menu.
      ControlWindow(10, 10); // parameters for user to change
      TilePresentationWindow(300, 50); // displaying generated tiles
      ImguiDemoWindow(10, 150); // Imgui demo for reference to ImGui examples
    } 
    if (is_program_terminated) glfwSetWindowShouldClose(system_window, GLFW_TRUE);
  }
};

