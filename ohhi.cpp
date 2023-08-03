/**
 * ohhi.cpp
 *
 * EECS 183
 * Project 3: 0h h1
 * Winter 2018
 *
 * Lucas Faudman
 * Lucasnf
 *
 * 0h h1 game
 */

#include <iostream>
#include <cctype>
#include "utility.h"
#include "ohhi.h"
#include "driver.h"








int count_unknown_squares(const int board[MAX_SIZE][MAX_SIZE], int size) {
    int unknown_squares = 0;
    
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if(board[row][col] == UNKNOWN){
                unknown_squares += 1;
            }
        }
    }
    return unknown_squares;
}



/**
 * --------------------------------------------------------
 * --------- VALIDITY CHECKING FUNCTIONS ------------------
 * --------------------------------------------------------
 */

bool row_has_no_threes_of_color(const int board[MAX_SIZE][MAX_SIZE],
                                int size,
                                int row,
                                int color) {
    
    int number_of_threes = 0;
    
    if (size < 3){
        return true;
    }else{
    for (int col = 0; col < (size - 2); col++) {
        
        if ((board[row][col] == color) && (board[row][(col + 1)] == color)
           && (board[row][(col + 2)] == color) ){
            number_of_threes += 1;
       }
    }
    
    if (number_of_threes >= 1) {
        return false;
    } else {
        return true;
    }
    }
}

bool col_has_no_threes_of_color(const int board[MAX_SIZE][MAX_SIZE],
                                int size,
                                int col,
                                int color) {
    int number_of_threes = 0;
    if (size < 3){
        return true;
    }else{
    for (int row = 0; row < (size - 2); row++) {
        if ((board[row][col] == color) && (board[(row + 1)][col] == color)
            && (board[(row + 2 )][col] == color) ){
            number_of_threes +=1;
        }
    }
    
    if (number_of_threes >= 1) {
        return false;
    } else {
        return true;
    }
    }
}

bool board_has_no_threes(const int board[MAX_SIZE][MAX_SIZE], int size) {
    for (int i = 0; i < size; i++) {
        
        if (!row_has_no_threes_of_color(board, size, i, BLUE) ||
            !row_has_no_threes_of_color(board, size, i, RED)  ||
            !col_has_no_threes_of_color(board, size, i, BLUE) ||
            !col_has_no_threes_of_color(board, size, i, RED) ) {
            return false;
        }
    }
    
    return true;
}

bool rows_are_different(const int board[MAX_SIZE][MAX_SIZE],
                        int size,
                        int row1,
                        int row2) {
    int number_of_same = 0;
    
    for (int col = 0; col < size; col++) {
        if ((board[row1][col] == board[row2][col])){
            number_of_same += 1;
            }
        if(board[row1][col] == UNKNOWN){
            return true;
        }
    }
    
    if (number_of_same == size) {
        return false;
    } else {
        return true;
    }
}

bool cols_are_different(const int board[MAX_SIZE][MAX_SIZE],
                        int size,
                        int col1,
                        int col2) {
    int number_of_same = 0;
    
    for (int row = 0; row < size; row++) {
        if ((board[row][col1] == board[row][col2])){
            number_of_same += 1;
        }
        if(board[row][col1] == UNKNOWN){
            return true;
        }
    }
    
    
    if (number_of_same == size) {
        return false;
    } else {
        return true;
    }

    return false;
}

bool board_has_no_duplicates(const int board[MAX_SIZE][MAX_SIZE], int size) {
    for (int i = 0; i < size ; ++i) {
        for(int j = 1; (j+i) < size; ++j){
        if ( !rows_are_different(board, size, i, i+j) ||
             !cols_are_different(board, size, i, i+j ) ) {
            return false;
        }
    }
    }
    return true;
}



/**
 * --------------------------------------------------------
 * ---------- SOLVING FUNCTIONS ---------------------------
 * --------------------------------------------------------
 */

void solve_three_in_a_row(int board[MAX_SIZE][MAX_SIZE],
                          int size,
                          int row,
                          bool announce) {
    
    if (size > 2){
    
    for (int col = 0; col < (size - 1); col++) {
        if (board[row][col] != UNKNOWN) {
            
            if (board[row][col] == board[row][col + 2]){
                if((board[row][col + 1] == UNKNOWN) && ( (col + 1) < size )) {
                    mark_square_as(board, size, row, col + 1 ,
                    opposite_color(board[row][col]), true);
                }
                
            }else{
                if ((board[row][col] == board[row][col + 1]) && (board[row][col] != UNKNOWN) ) {
                    if((col - 1) >= 0){
                        if (board[row][col - 1] == UNKNOWN){
                            mark_square_as(board, size, row, col - 1,
                            opposite_color(board[row][col]), true);
                        }
                    }
                    if((col + 2) < size){
                        if(board[row][col + 2] == UNKNOWN){
                          mark_square_as(board, size, row, col + 2,
                          opposite_color(board[row][col]), true);
                    }}
                 }
                }
            }
    }
    }
    return;
}

