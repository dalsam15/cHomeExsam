#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "board.h"
#include "player.h"

int main(int argc, char *argv[]){

	player black;
	player white;
	Board currentBoard;
	initBoard(&currentBoard);
/*
	printf("Enter a name for black player: \n");
	gets(black.Name);
	printf("You entered: %s\n", black.Name);


	printf("Enter a name for white player: \n");
	gets(white.Name);
	printf("You entered: %s\n", white.Name);

*/
	setPlayerName(&black,"Sam");
	setPlayerName(&white,"Ahmad");
	int BlackTurn = 1;
		
	printBoard(&currentBoard);
	
	char move[2];
	//scanf("%s", move);
	char xChar;
	char yChar;
	int x;
	int y;


	
	while(1){ // gamle loop
		if(BlackTurn){
			printf("%s is Black! Please enter a move:\n\n", black.Name);
			scanf("%s", move);
			xChar = move[0];
			yChar = move[1];
			x = getXValue(xChar);
			y = (int) (yChar - '0');
			if (isMoveLegal(&currentBoard, 1,x,y ) == 1){
				printBoard(&currentBoard);
				BlackTurn = 0; 
			
			}else{
				printf("%s\n", "Please enter valid input!");			
				scanf("%s", move);
				xChar = move[0];
				yChar = move[1];
				x = getXValue(xChar);
				y = (int) (yChar - '0');
				if (isMoveLegal(&currentBoard, 1,x,y ) == 1){
					printBoard(&currentBoard);
					BlackTurn = 0; 
			
				}			
			}	
			
		}if(!BlackTurn){
			printf("%s is White! Please enter a move:\n\n", white.Name);
			scanf("%s", move);
			xChar = move[0];
			yChar = move[1];
			x = getXValue(xChar);
			y = (int) (yChar - '0');
			if (isMoveLegal(&currentBoard, 0,x,y ) == 1){
				printBoard(&currentBoard);
				BlackTurn = 1; 
			}else{
				printf("%s\n", "Please enter valid input!");			
				scanf("%s", move);
				xChar = move[0];
				yChar = move[1];
				x = getXValue(xChar);
				y = (int) (yChar - '0');
				if (isMoveLegal(&currentBoard, 0,x,y ) == 1){
					printBoard(&currentBoard);
					BlackTurn = 1; 
				}			
			}
		
					
		}
		
	}
	

	
	
	return 0;

}

////[Columns][ROWS]
////[XXXXXXX][YYYY]
int checkUpLeft( Board* board, int color, int x, int y){
	int CrossAppo = 0;
	int endsWithOwn = 0;
	int j = x - 1;
	if(color) {  //Black
		if(board->fields[x-1][y-1] == WHITE){
			 CrossAppo = 1;
		}
		for(int i = y- 1;i>= 0; i-- ){
			if(board->fields[j][i] == BLACK){
				 endsWithOwn = 1;
			}
			j--;
		}
		if(endsWithOwn && CrossAppo){
			board->fields[x][y] = BLACK;
			j = x - 1;
			for(int i = y-1 ;i>=0; i-- ){
				if(board->fields[j][i] == BLACK){
					break;
				}
				if(board->fields[j][i] == WHITE){
					 board->fields[j][i] = BLACK;
				}
				j--;
			}
			return 1;	
		}
	}else{//white

		if(board->fields[x-1][y-1] == BLACK){
			 CrossAppo = 1;
		}
		j=x - 1;
		for(int i = y -1;i>= 0; i-- ){
			printf("x = %d - y = %d \n", j,i);			
			if(board->fields[j][i] == WHITE){
				 endsWithOwn = 1;
			}
			j--;
		}
	

		if(endsWithOwn && CrossAppo){//flipp
			board->fields[x][y] = WHITE;
			j = x - 1;
			for(int i = y- 1;i>= 0; i-- ){	
				if(board->fields[j][i] == WHITE){
					break;
				}
				if(board->fields[j][i] == BLACK){
					 board->fields[j][i] = WHITE;
				}
				j--;
			}
			return 1;	
		}

	}
	return 0;
}
int checkUpRight( Board* board, int color, int x, int y){
	int CrossAppo = 0;
	int endsWithOwn = 0;
	int j = x + 1;
	if(color) {  //Black
		if(board->fields[x+1][y-1] == WHITE){
			 CrossAppo = 1;
		}
		for(int i = y- 1;i>= 0; i-- ){
			if(board->fields[j][i] == BLACK){
				 endsWithOwn = 1;
			}
			j++;
		}
	

		if(endsWithOwn && CrossAppo){
			board->fields[x][y] = BLACK;
			j = x + 1;
			for(int i = y-1 ;i>=0; i-- ){
				if(board->fields[j][i] == BLACK){
					break;
				}
				if(board->fields[j][i] == WHITE){
					 board->fields[j][i] = BLACK;
				}
				j++;
			}
			return 1;	
		}
	}else{//white

		if(board->fields[x+1][y-1] == BLACK){
			 CrossAppo = 1;
		}
		j=x+1;
		for(int i = y -1;i>= 0; i-- ){
			
			if(board->fields[j][i] == WHITE){
				 endsWithOwn = 1;
			}
			j++;
		}
	

		if(endsWithOwn && CrossAppo){//flipp
			board->fields[x][y] = WHITE;
			j = x + 1;
			for(int i = y- 1;i>= 0; i-- ){	
				if(board->fields[j][i] == WHITE){
					break;
				}
				if(board->fields[j][i] == BLACK){
					 board->fields[j][i] = WHITE;
				}
				j++;
			}
			return 1;	
		}

	}
	return 0;
}
int checkDownRight( Board* board, int color, int x, int y){
	int CrossAppo = 0;
	int endsWithOwn = 0;
	int j = x + 1;
	if(color) {  //Black
		if(board->fields[y+1][x+1] == WHITE){
			 CrossAppo = 1;
		}
		for(int i = y+ 1;i<= BOARD_SIZE - y + 1; i++ ){

			if(board->fields[j][i] == BLACK){
				 endsWithOwn = 1;
			}
			j++;
		}
	

		if(endsWithOwn && CrossAppo){
			board->fields[x][y] = BLACK;
			j = x + 1;
			for(int i = y+ 1;i<= BOARD_SIZE - y + 1; i++ ){

				if(board->fields[j][i] == WHITE){
					 board->fields[j][i] = BLACK;
				}
				j++;
			}
			return 1;	
		}
	}else{//white

		if(board->fields[x+1][y+1] == BLACK){
			 CrossAppo = 1;
		}
		j=x+1;
		for(int i = y+ 1;i<= BOARD_SIZE - y + 1; i++ ){
			
			if(board->fields[j][i] == WHITE){
				 endsWithOwn = 1;
			}
			j++;
		}
	

		if(endsWithOwn && CrossAppo){//flipp
			board->fields[x][y] = WHITE;
			j = x + 1;
			for(int i = y+ 1;i<= BOARD_SIZE - y + 1; i++ ){	
				if(board->fields[j][i] == BLACK){
					 board->fields[j][i] = WHITE;
				}
				j++;
			}
			return 1;	
		}

	}
	return 0;
}



