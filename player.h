#ifdef __APPLE__
  #include <OpenGL/gl.h>
  #include <OpenGL/glu.h>
#else
  #include <GL/gl.h>
  #include <GL/glu.h>
#endif
 
typedef struct _player{
	float width;
	float height;
	float hspeed;
	float vspeed;
	float posX;
	float posY;
} Player;

void initPlayer(Player * player);
void setPlayerAttr(Player * thomas, float width, float height, float posX, float posY);
void freePlayer(Player * thomas);

void drawPlayer(Player * thomas);

