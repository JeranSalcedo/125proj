//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>

/* Antero, Elvis B 2014-10082 	*/
/* SAlcedo, Jan Raymond 2014-	*/
/* CMSC 125 T6L*/
/* SOKOBAN GAME  */

#include "../../sdk/dexsdk.h"

// DEFINED 
#define clear() printf("\n\n\n\n\n\n\n\n\n")
#define TRUE 1
#define FALSE 2
#define NOT !=
#define OVER 1
#define UP 0
#define LEFT 1
#define DOWN 2
#define RIGHT 3

// DEFINE COLORS OF SQUARES
#define GRASS 19
#define BOXNOTGS 54
#define BOXYESGS 36
#define WALL 56
#define GOALSQ 64
#define SOKOBAN 9

/* PROTOTYPES */
void map_init();
void print_block(int init_x, int init_y);
void print_board();
void changeState0(int direction, int p_y, int p_x);
void changeState1(int direction, int p_y, int p_x);
void move(int direction);

/* GLOBAL VARIABLES */
//GAME OVER condition
int GAME = 0;

//MAP VARIABLES
char **MAP;
int MAP_LENGTH = 15;
int MAP_WIDTH = 15;

// LEVEL VARIABLES
int level = 1;
int boxCounts[6] = {0, 4, 6, 7, 8, 10};
int check;

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
	int i,j, boxesLeft;

	//initialize graphics
	set_graphics(VGA_320X200X256);
	
	//initialize level
	map_init();

	while(GAME NOT OVER){	
		printf("\n\n 125 SOKOBAN\n");

		// if there are still boxes
		if ( boxCounts[level] == 0) {		
			if (level < 5) {
				// printf("Level %d completed!\n", level);
				level = level + 1;
				map_init();
			} else {
				printf(" You finished the game! Congrats! \n");
				GAME = 1;
			}	
		}

		// print board depending on the level
		print_board();

		printf(" Input move: ");
		command = (char)getch();

		//scanf(" %c", &command);

		// w/W is for up
		if(command == 'w' || command == 'W'){
			move(UP);
		// a/A is for left
		} else if(command == 'a' || command == 'A'){
			move(LEFT);
		// s/S is for down
		} else if(command == 's' || command == 'S'){
			move(DOWN);
		// d/D is for right
		} else if(command == 'd' || command == 'D'){
			move(RIGHT);
		// x/X is for exit
		} else if(command == 'x' || command == 'X'){
			printf(" Now exiting sokoban\n");
			GAME = 1;
		} else {
			printf(" That's an invalid input!\n");
		}

	}

	set_graphics(VGA_TEXT80X25X16);
	clrscr();
}