int checkUp( Board* board, int color, int x, int y){
	int CrossAppo = 0;
	int endsWithOwn = 0;
	int yCounter = y -1;
	if(color) {  //Black
		if(board->fields[x][y-1] == WHITE){
			 CrossAppo = 1;
			//printf("cp= %d\n",CrossAppo );
		}
		for(int i =  yCounter;i>=0; i-- ){
			//printf("x = %d - y = %d \n", x,i);

			if(board->fields[x][i] == BLACK){
				 endsWithOwn = 1;
			}
		}
	

		if(endsWithOwn && CrossAppo){ //flipp
			board->fields[x][y] = BLACK;
			for(int i =  yCounter;i>=0; i-- ){
				if(board->fields[x][i] == BLACK){
					break;
				}
				if(board->fields[x][i] == WHITE){
					board->fields[x][i] = BLACK;
				}
			}
			return 1;	
		}
	}else{//white
		if(board->fields[x][y-1] == BLACK){
			 CrossAppo = 1;
		}
		for(int i =  yCounter;i>=0; i-- ){

			if(board->fields[x][i] == WHITE){
				 endsWithOwn = 1;
			}
		}
	

		if(endsWithOwn && CrossAppo){ //flipp
			board->fields[x][y] = WHITE;
			for(int i =  yCounter;i>=0; i-- ){
				if(board->fields[x][i] == WHITE){
					break;
				}
				if(board->fields[x][i] == BLACK){
					board->fields[x][i] = WHITE;
				}
			}
			return 1;	
		}	
	}
	return 0;
}
int checkRight( Board* board, int color, int x, int y){
	int CrossAppo = 0;
	int endsWithOwn = 0;
	if(color) {  //Black
		if(board->fields[y][x+1] == WHITE){
			 CrossAppo = 1;
		}
		for(int i =  x + 1;i<= BOARD_SIZE - x + 1; i++ ){


			if(board->fields[y][i] == BLACK){
				 endsWithOwn = 1;
			}
		}
	

		if(endsWithOwn && CrossAppo){
			board->fields[x][y] = BLACK;
			for(int i =  x + 1;i<= BOARD_SIZE - x + 1; i++ ){

				if(board->fields[y][i] == WHITE){
					board->fields[y][i] = BLACK;
				}
			}
			return 1;	
		}
	}else{ //White

		if(board->fields[y][x+1] == BLACK){
			 CrossAppo = 1;
		}
		for(int i =  x + 1;i<= BOARD_SIZE - x + 1; i++ ){
				

			if(board->fields[y][i] == WHITE){
				 endsWithOwn = 1;
			}
		}
	

		if(endsWithOwn && CrossAppo){
			board->fields[x][y] = WHITE;
			for(int i =  x + 1;i<= BOARD_SIZE - x + 1; i++ ){	
				if(board->fields[i][y] == BLACK){
					board->fields[i][y] = WHITE;
				}
			}
			return 1;	
		}

	}
	return 0;
}

