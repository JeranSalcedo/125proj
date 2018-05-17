
/* CMSC 125					T-6L
 * SOKOBAN GAME
 *
 * Antero, Elvis B 			2014-10082
 * Salcedo, Jan Raymond G.	2014-44921
 */

#include "../../sdk/dexsdk.h"

#define TRUE 1
#define FALSE 0

#define IS =
#define NOT !=
#define OVER 1
#define ONGOING 0
#define BLOCK_SIZE 10
#define INITIAL_LEVEL 0

#define UP 0
#define LEFT 1
#define DOWN 2
#define RIGHT 3

#define BOX_N 'b'
#define BOX_Y 'B'
#define GOAL 'g'
#define PLAYER_N 'p'
#define PLAYER_Y 'P'
#define SPACE ' '
#define WALL 'w'

#define COLOR_BOX_N 19
#define COLOR_BOX_Y 54
#define COLOR_GOAL 36
#define COLOR_PLAYER 56
#define COLOR_SPACE 64
#define COLOR_WALL 9

void init_map();
void print_tooltip(int mode);
void print_board();
void move(int direction);
void changeState0(int direction, int p_y, int p_x);
void changeState1(int direction, int p_y, int p_x);

int GAME;
char **MAP;
int MAP_LENGTH = 15;
int MAP_WIDTH = 15;
int changed_block_x = -1;
int changed_block_y = -1;

int current_level = 4;
int number_of_boxes[6] = {0, 4, 6, 7, 8, 10};
int boxes_remaining = 0;

int player_x, player_y;

int main(){
	char command;

	//initialization
	set_graphics(VGA_320X200X256);
	GAME IS ONGOING;

	print_tooltip(0);
	while(GAME NOT OVER){	
		// if there are still boxes
		if(boxes_remaining == 0){		
			if(current_level < 5){
				current_level++;
				init_map();

				//updates the level and boxes
				print_tooltip(1);
			} else{
				//exits the game
				break;
			}
		}

		command = (char) getch();
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
		} else if(command == 'r' || command == 'R'){
			// restarts the current level
			boxes_remaining = number_of_boxes[current_level];
			print_tooltip(2);
			init_map();
		} else if(command == 't' || command == 'T'){
			// restarts from the first level
			current_level = 1;
			boxes_remaining = number_of_boxes[current_level];
			print_tooltip(1);
			init_map();
		} else if(command == 'x' || command == 'X'){
			//exits the game
			break;
		}

	}

	set_graphics(VGA_TEXT80X25X16);
	clrscr();
}

