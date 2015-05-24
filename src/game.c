#include "game.h"
#include "draw.h"
#include "time.h"
#include "math.h"

void launchGame(){
  
	static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

  //glClearColor(120,146,161, 1); 
  printf("game launched\n");

  /** 
  *INITIALIZING STUFF
  **/
  Color colors[3] = {setColor(105, 210, 231), setColor(243,134,48), setColor(155, 89, 182) };

  //set room attribute
  float gravity = 0.3;

  //set player attributes
  Players *playersList = initPlayerList();
  
  Player *thomas = createPlayer(25.0, 50.0, 60.0, 40.0, 6.0, 7.5, colors[0]);
  Player *marcel = createPlayer(70.0, 70.0, -30, 40.0, 4.0, 3.0, colors[1]);
  Player *pouity = createPlayer(15.0, 80.0, -100, 40.0, 5.0, 9.0, colors[2]);
  thomas->isCurrentPlayer = 1;


  addPlayer(playersList, thomas);
  addPlayer(playersList, marcel);
  addPlayer(playersList, pouity);
    printf("marcel is player %d\n", marcel->id);
  printf("thomas is player %d\n", thomas->id);

  printf("player initialized\n");


  Walls* wallsList = initWallList();
  Wall * wall1 = createWall(300.0, 25.0, -250.0, -100.0);
  Wall * wall2 = createWall(25.0, 150.0, 100.0, -50.0);
  Wall * wall3 = createWall(300.0, 25.0, 100.0, -100.0);
  addWall(wallsList, wall1);
  addWall(wallsList, wall2);
  addWall(wallsList, wall3);

  printf("wall initialized\n");

  int keyJump = 0;
  int keyLeft = 0;
  int keyRight = 0;
  int keySwitch = 0;

  /*float angle = 0;
  float screenRotateSpeed = 0.1;*/
  /**
  *STARTING LOOP
  **/

  int loop = 1;
  printf("started loop\n");
  while(loop){

    

    /* temps au début de la boucle */
    Uint32 startTime = SDL_GetTicks();
    


    /* dessin */
    glClear(GL_COLOR_BUFFER_BIT);



    glMatrixMode(GL_MODELVIEW);
 
    
    glLoadIdentity();

    if(keySwitch) switchCharacter(playersList);
    drawThumbnails(playersList);

     //ça c'est juste pour la frime
/*    if(angle > 10 || angle < -10){
      screenRotateSpeed *= -1;
    }
    angle += screenRotateSpeed;
    glRotatef(angle, 0, 0, 1);*/


      //set speed depending on gravity and player input
      setVSpeed(playersList, gravity);
      setHSpeed(playersList, keyLeft + keyRight);
  
      //use of pseudo-physics to check collisions and jumps
      isColliding(playersList, wallsList, keyJump);

    
      updatePlayerPos(thomas);
      updatePlayerPos(marcel);
      updatePlayerPos(pouity);
      
      drawPlayers(playersList);

      glColor3ub(230,223,215);
      drawWalls(wallsList);


      keyJump = 0;
      keySwitch = 0;

    SDL_GL_SwapBuffers();


    /****************
    EVENT HANDLER
    ******************/

    SDL_Event e;
    while(SDL_PollEvent(&e)) {
      if(e.type == SDL_QUIT) {
        loop = 0;
        break;
      }

      switch(e.type) {


        case SDL_JOYBUTTONDOWN:

          switch(e.jbutton.button)
          {
              case 4 :  //button "Start" pressed
                  loop = 0;
                  break;
              case 11 : // button "A" pressed
                  keyJump = 1; 
                  break;
          }
        break;

        case SDL_JOYAXISMOTION:
          printf("button rpesde : %d\n", e.jaxis.axis);
          switch(e.jaxis.axis){
            case 0 :

              if(e.jaxis.value < -9500){
                  keyLeft = -1;
              }

              else if(e.jaxis.value > 9500){
                  keyRight = 1;
              }
                  
              
              else{
                  keyLeft = 0;
                  keyRight = 0;
              }

              break;

          }
        break;


        case SDL_MOUSEBUTTONUP:
        break;

        case SDL_VIDEORESIZE:
        break;

        case SDL_KEYDOWN:
          switch(e.key.keysym.sym){
            case 'q' :
            case SDLK_ESCAPE :
              loop = 0;
              break;

            case SDLK_RIGHT :
              keyRight = 1;
              break;

            case SDLK_LEFT :
              keyLeft = -1;
              break;

            case SDLK_SPACE :
            case SDLK_UP:
              if(keyJump == 0){
                keyJump = 1;
              }
              break;
            case SDLK_TAB :
              keySwitch = 1;
            break;



            default : break;
            
          }
          break;
          


        case SDL_KEYUP:
            switch(e.key.keysym.sym){
              case SDLK_RIGHT :
                keyRight = 0;
                break;
              case SDLK_LEFT :
                keyLeft = 0;
                break;
              case SDLK_SPACE :
              case SDLK_UP:
                keyJump = 0;
                break;

              default:break;
            }
            break;

        default : break;

      }
      break;
    }

    Uint32 elapsedTime = SDL_GetTicks() - startTime;
    if(elapsedTime < FRAMERATE_MILLISECONDS) {
      SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
    }
  }

     

  free(thomas);

}

