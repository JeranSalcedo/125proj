#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define clear() printf("\n\n\n\n\n\n\n\n\n")

#define TRUE 1
#define FALSE 2

#define NOT !=
#define OVER 1
//#define LEVEL 1

#define UP 0
#define LEFT 1
#define DOWN 2
#define RIGHT 3

void map_init(int level);
void print_board();
void changeState0(int direction, int p_y, int p_x);
void changeState1(int direction, int p_y, int p_x);
void move(int direction);

//GAME OVER condition
int GAME = 0;

//MAP VARIABLES
char **MAP;
int MAP_LENGTH = 15;
int MAP_WIDTH = 15;

// LEVEL VARIABLES
int level = 0;
int boxCounts[5] = {4, 6, 7, 8, 10};

//PLAYER VARIABLES
int player_x, player_y;
char sokoban_char_not_goalsquare = 's';
char sokoban_char_goalsquare = 'S';

//STATES OF SQUARES
char sokoban_char_oldState;
char sokoban_square0_state;
char sokoban_square1_state;
char sokoban_square2_state;  

// MAIN FUNCTION
int main(){
	char command;

	//-----MAP INITIALIZATION
	if ( boxCounts[level] == 0) {		
		if (level < 4) {
			printf("Level %d completed!\n", level);
			level = level + 1;
		} else {
			printf("You finished the game! Congrats! \n");
			GAME = 1;
		}	
	}  
	map_init(level+1);	

	while(GAME NOT OVER){	
		print_board(level+1);

		printf("Input move: ");
		scanf(" %c", &command);

		if(command == 'w' || command == 'W'){
			move(UP);
		} else if(command == 'a' || command == 'A'){
			move(LEFT);
		} else if(command == 's' || command == 'S'){
			move(DOWN);
		} else if(command == 'd' || command == 'D'){
			move(RIGHT);
		} else {
			printf("That's an invalid input!\n");
		}
	}
}