void init_map(){
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
				MAP[x][y] = WALL;
			} else{
				MAP[x][y] = SPACE;
			}
		}
	}

	// map to initialize depends on the level
	switch(current_level){
		case 1:{
			MAP[7][3] = BOX_N;
			MAP[7][6] = BOX_N;
			MAP[7][8] = BOX_N;
			MAP[7][11] = BOX_N;

			MAP[1][5] = GOAL;
			MAP[1][9] = GOAL;
			MAP[13][5] = GOAL;
			MAP[13][9] = GOAL;

			player_x = 7;
			player_y = 7;
			break;
		}
		case 2:{
			MAP[6][11] = BOX_N;
			MAP[7][3] = BOX_N;
			MAP[7][6] = BOX_N;
			MAP[7][8] = BOX_N;
			MAP[7][11] = BOX_N;
			MAP[8][3] = BOX_N;

			MAP[1][3] = GOAL;
			MAP[1][9] = GOAL;
			MAP[5][1] = GOAL;
			MAP[9][13] = GOAL;
			MAP[13][5] = GOAL;
			MAP[13][11] = GOAL;

			MAP[1][4] = WALL;
			MAP[2][4] = WALL;
			MAP[5][7] = WALL;
			MAP[6][1] = WALL;
			MAP[6][2] = WALL;
			MAP[6][3] = WALL;
			MAP[6][4] = WALL;
			MAP[6][7] = WALL;
			MAP[8][7] = WALL;
			MAP[8][10] = WALL;
			MAP[8][11] = WALL;
			MAP[8][12] = WALL;
			MAP[8][13] = WALL;
			MAP[9][7] = WALL;
			MAP[12][10] = WALL;
			MAP[13][10] = WALL;

			player_x = 7;
			player_y = 7;
			break;
		}
		case 3:{
			MAP[4][8] = BOX_N;
			MAP[4][9] = BOX_N;
			MAP[5][6] = BOX_N;
			MAP[7][6] = BOX_N;
			MAP[7][8] = BOX_N;
			MAP[8][10] = BOX_N;
			MAP[8][11] = BOX_N;

			MAP[1][12] = GOAL;
			MAP[3][5] = GOAL;
			MAP[9][13] = GOAL;
			MAP[11][1] = GOAL;
			MAP[11][2] = GOAL;
			MAP[11][4] = GOAL;
			MAP[13][7] = GOAL;

			MAP[1][4] = WALL;
			MAP[1][9] = WALL;
			MAP[2][4] = WALL;
			MAP[2][9] = WALL;
			MAP[3][4] = WALL;
			MAP[3][9] = WALL;
			MAP[3][10] = WALL;
			MAP[3][11] = WALL;
			MAP[3][13] = WALL;
			MAP[4][4] = WALL;
			MAP[5][4] = WALL;
			MAP[6][1] = WALL;
			MAP[6][2] = WALL;
			MAP[6][3] = WALL;
			MAP[6][4] = WALL;
			MAP[6][5] = WALL;
			MAP[6][6] = WALL;
			MAP[10][3] = WALL;
			MAP[10][11] = WALL;
			MAP[10][12] = WALL;
			MAP[10][13] = WALL;
			MAP[11][3] = WALL;
			MAP[11][8] = WALL;
			MAP[11][9] = WALL;
			MAP[11][10] = WALL;
			MAP[12][1] = WALL;
			MAP[12][2] = WALL;
			MAP[12][3] = WALL;
			MAP[12][4] = WALL;
			MAP[12][5] = WALL;
			MAP[12][6] = WALL;
			MAP[12][8] = WALL;
			MAP[13][6] = WALL;
			MAP[13][8] = WALL;

			player_x = 7;
			player_y = 7;
			break;
		}
		case 4:{
			MAP[3][8] = BOX_N;
			MAP[4][5] = BOX_N;
			MAP[4][6] = BOX_N;
			MAP[7][6] = BOX_N;
			MAP[7][10] = BOX_N;
			MAP[8][11] = BOX_N;
			MAP[9][9] = BOX_N;
			MAP[10][5] = BOX_N;

			MAP[1][6] = GOAL;
			MAP[2][6] = GOAL;
			MAP[2][10] = GOAL;
			MAP[3][6] = GOAL;
			MAP[7][1] = GOAL;
			MAP[11][1] = GOAL;
			MAP[11][2] = GOAL;
			MAP[13][7] = GOAL;

			MAP[1][4] = WALL;
			MAP[1][9] = WALL;
			MAP[1][12] = WALL;
			MAP[2][4] = WALL;
			MAP[2][9] = WALL;
			MAP[3][3] = WALL;
			MAP[3][9] = WALL;
			MAP[4][3] = WALL;
			MAP[4][9] = WALL;
			MAP[4][10] = WALL;
			MAP[4][11] = WALL;
			MAP[5][3] = WALL;

			MAP[6][1] = WALL;
			MAP[6][2] = WALL;
			MAP[6][3] = WALL;
			MAP[6][5] = WALL;
			MAP[6][6] = WALL;
			MAP[6][8] = WALL;
			MAP[6][13] = WALL;
			MAP[7][13] = WALL;
			MAP[8][10] = WALL;
			MAP[8][13] = WALL;
			MAP[9][6] = WALL;
			MAP[9][10] = WALL;
			MAP[9][13] = WALL;
			MAP[10][3] = WALL;
			MAP[10][6] = WALL;
			MAP[10][10] = WALL;
			MAP[10][11] = WALL;
			MAP[10][12] = WALL;
			MAP[10][13] = WALL;
			MAP[11][3] = WALL;
			MAP[11][6] = WALL;
			MAP[11][8] = WALL;
			MAP[11][9] = WALL;
			MAP[12][1] = WALL;
			MAP[12][2] = WALL;
			MAP[12][3] = WALL;
			MAP[12][4] = WALL;
			MAP[12][5] = WALL;
			MAP[12][6] = WALL;
			MAP[12][8] = WALL;
			MAP[13][6] = WALL;
			MAP[13][8] = WALL;

			player_x = 7;
			player_y = 7;
			break;
		}
		case 5:{
			MAP[2][5] = BOX_N;
			MAP[2][11] = BOX_N;
			MAP[2][12] = BOX_N;
			MAP[6][1] = BOX_N;
			MAP[6][4] = BOX_N;
			MAP[6][9] = BOX_N;
			MAP[8][2] = BOX_N;
			MAP[7][6] = BOX_N;
			MAP[8][11] = BOX_N;
			MAP[10][5] = BOX_N;

			MAP[1][8] = GOAL;
			MAP[2][10] = GOAL;
			MAP[2][7] = GOAL;
			MAP[3][1] = GOAL;
			MAP[7][3] = GOAL;
			MAP[9][3] = GOAL;
			MAP[11][1] = GOAL;
			MAP[11][2] = GOAL;
			MAP[11][7] = GOAL;
			MAP[13][9] = GOAL;

			MAP[1][4] = WALL;
			MAP[1][9] = WALL;
			MAP[2][4] = WALL;
			MAP[2][8] = WALL;
			MAP[3][2] = WALL;
			MAP[3][4] = WALL;
			MAP[3][7] = WALL;
			MAP[4][3] = WALL;
			MAP[4][9] = WALL;
			MAP[4][10] = WALL;
			MAP[4][11] = WALL;
			MAP[5][3] = WALL;
			MAP[6][2] = WALL;
			MAP[6][3] = WALL;
			MAP[6][11] = WALL;
			MAP[6][12] = WALL;
			MAP[6][13] = WALL;
			MAP[7][8] = WALL;
			MAP[7][13] = WALL;
			MAP[8][13] = WALL;
			MAP[9][6] = WALL;
			MAP[9][13] = WALL;
			MAP[10][11] = WALL;
			MAP[1][1] = WALL;
			MAP[9][4] = WALL;
			MAP[9][8] = WALL;
			MAP[10][3] = WALL;
			MAP[10][6] = WALL;
			MAP[10][7] = WALL;
			MAP[10][8] = WALL;
			MAP[10][11] = WALL;
			MAP[10][12] = WALL;
			MAP[10][13] = WALL;
			MAP[11][3] = WALL;
			MAP[11][6] = WALL;
			MAP[11][8] = WALL;
			MAP[11][11] = WALL;
			MAP[12][3] = WALL;
			MAP[12][6] = WALL;
			MAP[12][11] = WALL;
			MAP[13][6] = WALL;
			MAP[13][10] = WALL;

			player_x = 7;
			player_y = 7;
		}
	}

	MAP[player_x][player_y] = PLAYER_N;
	boxes_remaining = number_of_boxes[current_level];
	print_board(0);
}

