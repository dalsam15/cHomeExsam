#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "board.h"
#include "player.h"

int isGameOver(const Board* board, int color);
int countColor(Board* board, int color);
void RemoveSpaces(char* source);
int validateMove(char * move);
void makeItLower(char * str);
int * getUserInput();
int isMoveLegal(const Board* board, int color, int x, int y);
int checkUp( Board* board, int color, int x, int y);
int checkRight( Board* board, int color, int x, int y);
int checkDown( Board* board, int color, int x, int y);
int checkLeft( Board* board, int color, int x, int y);
int checkDownRight( Board* board, int color, int x, int y);
int checkDownLeft( Board* board, int color, int x, int y);
int checkUpRight( Board* board, int color, int x, int y);
int checkUpLeft( Board* board, int color, int x, int y);

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
	


	int * usrIn;
	int x;
	int y;

	time_t t = time(NULL);
	struct tm *tm = localtime(&t);
	char s[64];
	strftime(s, sizeof(s), "%c", tm);
	FILE *fileDest = fopen("GameLog.txt", "a"); 
	
	fprintf(fileDest, "\n\n\n New game started at: %s \n",s );

	
	while(1){ // gamle loop
		if(BlackTurn){
			if(isGameOver(&currentBoard,1)){
				printf("%s is White and the Winner, CONGRATS!!!\n\n", white.Name);
				exit(0);		
				fclose(fileDest);
			}
			printf("%s is Black! Please enter a move:\n\n", black.Name);
			usrIn=getUserInput();
			x = *(usrIn+0);
			y = *(usrIn+1);

			if (isMoveLegal(&currentBoard, 1,x,y ) == 1){
				printBoard(&currentBoard);
				fprintf(fileDest, "Black -> %d - %d \n",x, y );
				BlackTurn = 0; 
			
			}else{
				if(isGameOver(&currentBoard,1)){
					printf("%s is White and the Winner, CONGRATS!!!\n\n", white.Name);
					exit(0);
					fclose(fileDest);		
				}

				printf("%s\n", "Please enter valid input!");			
				usrIn=getUserInput();
				x = *(usrIn+0);
				y = *(usrIn+1);
				if (isMoveLegal(&currentBoard, 1,x,y ) == 1){
					printBoard(&currentBoard);
					fprintf(fileDest, "Black -> %d - %d \n",x, y  );
					BlackTurn = 0; 
			
				}			
			}	
			
		}if(!BlackTurn){
			if(isGameOver(&currentBoard,0)){
				printf("%s is Black and the Winner, CONGRATS!!!\n\n", black.Name);
				exit(0);
				fclose(fileDest);		
			}
			printf("%s is White! Please enter a move:\n\n", white.Name);
			usrIn=getUserInput();
			x = *(usrIn+0);
			y = *(usrIn+1);

			if (isMoveLegal(&currentBoard, 0,x,y ) == 1){
				printBoard(&currentBoard);
				fprintf(fileDest, "White -> %d - %d \n",x, y  );
				BlackTurn = 1; 
			}else{
				if(isGameOver(&currentBoard,0)){
					printf("%s is Black and the Winner, CONGRATS!!!\n\n", black.Name);
					exit(0);		
					fclose(fileDest);
				}
				printf("%s\n", "Please enter valid input!");			
				usrIn=getUserInput();
				x = *(usrIn+0);
				y = *(usrIn+1);

				if (isMoveLegal(&currentBoard, 0,x,y ) == 1){
					fprintf(fileDest, "White -> %d - %d \n",x, y  );
					printBoard(&currentBoard);
					BlackTurn = 1; 
				}			
			}
		
					
		}
		
	}
	

	
	fclose(fileDest);

	return 0;
	
}



int isGameOver(const Board* board, int color){
	//1 for svart
	//0 for hvit	
	if(color){ // sjekker om noe av den fargen er igjen 
	
		if(countColor(board,1) ==0){
			return 1;		
		}					
	}else{
		if(countColor(board,0) ==0){
			return 1;		
		}				
	}
	return 0;
}

int countColor(Board* board, int color){
	//1 for svart
	//0 for hvit
	int i, j;
	int black = 0;
	int white = 0;
	for(i = 0; i< BOARD_SIZE; i++){
		for( j= 0; j< BOARD_SIZE; j++){
			if(board->fields[i][j] == BLACK){
				black++;			
			}
			if(board->fields[i][j] == WHITE){
				white++;			
			}			
		}	
	}
	if(color){
		return black;		
	}else{
		return white;	
	}


}

