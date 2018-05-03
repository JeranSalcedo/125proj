#include <stdio.h>
#include <stdlib.h>

#define clear() printf("\n\n\n\n\n\n\n\n\n")
#define TRUE 1
#define FALSE 2

#define NOT !=
#define OVER 1

#define UP 0
#define LEFT 1
#define DOWN 2
#define RIGHT 3

void map_init(int level);
void print_board();
void move(int direction);

int GAME = 0;
int MAP_LENGTH = 15;
int MAP_WIDTH = 15;

char **MAP;

int player_x, player_y;
char sokoban_char = 's';

int main(){
	char command;

	//-----MAP INIT
	map_init(1);

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
	int i, x, y;

	MAP = (char **) malloc(MAP_WIDTH * sizeof(char *));
	for(x = 0; x < MAP_WIDTH; x++){
		MAP[x] = (char *) malloc(MAP_LENGTH * sizeof(char));
	}

	//-----BOUNDARY
	for(x = 0; x < MAP_WIDTH; x++){
		for(y = 0; y < MAP_LENGTH; y++){
			if(x == 0 || x == 14 || y == 0 || y == 14){
				MAP[x][y] = 'W';
			} else{
				MAP[x][y] = ' ';
			}
		}
	}

	switch(level){
		case 1:{
			MAP[3][7] = 'b';
			MAP[6][7] = 'b';
			MAP[8][7] = 'b';
			MAP[11][7] = 'b';

			MAP[5][1] = 'g';
			MAP[9][1] = 'g';
			MAP[5][13] = 'g';
			MAP[9][13] = 'g';

			MAP[7][7] = sokoban_char;
			break;
		}
		case 2:{
			MAP[3][7] = 'b';

			MAP[5][1] = 'g';

			MAP[7][7] = sokoban_char;
			break;
		}
		case 3:{
			MAP[3][7] = 'b';

			MAP[5][1] = 'g';

			MAP[7][7] = sokoban_char;
			break;
		}
		case 4:{
			MAP[3][7] = 'b';

			MAP[5][1] = 'g';

			MAP[7][7] = sokoban_char;
			break;
		}
		case 5:{
			MAP[3][7] = 'b';

			MAP[5][1] = 'g';

			MAP[7][7] = sokoban_char;
		}
	}
}

void print_board(){
	int x, y;

	putchar('\n');
	for(x = 0; x < MAP_WIDTH; x++){
		for(y = 0; y < MAP_LENGTH; y++){
			printf("%c ", MAP[x][y]);
		}
		switch(x){
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