void print_tooltip(int mode){
	int x, y;
	
	char message_level[2];
	char message_boxes[3];

	switch(mode){
		case 0:
			write_text("LEVEL", 10, 10, 63, 0);
			write_text("Boxes left: ", 10, 20, 63, 0);

			write_text("COMMANDS: ", 170, 30, 63, 0);
			write_text("move up: w", 170, 40, 63, 0);
			write_text("move left: a", 170, 50, 63, 0);
			write_text("move down: s", 170, 60, 63, 0);
			write_text("move right: d", 170, 70, 63, 0);
			write_text("restart level: r", 170, 90, 63, 0);
			write_text("restart game: t", 170, 100, 63, 0);
			write_text("exit: x", 170, 110, 63, 0);
		case 1:
			sprintf(message_level, "%d", current_level);
			for(y = 10; y < 20; y++){
				for(x = 60; x < 70; x++){
					write_pixel(x, y, 100);
				}
			}
			write_text(message_level, 60, 10, 63, 0);
		case 2:
			sprintf(message_boxes, "%d", boxes_remaining);
			for(y = 20; y < 30; y++){
				for(x = 115; x < 145; x++){
					write_pixel(x, y, 100);
				}
			}
			write_text(message_boxes, 115, 20, 63, 0);
	}
}

