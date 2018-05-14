#pragma once  
#include <vector> 

#include <GLFW\glfw3.h>

#define GT_BLACK 0.0f, 0.0f, 0.0f
#define GT_WHITE 1.0f, 1.0f, 1.0f
#define GT_RED   1.0f, 0.0f, 0.0f
#define GT_GREEN 0.0f, 1.0f, 0.0f
#define GT_BLUE  0.0f, 0.0f, 1.0f

class GridTexture
{
private:
  GLuint texID;
  std::vector<float> texelRGBs;
  unsigned int sizex = 0;
  unsigned int sizey = 0;

public:

  GridTexture(unsigned int x = 4, unsigned int y = 4)
  {
    sizex = x;
    sizey = y;
    glGenTextures(1, &texID);
    texelRGBs = std::vector<float>(3 * sizex * sizey, 1.0);
    for (unsigned int i = 0; i < sizex * sizey; i++) {
      float f = (float)(i % 2);
      texelRGBs.at(3 * (i)+0) = f; // R
      texelRGBs.at(3 * (i)+1) = f; // G
      texelRGBs.at(3 * (i)+2) = f; // B 
    }
  }

  ~GridTexture() = default;

  GLuint Update() {
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, sizex, sizey, 0, GL_RGB, GL_FLOAT, texelRGBs.data());
    glGenerateMipmap(GL_TEXTURE_2D);
    return texID;
  }

  void SetTexelColor(unsigned int x, unsigned int y, float r, float g, float b)
  {
    if (x < sizey && y < sizex) {
      texelRGBs[3 * (sizex * y + x) + 0] = r; // R
      texelRGBs[3 * (sizex * y + x) + 1] = g; // G
      texelRGBs[3 * (sizex * y + x) + 2] = b; // B
    }
    return;
  }


};

