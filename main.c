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
	scanf("%s", move);
	char xChar = move[0];
	char yChar = move[1];
	int x = getXValue(xChar);
	int y = (int) (yChar - '0');


	
	while(1){ // gamle loop
		if(BlackTurn){
			printf("%s is Blacks! Please enter a move:\n\n", black.Name);
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
			}	
			
		}if(!BlackTurn){
			printf("%s is White! Please enter a move:\n\n", white.Name);			
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
			}
		
					
		}
		
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

int isMoveLegal(const Board* board, int color, int x, int y){
	//1 for svart
	//0 for hvit
	x = x -1;
	y = y -1;
	//printf("x= %d - y= %d\n", x, y);
	if(board->fields[y][x] != EMPTY){
		return 0;
	}
		
	if (checkUp(board, color,x,y) == 1 ||checkRight(board, color,x,y) == 1
	    ||checkDown(board, color,x,y) == 1 ||checkLeft(board, color,x,y) == 1){
		return 1;	
	}
	

	return 0;

}

int checkUp( Board* board, int color, int x, int y){
	int CrossAppo = 0;
	int endsWithOwn = 0;
	if(color) {  //Black
		if(board->fields[y-1][x] == WHITE){
			 CrossAppo = 1;
		}
		for(int i =  BOARD_SIZE - y + 1;i>=0; i-- ){
			//printf("x = %d - y = %d \n", x,i);	

			if(board->fields[i][x] == BLACK){
				 endsWithOwn = 1;
			}
		}
	

		if(endsWithOwn && CrossAppo){ //flipp
			board->fields[x][y] = BLACK;
			for(int i =  BOARD_SIZE - y + 1;i>=0; i-- ){

				if(board->fields[i][x] == WHITE){
					board->fields[i][x] = BLACK;
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
			//printf("x = %d - y = %d \n", i,y);	

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
	}
	return 0;
}

int checkLeft( Board* board, int color, int x, int y){
	int CrossAppo = 0;
	int endsWithOwn = 0;
	if(color) {  //Black
		if(board->fields[y][x-1] == WHITE){
			 CrossAppo = 1;
		}
		for(int i =  BOARD_SIZE - x + 1;i>= 0; i-- ){
			//printf("x = %d - y = %d \n", i,y);	

			if(board->fields[y][i] == BLACK){
				 endsWithOwn = 1;
			}
		}
	

		if(endsWithOwn && CrossAppo){
			board->fields[x][y] = BLACK;
			for(int i =  BOARD_SIZE - x + 1;i>= 0; i-- ){

				if(board->fields[y][i] == WHITE){
					board->fields[y][i] = BLACK;
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
		if(board->fields[y+1][x] == WHITE){
			 CrossAppo = 1;
		}
		for(int i = y+ 1;i<= BOARD_SIZE - y + 1; i++ ){
			//printf("x = %d - y = %d \n", x,i);	

			if(board->fields[i][x] == BLACK){
				 endsWithOwn = 1;
			}
		}
	

		if(endsWithOwn && CrossAppo){
			board->fields[x][y] = BLACK;
			for(int i = y+ 1;i<= BOARD_SIZE - y + 1; i++ ){

				if(board->fields[i][x] == WHITE){
					 board->fields[i][x] = BLACK;
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