void solve_three_in_a_column(int board[MAX_SIZE][MAX_SIZE],
                             int size,
                             int col,
                             bool announce) {
    
    if (size > 2){
        
        for (int row = 0; row < (size - 1); row++) {
            if (board[row][col] != UNKNOWN) {
                
                if (board[row][col] == board[row + 2][col]){
                    if((board[row + 1][col] == UNKNOWN) && ( (row + 1) < size )) {
                        mark_square_as(board, size, row + 1, col,
                                       opposite_color(board[row][col]), true);
                    }
                    
                }else{
                    if ((board[row][col] == board[row + 1][col]) && (board[row][col] != UNKNOWN) ) {
                        if((row - 1) >= 0){
                            if (board[row - 1][col] == UNKNOWN){
                                mark_square_as(board, size, row - 1, col,
                                               opposite_color(board[row][col]), true);
                            }
                        }
                        if((row + 2) < size){
                            if(board[row + 2][col] == UNKNOWN){
                                mark_square_as(board, size, row + 2, col,
                                               opposite_color(board[row][col]), true);
                            }}
                    }
                }
            }
        }
    }
    return;
}


void solve_balance_row(int board[MAX_SIZE][MAX_SIZE],
                       int size,
                       int row,
                       bool announce) {
    int num_red = 0;
    int num_blue = 0;
    
    for (int col = 0; col < size; col++) {
        if (board[row][col] == RED) {
            num_red++;
        } else if (board[row][col] == BLUE) {
            num_blue++;
        }
    }
    
    int color = UNKNOWN;
    if (num_red == size / 2) {
        color = RED;
    } else if (num_blue == size / 2) {
        color = BLUE;
    }
    
    for(int col = 0; col < size; col++){
        if ((board[row][col] == UNKNOWN) && (color != UNKNOWN)) {
            mark_square_as(board, size, row, col,
                           opposite_color(color), true);
        }
    
    
    }
    
    return;
}

void solve_balance_column(int board[MAX_SIZE][MAX_SIZE],
                          int size,
                          int col,
                          bool announce) {
    int num_red = 0;
    int num_blue = 0;
    
    for (int row = 0; row < size; row++) {
        if (board[row][col] == RED) {
            num_red++;
        } else if (board[row][col] == BLUE) {
            num_blue++;
        }
    }
    
    int color = UNKNOWN;
    if (num_red == size / 2) {
        color = RED;
    } else if (num_blue == size / 2) {
        color = BLUE;
    }
    
    for(int row = 0; row < size; row++){
        if ((board[row][col] == UNKNOWN) && (color != UNKNOWN)) {
            mark_square_as(board, size, row, col,
                           opposite_color(color), true);
        }
        
        
    }
    

    return;
}


















/**
 * --------------------------------------------------------
 * ---------- GAMEPLAY FUNCTIONS --------------------------
 * --------------------------------------------------------
 */

bool board_is_solved(const int board[MAX_SIZE][MAX_SIZE], int size) {
    if(count_unknown_squares(board, size) != 0){
        return false;
    }else{
        if(board_has_no_threes(board, size) && board_has_no_duplicates(board, size) && board_is_balanced(board, size)){
            return  true;
        }
    return false;
}
}

bool check_valid_input(int size, int row_input, char col_input,
                       char color_char, int &row, int &col) {

    string errorMessage = "Sorry, that's not a valid input.";
    
    // Check row input for validity
    if (row_input >= 1 && row_input <= size) {
        
        // Check column input for validity
        if ((toupper(col_input) <= ('A' + size - 1)) && (toupper(col_input) >= 'A')) {
            
            // Check color input for validity
            if (toupper(color_char) == UNKNOWN_LETTER
                || toupper(color_char) == BLUE_LETTER
                || toupper(color_char) == RED_LETTER){
                col = toupper(col_input) - 'A';
                row = row_input - 1;
                return true;
            }
            
            else {
                cout << errorMessage << endl;
                return false;
            }
        }
        
        else {
            cout << errorMessage << endl;
            return false;
        }
    }
    
    else {
        cout << errorMessage << endl;
        return false;
    }
    
    
    
    
    return false;
}

bool check_valid_move(const int original_board[MAX_SIZE][MAX_SIZE],
                      const int current_board[MAX_SIZE][MAX_SIZE],
                      int size, int row, int col, int color) {
    
    // Creating a copy of the board to modify
    int boardCopy[MAX_SIZE][MAX_SIZE];
    copy_board(current_board, boardCopy, size);
    
    
    string originalSquare = "Sorry, original squares cannot be changed.";
    string violatesRule = "Sorry, that move violates a rule.";
    
    // Chcek if row and col inputs are in valid range
    if ((row >= 0) && (row < size) && (col >= 0) && (col < size)) {
        
        // Check if the square was defined in the original board
        if ((original_board[row][col] == BLUE) || (original_board[row][col] == RED)) {
            cout << originalSquare << endl;
            return false;
        }
        
        // Modifying the copied board
        mark_square_as(boardCopy, size, row, col, color, false);
        
        // Check modified board validity
        if (!board_is_valid(boardCopy, size)) {
            cout << violatesRule << endl;
            return false;
        }
        
        return true;
    }
    
    return false;
    
}




















/**
 * --------------------------------------------------------
 * ---------------- S'MORES FUNCTIONS    ------------------
 * ---------- DO NOT DELETE THESE FUNCTIONS ---------------
 * ------------- FOR THE REGULAR PROJECT ------------------
 * --------------------------------------------------------
 */

void solve_lookahead_row(int board[MAX_SIZE][MAX_SIZE],
                         int size,
                         int row,
                         bool announce) {
    // write your code here

    return;
}

void solve_lookahead_column(int board[MAX_SIZE][MAX_SIZE],
                            int size,
                            int col,
                            bool announce) {
    // write your code here
    return;
}
