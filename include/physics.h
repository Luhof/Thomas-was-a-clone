#include "objects/player.h"
#include "objects/wall.h"

int placeMeeting(float top1, float right1, float bottom1, float left1, float top2, float right2, float bottom2, float left2);
void playerWallCollisions(Player * player, Walls * wallsList, int keyJump);
void playerPlayerCollisions(Player * player, Players *playersList, Walls * wallsList, int keyJump);
void getParents(Players * playersList);
int arePlayersOnEndPos(Players * playersList);
int isPlayerOnEndPos(Player * player);