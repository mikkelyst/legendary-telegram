
#include <stdio.h>
#include <iostream> 

#include <GL\gl3w.h>   
#include <GLFW\glfw3.h> 

#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"  

#include "CellGrid.h"
 

void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Error %d: %s\n", error, description);
}

int main(int, char**)
{
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    GLFWwindow* window = glfwCreateWindow(1600, 900, "ImGui GLFW+OpenGL3 example", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
    gl3wInit();

	static GLuint tex;
	// Black/white checkerboard
	float pixels[] = {
		0.0f, 0.0f, 0.0f,	1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f,	1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f,	1.0f, 1.0f, 1.0f,  0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,	1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f,	1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f,	1.0f, 1.0f, 1.0f,  0.0f, 0.0f, 0.0f
	}; 

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 4, 4, 0, GL_RGB, GL_FLOAT, pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
	

    // Setup ImGui binding
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io; 
    ImGui_ImplGlfwGL3_Init(window, true);

    // Setup ImGui style
    ImGui::StyleColorsDark(); 

    bool show_demo_window = false; 
	bool show_ca_window = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f); 
	 

    // Main loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		ImGui_ImplGlfwGL3_NewFrame();
		{
			ImGui::Text("CA simulation 152017");                             
			ImGui::ColorEdit3("clear color", (float*)&clear_color);  
			ImGui::Checkbox("ImGui Demo Window", &show_demo_window);      // Edit bools storing our windows open/close state 
			ImGui::Checkbox("Simulation  Window", &show_ca_window);
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		}

		if (show_demo_window)
		{
			ImGui::SetNextWindowPos(ImVec2(10, 200), ImGuiCond_FirstUseEver); 
			ImGui::ShowDemoWindow(&show_demo_window);
		}

		if (show_ca_window)
		{
			ImGui::SetNextWindowPos(ImVec2(600, 20), ImGuiCond_FirstUseEver); 
			if (ImGui::Begin("Simulation Window", &show_ca_window, 
				ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings)) 
			{
				ImGui::Image(reinterpret_cast<void*>(tex), ImVec2(800.f, 800.f));
				ImGui::End();
			}
	
		}

        // Rendering
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

		// Render gui
        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
		
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
