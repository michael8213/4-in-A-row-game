#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include <stdbool.h>

/*
 michael kan tor 318433232
this program is the game 4 in a row, a two player game in which you need to string 4 X's or O's 
in a row, column or diaognal.
injoy :)
*/

/*************** Board ***************/
#define ROWS 6
#define COLS 7
char board[ROWS][COLS];


/*********** Declarations ************/

/// This function initializes the game board by assigning each cell
/// with ' ' (resulting with an empty game board).
void initBoard();

/// This function gets a row number and a column number (a cell),
/// and returns the character in that cell (could be 'X', 'O' or ' ').
/// For example:
/// char c = getCell(1, 1);
char getCell(int row, int col);

/// This function gets a row number, a column number and a sign,
/// and assigns the cell with the given sign.
/// For example:
/// setCell(1, 1, 'X');
void setCell(int row, int col, char sign);

/// This function clears the screen.
void clearScreen();

/// This function prints the table
void printBoard();

/// This function checks the validity of the input
int isValidInput(int colNum);

/// This function implements the players choices
int implementChoice(int colNum, char sign);

/// This function checks if there is a winner
bool foundWinner(int colNum, int rowNum, char sign);

/// This function checks if there is a draw
bool foundDraw();

/// This function checks if there is 4 in a row
bool rowWin(int colNum, int rowNum, char sign);

/// This function checks if there is 4 in a column
bool colWin(int colNum, int rowNum, char sign);

/// This function checks if there is 4 in a diagonal
bool diagonalWin(int colNum, int rowNum, char sign);





/*************** Main ****************/
void main()
{
	int temp = 0;
	int playerNum = 1, colNum = 0, newChoice = 0, checkedColNum = 0, lastRowImplemented = 0, playerWhoWon = 0;
	char sign = 'X';


	initBoard();
	printBoard(); 

	while ((foundWinner(colNum, lastRowImplemented, sign) && !foundDraw())) // game loop
	{
		// this block of code receivs the input for the desired column and check its validity
		printf("Player number %d: \nPlease enter column input (a number between 1-7): ", playerNum);
		scanf("%d", &colNum);
		checkedColNum = isValidInput(colNum);

		if (playerNum == 1) { // make play for player 1
			sign = 'X';
			lastRowImplemented = implementChoice(checkedColNum, sign);
			playerNum = 2;
		}
		else // make play for player 2
		{
			sign = 'O';
			lastRowImplemented = implementChoice(checkedColNum, sign);
			playerNum = 1;
		}
		// the following block of code checks if a winner is found and prints the appropriate message
		if (!foundWinner(colNum, lastRowImplemented, sign)) { 
			playerWhoWon = playerNum;
			if (playerNum == 1) {
				playerWhoWon = 2; // player 2 won
			}
			else {
				playerWhoWon = 1; //player 1 won
			}
			clearScreen();
			printBoard();
			printf("Player number %d won, congrats :)\n", playerWhoWon); // printing victory message
		}
		else { // if not found winner, continue play
			clearScreen();
			printBoard();
		}
		if (foundDraw()) { // checking if there is a darw, meaning full board and no winner
			printf("This game is a draw!\n");
		}
		
		
	}//while




}//main


/********** Implementations **********/
char getCell(int row, int col)
{
	return board[row - 1][col - 1];
}

void setCell(int row, int col, char sign)
{
	board[row - 1][col - 1] = sign;
}

void initBoard()
{
	int i, j;

	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			setCell(i + 1, j + 1, ' ');
		}
	}
}

void clearScreen()
{
	system("cls");
}


void printBoard() {
	char rowLetter = 65; // "a"
	printf(" ");
	for (int i = 1; i <= COLS; i++) {
		printf("    %d", i);
	}
	printf("\n");
	for (int j = 0; j < ROWS; j++) {
		printf("%c", rowLetter);
		for (int k = 0; k < COLS; k++) {
			printf("    %c", board[j][k]);
		}
		rowLetter++;
		printf("\n");

	}
}





int isValidInput(int colNum) {
	char lastCellInColumn;
	int newColNum = 0;
	if (colNum > 7 || colNum < 1) {
		while (newColNum > 7 || newColNum < 1)
		{


			printf("The col you entered is not between 1-7.\nPlease enter column input (a number between 1-7): ");
			scanf("%d", &newColNum);
		}
		return newColNum;

		
	}
	
	lastCellInColumn = getCell(1, colNum);
	if (lastCellInColumn != ' ') {
		while (lastCellInColumn != ' ') {
			printf("The col you entered is full.\nPlease enter column input (a number between 1-7): ");
			scanf("%d", &newColNum);
			lastCellInColumn = getCell(1, newColNum);
		}
		return newColNum;
	}

	else {
		return colNum;
	}
}//isValidInput

