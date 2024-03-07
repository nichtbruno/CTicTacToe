#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

// BOARD
void drawBoard(char[3][3]);
short checkBoard(char[3][3]);
char checkForWinner(char[3][3]);
// PLAYER
void play(char[3][3], char);
char chooseCharacter();
// COMPUTER
void computerPlay(char[3][3], char);

typedef struct {
	char character;
} Player;

int main() {
	srand(time(NULL));
	char exampleBoard[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
	char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
	Player player1, computer1;
	player1.character = chooseCharacter();
	computer1.character = (player1.character == 'o') ? 'x' : 'o';

	drawBoard(exampleBoard);
	while (checkBoard(board) != 0) {
		play(board, player1.character);
		computerPlay(board, computer1.character);
		drawBoard(board);
		char winner = checkForWinner(board);
		if (winner != ' ') {
			printf("Congratulations!! \'%c\' won the game!!!", winner);
			break;
		}
	}
	
	return 0;
}

// BOARD
void drawBoard(char board[3][3]) {
	for(int i=0; i<3; i++) {
		printf(" %c | %c | %c \n", board[i][0], board[i][1], board[i][2]);
		printf((i<2) ? "---|---|---\n" : "");
	}
}

short checkBoard(char board[3][3]) {
	short freeTiles = 9;
	for(int i=1; i<=9; i++) {
		short row = ceil(i/3)-1;
		if(board[row][i-(3*row)-1] != ' ') {
			freeTiles--;
		}
	}
	return freeTiles;
}

char checkForWinner(char board[3][3]) {
	// check rows
	for(int i=0; i<3; i++) {
		if(board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
			return board[i][0];
		}
	}
	// check columns
	for(int i=0; i<3; i++) {
		if(board[0][i] == board[1][i] && board[0][i] == board[2][i]) {
			return board[0][i];
		}
	}
	// check diagonals
	if(board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
		return board[0][0];
	}
	if(board[2][0] == board[1][1] && board[2][0] == board[0][2]) {
		return board[2][0];
	}
	return ' ';
}

// PLAYER
void play(char board[3][3], char playerCharacter) {
	short tile;
	while (1) {
		printf("Pick a tile to play: ");
		scanf("%d", &tile);
		if(tile > 0 && tile < 10) {
			break;
		}
		printf("\nThe number must be between 1 and 9!");
	}
	// kinda extra work but easier to play when saying 1 to 9
	short row = ceil(tile/3)-1;
	board[row][tile-(3*row)-1] = playerCharacter;
}

char chooseCharacter() {
	char character;
	printf("What character do you want to play as: ");
	scanf("%c", &character);
	printf("Great choice! Let's play!\n");
	return character;
}

// COMPUTER
void computerPlay(char board[3][3], char computerCharacter) {
	int tile;
	while (1) {
		tile = rand() % 9 + 1;
		short row = ceil(tile/3)-1;
		if(board[row][tile-(3*row)-1] == ' ') {
			board[row][tile-(3*row)-1] = computerCharacter;
			break;
		}
	}
}
