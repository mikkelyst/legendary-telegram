#pragma once  
#include <vector> 

#include <GLFW\glfw3.h>

typedef struct Color3f
{
  GLfloat r;
  GLfloat g;
  GLfloat b; 
};

const Color3f C_BLACK = { 0.0f, 0.0f, 0.0f };
const Color3f C_WHITE = { 1.0f, 1.0f, 1.0f };
const Color3f C_RED   = { 1.0f, 0.0f, 0.0f };
const Color3f C_GREEN = { 0.0f, 1.0f, 0.0f };
const Color3f C_BLUE  = { 0.0f, 0.0f, 1.0f };

class BoardTexture
{
private:
  GLuint texID;
  std::vector<Color3f> texelsRGBA;
  unsigned int sizex;
  unsigned int sizey;

public:

  BoardTexture(unsigned int x = 4, unsigned int y = 4)
  {
    sizex = x;
    sizey = y;
    texelsRGBA = std::vector<Color3f>(sizex * sizey, C_WHITE);
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

  void SetTexelColor(unsigned int x, unsigned int y, Color3f color)
  {
    if ((x < sizex) && (y < sizey)) texelsRGBA.at(sizex * y + x) = color;
    return;
  }

  void Test()
  {
    Color3f c = C_WHITE;
    for (unsigned int x = 0; x < sizex; x++) {
      for (unsigned int y = 0; y < sizey; y++) { 
        if (x % 2 || y % 2)
          c = C_BLACK;
        else
          c = C_WHITE;
        SetTexelColor(x, y, c);
      }
    }
  }

};

