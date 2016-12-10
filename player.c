#include "player.h"
#include "board.h"
#include <string.h>

void setPlayerName(player * thisP, const  char* name){
	strcpy(thisP->Name , name);	
	//thisP->Name = name;

}
/*
void setPlayerColor(player * thisP, const * Field color){
	thisP->Color = color;

}

*/
