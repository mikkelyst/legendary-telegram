#pragma once  
#include <vector> 

#include <GLFW\glfw3.h>

typedef struct Color_RGB_3GLf
{
  GLfloat r;
  GLfloat g;
  GLfloat b;
};

const Color_RGB_3GLf color_BLACK = { 0.0f, 0.0f, 0.0f };
const Color_RGB_3GLf color_WHITE = { 1.0f, 1.0f, 1.0f };
const Color_RGB_3GLf color_RED = { 1.0f, 0.0f, 0.0f };
const Color_RGB_3GLf color_GREEN = { 0.0f, 1.0f, 0.0f };
const Color_RGB_3GLf color_BLUE = { 0.0f, 0.0f, 1.0f };

class BoardTexture2D
{
private:
  GLuint texID;
  std::vector<Color_RGB_3GLf> texelsRGBA;
  unsigned int texelCountX;
  unsigned int texelCountY;

public:
  float displayScale = 5.0f;
  BoardTexture2D( unsigned int x = 64, unsigned int y = 64 )
  {
    texelCountX = x;
    texelCountY = y;
    texelsRGBA = std::vector<Color_RGB_3GLf>( texelCountX * texelCountY, color_WHITE );
    glGenTextures( 1, &texID );
    glBindTexture( GL_TEXTURE_2D, texID );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, texelCountX, texelCountY, 0, GL_RGB, GL_FLOAT, texelsRGBA.data() );
    glGenerateMipmap( GL_TEXTURE_2D );
  }
  ~BoardTexture2D()
  {
    glDeleteTextures( 1, &texID );
  }
  GLuint Update()
  {
    glBindTexture( GL_TEXTURE_2D, texID );
    glTexSubImage2D( GL_TEXTURE_2D, 0, 0, 0, texelCountX, texelCountY, GL_RGB, GL_FLOAT, texelsRGBA.data() );
    return texID;
  }
  float ScaledSizeX() { return texelCountX*displayScale; }
  float ScaledSizeY() { return texelCountY*displayScale; }
  void SetTexelColor( unsigned int x, unsigned int y, Color_RGB_3GLf color )
  {
    if ( ( x < texelCountX ) && ( y < texelCountY ) ) texelsRGBA.at( texelCountX * y + x ) = color;
    return;
  }
  void Clear( Color_RGB_3GLf clearColor )
  {
    texelsRGBA.assign( texelCountX * texelCountY, clearColor );
  }
  void ChessClear()
  {
    for ( unsigned int x = 0; x < texelCountX; x++ )
    {
      for ( unsigned int y = 0; y < texelCountY; y++ )
      {
        if ( ( x % 2 ) ^ ( y % 2 ) )
          SetTexelColor( x, y, color_WHITE );
        else
          SetTexelColor( x, y, color_BLACK );
      }
    }
  }
};

