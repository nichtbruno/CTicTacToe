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
int chooseGameMode();
// COMPUTER
void computerPlay(char[3][3], char);

typedef struct {
    char character;
} Player;

enum GameMode {
    SINGLEPLAYER,
    MULTIPLAYER,
};

int main() {
    srand(time(NULL));
    char exampleBoard[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
    char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    Player player1, player2;
    enum GameMode gameMode = chooseGameMode();

    player1.character = chooseCharacter();
    if (gameMode == MULTIPLAYER) {
        player2.character = chooseCharacter();
    } else {
        player2.character = (player1.character == 'o') ? 'x' : 'o';
    }

    drawBoard(exampleBoard);
    char winner;
    while (checkBoard(board) != 0) {
        play(board, player1.character);
        winner = checkForWinner(board);
        if (winner != ' ') {
            drawBoard(board);
            break;
        }
        if (gameMode == SINGLEPLAYER) {
            computerPlay(board, player2.character);
        } else {
            play(board, player2.character);
        }
        drawBoard(board);
        winner = checkForWinner(board);
        if (winner != ' ') { break; }
    }
    printf("Congratulations!! \'%c\' won the game!!!\n", winner);

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
        short row = ceil((float)i/3)-1;
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
        printf("\'%c\' pick a tile to play: ", playerCharacter);
        scanf("%hd", &tile);
        if(tile <= 0 || tile >= 10) {
            printf("The number must be between 1 and 9!\n");
            continue;
        }
        short row = ceil((float)tile/3)-1;
        if(board[row][tile-(3*row)-1] != ' ') {
            printf("The tile must be empty\n");
            continue;
        }
        board[row][tile-(3*row)-1] = playerCharacter;
        break;
    }
}

char chooseCharacter() {
    char character;
    printf("What character do you want to play as: ");
    scanf(" %c", &character);
    return character;
}

int chooseGameMode() {
    char type;
    printf("Do you want to play against a computer [c] or against an another player [p]?: ");
    scanf("%c", &type);
    if (type == 'c') {
        return SINGLEPLAYER;
    }
    return MULTIPLAYER;
}

// COMPUTER
void computerPlay(char board[3][3], char computerCharacter) {
    int tile;
    while (1) {
        tile = rand() % 9 + 1;
        short row = ceil((float)tile/3)-1;
        if(board[row][tile-(3*row)-1] == ' ') {
            board[row][tile-(3*row)-1] = computerCharacter;
            break;
        }
    }
}
