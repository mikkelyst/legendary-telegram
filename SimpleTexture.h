#pragma once  
#include <vector>  
#include <GLFW\glfw3.h>

struct Color_RGB_3GLf
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

class SimpleTexture2D
{
private:
  static SimpleTexture2D* single_instance;
  GLuint texID;
  unsigned int texelCountX;
  unsigned int texelCountY;
  std::vector<Color_RGB_3GLf> texelsRGBA;
  
  SimpleTexture2D( unsigned int x, unsigned int y )
  {
    texelCountX = x;
    texelCountY = y;
    texelsRGBA = std::vector<Color_RGB_3GLf>( texelCountX * texelCountY, color_BLUE );
    glGenTextures( 1, &texID );
    glBindTexture( GL_TEXTURE_2D, texID );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, texelCountX, texelCountY, 0, GL_RGB, GL_FLOAT, texelsRGBA.data() );
    glGenerateMipmap( GL_TEXTURE_2D );
  }

public: 
  static void Resize( unsigned width, unsigned height )
  {
    delete single_instance;
    single_instance = new SimpleTexture2D( width, height );
  }

  static SimpleTexture2D* Texture() { 
    if ( !single_instance ) single_instance = new SimpleTexture2D( 4, 4 );
    return single_instance; 
  }

  ~SimpleTexture2D()
  {
    glDeleteTextures( 1, &texID );
  } 

  void* Render()
  {
    glBindTexture( GL_TEXTURE_2D, texID );
    glTexSubImage2D( GL_TEXTURE_2D, 0, 0, 0, texelCountX, texelCountY, GL_RGB, GL_FLOAT, texelsRGBA.data() );
    return reinterpret_cast<void*>( texID );
  }
  void SetTexelColor( unsigned int x, unsigned int y, Color_RGB_3GLf color )
  {
    if ( ( x < texelCountX ) && ( y < texelCountY ) ) texelsRGBA.at( texelCountX * y + x ) = color;
    return;
  }
  void Clear( Color_RGB_3GLf clearColor )
  {
    texelsRGBA.assign( texelCountX * texelCountY, clearColor );
  }

};

SimpleTexture2D* SimpleTexture2D::single_instance = 0;

