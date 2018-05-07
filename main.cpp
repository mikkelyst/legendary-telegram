
#include <iostream> 

#include <GL\gl3w.h>   
#include <GLFW\glfw3.h> 

#include "MapGenUI.h"
#include "GridTexture.h"

GLFWwindow* window;


 
void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Error %d: %s\n", error, description);
}

unsigned int glfw_setup()
{
	// Setup window
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
	{
		return 1;
	}
	else {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
		window = glfwCreateWindow(1600, 900, "Cellular Automata Map Generator 152017", NULL, NULL);
		glfwMakeContextCurrent(window);
		glfwSwapInterval(1); // Enable vsync
		gl3wInit();
		return 0;
	}
}

int main(int, char**)
{
	if (glfw_setup()) return 1;

	MapGenUI *uiWindow = new MapGenUI(window);
	GridTexture *gridWindowTex = new GridTexture();

    
	while (!glfwWindowShouldClose(window)) // Main loop
	{
		glfwPollEvents();
		
		uiWindow->Update();
		uiWindow->UpdateCellsWindow( reinterpret_cast<void*>(gridWindowTex->Update()) );
		uiWindow->Render();

		// Now, based on ui settings, make changes to map texture
		gridWindowTex->ChangeTexelState(2, 3, uiWindow->my_pixel);
		
        glfwSwapBuffers(window);
    }

    delete uiWindow;
	delete gridWindowTex;

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
