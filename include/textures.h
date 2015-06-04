#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#ifdef __APPLE__
  #include <OpenGL/gl.h>
  #include <OpenGL/glu.h>
#else
  #include <GL/gl.h>
  #include <GL/glu.h>
#endif

#ifndef _TEX_H_
#define _TEX_H_


typedef struct _texture{
	SDL_Surface *texture;
	GLuint textureId;
	GLenum format;
	float textureX;
	float textureY;
} Texture;

typedef struct _textures{
	struct _texture * myTexture;
	struct _textures * nextTexture;
	struct _textures * firstTexture; 
} Textures;

Textures * initTexturesList();
Texture * initTexture(char * url);

void freeTexture(Texture * texture);
void addTexture(Textures * textureList, Texture * newTexture);
#endif