// prints the present state of the map
void print_board(int mode){
	int x, y, i, j, color, type;
	
	const int X_PADDING = 10;
	const int Y_PADDING = 40;

	switch(mode){
		case 0:{
			for (y = 0; y < MAP_LENGTH; y++){
				for(x = 0; x < MAP_WIDTH; x++){
					type = MAP[x][y];

					switch(type){
						case BOX_N: color = COLOR_BOX_N; break;
						case BOX_Y: color = COLOR_BOX_Y; break;
						case GOAL: color = COLOR_GOAL; break;
						case PLAYER_N:
						case PLAYER_Y: color = COLOR_PLAYER; break;
						case SPACE: color = COLOR_SPACE; break;
						case WALL: color = COLOR_WALL; break;
						default: color = WHITE;
					}

					for(i = Y_PADDING; i < Y_PADDING + BLOCK_SIZE; i++){
						for(j = X_PADDING; j < X_PADDING + BLOCK_SIZE; j++){
							write_pixel(x * BLOCK_SIZE + j, y * BLOCK_SIZE + i, color);
						}
					}
				}
			}
			break;
		}
		case 1:{
			type = MAP[changed_block_x][changed_block_y];

			switch(type){
				case BOX_N: color = COLOR_BOX_N; break;
				case BOX_Y: color = COLOR_BOX_Y; break;
				case GOAL: color = COLOR_GOAL; break;
				case PLAYER_N:
				case PLAYER_Y: color = COLOR_PLAYER; break;
				case SPACE: color = COLOR_SPACE; break;
				case WALL: color = COLOR_WALL; break;
				default: color = WHITE;
			}

			for(y = Y_PADDING; y < Y_PADDING + BLOCK_SIZE; y++){
				for(x = X_PADDING; x < X_PADDING + BLOCK_SIZE; x++){
					write_pixel(changed_block_x * BLOCK_SIZE + x, changed_block_y * BLOCK_SIZE + y, color);
				}
			}
			changed_block_x = changed_block_y = -1;
		}
	}
}

