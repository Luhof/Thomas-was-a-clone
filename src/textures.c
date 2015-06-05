#include "textures.h"

Textures * initTexturesList(){
  Textures * textureList = calloc(1, sizeof(Textures));
  if(textureList==NULL){
    printf("erreur textures\n");
    exit(1);
  }

  textureList->myTexture = NULL;
  textureList->nextTexture = NULL;

  return textureList;
}

Texture * initTexture(char * url){

  Texture * myTexture = calloc(1, sizeof(Texture));
	if(myTexture==NULL){
        fprintf(stderr, "Error initializing players list:(");
        exit(1);
    }
  	myTexture->texture = NULL;
    myTexture->textureX = 0;
    myTexture->textureY = 0;
 // myTexture->textureId;
  //GLuint textureId;
  glGenTextures(1,&myTexture->textureId);
  //glBindTexture(GL_TEXTURE_2D, myTexture->textureId);

  

    GLenum format;
   myTexture->texture = IMG_Load(url);
   if(myTexture->texture==NULL){
   	printf("error can't open file\n");
   	exit(1);
   }
    switch(myTexture->texture->format->BytesPerPixel) {
        case 1:
            format = GL_RED;
            break;
        case 3:
            format = GL_BGR;
            break;
        case 4:
            format = GL_BGRA;
            break;
        default:
            fprintf(stderr, "Format des pixels de l'image non pris en charge\n");
            exit(1);
    }
    myTexture->format = format;
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, myTexture->texture->w, myTexture->texture->h, 0, format, GL_UNSIGNED_BYTE, myTexture->texture->pixels);
    //glBindTexture(GL_TEXTURE_2D, 0);
    //SDL_FreeSurface(myTexture->texture); // Image contenu sur GPU
     

    glBindTexture(GL_TEXTURE_2D, myTexture->textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, myTexture->texture->w, myTexture->texture->h, 0, myTexture->format, GL_UNSIGNED_BYTE, myTexture->texture->pixels);
    
 //glBindTexture(GL_TEXTURE_2D, myTexture->textureId);

 return myTexture;
}

void freeTexture(Texture * texture){
	glDisable(GL_TEXTURE_2D);
	glDeleteTextures(1, &texture->textureId);
  free(texture);
}

void addTexture(Textures * textureList, Texture * newTexture){
  Textures * tempTexture = calloc(1, sizeof(Textures));
  if(newTexture==NULL || textureList==NULL) exit(1);
  tempTexture->myTexture = newTexture;
  
  tempTexture->nextTexture = textureList->firstTexture;
  textureList->firstTexture = tempTexture;
  
}
