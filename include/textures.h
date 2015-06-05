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
	int isFront;
} Texture;

typedef struct _textures{
	struct _texture * myTexture;
	struct _textures * nextTexture;
	struct _textures * firstTexture; 
} Textures;

//initialize a Texture List
Textures * initTexturesList();
//create a texture usable and drawable from an url
Texture * initTexture(char * url);

//frees a texture
void freeTexture(Texture * texture);
//add a texture to a Texture List.
void addTexture(Textures * textureList, Texture * newTexture);
#endif