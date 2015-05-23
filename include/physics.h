#include "objects/player.h"
#include "objects/wall.h"

int placeMeeting(int top1, int right1, int bottom1, int left1, int top2, int right2, int bottom2, int left2);
void playerWallCollisions(Player * player, Walls * wallsList, int keyJump);
void playerPlayerCollisions(Player * player, Players *playersList, int keyJump);