void map_init(int level){
	int x, y;

	MAP = (char **) malloc(MAP_WIDTH * sizeof(char *));
	for(y = 0; y < MAP_LENGTH; y++){
		MAP[y] = (char *) malloc(MAP_LENGTH * sizeof(char));
	}

	//-----BOUNDARY
	for(y = 0; y < MAP_LENGTH; y++){
		for(x = 0; x < MAP_WIDTH; x++){
			if(x == 0 || x == 14 || y == 0 || y == 14){
				MAP[y][x] = 'W';
			} else{
				MAP[y][x] = ' ';
			}
		}
	}

	switch(level){
		case 1:{
			MAP[7][3] = 'b';
			MAP[7][6] = 'b';
			MAP[7][8] = 'b';
			MAP[7][11] = 'b';

			MAP[1][5] = 'g';
			MAP[1][9] = 'g';
			MAP[13][5] = 'g';
			MAP[13][9] = 'g';

			player_x = 7;
			player_y = 7;
			MAP[player_y][player_x] = sokoban_char_not_goalsquare   ; 
			break;
		}
		case 2:{
			MAP[6][11] = 'b';
			MAP[7][3] = 'b';
			MAP[7][6] = 'b';
			MAP[7][8] = 'b';
			MAP[7][11] = 'b';
			MAP[8][3] = 'b';

			MAP[1][3] = 'g';
			MAP[1][9] = 'g';
			MAP[5][1] = 'g';
			MAP[9][13] = 'g';
			MAP[13][5] = 'g';
			MAP[13][11] = 'g';

			MAP[1][4] = 'W';
			MAP[2][4] = 'W';
			MAP[5][7] = 'W';
			MAP[6][1] = 'W';
			MAP[6][2] = 'W';
			MAP[6][3] = 'W';
			MAP[6][4] = 'W';
			MAP[6][7] = 'W';
			MAP[8][7] = 'W';
			MAP[8][10] = 'W';
			MAP[8][11] = 'W';
			MAP[8][12] = 'W';
			MAP[8][13] = 'W';
			MAP[9][7] = 'W';
			MAP[12][10] = 'W';
			MAP[13][10] = 'W';

			player_x = 7;
			player_y = 7;
			MAP[player_y][player_x] = sokoban_char_not_goalsquare  ;
			break;
		}
		case 3:{
			MAP[4][8] = 'b';
			MAP[4][9] = 'b';
			MAP[5][6] = 'b';
			MAP[7][6] = 'b';
			MAP[7][8] = 'b';
			MAP[8][10] = 'b';
			MAP[8][11] = 'b';

			MAP[1][12] = 'g';
			MAP[3][5] = 'g';
			MAP[9][13] = 'g';
			MAP[11][1] = 'g';
			MAP[11][2] = 'g';
			MAP[11][4] = 'g';
			MAP[13][7] = 'g';

			MAP[1][4] = 'W';
			MAP[1][9] = 'W';
			MAP[2][4] = 'W';
			MAP[2][9] = 'W';
			MAP[3][4] = 'W';
			MAP[3][9] = 'W';
			MAP[3][10] = 'W';
			MAP[3][11] = 'W';
			MAP[3][13] = 'W';
			MAP[4][4] = 'W';
			MAP[5][4] = 'W';
			MAP[6][1] = 'W';
			MAP[6][2] = 'W';
			MAP[6][3] = 'W';
			MAP[6][4] = 'W';
			MAP[6][5] = 'W';
			MAP[6][6] = 'W';
			MAP[10][3] = 'W';
			MAP[10][11] = 'W';
			MAP[10][12] = 'W';
			MAP[10][13] = 'W';
			MAP[11][3] = 'W';
			MAP[11][8] = 'W';
			MAP[11][9] = 'W';
			MAP[11][10] = 'W';
			MAP[12][1] = 'W';
			MAP[12][2] = 'W';
			MAP[12][3] = 'W';
			MAP[12][4] = 'W';
			MAP[12][5] = 'W';
			MAP[12][6] = 'W';
			MAP[12][8] = 'W';
			MAP[13][6] = 'W';
			MAP[13][8] = 'W';

			player_x = 7;
			player_y = 7;
			MAP[player_y][player_x] = sokoban_char_not_goalsquare;
			break;
		}
		case 4:{
			MAP[3][8] = 'b';
			MAP[4][5] = 'b';
			MAP[4][6] = 'b';
			MAP[7][6] = 'b';
			MAP[7][10] = 'b';
			MAP[8][11] = 'b';
			MAP[9][9] = 'b';
			MAP[10][5] = 'b';

			MAP[1][6] = 'g';
			MAP[2][6] = 'g';
			MAP[2][10] = 'g';
			MAP[3][6] = 'g';
			MAP[7][1] = 'g';
			MAP[11][1] = 'g';
			MAP[11][2] = 'g';
			MAP[13][7] = 'g';

			MAP[1][4] = 'W';
			MAP[1][9] = 'W';
			MAP[1][12] = 'W';
			MAP[2][4] = 'W';
			MAP[2][9] = 'W';
			MAP[3][3] = 'W';
			MAP[3][9] = 'W';
			MAP[4][3] = 'W';
			MAP[4][9] = 'W';
			MAP[4][10] = 'W';
			MAP[4][11] = 'W';
			MAP[5][3] = 'W';

			MAP[6][1] = 'W';
			MAP[6][2] = 'W';
			MAP[6][3] = 'W';
			MAP[6][5] = 'W';
			MAP[6][6] = 'W';
			MAP[6][7] = 'W';
			MAP[6][8] = 'W';
			MAP[6][13] = 'W';
			MAP[7][13] = 'W';
			MAP[8][10] = 'W';
			MAP[8][13] = 'W';
			MAP[9][6] = 'W';
			MAP[9][10] = 'W';
			MAP[9][13] = 'W';
			MAP[10][3] = 'W';
			MAP[10][6] = 'W';
			MAP[10][10] = 'W';
			MAP[10][11] = 'W';
			MAP[10][12] = 'W';
			MAP[10][13] = 'W';
			MAP[11][3] = 'W';
			MAP[11][6] = 'W';
			MAP[11][8] = 'W';
			MAP[11][9] = 'W';
			MAP[12][1] = 'W';
			MAP[12][2] = 'W';
			MAP[12][3] = 'W';
			MAP[12][4] = 'W';
			MAP[12][5] = 'W';
			MAP[12][6] = 'W';
			MAP[12][8] = 'W';
			MAP[13][6] = 'W';
			MAP[13][8] = 'W';

			player_x = 7;
			player_y = 7;
			MAP[player_y][player_x] = sokoban_char_not_goalsquare;
			break;
		}
		case 5:{
			MAP[2][5] = 'b';
			MAP[2][11] = 'b';
			MAP[2][12] = 'b';
			MAP[6][1] = 'b';
			MAP[6][4] = 'b';
			MAP[6][9] = 'b';
			MAP[8][2] = 'b';
			MAP[7][6] = 'b';
			MAP[8][11] = 'b';
			MAP[10][5] = 'b';

			MAP[1][8] = 'g';
			MAP[2][10] = 'g';
			MAP[2][7] = 'g';
			MAP[3][1] = 'g';
			MAP[7][3] = 'g';
			MAP[9][3] = 'g';
			MAP[11][1] = 'g';
			MAP[11][2] = 'g';
			MAP[11][7] = 'g';
			MAP[13][9] = 'g';

			MAP[1][4] = 'W';
			MAP[1][9] = 'W';
			MAP[2][4] = 'W';
			MAP[2][8] = 'W';
			MAP[3][2] = 'W';
			MAP[3][4] = 'W';
			MAP[3][7] = 'W';
			MAP[4][3] = 'W';
			MAP[4][9] = 'W';
			MAP[4][10] = 'W';
			MAP[4][11] = 'W';
			MAP[5][3] = 'W';
			MAP[5][6] = 'W';
			MAP[6][2] = 'W';
			MAP[6][3] = 'W';
			MAP[6][5] = 'W';
			MAP[6][6] = 'W';
			MAP[6][11] = 'W';
			MAP[6][12] = 'W';
			MAP[6][13] = 'W';
			MAP[7][8] = 'W';
			MAP[7][13] = 'W';
			MAP[8][9] = 'W';
			MAP[8][13] = 'W';
			MAP[9][6] = 'W';
			MAP[9][13] = 'W';
			MAP[10][11] = 'W';
			MAP[1][1] = 'W';
			MAP[9][4] = 'W';
			MAP[9][8] = 'W';
			MAP[10][3] = 'W';
			MAP[10][6] = 'W';
			MAP[10][7] = 'W';
			MAP[10][8] = 'W';
			MAP[10][11] = 'W';
			MAP[10][12] = 'W';
			MAP[10][13] = 'W';
			MAP[11][3] = 'W';
			MAP[11][6] = 'W';
			MAP[11][8] = 'W';
			MAP[11][11] = 'W';
			MAP[12][3] = 'W';
			MAP[12][4] = 'W';
			MAP[12][5] = 'W';
			MAP[12][6] = 'W';
			MAP[12][10] = 'W';
			MAP[13][6] = 'W';
			MAP[13][10] = 'W';

			player_x = 7;
			player_y = 7;
			MAP[player_y][player_x] = sokoban_char_not_goalsquare;
		}
	}
}

