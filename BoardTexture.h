#pragma once  
#include <vector> 

#include <GLFW\glfw3.h>

typedef struct Color_RGB_3GLf
{
  GLfloat r;
  GLfloat g;
  GLfloat b; 
};

const Color_RGB_3GLf C_BLACK = { 0.0f, 0.0f, 0.0f };
const Color_RGB_3GLf C_WHITE = { 1.0f, 1.0f, 1.0f };
const Color_RGB_3GLf C_RED   = { 1.0f, 0.0f, 0.0f };
const Color_RGB_3GLf C_GREEN = { 0.0f, 1.0f, 0.0f };
const Color_RGB_3GLf C_BLUE  = { 0.0f, 0.0f, 1.0f };

class BoardTexture
{
private:
  GLuint texID;
  std::vector<Color_RGB_3GLf> texelsRGBA;
  unsigned int sizex;
  unsigned int sizey;

public:

  BoardTexture(unsigned int x = 4, unsigned int y = 4)
  {
    sizex = x;
    sizey = y;
    texelsRGBA = std::vector<Color_RGB_3GLf>(sizex * sizey, C_WHITE);
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, sizex, sizey, 0, GL_RGB, GL_FLOAT, texelsRGBA.data());
    glGenerateMipmap(GL_TEXTURE_2D);
  }

  ~BoardTexture() {
    glDeleteTextures(1, &texID);
  }

  GLuint Update() {
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, sizex, sizey, GL_RGB, GL_FLOAT, texelsRGBA.data());
    return texID;
  }

  void SetTexelColor(unsigned int x, unsigned int y, Color_RGB_3GLf color)
  {
    if ((x < sizex) && (y < sizey)) texelsRGBA.at(sizex * y + x) = color;
    return;
  }

  void Clear(Color_RGB_3GLf clearColor)
  {  
    texelsRGBA.assign(sizex * sizey, clearColor);
  }

  void Test()
  { 
    for (unsigned int x = 0; x < sizex; x++) {
      for (unsigned int y = 0; y < sizey; y++) {
        if ((x % 2) ^ (y % 2))
          SetTexelColor(x, y, C_WHITE);
        else
          SetTexelColor(x, y, C_BLACK);
      }
    }
  }

};

