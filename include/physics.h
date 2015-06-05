#include "objects/player.h"
#include "objects/wall.h"

//Returns 1 if there is a collision using coordonates
int placeMeeting(float top1, float right1, float bottom1, float left1, float top2, float right2, float bottom2, float left2);
//updates player->wall collisions and fix eventual positions
void playerWallCollisions(Player * player, Walls * wallsList, int keyJump);
//updates player->player collisions and fix eventual positions
void playerPlayerCollisions(Player * player, Players *playersList, Walls * wallsList, int keyJump);
//update isHolding values of a player node
void getParents(Players * playersList);
//return 1 if player has won the level
int arePlayersOnEndPos(Players * playersList);
//return 1 if one character is on its end pos
int isPlayerOnEndPos(Player * player);