void map_init(){
	int x, y;

	// allocate for map
	MAP = (char **) malloc(MAP_WIDTH * sizeof(char *));
	for(y = 0; y < MAP_LENGTH; y++){
		MAP[y] = (char *) malloc(MAP_LENGTH * sizeof(char));
	}

	//-----BOUNDARY
	for(y = 0; y < MAP_LENGTH; y++){
		for(x = 0; x < MAP_WIDTH; x++){
			if(x == 0 || x == 14 || y == 0 || y == 14){
				MAP[x][y] = 'W';
			} else{
				MAP[x][y] = ' ';
			}
		}
	}

	// map to initialize depends on the level
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

void print_block(int init_x, int init_y){
	int x, y;

	//int color;
	//int type = MAP[][]

	const int X_PADDING = 10;
	const int Y_PADDING = 40;

	init_x *= 10;
	init_y *= 10;
	
	write_pixel(init_x, init_y, 100);
	// for (y = 0; y < 10; y++){
	// 	for (x = 0; x < 10 ; x++){
	// 	}
	// }
	
	//write_pixel();
}

// prints the present state of the map
void print_board(){
	// 
	int X_PADDING = 10;
	int Y_PADDING = 40;
	int x, y, i, j ;
	
	char message_level[2];
	char message_boxes[3];

	// for block
	int color = 0;
	int type;


	//printf(" \nLEVEL %d - - - - - - - - - - - \n", levelStage);
	//printf(" Boxes left: %d\n\n", boxCounts[level]);
	sprintf(message_level, "%d", level);
	sprintf(message_boxes, "%d", level);

	clrscr();

	// (level , )
	write_text("LEVEL", 10, 10, 63, 0);
	write_text(message_level, 70, 10, 63, 0);
	write_text("Boxes left: ", 10, 20, 63, 0);
	write_text(message_boxes, 150, 20, 63, 0);

	write_text("COMMANDS: ", 170, 30, 63, 0);
	write_text("Move up: w", 170, 40, 63, 0);
	write_text("Move left: a", 170, 50, 63, 0);
	write_text("Move down: s", 170, 60, 63, 0);
	write_text("Move right: d", 170, 70, 63, 0);
	write_text("Exit: x", 170, 80, 63, 0);

	for (y = 0; y < MAP_LENGTH; y++){
		for(x = 0; x < MAP_WIDTH; x++){
			
			type = MAP[x][y];

			switch(type){
				case 'b': color = BOXNOTGS; break;
				case 'B': color = BOXYESGS; break;
				case ' ': color = GRASS; break;
				case 'W': color = WALL; break;
				case 's': color = SOKOBAN; break;
				case 'S': color = SOKOBAN; break;
				case 'g': color = GOALSQ;
			}

			for (i=Y_PADDING; i<Y_PADDING + 10; i++){
				for (j=X_PADDING; j<X_PADDING + 10; j++){
					write_pixel(x * 10 + j, y * 10 + i, color);
				}
			}			
			//write_pixel(x*10, y*10, color);
			//color = color + 1;
		}
	}
	/*
	// prints the map and the commands
	for(y = 0; y < MAP_LENGTH; y++){
		for(x = 0; x < MAP_WIDTH; x++){
			printf("%c ", MAP[x][y]);
		}
		
		switch(y){
			case 1: printf("\tCOMMANDS:");
					break;
			case 2: printf("\tMOVE UP: w / W");
					break;
			case 3: printf("\tMOVE LEFT: a / A");
					break;
			case 4: printf("\tMOVE RIGHT: d / D");
					break;
			case 5: printf("\tMOVE DOWN: s / S");
					break;
			case 6: printf("\tEXIT: x / X");
					break;
			case 8: printf("\tW - Wall");
					break;
			case 9: printf("\tb - box not yet on a goal square");
					break;
			case 10: printf("\tB - box on a goal square");
					break;
			case 11: printf("\ts - sokoban not on a goal square");
					break;
			case 12: printf("\tS - sokoban on a goal square");
					break;
			case 13: printf("\tg - goal square");
		}
		printf("\n");
		
	}
	*/
}

// changes state of the sokoban (s)
void changeState0(int direction, int p_y, int p_x){
	int player_xState1, player_yState1;
	
	// change depends on the direction it is heading to
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

	// if the box in front of sokoban is still within the acceptable bounds of the map
	if ( (player_xState1 > 0 || player_xState1 < 14 ) && (player_yState1 > 0 || player_yState1 < 14 ) ){
		// if sokoban is not stepping on the goal square
		if (sokoban_square0_state == 's'){
			MAP[player_y][player_x] = ' ';
			
			// if sokoban is heading to a goal square
			if (sokoban_square1_state == 'g'){
				player_y = player_yState1;
				player_x = player_xState1;
				MAP[player_yState1][player_xState1] = 'S';

			// if sokoban is heeading to a blank square
			} else if (sokoban_square1_state == ' '){
				player_y = player_yState1;
				player_x = player_xState1;
				MAP[player_yState1][player_xState1] = 's';
			}
		// if sokoban is stepping on a goal square
		} else if (sokoban_square0_state == 'S'){
			// map the former stepped square as a goal square
			MAP[player_y][player_x] = 'g';
			
			// if sokoban is heading to a goal square
			if (sokoban_square1_state == 'g'){
				player_y = player_yState1;
				player_x = player_xState1;
				MAP[player_yState1][player_xState1] = 'S';
			// if sokoban is heeading to a blank square
			} else if (sokoban_square1_state == ' '){
				player_y = player_yState1;
				player_x = player_xState1;
				MAP[player_yState1][player_xState1] = 's';
			}
		}	
	// if the box in front of sokoban is not within the acceptable bounds of the map
	} else {
		printf("Move is invalid!\n");
	}
}

// changes state of the square in front of sokoban (s)
void changeState1(int direction, int p_y, int p_x){
	int player_xState2, player_yState2;
	
	// change depends on the direction the sokoban is heading to
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

	// if the square two squares away from sokoban is still within the acceptable bounds of the map
	if ( (player_xState2 > 0 || player_xState2 < 14 ) && (player_yState2 > 0 || player_yState2 < 14 ) ){
		
		// if sokoban is pushing a box away from the goal square
		if (sokoban_square1_state == 'B'){
			// the box will leave the goal square
			MAP[player_yState2][player_xState2] = 'g';
			sokoban_square1_state = 'g';
			
			// therefore reducing the boxes completed
			boxCounts[level] = boxCounts[level] + 1;

		// if sokoban is pushing a box away from a goal square
		} else {
			MAP[player_yState2][player_xState2] = ' ';
			sokoban_square1_state = ' ';
		}
	} else {
		printf("Move is invalid!\n");
	}
}

void move(int direction){
	
	// the move wil depend on the direction the sokoban is heading to
	switch(direction){
		case UP:
			if ( player_x - 1 >= 0) {
				//printf("MOVE IS VALID - %d\n", UP);

				// records state of the square the sokoban occupies and both the two squares it is heading to 
				sokoban_square0_state = MAP[player_y][player_x];
				sokoban_square1_state = MAP[player_y][player_x-1];
				sokoban_square2_state = MAP[player_y][player_x-2];			

				// if the sokoban is heading to a box
				if ( MAP[player_y][player_x-1] == 'b' || MAP[player_y][player_x-1] == 'B' ){
					//printf("first square is a box\n");
					
					// if that box is heading to a goal square
					if ( sokoban_square2_state == 'g' ){
						//printf("second square is a goal square!\n ");
						
						// render the square as a box stepping on a goal square
						MAP[player_y][player_x-2] = 'B';
						sokoban_square2_state = 'B';
						// since a box has been put to a goal square, the number of boxes not on the goal squares will be reduced by one  
						boxCounts[level] = boxCounts[level] - 1;

						// function to change the state of square in front of sokoban
						changeState1(UP, player_y, player_x);
						// function to change the state of square occupied by sokoban						
						changeState0(UP, player_y, player_x);

					// if that box is heading to a blank square
					} else if ( sokoban_square2_state == ' ' ) {
						//printf("second square is blank\n");
						
						// render the square as a box not stepping on a goal square
						MAP[player_y][player_x-2] = 'b';
						sokoban_square2_state = 'b';

						// function to change the state of square in front of sokoban						
						changeState1(UP, player_y, player_x);
						// function to change the state of square occupied by sokoban
						changeState0(UP, player_y, player_x);			
					}
						 
				// if the square on its direction is a goal square
				} else if ( MAP[player_y][player_x-1] == 'g' ) {
					//printf("first square is g\n");
					MAP[player_y][player_x-1] = sokoban_char_goalsquare;

					changeState0(UP, player_y, player_x);
										
				// if the square on its direction is a blank square			
				} else if ( MAP[player_y][player_x-1] == ' ' ) {
					//printf("first square is blank\n");
					MAP[player_y][player_x-1] = 's'; 
					changeState0(UP, player_y, player_x);
				
				} else {
					printf("move unknown\n");
				}

				printf(" SOKOBAN NOW IN SQUARE (%d, %d)\n", player_x, player_y);
			} else {
				printf(" Move is invalid!\n");
			}

			break;

		case LEFT:
			if ( player_y - 1 >= 0){
				//printf("MOVE IS left - %d\n", LEFT);

				// records state of the square the sokoban occupies and both the two squares it is heading to 
				sokoban_square0_state = MAP[player_y][player_x];
				sokoban_square1_state = MAP[player_y-1][player_x];
				sokoban_square2_state = MAP[player_y-2][player_x];			

				// if the sokoban is heading to a box
				if ( MAP[player_y-1][player_x] == 'b' || MAP[player_y-1][player_x] == 'B' ){
					//printf("first square is a box\n");
					
					// if that box is heading to a goal square
					if ( sokoban_square2_state == 'g' ){
						//printf("second square is a goal square!\n ");
						
						// render the square as a box stepping on a goal square
						MAP[player_y-2][player_x] = 'B';
						sokoban_square2_state = 'B';
						
						// reduces boxCounts
						boxCounts[level] = boxCounts[level] - 1;
						
						// function to change the state of square in front of sokoban
						changeState1(LEFT, player_y, player_x);
						// function to change the state of square occupied by sokoban
						changeState0(LEFT, player_y, player_x);
						
					} else if ( sokoban_square2_state == ' ' ) {
						//printf("second square is blank\n");
						
						MAP[player_y-2][player_x] = 'b';
						sokoban_square2_state = 'b';
						// function to change the state of square in front of sokoban
						changeState1(LEFT, player_y, player_x);
						// function to change the state of square occupied by sokoban
						changeState0(LEFT, player_y, player_x);			
					}
						 
				// if the square on its direction is a goal square
				} else if ( MAP[player_y-1][player_x] == 'g' ) {
					//printf("first square is g\n");
					MAP[player_y-1][player_x] = sokoban_char_goalsquare;
					changeState0(LEFT, player_y, player_x);
										
				// if the square on its direction is a blank square			
				} else if ( MAP[player_y-1][player_x] == ' ' ) {
					//printf("first square is blank\n");
					MAP[player_y-1][player_x] = 's'; 
					changeState0(LEFT, player_y, player_x);
				} else {
					printf("move unknown\n");
				}

				printf(" SOKOBAN NOW IN SQUARE (%d, %d)\n", player_x, player_y);
			} else {
				printf(" Move is invalid!\n");
			}

			break;
		case DOWN:
			if ( player_x + 1 <= 14){
				// printf("MOVE IS VALID - %d\n", DOWN);
				
				// records state of the square the sokoban occupies and both the two squares it is heading to 
				sokoban_square0_state = MAP[player_y][player_x];
				sokoban_square1_state = MAP[player_y][player_x+1];
				sokoban_square2_state = MAP[player_y][player_x+2];			

				if ( MAP[player_y][player_x+1] == 'b' || MAP[player_y][player_x+1] == 'B' ){
					// printf("first square is a box\n");
					
					// if that box is heading to a goal square
					if ( sokoban_square2_state == 'g' ){
						// printf("second square is a goal square!\n ");

						// render the square as a box stepping on a goal square
						MAP[player_y][player_x+2] = 'B';
						sokoban_square2_state = 'B';
						
						//reduces boxCounts
						boxCounts[level] = boxCounts[level] - 1;

						// function to change the state of square in front of sokoban
						changeState1(DOWN, player_y, player_x);
						// function to change the state of square occupied by sokoban
						changeState0(DOWN, player_y, player_x);
						
					} else if ( sokoban_square2_state == ' ' ) {
						// printf("second square is blank\n");
						
						MAP[player_y][player_x+2] = 'b';
						sokoban_square2_state = 'b';

						// function to change the state of square in front of sokoban
						changeState1(DOWN, player_y, player_x);
						// function to change the state of square occupied by sokoban
						changeState0(DOWN, player_y, player_x);			
					}
						 
				// if the square on its direction is a goal square
				} else if ( MAP[player_y][player_x+1] == 'g' ) {
					// printf("first square is g\n");
					MAP[player_y][player_x+1] = sokoban_char_goalsquare;
					changeState0(DOWN, player_y, player_x);
										
				// if the square on its direction is a blank square			
				} else if ( MAP[player_y][player_x+1] == ' ' ) {
					// printf("first square is blank\n");
					MAP[player_y][player_x+1] = 's'; 
					changeState0(DOWN, player_y, player_x);
				
				} else {
					printf("move unknown\n");
				}

				printf(" SOKOBAN NOW IN SQUARE (%d, %d)\n", player_x, player_y);
			} else {
				printf(" Move is invalid!\n");
			}

			break;

		case RIGHT:	
			if ( player_y + 1 <= 14){
				// printf("MOVE IS VALID - %d\n", RIGHT);

				// records state of the square the sokoban occupies and both the two squares it is heading to 
				sokoban_square0_state = MAP[player_y][player_x];
				sokoban_square1_state = MAP[player_y+1][player_x];
				sokoban_square2_state = MAP[player_y+2][player_x];			

				// if that box is heading to a goal square
				if ( MAP[player_y+1][player_x] == 'b' || MAP[player_y+1][player_x] == 'B' ){
					// printf("first square is a box\n");
					
					if ( sokoban_square2_state == 'g' ){
						// printf("second square is a goal square!\n ");
						
						// render the square as a box stepping on a goal square
						MAP[player_y+2][player_x] = 'B';
						sokoban_square2_state = 'B';
						
						// reduces boxCounts
						boxCounts[level] = boxCounts[level] - 1;
						
						// function to change the state of square in front of sokoban
						changeState1(RIGHT, player_y, player_x);
						// function to change the state of square occupied by sokoban
						changeState0(RIGHT, player_y, player_x);
						
					} else if ( sokoban_square2_state == ' ' ) {
						// printf("second square is blank\n");
						
						MAP[player_y+2][player_x] = 'b';
						sokoban_square2_state = 'b';
						
						// function to change the state of square in front of sokoban
						changeState1(RIGHT, player_y, player_x);
						// function to change the state of square occupied by sokoban
						changeState0(RIGHT, player_y, player_x);			
					}
						 
				// if the square on its direction is a goal square
				} else if ( MAP[player_y+1][player_x] == 'g' ) {
					// printf("first square is g\n");
					MAP[player_y+1][player_x] = sokoban_char_goalsquare;
					changeState0(RIGHT, player_y, player_x);
										
				// if the square on its direction is a blank square			
				} else if ( MAP[player_y+1][player_x] == ' ' ) {
					// printf("first square is blank\n");
					MAP[player_y+1][player_x] = 's'; 
					changeState0(RIGHT, player_y, player_x);
				
				} else {
					printf(" Move unknown\n");
				}

				printf(" SOKOBAN NOW IN SQUARE (%d, %d)\n", player_x, player_y);
			} else {
				printf(" Move is invalid!\n");
			}

			break;
		default: 
			printf("What is the direction though?");
	}		
}