#pragma once  
#include <vector>  
#include <GLFW\glfw3.h>

typedef GLuint Color_RGBA;

const Color_RGBA color_BLACK = 0x000000CC;
const Color_RGBA color_WHITE = 0xFFFFFFCC;
const Color_RGBA color_RED = 0xFF0000CC;
const Color_RGBA color_GREEN = 0x00FF00CC;
const Color_RGBA color_BLUE = 0x0000FFCC;

class SimpleTexture2D
{
private:
  static std::vector<SimpleTexture2D*> textures;

  GLuint texID_GL;
  unsigned int texSizeX;
  unsigned int texSizeY;
  std::vector<Color_RGBA> texelsRGBA;

  SimpleTexture2D( unsigned width, unsigned height )
  {
    texSizeX = width;
    texSizeY = height;
    Clear( color_BLUE );
    glGenTextures( 1, &texID_GL );
    glBindTexture( GL_TEXTURE_2D, texID_GL );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, texSizeX, texSizeY, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, texelsRGBA.data() );
    glGenerateMipmap( GL_TEXTURE_2D );
  }

public: 
  static SimpleTexture2D* Texture( unsigned i )
  {
    if ( !( i < textures.size() ) )
      textures.emplace( textures.begin() + i, new SimpleTexture2D( 2, 2 ) );
    return textures.at( i );
  } 
  ~SimpleTexture2D()
  {
    glDeleteTextures( 1, &texID_GL );
  } 
  void Resize( unsigned width, unsigned height)
  {
    texSizeX = width;
    texSizeY = height;
    Clear( color_BLUE );
    glDeleteTextures( 1, &texID_GL );
    glGenTextures( 1, &texID_GL );
    glBindTexture( GL_TEXTURE_2D, texID_GL );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, texSizeX, texSizeY, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, texelsRGBA.data() );
    glGenerateMipmap( GL_TEXTURE_2D );
    return;
  }
  void* Render()
  {
    glBindTexture( GL_TEXTURE_2D, texID_GL );
    glTexSubImage2D( GL_TEXTURE_2D, 0, 0, 0, texSizeX, texSizeY, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, texelsRGBA.data() );
    return reinterpret_cast<void*>( texID_GL );
  }
  void SetTexelColor( unsigned int x, unsigned int y, Color_RGBA color )
  {
    if ( ( x < texSizeX ) && ( y < texSizeY ) ) texelsRGBA.at( texSizeX * y + x ) = color;
    return;
  }
  void Clear( Color_RGBA clearColor )
  {
    texelsRGBA.assign( texSizeX * texSizeY, clearColor );
  }

};

std::vector<SimpleTexture2D*> SimpleTexture2D::textures = std::vector<SimpleTexture2D*>();