int checkLeft( Board* board, int color, int x, int y){
	int CrossAppo = 0;
	int endsWithOwn = 0;
	int xCounter = x - 1;
	if(color) {  //Black
		if(board->fields[x-1][y] == WHITE){
			 CrossAppo = 1;
		}
		for(int i =  xCounter;i>= 0; i-- ){
			
			if(board->fields[i][y] == BLACK){
				 endsWithOwn = 1;
			}
		}
	

		if(endsWithOwn && CrossAppo){
			board->fields[x][y] = BLACK;
			for(int i = xCounter;i>= 0; i-- ){
				if(board->fields[i][y] == BLACK){
					break;
				}				
				if(board->fields[i][y] == WHITE){
					board->fields[i][y] = BLACK;
				}
				
			}
			return 1;	
		}
	}else{ //white
	
		if(board->fields[x-1][y] == BLACK){
			 CrossAppo = 1;
		}
		for(int i =  xCounter;i>= 0; i-- ){
				

			if(board->fields[i][y] == WHITE){
				 endsWithOwn = 1;
			}
		}
	

		if(endsWithOwn && CrossAppo){
			board->fields[x][y] = WHITE;
			for(int i =  xCounter;i>= 0; i-- ){

				if(board->fields[i][y] == WHITE){
					break;
				}
				if(board->fields[i][y] == BLACK){
					
					board->fields[i][y] = WHITE;
				}

			}
			return 1;	
		}
	}
	return 0;
}

int checkDown( Board* board, int color, int x, int y){
	int CrossAppo = 0;
	int endsWithOwn = 0;
	if(color) {  //Black
		
		if(board->fields[x][y+1] == WHITE){
			 CrossAppo = 1;
		}
		//printf("%d\n",CrossAppo);
		for(int i = y+ 1;i< BOARD_SIZE - y ; i++ ){
			

			if(board->fields[x][i] == BLACK){
				 endsWithOwn = 1;
			}
		}
	

		if(endsWithOwn && CrossAppo){
			board->fields[x][y] = BLACK;
			for(int i = y+ 1;i<= BOARD_SIZE - y + 1; i++ ){

				if(board->fields[x][i] == WHITE){
					 board->fields[x][i] = BLACK;
				}
			}
			return 1;	
		}
	}else{//white

		if(board->fields[x][y+1] == BLACK){
			 CrossAppo = 1;
		}
		for(int i = y+ 1;i<= BOARD_SIZE - y + 1; i++ ){
			

			if(board->fields[x][i] == WHITE){
				 endsWithOwn = 1;
			}
		}
	

		if(endsWithOwn && CrossAppo){
			board->fields[x][y+1] = WHITE;
			for(int i = y+ 1;i<= BOARD_SIZE - y + 1; i++ ){	
				if(board->fields[x][i] == BLACK){
					 board->fields[x][i] = WHITE;
				}
			}
			return 1;	
		}

	}
	return 0;
}
int getXValue(char* xChar){
	if(xChar == 'a'){
		return 1;	
	}
	if(xChar == 'b'){
		return 2;	
	}	
	if(xChar == 'c'){
		return 3;	
	}
	if(xChar == 'd'){
		return 4;	
	}	
	if(xChar == 'e'){
		return 5;	
	}	
	if(xChar == 'f'){
		return 6;	
	}	
	
	if(xChar == 'g'){
		return 7;	
	}	
	if(xChar == 'h'){
		return 8;	
	}
	return 100;	
}
void RemoveSpaces(char* source)
{
  char* i = source;
  char* j = source;
  while(*j != 0)
  {
    *i = *j++;
    if(*i != ' ')
      i++;
  }
  *i = 0;
}
//http://stackoverflow.com/questions/1726302/removing-spaces-from-a-string-in-c



void makeItLower(char * str){
	const int length = strlen( str ); 
	char* lower = ( char* )malloc( length + 1 ); 
	lower[ length ] = 0; 

	
	for( int i = 0; i < length; i++ )
	{
	    lower[ i ] = tolower( str[ i ] );
	}
	
	str = lower;

}
 //http://stackoverflow.com/questions/20385768/c-pointer-char-to-lowercase


int isMoveLegal(const Board* board, int color, int x, int y){
	//1 for svart
	//0 for hvit
	x = x -1;
	y = y -1;
	//printf("x= %d - y= %d\n", x, y);
	if(board->fields[y][x] != EMPTY){
		return 0;
	}
		
	if (checkUp(board, color,x,y) == 1 ||checkDown(board, color,x,y) == 1 ||checkRight(board, color,x,y) == 1 ||checkLeft(board, color,x,y) == 1 || checkDownRight(board, color,x,y)==1 || checkUpRight(board, color,x,y)==1 || checkUpLeft(board, color,x,y)==1){
		return 1;	
	}
	

	return 0;

}



int validateMove(char * move){
	RemoveSpaces(move);
	//makeItLower(&move);
	//printf("%s\n", move);
	if(strlen(move) >2 || strlen(move) < 2){
		printf("Invalid input, please try again");
		return 0;			
	}else{
		return 1;
	}

		
}


