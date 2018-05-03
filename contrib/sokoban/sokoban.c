#include <stdio.h>
#include <stdlib.h>

#define clear() printf("\n\n\n\n\n\n\n\n\n")

#define TRUE 1
#define FALSE 2

#define NOT !=
#define OVER 1
#define FIRST_LEVEL 1

#define UP 0
#define LEFT 1
#define DOWN 2
#define RIGHT 3

void map_init(int level);
void print_board();
void move(int direction);

//GAME OVER condition
int GAME = 0;

//MAP VARIABLES
char **MAP;
int MAP_LENGTH = 15;
int MAP_WIDTH = 15;

//PLAYER VARIABLES
int player_x, player_y;
char sokoban_char = 's';

int main(){
	char command;

	//-----MAP INITIALIZATION
	map_init(FIRST_LEVEL);

	while(GAME NOT OVER){
		print_board();

		printf("Input move: ");
		scanf("%c", &command);

		if(command == 'w' || command == 'W'){
			move(UP);
		} else if(command == 'a' || command == 'A'){
			move(LEFT);
		} else if(command == 's' || command == 'S'){
			move(DOWN);
		} else if(command == 'd' || command == 'D'){
			move(RIGHT);
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
				MAP[x][y] = 'W';
			} else{
				MAP[x][y] = ' ';
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
			MAP[player_x][player_y] = sokoban_char;
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
			MAP[player_x][player_y] = sokoban_char;
			break;
		}
		case 3:{
			MAP[4][8] = 'b';
			MAP[4][9] = 'b';
			MAP[5][6] = 'b';
			MAP[5][7] = 'b';
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
			MAP[player_x][player_y] = sokoban_char;
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

			// MAP[1][4] = 'W';
			// MAP[1][4] = 'W';
			// MAP[1][4] = 'W';
			// MAP[1][4] = 'W';
			// MAP[1][4] = 'W';
			// MAP[1][4] = 'W';
			// MAP[1][4] = 'W';
			// MAP[1][4] = 'W';
			// MAP[1][4] = 'W';
			// MAP[1][4] = 'W';
			// MAP[1][4] = 'W';
			// MAP[1][4] = 'W';
			// MAP[1][4] = 'W';
			// MAP[1][4] = 'W';
			// MAP[1][4] = 'W';
			// MAP[1][4] = 'W';
			// MAP[1][4] = 'W';
			// MAP[1][4] = 'W';
			// MAP[1][4] = 'W';
			// MAP[1][4] = 'W';
			// MAP[1][4] = 'W';
			// MAP[1][4] = 'W';
			// MAP[1][4] = 'W';
			// MAP[1][4] = 'W';
			// MAP[1][4] = 'W';
			// MAP[1][4] = 'W';
			// MAP[1][4] = 'W';
			// MAP[1][4] = 'W';
			// MAP[1][4] = 'W';
			// MAP[1][4] = 'W';
			// MAP[1][4] = 'W';
			// MAP[1][4] = 'W';
			// MAP[1][4] = 'W';
			// MAP[1][4] = 'W';
			// MAP[1][4] = 'W';
			// MAP[1][4] = 'W';
			// MAP[1][4] = 'W';
			// MAP[1][4] = 'W';
			// MAP[1][4] = 'W';
			// MAP[1][4] = 'W';
			// MAP[1][4] = 'W';
			// MAP[1][4] = 'W';

			player_x = 7;
			player_y = 7;
			MAP[player_x][player_y] = sokoban_char;
			break;
		}
		case 5:{
			MAP[3][7] = 'b';

			MAP[5][1] = 'g';

			player_x = 7;
			player_y = 7;
			MAP[player_x][player_y] = sokoban_char;
		}
	}
}

void print_board(){
	int x, y;

	putchar('\n');
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

void checkIfMovable(int direction){
	switch(direction){
		case UP:
			// if up of sokoban isn't obstructed by a wall
		/*
			if (player_x - 1 != 'W' && ((player_x - 1 != 'b' || player_x - 1 != 'B') && (player_x - 2 != 'b' || player_x - 2 != 'B')) ){
				if (player_x - 1 == ){

				}
			}

		*/
			checkIfMovable(UP);
			break;
		case LEFT:
			checkIfMovable(LEFT);
			break;
		case DOWN:
			checkIfMovable(DOWN);
			break;
		case RIGHT:	
			checkIfMovable(RIGHT);
			break;
	}	
}

void move(int direction){
	switch(direction){
		case UP:
			// if up of sokoban isn't obstructed by a wall
		/*
			if (player_x - 1 != 'W' && ((player_x - 1 != 'b' || player_x - 1 != 'B') && (player_x - 2 != 'b' || player_x - 2 != 'B')) ){
				if (player_x - 1 == ){

				}
			}

		*/
			checkIfMovable(UP);
			break;
		case LEFT:
			checkIfMovable(LEFT);
			break;
		case DOWN:
			checkIfMovable(DOWN);
			break;
		case RIGHT:	
			checkIfMovable(RIGHT);
			break;
	}
}