void print_board(int stage){
	int x, y;

	putchar('\n');
	printf(" - - - - - - - - - - - - - - \n");
	printf(" - - - - - LEVEL %d - - - - - \n", stage);
	printf(" - - - - - - - - - - - - - - \n\n");
	printf(" Boxes left: %d\n\n", boxCounts[level]);

	for(y = 0; y < MAP_LENGTH; y++){
		for(x = 0; x < MAP_WIDTH; x++){
			printf("%c ", MAP[x][y]);
		}
		switch(y){
			case 1: printf("\tCOMMANDS:");
					break;
			case 2: printf("\tMOVE UP: W");
					break;
			case 3: printf("\tMOVE LEFT: A");
					break;
			case 4: printf("\tMOVE RIGHT: D");
					break;
			case 5: printf("\tMOVE DOWN: S");
					break;
			case 7: printf("\tW - Wall");
					break;
			case 8: printf("\tb - Box not yet on a goal square");
					break;
			case 9: printf("\tB - Box on a goal square");
					break;
			case 10: printf("\ts - Sokoban not on a goal square");
					break;
			case 11: printf("\tS - Sokoban on a goal square");
					break;
			case 12: printf("\tg - goal square");
		}
		putchar('\n');
	}
}

void changeState0(int direction, int p_y, int p_x){
	int player_xState1, player_yState1;
	
	switch(direction){
		case UP:	
			player_yState1 = p_y;
			player_xState1 = p_x-1;
			break;
		case LEFT: 
			player_yState1 = p_y-1;
			player_xState1 = p_x;
			break;
		case DOWN: 
			player_yState1 = p_y;
			player_xState1 = p_x+1;
			break;
		case RIGHT:
			player_yState1 = p_y+1;
			player_xState1 = p_x;
			break;		
	}

	if ( (player_xState1 > 0 || player_xState1 < 14 ) && (player_yState1 > 0 || player_yState1 < 14 ) ){
		if (sokoban_square0_state == 's'){
			MAP[player_y][player_x] = ' ';
			
			if (sokoban_square1_state == 'g'){
				player_y = player_yState1;
				player_x = player_xState1;
				MAP[player_yState1][player_xState1] = 'S';
			} else if (sokoban_square1_state == ' '){
				player_y = player_yState1;
				player_x = player_xState1;
				MAP[player_yState1][player_xState1] = 's';
			}
		} else if (sokoban_square0_state == 'S'){
			MAP[player_y][player_x] = 'g';
			
			if (sokoban_square1_state == 'g'){
				player_y = player_yState1;
				player_x = player_xState1;
				MAP[player_yState1][player_xState1] = 'S';
			} else if (sokoban_square1_state == ' '){
				player_y = player_yState1;
				player_x = player_xState1;
				MAP[player_yState1][player_xState1] = 's';
			}
		}	
	} else {
		printf("Move is invalid!\n");
	}
}