int implementChoice(int colNum, char sign) {
	int i = ROWS;
	for (i; i > 0; i--) {
		char tempCell;
		tempCell = getCell(i, colNum);


		if (tempCell == ' ') {
			setCell(i, colNum, sign);
			return i;
		}
	}
}//implementChoices

bool foundWinner(int colNum, int rowNum, char sign) {
	if (rowWin(colNum, rowNum, sign)) {
		return false;
	}
	else if (colWin(colNum, rowNum, sign)) {
		return false;
	}
	else if(diagonalWin(colNum, rowNum, sign)) {
		return false;
	}
	else {
		return true;
	}
}//foundWinner


bool foundDraw() {
	char A1, A2, A3, A4, A5, A6, A7;
	A1 = getCell(1, 1);
	A2 = getCell(1, 2);
	A3 = getCell(1, 3);
	A4 = getCell(1, 4);
	A5 = getCell(1, 5);
	A6 = getCell(1, 6);
	A7 = getCell(1, 7);
	if (A1 != ' ' && A2 != ' ' && A3 != ' ' && A4 != ' ' && A5 != ' ' && A6 != ' ' && A7 != ' ') {
		return true;
	}
	else {
		return false;
	}
}//foundDraw


bool rowWin(int colNum, int rowNum, char sign) { // check if there is 4 in a line
	char forward1, forward2, forward3, back1, back2, back3;
	forward1 = getCell(rowNum, colNum + 1);
	forward2 = getCell(rowNum, colNum + 2);
	forward3 = getCell(rowNum, colNum + 3);
	back1 = getCell(rowNum, colNum - 1);
	back2 = getCell(rowNum, colNum - 2);
	back3 = getCell(rowNum, colNum - 3);
	if (sign == forward1 && sign == forward2 && sign == forward3) { // first to last 1/4
		return true;
	}
	else if (sign == forward1 && sign == forward2 && sign == back1) { // 2/4
		return true;
	}
	else if(sign == forward1 && sign == back1 && sign == back2){ // 3/4
		return true;
	}
	else if (sign == back1 && sign == back2 && sign == back3) { // 4/4
		return true;
	}
	else
	{
		return false;
	}

}   //rowWin


bool colWin(int colNum, int rowNum, char sign) {
	char under1, under2, under3;
	under1 = getCell(rowNum + 1, colNum);
	under2 = getCell(rowNum + 2, colNum);
	under3 = getCell(rowNum + 3, colNum);
	if (under1 == sign && under2 == sign && under3 == sign) { 
		return true;
	}
	else {
		return false;
	}
	
}// colwin

bool diagonalWin(int colNum, int rowNum, char sign) {
	char upRight1, upRight2, upRight3, downLeft1, downLeft2, downLeft3;
	char downRight1, downRight2, downRight3, upLeft1, upLeft2, upLeft3;
	upRight1 = getCell(rowNum - 1, colNum + 1);
	upRight2 = getCell(rowNum - 2, colNum + 2);
	upRight3 = getCell(rowNum - 3, colNum + 3);
	downLeft1 = getCell(rowNum + 1, colNum - 1);
	downLeft2 = getCell(rowNum + 2, colNum - 2);
	downLeft3 = getCell(rowNum + 3, colNum - 3);
	
	downRight1 = getCell(rowNum + 1, colNum + 1);
	downRight2 = getCell(rowNum + 2, colNum + 2);
	downRight3 = getCell(rowNum + 3, colNum + 3);
	upLeft1 = getCell(rowNum - 1, colNum - 1);
	upLeft2 = getCell(rowNum - 2, colNum - 2);
	upLeft3 = getCell(rowNum - 3, colNum - 3);




	if (sign == upRight1 && sign == upRight2 && sign == upRight3) {// left to right rising 1/4
		return true;
	}
	else if(sign == downLeft1 && sign == upRight1 && sign == upRight2) { // 2/4
		return true;
	}
	else if (sign == downLeft1 && sign == downLeft2 && sign == upRight1) { // 3/4
		return true;
	}
	else if(sign == downLeft1 && sign == downLeft2 && sign == downLeft3){ // 4/4
		return true;
	} 

	else if(sign == downRight1 && sign == downRight2 && sign == downRight3){  // right to left rising 1/4
		return true;
	} 
	else if (sign == downRight1 && sign == downRight2 && sign == upLeft1) {  //  2/4
		return true;
	}
	else if (sign == downRight1 && sign == upLeft1 && sign == upLeft2) {  //  3/4
		return true;
	}
	else if (sign == upLeft1 && sign == upLeft2 && sign == upLeft3) {  //  4/4
		return true;
	}

	else {
		return false;
	}
}//diagonalWin