int isMoveLegal(const Board* board, int color, int x, int y){
	//1 for svart
	//0 for hvit
	x = x -1;
	y = y -1;
	int legal = 0;
	if(board->fields[x][y] != EMPTY){

		return 0;
	}
	
		
	if (checkUp(board, color,x,y) == 1){
		legal = 1;	
	}
	if (checkRight(board, color,x,y) == 1){
		legal = 1;	
	}
	if (checkDown(board, color,x,y) == 1){
		legal = 1;	
	}

	if (checkLeft(board, color,x,y) == 1){
		legal = 1;	
	}
	if (checkDownRight(board, color,x,y) == 1){
		legal = 1;	
	}
	if (checkDownLeft(board, color,x,y) == 1){
		legal = 1;	
	}
	if (checkUpRight(board, color,x,y) == 1){
		legal = 1;	
	}
	if (checkUpLeft(board, color,x,y) == 1){
		legal = 1;	
	}


	return legal;

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
			if(board->fields[j][i] == EMPTY){
				break;			
			}
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
			if(board->fields[j][i] == EMPTY){
				break;			
			}		
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
			if(board->fields[j][i] == EMPTY){
				break;			
			}
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
			if(board->fields[j][i] == EMPTY){
				break;			
			}			
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
int checkDownLeft( Board* board, int color, int x, int y){
	int CrossAppo = 0;
	int endsWithOwn = 0;
	int j = x - 1;
	int yCounter = y + 1;
	if(color) {  //Black
		if(board->fields[x-1][y+1] == WHITE){
			 CrossAppo = 1;
		}
		for(int i = yCounter;i<= BOARD_SIZE ; i++ ){
			if(board->fields[j][i] == EMPTY){
				break;			
			}
			if(board->fields[j][i] == BLACK){
				 endsWithOwn = 1;
			}
			j--;
		}
	

		if(endsWithOwn && CrossAppo){
			board->fields[x][y] = BLACK;
			j = x - 1;
			for(int i = yCounter;i<= BOARD_SIZE; i++ ){
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

		if(board->fields[x-1][y+1] == BLACK){
			 CrossAppo = 1;
		}
		j=x-1;
		for(int i = yCounter;i<= BOARD_SIZE; i++ ){
			if(board->fields[j][i] == EMPTY){
				break;			
			}			
			if(board->fields[j][i] == WHITE){
				 endsWithOwn = 1;
			}
			j--;
		}
	

		if(endsWithOwn && CrossAppo){//flipp
			board->fields[x][y] = WHITE;
			j = x - 1;
			for(int i = yCounter;i<= BOARD_SIZE; i++ ){	
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
int checkDownRight( Board* board, int color, int x, int y){
	int CrossAppo = 0;
	int endsWithOwn = 0;
	int j = x + 1;
	int yCounter = y + 1;
	if(color) {  //Black
		if(board->fields[x+1][y+1] == WHITE){
			 CrossAppo = 1;
		}
		for(int i = yCounter;i<= BOARD_SIZE ; i++ ){

			if(board->fields[j][i] == EMPTY){
				break;			
			}
			if(board->fields[j][i] == BLACK){
				 endsWithOwn = 1;
			}
			j++;
		}
	

		if(endsWithOwn && CrossAppo){
			board->fields[x][y] = BLACK;
			j = x + 1;
			for(int i = yCounter;i<= BOARD_SIZE ; i++ ){
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

		if(board->fields[x+1][y+1] == BLACK){
			 CrossAppo = 1;
		}
		j=x+1;
		for(int i = yCounter;i<= BOARD_SIZE ; i++ ){
			if(board->fields[j][i] == EMPTY){
				break;			
			}			
			if(board->fields[j][i] == WHITE){
				 endsWithOwn = 1;
			}
			j++;
		}
	

		if(endsWithOwn && CrossAppo){//flipp
			board->fields[x][y] = WHITE;
			j = x + 1;
			for(int i = yCounter;i<= BOARD_SIZE ; i++ ){	
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



int checkUp( Board* board, int color, int x, int y){
	int CrossAppo = 0;
	int endsWithOwn = 0;
	int yCounter = y -1;
	if(color) {  //Black
		if(board->fields[x][y-1] == WHITE){
			 CrossAppo = 1;
		}
		for(int i =  yCounter;i>=0; i-- ){
			if(board->fields[x][i] == EMPTY){
				break;			
			}
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
			if(board->fields[x][i] == EMPTY){
				break;			
			}
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
	int xCounter = x+1;
	if(color) {  //Black
		if(board->fields[x+1][y] == WHITE){
			 CrossAppo = 1;
		}
		for(int i = xCounter;i<= BOARD_SIZE ; i++ ){
			if(board->fields[i][y] == EMPTY){
				break;			
			}
			if(board->fields[i][y] == BLACK){
				 endsWithOwn = 1;
			}
		}

		if(endsWithOwn && CrossAppo){
			board->fields[x][y] = BLACK;
			for(int i =  xCounter;i<= BOARD_SIZE ; i++ ){

				if(board->fields[i][y] == BLACK){
					break;
				}
				if(board->fields[i][y] == WHITE){
					board->fields[i][y] = BLACK;
				}
			}
			return 1;	
		}
	}else{ //White

		if(board->fields[x+1][y] == BLACK){
			 CrossAppo = 1;
		}
		for(int i =  xCounter;i<= BOARD_SIZE ; i++ ){

			if(board->fields[i][y] == EMPTY){
				break;			
			}
	
			if(board->fields[i][y] == WHITE){
				 endsWithOwn = 1;
			}
		}
	

		if(endsWithOwn && CrossAppo){
			board->fields[x][y] = WHITE;
			for(int i =  xCounter;i<= BOARD_SIZE ; i++ ){	
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

int checkLeft( Board* board, int color, int x, int y){
	int CrossAppo = 0;
	int endsWithOwn = 0;
	int xCounter = x - 1;
	if(color) {  //Black
		if(board->fields[x-1][y] == WHITE){
			 CrossAppo = 1;
		}
		for(int i =  xCounter;i>= 0; i-- ){
			if(board->fields[i][y] == EMPTY){
				break;			
			}			
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
				
			if(board->fields[i][y] == EMPTY){
				break;			
			}
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
		for(int i = y+ 1;i< BOARD_SIZE - y ; i++ ){
			if(board->fields[x][i] == EMPTY){
				break;			
			}			

			if(board->fields[x][i] == BLACK){
				 endsWithOwn = 1;
			}
		}
	

		if(endsWithOwn && CrossAppo){
			board->fields[x][y] = BLACK;
			for(int i = y+ 1;i<= BOARD_SIZE - y ; i++ ){
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

		if(board->fields[x][y+1] == BLACK){
			 CrossAppo = 1;
		}
		for(int i = y+ 1;i<= BOARD_SIZE - y ; i++ ){
			if(board->fields[x][i] == EMPTY){
				break;			
			}			

			if(board->fields[x][i] == WHITE){
				 endsWithOwn = 1;
			}
		}
	

		if(endsWithOwn && CrossAppo){
			board->fields[x][y] = WHITE;
			for(int i = y+ 1;i<= BOARD_SIZE - y; i++ ){	
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
	strcpy(str, lower);

}
 //http://stackoverflow.com/questions/20385768/c-pointer-char-to-lowercase



int validateMove(char * move){
	RemoveSpaces(move);
	makeItLower(move);
	if(strlen(move) >2 ){//fjerner komma
		move[1]=' ';
		RemoveSpaces(move);
			
	}	
	return 1;
		
}

int * getUserInput(){

	char move[3];
	scanf(" %[^\n]", move);
	validateMove(move);
	char xChar = move[0];
	char yChar = move[1];
	int x;
	int y;
	static int r[2];
	if(xChar == 'a' ) {
		x = 1;	
	}
	if(xChar == 'b'){
		x = 2;	
	}	
	if(xChar == 'c'){
		x = 3;	
	}
	if(xChar == 'd'){
		x = 4;	
	}	
	if(xChar == 'e'){
		x = 5;	
	}	
	if(xChar == 'f'){
		x = 6;	
	}	
	
	if(xChar == 'g'){
		x = 7;	
	}	
	if(xChar == 'h'){
		x = 8;	
	}

	y = (int) (yChar - '0');
	r[0] = x;
	r[1] = y;

	return r;
	
}
//http://stackoverflow.com/questions/1442116/how-to-get-date-and-time-value-in-c-program