void changeState1(int direction, int p_y, int p_x){
	int player_xState2, player_yState2;
	
	switch(direction){
		case UP:	
			player_yState2 = p_y;
			player_xState2 = p_x-1;
			break;
		case LEFT: 
			player_yState2 = p_y-1;
			player_xState2 = p_x;
			break;
		case DOWN: 
			player_yState2 = p_y;
			player_xState2 = p_x+1;
			break;
		case RIGHT:
			player_yState2 = p_y+1;
			player_xState2 = p_x;
			break;		
	}

	if ( (player_xState2 > 0 || player_xState2 < 14 ) && (player_yState2 > 0 || player_yState2 < 14 ) ){
		if (sokoban_square1_state == 'B'){
			MAP[player_yState2][player_xState2] = 'g';
			sokoban_square1_state = 'g';
			//reduces boxes completed
			//boxCounts[level] = boxCounts[level] + 1;

		} else {
			MAP[player_yState2][player_xState2] = ' ';
			sokoban_square1_state = ' ';
		}
	} else {
		printf("Move is invalid!\n");
	}
}

void move(int direction){
	
	switch(direction){
		case UP:
			if ( player_x - 1 >= 0) {
				printf("MOVE IS VALID - %d\n", UP);

				sokoban_square0_state = MAP[player_y][player_x];
				sokoban_square1_state = MAP[player_y][player_x-1];
				sokoban_square2_state = MAP[player_y][player_x-2];			

				// IF BOX IS AGAINST ITS DIRECTION
				// CHANGE STATE1 FIRST

				if ( MAP[player_y][player_x-1] == 'b' || MAP[player_y][player_x-1] == 'B' ){
					printf("first square is a box\n");
					
					if ( sokoban_square2_state == 'g' ){
						printf("second square is a goal square!\n ");
						
						MAP[player_y][player_x-2] = 'B';
						sokoban_square2_state = 'B';
						boxCounts[level] = boxCounts[level] - 1;

						changeState1(UP, player_y, player_x);
						changeState0(UP, player_y, player_x);
						
					} else if ( sokoban_square2_state == ' ' ) {
						printf("second square is blank\n");
						
						MAP[player_y][player_x-2] = 'b';
						sokoban_square2_state = 'b';

						changeState1(UP, player_y, player_x);
						changeState0(UP, player_y, player_x);			
					}
						 
				// if the square on its direction is a goal square
				} else if ( MAP[player_y][player_x-1] == 'g' ) {
					printf("first square is g\n");
					MAP[player_y][player_x-1] = sokoban_char_goalsquare;
					changeState0(UP, player_y, player_x);
										
				// if the square on its direction is a blank square			
				} else if ( MAP[player_y][player_x-1] == ' ' ) {
					printf("first square is blank\n");
					MAP[player_y][player_x-1] = 's'; 
					changeState0(UP, player_y, player_x);
				
				} else {
					printf("move unknown\n");
				}

				printf("SOKOBAN NOW IN SQUARE (%d, %d)\n", player_x, player_y);
			} else {
				printf("MOVE NOT VALID!\n");
			}

			break;

		case LEFT:
			if ( player_y - 1 >= 0){
				printf("MOVE IS left - %d\n", LEFT);
				//printf("UMABOT!\n");

				sokoban_square0_state = MAP[player_y][player_x];
				sokoban_square1_state = MAP[player_y-1][player_x];
				sokoban_square2_state = MAP[player_y-2][player_x];			

				// IF BOX IS AGAINST ITS DIRECTION
				// CHANGE STATE1 FIRST

				if ( MAP[player_y-1][player_x] == 'b' || MAP[player_y-1][player_x] == 'B' ){
					printf("first square is a box\n");
					
					if ( sokoban_square2_state == 'g' ){
						printf("second square is a goal square!\n ");
						
						MAP[player_y-2][player_x] = 'B';
						sokoban_square2_state = 'B';
						boxCounts[level] = boxCounts[level] - 1;

						changeState1(LEFT, player_y, player_x);
						changeState0(LEFT, player_y, player_x);
						
					} else if ( sokoban_square2_state == ' ' ) {
						printf("second square is blank\n");
						
						MAP[player_y-2][player_x] = 'b';
						sokoban_square2_state = 'b';

						changeState1(LEFT, player_y, player_x);
						changeState0(LEFT, player_y, player_x);			
					}
						 
				// if the square on its direction is a goal square
				} else if ( MAP[player_y-1][player_x] == 'g' ) {
					printf("first square is g\n");
					MAP[player_y-1][player_x] = sokoban_char_goalsquare;
					changeState0(LEFT, player_y, player_x);
										
				// if the square on its direction is a blank square			
				} else if ( MAP[player_y-1][player_x] == ' ' ) {
					printf("first square is blank\n");
					MAP[player_y-1][player_x] = 's'; 
					changeState0(LEFT, player_y, player_x);
				} else {
					printf("move unknown\n");
				}

				printf("SOKOBAN NOW IN SQUARE (%d, %d)\n", player_x, player_y);
			} else {
				printf("MOVE NOT VALID!\n");
			}

			break;
		case DOWN:
			if ( player_x + 1 <= 14){
				printf("MOVE IS VALID - %d\n", DOWN);

				sokoban_square0_state = MAP[player_y][player_x];
				sokoban_square1_state = MAP[player_y][player_x+1];
				sokoban_square2_state = MAP[player_y][player_x+2];			

				// IF BOX IS AGAINST ITS DIRECTION
				// CHANGE STATE1 FIRST

				if ( MAP[player_y][player_x+1] == 'b' || MAP[player_y][player_x+1] == 'B' ){
					printf("first square is a box\n");
					
					if ( sokoban_square2_state == 'g' ){
						printf("second square is a goal square!\n ");
						
						MAP[player_y][player_x+2] = 'B';
						sokoban_square2_state = 'B';

						changeState1(DOWN, player_y, player_x);
						changeState0(DOWN, player_y, player_x);
						
					} else if ( sokoban_square2_state == ' ' ) {
						printf("second square is blank\n");
						
						MAP[player_y][player_x+2] = 'b';
						sokoban_square2_state = 'b';
						boxCounts[level] = boxCounts[level] - 1;

						changeState1(DOWN, player_y, player_x);
						changeState0(DOWN, player_y, player_x);			
					}
						 
				// if the square on its direction is a goal square
				} else if ( MAP[player_y][player_x+1] == 'g' ) {
					printf("first square is g\n");
					MAP[player_y][player_x+1] = sokoban_char_goalsquare;
					changeState0(DOWN, player_y, player_x);
										
				// if the square on its direction is a blank square			
				} else if ( MAP[player_y][player_x+1] == ' ' ) {
					printf("first square is blank\n");
					MAP[player_y][player_x+1] = 's'; 
					changeState0(DOWN, player_y, player_x);
				
				} else {
					printf("move unknown\n");
				}

				printf("SOKOBAN NOW IN SQUARE (%d, %d)\n", player_x, player_y);
			} else {
				printf("MOVE NOT VALID!\n");
			}

			break;

		case RIGHT:	
			if ( player_y + 1 <= 14){
				printf("MOVE IS VALID - %d\n", RIGHT);

				sokoban_square0_state = MAP[player_y][player_x];
				sokoban_square1_state = MAP[player_y+1][player_x];
				sokoban_square2_state = MAP[player_y+2][player_x];			

				// IF BOX IS AGAINST ITS DIRECTION
				// CHANGE STATE1 FIRST

				if ( MAP[player_y+1][player_x] == 'b' || MAP[player_y+1][player_x] == 'B' ){
					printf("first square is a box\n");
					
					if ( sokoban_square2_state == 'g' ){
						printf("second square is a goal square!\n ");
						
						MAP[player_y+2][player_x] = 'B';
						sokoban_square2_state = 'B';
						boxCounts[level] = boxCounts[level] - 1;

						changeState1(RIGHT, player_y, player_x);
						changeState0(RIGHT, player_y, player_x);
						
					} else if ( sokoban_square2_state == ' ' ) {
						printf("second square is blank\n");
						
						MAP[player_y+2][player_x] = 'b';
						sokoban_square2_state = 'b';

						changeState1(RIGHT, player_y, player_x);
						changeState0(RIGHT, player_y, player_x);			
					}
						 
				// if the square on its direction is a goal square
				} else if ( MAP[player_y+1][player_x] == 'g' ) {
					printf("first square is g\n");
					MAP[player_y+1][player_x] = sokoban_char_goalsquare;
					changeState0(RIGHT, player_y, player_x);
										
				// if the square on its direction is a blank square			
				} else if ( MAP[player_y+1][player_x] == ' ' ) {
					printf("first square is blank\n");
					MAP[player_y+1][player_x] = 's'; 
					changeState0(RIGHT, player_y, player_x);
				
				} else {
					printf("move unknown\n");
				}

				printf("SOKOBAN NOW IN SQUARE (%d, %d)\n", player_x, player_y);
			} else {
				printf("MOVE NOT VALID!\n");
			}

			break;
		default: 
			printf("What is the direction though?");
	}		
}