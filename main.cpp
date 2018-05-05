
#include <iostream> 

#include <GL\gl3w.h>   
#include <GLFW\glfw3.h> 

#include "MapGenUI.h"
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
    GLFWwindow* window = glfwCreateWindow(1600, 900, "Cellular Automata Map Generator 152017", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
    gl3wInit();

	MapGenUI *uiWindow = new MapGenUI(window);
	CellGrid *cg1 = new CellGrid();

    
	while (!glfwWindowShouldClose(window)) // Main loop
	{
		glfwPollEvents();
		
		uiWindow->UpdateInterface();
		uiWindow->UpdateCellGrid( reinterpret_cast<void*>(cg1->UpdateTexture()) );
		uiWindow->RenderInterface();

		//cg1->ChangePixel()
		
        glfwSwapBuffers(window);
    }

    delete uiWindow;

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
