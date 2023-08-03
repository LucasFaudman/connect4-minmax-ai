#ifndef connect4_h__
#define connect4_h__

#include <string>
#include "board.h"

using namespace std;

/*
 IT IS ABSOLUTELY PIVOTAL THAT YOU DO NOT EDIT THIS FILE
 */

// This serves as the main function for the Core portion of the project.
// It is where you will write the menu-driven gameplay for the Core.


void terminalPlayColor();
void terminalPlayColorAI1st(int diffLevel);
void terminalPlayColorAI2nd(int diffLevel);
void AIbattle();

// Effects: Lets the user choose whether to start a new game, or load an
//          existing one. Returns the game board. modifies p1 and p2 to be
//          the player names.
// Difficulty: **
// Topics: Basic/IO, pass by reference, class construction
Board getBoard(string &p1, string &p2);
Board getBoardAI1(string &p1, string &p2);
Board getBoardAI2(string &p1, string &p2);
void setLastMove(Board& boardToPrint, Board newBoard);

// Prompts the user for the filename, and saves the board.
// Difficulty: *
// Topics: streams
void saveBoard(string p1, string p2, const Board &board);


///Cool printing stuff
void printBrian(string loserName);
void printObamaB();
void printObamaR();
void printWin();
void printLose();
void printDraw();
void printTitle2();

#endif