void move(int direction){
	
	// the move wil depend on the direction the sokoban is heading to
	switch(direction){
		case UP:{
			//checks if the move is valid
			if(
				//block is unoccupied OR block has a BOX but the next block is unoccupied
				MAP[player_x][player_y - 1] == SPACE ||
				MAP[player_x][player_y - 1] == GOAL ||
				(
					(
						MAP[player_x][player_y - 2] == SPACE || 
						MAP[player_x][player_y - 2] == GOAL
					)
					&&
					(
						MAP[player_x][player_y - 1] == BOX_N ||
						MAP[player_x][player_y - 1] == BOX_Y
					)
				)
			){
				//moves the box, if any, and updates the box counter
				if(MAP[player_x][player_y - 1] == BOX_N || MAP[player_x][player_y - 1] == BOX_Y){
					MAP[player_x][player_y - 2] = MAP[player_x][player_y - 2] == GOAL? BOX_Y : BOX_N;

					changed_block_x = player_x;
					changed_block_y = player_y - 2;
					print_board(1);
					if(MAP[player_x][player_y - 1] == BOX_N && MAP[player_x][player_y - 2] == BOX_Y){
						boxes_remaining--;
						print_tooltip(2);
					}
					if(MAP[player_x][player_y - 1] == BOX_Y && MAP[player_x][player_y - 2] == BOX_N){
						boxes_remaining++;
						MAP[player_x][player_y - 1] = GOAL;
						print_tooltip(2);
					}
				}
				//updates the block the player went to and the block the player came from
				MAP[player_x][player_y - 1] = MAP[player_x][player_y - 1] == GOAL? PLAYER_Y : PLAYER_N;
				MAP[player_x][player_y] = MAP[player_x][player_y] == PLAYER_Y? GOAL : SPACE;

				changed_block_x = player_x;
				changed_block_y = player_y - 1;
				print_board(1);
				changed_block_x = player_x;
				changed_block_y = player_y;
				print_board(1);

				//updates the player's coordinates
				player_y--;
			}
			break;
		}
		case LEFT:{
			if(
				MAP[player_x - 1][player_y] == SPACE ||
				MAP[player_x - 1][player_y] == GOAL ||
				(
					(
						MAP[player_x - 2][player_y] == SPACE || 
						MAP[player_x - 2][player_y] == GOAL
					)
					&&
					(
						MAP[player_x - 1][player_y] == BOX_N ||
						MAP[player_x - 1][player_y] == BOX_Y
					)
				)
			){
				if(MAP[player_x - 1][player_y] == BOX_N || MAP[player_x - 1][player_y] == BOX_Y){
					MAP[player_x - 2][player_y] = MAP[player_x - 2][player_y] == GOAL? BOX_Y : BOX_N;

					changed_block_x = player_x - 2;
					changed_block_y = player_y;
					print_board(1);
					if(MAP[player_x - 1][player_y] == BOX_N && MAP[player_x - 2][player_y] == BOX_Y){
						boxes_remaining--;
						print_tooltip(2);
					}
					if(MAP[player_x - 1][player_y] == BOX_Y && MAP[player_x - 2][player_y] == BOX_N){
						boxes_remaining++;
						MAP[player_x - 1][player_y] = GOAL;
						print_tooltip(2);
					}
				}
				MAP[player_x - 1][player_y] = MAP[player_x - 1][player_y] == GOAL? PLAYER_Y : PLAYER_N;
				MAP[player_x][player_y] = MAP[player_x][player_y] == PLAYER_Y? GOAL : SPACE;

				changed_block_x = player_x - 1;
				changed_block_y = player_y;
				print_board(1);
				changed_block_x = player_x;
				changed_block_y = player_y;
				print_board(1);

				player_x--;
			}
			print_board(0);
			break;
		}
		case RIGHT:{
			if(
				MAP[player_x + 1][player_y] == SPACE ||
				MAP[player_x + 1][player_y] == GOAL ||
				(
					(
						MAP[player_x + 2][player_y] == SPACE || 
						MAP[player_x + 2][player_y] == GOAL
					)
					&&
					(
						MAP[player_x + 1][player_y] == BOX_N ||
						MAP[player_x + 1][player_y] == BOX_Y
					)
				)
			){
				if(MAP[player_x + 1][player_y] == BOX_N || MAP[player_x + 1][player_y] == BOX_Y){
					MAP[player_x + 2][player_y] = MAP[player_x + 2][player_y] == GOAL? BOX_Y : BOX_N;

					changed_block_x = player_x + 2;
					changed_block_y = player_y;
					print_board(1);
					if(MAP[player_x + 1][player_y] == BOX_N && MAP[player_x + 2][player_y] == BOX_Y){
						boxes_remaining--;
						print_tooltip(2);
					}
					if(MAP[player_x + 1][player_y] == BOX_Y && MAP[player_x + 2][player_y] == BOX_N){
						boxes_remaining++;
						MAP[player_x + 1][player_y] = GOAL;
						print_tooltip(2);
					}
				}
				MAP[player_x + 1][player_y] = MAP[player_x + 1][player_y] == GOAL? PLAYER_Y : PLAYER_N;
				MAP[player_x][player_y] = MAP[player_x][player_y] == PLAYER_Y? GOAL : SPACE;

				changed_block_x = player_x + 1;
				changed_block_y = player_y;
				print_board(1);
				changed_block_x = player_x;
				changed_block_y = player_y;
				print_board(1);

				player_x++;
			}
			print_board(0);
			break;
		}
		case DOWN:{
			if(
				MAP[player_x][player_y + 1] == SPACE ||
				MAP[player_x][player_y + 1] == GOAL ||
				(
					(
						MAP[player_x][player_y + 2] == SPACE || 
						MAP[player_x][player_y + 2] == GOAL
					)
					&&
					(
						MAP[player_x][player_y + 1] == BOX_N ||
						MAP[player_x][player_y + 1] == BOX_Y
					)
				)
			){
				if(MAP[player_x][player_y + 1] == BOX_N || MAP[player_x][player_y + 1] == BOX_Y){
					MAP[player_x][player_y + 2] = MAP[player_x][player_y + 2] == GOAL? BOX_Y : BOX_N;

					changed_block_x = player_x;
					changed_block_y = player_y + 2;
					print_board(1);
					if(MAP[player_x][player_y + 1] == BOX_N && MAP[player_x][player_y + 2] == BOX_Y){
						boxes_remaining--;
						print_tooltip(2);
					}
					if(MAP[player_x][player_y + 1] == BOX_Y && MAP[player_x][player_y + 2] == BOX_N){
						boxes_remaining++;
						MAP[player_x][player_y + 1] = GOAL;
						print_tooltip(2);
					}
				}
				MAP[player_x][player_y + 1] = MAP[player_x][player_y + 1] == GOAL? PLAYER_Y : PLAYER_N;
				MAP[player_x][player_y] = MAP[player_x][player_y] == PLAYER_Y? GOAL : SPACE;

				changed_block_x = player_x;
				changed_block_y = player_y + 1;
				print_board(1);
				changed_block_x = player_x;
				changed_block_y = player_y;
				print_board(1);

				player_y++;
			}
			print_board(0);
		}
	}		
}