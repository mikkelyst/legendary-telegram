#include <iostream> 

#include <GL\gl3w.h>   
#include <GLFW\glfw3.h> 

#include "UserInterface_MapGenerator.h" 

GLFWwindow* window;

void glfw_error_callback (int error, const char* description)
{
  std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

bool glfwSetupWindow (unsigned int width, unsigned int height, const char* title)
{
  glfwSetErrorCallback (glfw_error_callback);
  if ( glfwInit () )
  {
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint (GLFW_MAXIMIZED, GLFW_TRUE);
#if __APPLE__
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    window = glfwCreateWindow (width, height, title, NULL, NULL);
    glfwMakeContextCurrent (window);
    glfwSwapInterval (1); // Enable vsync
    gl3wInit ();
    return true;
  }
  return false;
}

int main (int, char**)
{
  if ( !glfwSetupWindow (800, 600, "Cellular Automata Map Generator 152017") ) return 1;
  else
  {
    UserInterface_MapGenerator missionControls = UserInterface_MapGenerator (window);
    while ( !glfwWindowShouldClose (window) ) // Main loop
    {
      glfwPollEvents ();
      {
        missionControls.Update ();
        missionControls.Render ();
      }
      glfwSwapBuffers (window);
    }
  }
  glfwDestroyWindow (window);
  glfwTerminate ();
  return 0;
}
