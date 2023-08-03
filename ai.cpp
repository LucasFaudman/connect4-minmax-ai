#include "ai.h"
#include "board.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <sys/time.h>
#include <map>


const int_fast8_t middleOut[NUM_COLS] = {3,2,4,1,5,0,6};

std::map<string, int_fast8_t> TT;
u_long numTimesSeen = 0;

///Expert AI (Actual project stuff)
int connect4AI(const Board& board){
    
    int best = 420, winMove = 420, blockMove = 420, win2Setup = 420, block2 = 420;
    int forceWinMove = 420, blockFW = 420, forceWinMove2 = 420, blockFW2 = 420;
    int forceWinMove3 = 420, blockFW3 =420, forceWinMove4 = 420, blockFW4 = 420;

    
    Board boardP1 = board;
    Board boardP2;
    
    
    for (int i = 0; i < NUM_COLS; ++i){
        int testMove = middleOut[i];
        Result notIllegal = boardP1.makeMove(testMove);
        boardP1 = board;
        boardP2 = board;
        boardP2.updateToMove();
        
        if(notIllegal != IllegalMove){
            if(isWin(testMove, boardP1)){
                winMove = testMove;
            }
            else {
                if(isWin(testMove, boardP2)){
                    blockMove = testMove;
                }
                else {
                    if(noWinSetup(testMove, boardP1)){
                        if(is2WinSetup(testMove, boardP1)){
                            win2Setup = testMove;
                        }
                        else {
                            if(is2WinSetup(testMove, boardP2)){
                                block2 = testMove;
                            }
                            else {
                                if(isForceWin(testMove, boardP1)){
                                    forceWinMove = testMove;
                                }
                                else{
                                    if(isForceWin(testMove, boardP2)){
                                        blockFW = testMove;
                                    }
                                    else {
                                        if(is2LayerForceWin(testMove, boardP1)){
                                            forceWinMove2 = testMove;
                                        }
                                        else{
                                            if(is2LayerForceWin(testMove, boardP2)){
                                               blockFW2 = testMove;
                                            }
                                            else {
                                                if(is3LayerForceWin(testMove, boardP1)){
                                                    forceWinMove3 = testMove;
                                                }
                                                else {
                                                    if(is3LayerForceWin(testMove, boardP2)){
                                                        blockFW3 = testMove;
                                                    }
                                                    else {
                                                        if(is4LayerForceWin(testMove, boardP1)){
                                                            forceWinMove4 = testMove;
                                                        }
                                                        else {
                                                            if(is4LayerForceWin(testMove, boardP2)){
                                                                blockFW4 = testMove;
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                                
                            }
                        }
                        
                    }
                }
            }
            
        }
    }
    
    boardP1 = board;
    if(winMove != 420){
        best = winMove;
    }
    else{
        if(blockMove != 420){
            best = blockMove;
        }
        else {
            if(win2Setup != 420){
                best = win2Setup;
            }
            else {
                if (block2 != 420){
                    best = block2;
                }
                else {
                    if(boardP1.numMovesPlayed >= 15 || (numColsFull(boardP1) >= 2) ){
                        //AI 1
                        set_color(LIGHTMAGENTA_CODE);
                        cout <<  "🤔🤔🤔🤔🤔🤔🤔🤔🤔";
                        cout << endl << "AI is Thinking...." << endl;
                        cout <<  "🤔🤔🤔🤔🤔🤔🤔🤔🤔" << endl;
                        reset_color();
                        best = SBgetnMaxCol(boardP1, -21, 21);
                    }
                    else {
                    if(forceWinMove != 420){
                        best = forceWinMove;
                    }
                    else{
                        if(forceWinMove2 != 420){
                            best = forceWinMove2;
                        }
                        else {
                            if(forceWinMove3 != 420){
                                best = forceWinMove3;
                            }
                            else {
                                if(forceWinMove4 !=420){
                                    best = forceWinMove4;
                                }
                                else {
                                    if(blockFW != 420){
                                        best = blockFW;
                                    }
                                    else{
                                        if(blockFW2 != 420){
                                            best = blockFW2;
                                        }
                                        else {
                                            if(blockFW3 != 420){
                                                best = blockFW3;
                                            }
                                            else {
                                                if(blockFW4 !=420){
                                                    best = blockFW4;
                                                }
                                                else {
                                                   best = bestMove(boardP1);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return best;
    
}



//SECOND AI RUNNING FUNCTION SO WE CAN TEST OUR AIS AGAISNT EACHOTHER
int connect4AI2(const Board& board){
    
    int best = 420, winMove = 420, blockMove = 420, win2Setup = 420, block2 = 420;
    int forceWinMove = 420, blockFW = 420, forceWinMove2 = 420, blockFW2 = 420;
    int forceWinMove3 = 420, blockFW3 =420, forceWinMove4 = 420, blockFW4 = 420;
    
    
    Board boardP1 = board;
    Board boardP2;
    
    
    for (int i = 0; i < NUM_COLS; ++i){
        int testMove = middleOut[i];
        Result notIllegal = boardP1.makeMove(testMove);
        boardP1 = board;
        boardP2 = board;
        boardP2.updateToMove();
        
        if(notIllegal != IllegalMove){
            if(isWin(testMove, boardP1)){
                winMove = testMove;
            }
            else {
                if(isWin(testMove, boardP2)){
                    blockMove = testMove;
                }
                else {
                    if(noWinSetup(testMove, boardP1)){
                        if(is2WinSetup(testMove, boardP1)){
                            win2Setup = testMove;
                        }
                        else {
                            if(is2WinSetup(testMove, boardP2)){
                                block2 = testMove;
                            }
                            else {
                                if(isForceWin(testMove, boardP1)){
                                    forceWinMove = testMove;
                                }
                                else{
                                    if(isForceWin(testMove, boardP2)){
                                        blockFW = testMove;
                                    }
                                    else {
                                        if(is2LayerForceWin(testMove, boardP1)){
                                            forceWinMove2 = testMove;
                                        }
                                        else{
                                            if(is2LayerForceWin(testMove, boardP2)){
                                                blockFW2 = testMove;
                                            }
                                            else {
                                                if(is3LayerForceWin(testMove, boardP1)){
                                                    forceWinMove3 = testMove;
                                                }
                                                else {
                                                    if(is3LayerForceWin(testMove, boardP2)){
                                                        blockFW3 = testMove;
                                                    }
                                                    else {
                                                        if(is4LayerForceWin(testMove, boardP1)){
                                                            forceWinMove4 = testMove;
                                                        }
                                                        else {
                                                            if(is4LayerForceWin(testMove, boardP2)){
                                                                blockFW4 = testMove;
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                                
                            }
                        }
                        
                    }
                }
            }
            
        }
    }
    
    boardP1 = board;
    if(winMove != 420){
        best = winMove;
    }
    else{
        if(blockMove != 420){
            best = blockMove;
        }
        else {
            if(win2Setup != 420){
                best = win2Setup;
            }
            else {
                if (block2 != 420){
                    best = block2;
                }
                else {
                    if(boardP1.numMovesPlayed > 13 && (numColsFull(boardP1) >= 1) ){
                        //AI 1
                        set_color(LIGHTMAGENTA_CODE);
                        cout << endl << "AI is Thinking...." << endl;
                        reset_color();
                        best = SBgetnMaxCol(boardP1, -18, 18);
                    }
                    else {
                        if(forceWinMove != 420){
                            best = forceWinMove;
                        }
                        else{
                            if(forceWinMove2 != 420){
                                best = forceWinMove2;
                            }
                            else {
                                if(forceWinMove3 != 420){
                                    best = forceWinMove3;
                                }
                                else {
                                    if(forceWinMove4 !=420){
                                        best = forceWinMove4;
                                    }
                                    else {
                                        if(blockFW != 420){
                                            best = blockFW;
                                        }
                                        else{
                                            if(blockFW2 != 420){
                                                best = blockFW2;
                                            }
                                            else {
                                                if(blockFW3 != 420){
                                                    best = blockFW3;
                                                }
                                                else {
                                                    if(blockFW4 !=420){
                                                        best = blockFW4;
                                                    }
                                                    else {
                                                        best = bestMove(boardP1);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return best;
    
}

///Hard AI
int connect4AIH(const Board& board){
    
    int best = 420, winMove = 420, blockMove = 420, win2Setup = 420, block2 = 420;
    int forceWinMove = 420, blockFW = 420, forceWinMove2 = 420, blockFW2 = 420;
    int forceWinMove3 = 420, blockFW3 =420, forceWinMove4 = 420, blockFW4 = 420;
    
    
    Board boardP1 = board;
    Board boardP2;
    
    for (int i = 0; i < NUM_COLS; ++i){
        int testMove = middleOut[i];
        Result notIllegal = boardP1.makeMove(testMove);
        boardP1 = board;
        boardP2 = board;
        boardP2.updateToMove();
        
        if(notIllegal != IllegalMove){
            if(isWin(testMove, boardP1)){
                winMove = testMove;
            }
            else {
                if(isWin(testMove, boardP2)){
                    blockMove = testMove;
                }
                else {
                    if(noWinSetup(testMove, boardP1)){
                        if(is2WinSetup(testMove, boardP1)){
                            win2Setup = testMove;
                        }
                        else {
                            if(is2WinSetup(testMove, boardP2)){
                                block2 = testMove;
                            }
                            else {
                                if(isForceWin(testMove, boardP1)){
                                    forceWinMove = testMove;
                                }
                                else{
                                    if(isForceWin(testMove, boardP2)){
                                        blockFW = testMove;
                                    }
                                    else {
                                        if(is2LayerForceWin(testMove, boardP1)){
                                            forceWinMove2 = testMove;
                                        }
                                        else{
                                            if(is2LayerForceWin(testMove, boardP2)){
                                                blockFW2 = testMove;
                                            }
                                            else {
                                                if(is3LayerForceWin(testMove, boardP1)){
                                                    forceWinMove3 = testMove;
                                                }
                                                else {
                                                    if(is3LayerForceWin(testMove, boardP2)){
                                                        blockFW3 = testMove;
                                                    }
                                                    else {
                                                        if(is4LayerForceWin(testMove, boardP1)){
                                                            forceWinMove4 = testMove;
                                                        }
                                                        else {
                                                            if(is4LayerForceWin(testMove, boardP2)){
                                                                blockFW4 = testMove;
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                                
                            }
                        }
                        
                    }
                }
            }
            
        }
    }
    
    boardP1 = board;
    if(winMove != 420){
        best = winMove;
    }
    else{
        if(blockMove != 420){
            best = blockMove;
        }
        else {
            if(win2Setup != 420){
                best = win2Setup;
            }
            else {
                if (block2 != 420){
                    best = block2;
                }
                else {
                    if(numColsFull(boardP1) >= 4 ){
                        best = getnMaxCol(boardP1, -18, 18);
                    }
                    else {
                        if(forceWinMove != 420){
                            best = forceWinMove;
                        }
                        else{
                            if(forceWinMove2 != 420){
                                best = forceWinMove2;
                            }
                            else {
                                if(forceWinMove3 != 420){
                                    best = forceWinMove3;
                                }
                                else {
                                    if(forceWinMove4 !=420){
                                        best = forceWinMove4;
                                    }
                                    else {
                                        if(blockFW != 420){
                                            best = blockFW;
                                        }
                                        else{
                                            if(blockFW2 != 420){
                                                best = blockFW2;
                                            }
                                            else {
                                                if(blockFW3 != 420){
                                                    best = blockFW3;
                                                }
                                                else {
                                                    if(blockFW4 !=420){
                                                        best = blockFW4;
                                                    }
                                                    else {
                                                        best = bestMove(boardP1);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    return best;
    
}

//MEDIUM AI//////////////
int connect4AIM(const Board& board){
    
    int best = 420, winMove = 420, blockMove = 420, win2Setup = 420, block2 = 420;
    int forceWinMove = 420, blockFW = 420, forceWinMove2 = 420, blockFW2 = 420;
    
    Board boardP1 = board;
    Board boardP2;
    
    for (int i = 0; i < NUM_COLS; ++i){
        int testMove = middleOut[i];
        Result notIllegal = boardP1.makeMove(testMove);
        boardP1 = board;
        boardP2 = board;
        boardP2.updateToMove();
        
        if(notIllegal != IllegalMove){
            if(isWin(testMove, boardP1)){
                winMove = testMove;
            }
            else {
                if(isWin(testMove, boardP2)){
                    blockMove = testMove;
                }
                else {
                    if(noWinSetup(testMove, boardP1)){
                        if(is2WinSetup(testMove, boardP1)){
                            win2Setup = testMove;
                        }
                        else {
                            if(is2WinSetup(testMove, boardP2)){
                                block2 = testMove;
                            }
                            else {
                                if(isForceWin(testMove, boardP1)){
                                    forceWinMove = testMove;
                                }
                                else{
                                    if(isForceWin(testMove, boardP2)){
                                        blockFW = testMove;
                                    }
                                    else {
                                        if(is2LayerForceWin(testMove, boardP1)){
                                            forceWinMove2 = testMove;
                                        }
                                        else{
                                            if(is2LayerForceWin(testMove, boardP2)){
                                                blockFW2 = testMove;
                                            }
                                        }
                                    }
                                }
                                
                            }
                        }
                        
                    }
                }
            }
            
        }
    }
    
    boardP1 = board;
    if(winMove != 420){
        best = winMove;
    }
    else{
        if(blockMove != 420){
            best = blockMove;
        }
        else {
            if(win2Setup != 420){
                best = win2Setup;
            }
            else {
                if (block2 != 420){
                    best = block2;
                }
                else {
                    if(forceWinMove != 420){
                        best = forceWinMove;
                    }
                    else{
                        if(blockFW != 420){
                            best = forceWinMove2;
                        }
                        else {
                            best = bestMove(boardP1);
                        }
                    }
                }
            }
        }
    }
    
    return best;
    
}

///EASY AI
int connect4AIE(const Board& board){
    
    int best = 420, winMove = 420, blockMove = 420, win2Setup = 420, block2 = 420;
    Board boardP1 = board;
    Board boardP2;
    
    for (int i = 0; i < NUM_COLS; ++i){
        int testMove = middleOut[i];
        Result notIllegal = boardP1.makeMove(testMove);
        boardP1 = board;
        boardP2 = board;
        boardP2.updateToMove();
        
        if(notIllegal != IllegalMove){
            if(isWin(testMove, boardP1)){
                winMove = testMove;
            }
            else {
                if(isWin(testMove, boardP2)){
                    blockMove = testMove;
                }
            }
            
        }
    }
    
    boardP1 = board;
    if(winMove != 420){
        best = winMove;
    }
    else{
        if(blockMove != 420){
            best = blockMove;
        }
        else {
            best = bestMove(boardP1);
                }
            }
    
    return best;
    
}

//Self-Esteem Booster
int connect4AISE(const Board& board){
    int best = 420, winMove = 420, blockMove = 420, win2Setup = 420, block2 = 420;
    Board boardP1 = board;
    Board boardP2;
    
    for (int i = 0; i < NUM_COLS; ++i){
        int testMove = middleOut[i];
        Result notIllegal = boardP1.makeMove(testMove);
        boardP1 = board;
        boardP2 = board;
        boardP2.updateToMove();
        
        if(notIllegal != IllegalMove){
            if(isWin(testMove, boardP1)){
                winMove = testMove;
            }
            else {
                if(isWin(testMove, boardP2)){
                    //blockMove = testMove;
                }
            }
            
        }
    }
    
    boardP1 = board;
    if(winMove != 420){
        best = winMove;
    }
    else{
        if(blockMove != 420){
            best = blockMove;
        }
        else {
            best = rand() % NUM_COLS;
                }
            }
    
    return best;
    
}




bool isWin(int col, Board testboard) {
    return testboard.makeMove(col) == Win;
}

bool noWinSetup(int col, Board testboard){
    Board test;
    test = testboard;
    
    test.makeMove(col);
    
    for(int i = 0; i < NUM_COLS; ++i){
        if(isWin(middleOut[i], test)){
            return false;
        }
    }
    return true;
}

bool is2WinSetup(int col, Board testboard){
    
    int numWinMoves = 0;
    Board test = testboard;
    test.makeMove(col);
    test.updateToMove();
    
    for(int i = 0; i < NUM_COLS; ++i){
        if(isWin(middleOut[i], test)){
            numWinMoves += 1;
        }
    }
    return numWinMoves > 1;
}

bool no2WinSetups(int col, Board testboard){
    Board test = testboard;
    test.makeMove(col);
    
    for(int i = 0; i< NUM_COLS; ++i){
        if(is2WinSetup(middleOut[i], test)){
            return false;
        }
    }
    
    return true;
    
}
bool noForceWinSetup(int col, Board testboard){
    Board test = testboard;
    
    test.makeMove(col);
    
    for(int i = 0; i< NUM_COLS; ++i){
        if(isOpponentForceWin(middleOut[i], test)){
            return false;
        }
    }
    
    return true;
    
}

bool isMyWinSetup(int col, Board testboard){
    Board test;
    test = testboard;
    
    
    test.makeMove(col);
    test.updateToMove();
    
    for(int i = 0; i < NUM_COLS; ++i){
        if(isWin(middleOut[i], test)){
            return true;
        }
    }
    return false;
}

int getWinCol(Board testboard){
    Board test;
    test = testboard;
    test.updateToMove();
    
    for(int i = 0; i < NUM_COLS; ++i){
        if(isWin(middleOut[i], test)){
            return middleOut[i];
        }
    }
    return 0;
}
    

bool isForceWin(int col, Board testboard){
    Board test = testboard;
    
    
    if(isMyWinSetup(col, test) && noWinSetup(col, test) ) { //}&& no2WinSetups(col, test3)){
            test.makeMove(col);
            Board test3 = test;
        
            test.makeMove(getWinCol(test));
            
            for(int i=0; i < NUM_COLS; ++i){
                Board test2 = test;
                int testMove = middleOut[i];
                if(isWin(testMove, test2) || ( is2WinSetup(testMove, test2) && noWinSetup(testMove, test2) && !isMyWinSetup(getWinCol(test3), test3)) ) {
                    return true;
                }
            }
        }
    return false;
}

bool isOpponentForceWin(int col, Board testboard){
    Board test = testboard;
    
    
    if(isMyWinSetup(col, test) && noWinSetup(col, test)) {
        test.makeMove(col);
        test.makeMove(getWinCol(test));
        
        for(int i=0; i < NUM_COLS; ++i){
            Board test2 = test;
            int testMove = middleOut[i];
            if(isWin(testMove, test2) || (is2WinSetup(testMove, test2) && noWinSetup(testMove, test2) )) {
                return true;
            }
        }
    }
    return false;
}



bool is2LayerForceWin(int col, Board testboard){
    Board test = testboard;
    
    
    if(isMyWinSetup(col, test) && noWinSetup(col, test) ) {
        test.makeMove(col);
        Board test3 = test;
        
        test.makeMove(getWinCol(test));
        
        for(int i=0; i < NUM_COLS; ++i){
            Board test2 = test;
            int testMove = middleOut[i];
            
            if(isForceWin(testMove , test2) && noWinSetup(testMove, test2)  && !isMyWinSetup(getWinCol(test3), test3)) {
                return true;
            }
        }
    }
    return false;
}

bool is3LayerForceWin(int col, Board testboard){
    Board test = testboard;
    
    
    if(isMyWinSetup(col, test) && noWinSetup(col, test) ) {
        test.makeMove(col);
        Board test3 = test;
        
        test.makeMove(getWinCol(test));
        
        for(int i=0; i < NUM_COLS; ++i){
            Board test2 = test;
            int testMove = middleOut[i];
            
            if(is2LayerForceWin(testMove , test2) && noWinSetup(testMove, test2)  && !isMyWinSetup(getWinCol(test3), test3)) {
                return true;
            }
        }
    }
    return false;
}

bool is4LayerForceWin(int col, Board testboard){
    Board test = testboard;
    
    
    if(isMyWinSetup(col, test) && noWinSetup(col, test) ) {
        test.makeMove(col);
        Board test3 = test;
        
        test.makeMove(getWinCol(test));
        
        for(int i=0; i < NUM_COLS; ++i){
            Board test2 = test;
            int testMove = middleOut[i];
            
            if(is3LayerForceWin(testMove , test2) && noWinSetup(testMove, test2)  && !isMyWinSetup(getWinCol(test3), test3)) {
                return true;
            }
        }
    }
    return false;
}


int bestMove(Board testboard){
    
    int bestMove = 420, highCount = 0, setupMove = 420;
    PieceType player, notPlayer;
    Board test; Board test2;
    test = testboard;
    
    if(test.numMovesPlayed % 2 == 0){
        player = Player1;
        notPlayer = Player2;
    }
    else {
        player = Player2;
        notPlayer = Player1;
    }
    
    for (int i = 0; i < NUM_COLS; ++i){
        int count = 0;
        int numBlocked = 0;
        
        int countE, countW, countNE,
        countSE, countNW, countSW, countEW,
        countSWNE, countSENW;
        
        int testMove = middleOut[i];
        Result notIllegal = IllegalMove;
        
        notIllegal = test.makeMove(testMove);
        test = testboard;
        test2 = test;
        test2.updateToMove();
        
        
        if(notIllegal == NoResult && noWinSetup(testMove, test)  && no2WinSetups(testMove, test) && noForceWinSetup(testMove, test)){
            
            
            countW =  1 * test.usablePiecesInDirection(notPlayer, testboard.getFirstFreeRow(testMove), testMove , 0, -1);
            countE =  1 * test.usablePiecesInDirection(notPlayer, testboard.getFirstFreeRow(testMove), testMove, 0, 1);
            countEW = countE + countW;
            
            countNW =  1 * test.usablePiecesInDirection(notPlayer, testboard.getFirstFreeRow(testMove), testMove, 1, -1);
            countSE =  1 * test.usablePiecesInDirection(notPlayer, testboard.getFirstFreeRow(testMove), testMove, -1, 1);
            countSENW = countSE + countNW;
            
            countSW =  1 * test.usablePiecesInDirection(notPlayer, testboard.getFirstFreeRow(testMove), testMove, -1, -1);
            countNE=  1 * test.usablePiecesInDirection(notPlayer, testboard.getFirstFreeRow(testMove), testMove, 1, 1);
            countSWNE = countSW + countNE;
            
            if(countEW >= 3){
                count += 3;
                count +=  1 * test.AIpiecesInDirection(player, testboard.getFirstFreeRow(testMove), testMove , 0, -1);
                count += 1 * test.AIpiecesInDirection(player, testboard.getFirstFreeRow(testMove), testMove, 0, 1);
            }
            
            if(countSENW >= 3){
                count += 3;
                count += 1 * test.AIpiecesInDirection(player, testboard.getFirstFreeRow(testMove), testMove, 1, -1);
                count +=  1 * test.AIpiecesInDirection(player, testboard.getFirstFreeRow(testMove), testMove, -1, 1);
                
            }
            
            if(countSWNE >= 3){
                count += 3;
                count += 1 * test.AIpiecesInDirection(player, testboard.getFirstFreeRow(testMove), testMove, -1, -1);
                count +=  1 * test.AIpiecesInDirection(player, testboard.getFirstFreeRow(testMove), testMove, 1, 1);
            }
            
            
            
            
            
             countW =  1 * test.usablePiecesInDirection(player, testboard.getFirstFreeRow(testMove), testMove , 0, -1);
             countE =  1 * test.usablePiecesInDirection(player, testboard.getFirstFreeRow(testMove), testMove, 0, 1);
             countEW = countE + countW;
             
             countNW =  1 * test.usablePiecesInDirection(player, testboard.getFirstFreeRow(testMove), testMove, 1, -1);
             countSE =  1 * test.usablePiecesInDirection(player, testboard.getFirstFreeRow(testMove), testMove, -1, 1);
             countSENW = countSE + countNW;
             
             countSW =  1 * test.usablePiecesInDirection(player, testboard.getFirstFreeRow(testMove), testMove, -1, -1);
             countNE=  1 * test.usablePiecesInDirection(player, testboard.getFirstFreeRow(testMove), testMove, 1, 1);
             countSWNE = countSW + countNE;
             
             if(countEW >= 3){
             numBlocked += 2;
                 /*
                 count +=  2 * test.AIpiecesInDirection(notPlayer, testboard.getFirstFreeRow(testMove), testMove , 0, -1);
                 count += 2 * test.AIpiecesInDirection(notPlayer, testboard.getFirstFreeRow(testMove), testMove, 0, 1);
                 */
             }
             
             if(countSENW >= 3){
             numBlocked += 2;
                 /*
                 count += 2 * test.AIpiecesInDirection(notPlayer, testboard.getFirstFreeRow(testMove), testMove, 1, -1);
                 count +=  2 * test.AIpiecesInDirection(notPlayer, testboard.getFirstFreeRow(testMove), testMove, -1, 1);
                  */
             }
             
             if(countSWNE >= 3){
             numBlocked += 2;
                 /*
                 count += 2 * test.AIpiecesInDirection(notPlayer, testboard.getFirstFreeRow(testMove), testMove, -1, -1);
                 count +=  2 * test.AIpiecesInDirection(notPlayer, testboard.getFirstFreeRow(testMove), testMove, 1, 1);
                  */
             }
             count += numBlocked;
             
            
    
            if((count > highCount)){
                highCount = count;
                setupMove = testMove;
            }
        }
        
    }
    if(setupMove != 420){
        bestMove = setupMove;
    }
    else{
        bestMove = bestMovePV(testboard);
    }
    
    return bestMove;
}



int bestMovePV(Board testboard){
    int openRow, max = 0, bestMove = 420;
    
    int positionValues[NUM_ROWS][NUM_COLS] = {
        {300, 400, 500, 400, 500, 400, 300},
        {400, 600, 800, 1000, 800, 600, 400},
        {500, 800, 1100, 1300, 1100, 800, 500},
        {500, 800, 1100, 1300, 1100, 800, 500},
        {400, 600, 800, 1000, 800, 600, 400},
        {300, 420, 500, 900, 500, 420, 300}};
    
    
    for(int i = 0; i < NUM_COLS; ++i){
        int testMove = middleOut[i];
        Board test = testboard;
        openRow = test.getFirstFreeRow(testMove);
        
        if((openRow < NUM_ROWS) && noWinSetup(testMove , test)  && no2WinSetups(testMove, test)){
            if(positionValues[openRow][testMove] >= max){
                max = positionValues[openRow][testMove];
                bestMove = testMove;
            }
        }
    }
    
    
    if(bestMove != 420){
        return bestMove;
    }
    else {
        for(int i = 0; i < NUM_COLS; ++i){
            int testMove = middleOut[i];
            Board test = testboard;
            openRow = test.getFirstFreeRow(testMove);
            
            if((openRow < NUM_ROWS)){
                if(positionValues[openRow][testMove] >= max){
                    max = positionValues[openRow][testMove];
                    bestMove = testMove;
                }
            }
        }
    }
    return bestMove;
}


int numColsFull(Board testboard){
    int numFull = 0;
    Board test = testboard;
    for(int i =0; i < NUM_COLS; ++i){
        if(test.getFirstFreeRow(i) == NUM_ROWS){
            numFull += 1;
        }
    }
    return numFull;
}

int_fast8_t nMax(int_fast8_t alpha, int_fast8_t beta, Board& testboard) {
    
    if(alpha < beta){
        Board test = testboard;
        if(test.numMovesPlayed == 42){
            return 0;
        }
        
        for(int_fast8_t i = 0; i < NUM_COLS; ++i){
            int_fast8_t testMove = middleOut[i];
            
            if((isWin(testMove, test))){
                return ((43 - test.numMovesPlayed) / 2) ;
            }
        }
        
        int_fast8_t max = ((41 - test.numMovesPlayed) / 2) ;
        if(beta > max) {
            beta = max;
            if(alpha >= beta) {
                return beta;
            }
        }
        
        for(int_fast8_t i = 0; i < NUM_COLS; ++i){
            int_fast8_t testMove = middleOut[i];
            test = testboard;
            if((test.makeTestMove(testMove) != IllegalMove)) {
                int_fast8_t score = -nMax(-beta, -alpha, test);
                
                if(score >= beta){
                    return score;
                }
                if(score > alpha) {
                    alpha = score;
                }
            }
            
        }
    }
    return alpha;
}


string getFenKey(Board testboard){
    string key = "";
    ostringstream os;
    testboard.printBoard_as_FENstring(os);
    key += os.str();
    
    if(testboard.nextPlayer_to_move == Player1){
        key += 'X';
    }
    else{
        key += 'O';
    }
    
    return key;
}



int getnMaxCol(Board testboard, int_fast8_t testAlphaVal, int_fast8_t testBetaVal){
    int moveScores[NUM_COLS];
    int bestMove = 0, bestScore = -420;
    Board test  = testboard;
    Result notIllegal;
    
    for(int i = 0; i < NUM_COLS; ++i){
        test = testboard;
        int testMove = middleOut[i];
        notIllegal = test.makeMove(testMove);
        
        
        if(notIllegal != IllegalMove){
            moveScores[testMove] = -nMax(testAlphaVal, testBetaVal, test);
        }
        else{
            moveScores[testMove] = 420;
        }
    }
    
    for(int j = 0; j < NUM_COLS; ++j){
        test = testboard;
        if((moveScores[j]  > bestScore) && (moveScores[j]  != 420)){
            bestScore = moveScores[j];
            bestMove = j;
        }
    }
    return bestMove;
}


////////////STRINGBOARD AI FUNCTIONS//////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
int SBgetnMaxCol(Board testboard, int_fast8_t testAlphaVal, int_fast8_t testBetaVal){
    int moveScores[NUM_COLS];
    int bestMove = 0, bestScore = -420;
    stringBoard testString(testboard);
    stringBoard test;
    Result notIllegal;
    int numTests = 0;
    
    for(int i = 0; i < NUM_COLS; ++i){
        test = testString;
        string key = test.mine + test.taken;
        if(numTests % 2 == 0){
            TT.clear();
        }
        test = testString;
        int testMove = middleOut[i];
        notIllegal = test.SBmakeMove(testMove);
        
        
        if(notIllegal != IllegalMove){
            moveScores[testMove] = -SBnMax(testAlphaVal, testBetaVal, test);
            numTests += 1;
            
        }
        else{
            moveScores[testMove] = 420;
        }
    }
    
    for(int j = 0; j < NUM_COLS; ++j){
        if((moveScores[j]  > bestScore) && (moveScores[j]  != 420)){
            bestScore = moveScores[j];
            bestMove = j;
        }
    }
    
    return bestMove;
}

int_fast8_t SBnMax(int_fast8_t alpha, int_fast8_t beta, stringBoard& testboard) {
    
    if(alpha < beta){
        stringBoard test = testboard;
        if(test.numMovesPlayed == 42){
            return 0;
        }
        
        for(int_fast8_t i = 0; i < NUM_COLS; ++i){
            int_fast8_t testMove = middleOut[i];
            test = testboard;
            if(SBisWin(testMove, test)){
                return ((43 - test.numMovesPlayed) / 2) ;
            }
        }
        
        int_fast8_t max = ((41 - testboard.numMovesPlayed) / 2) ;
        if(beta > max) {
            beta = max;
            if(alpha >= beta) {
                return beta;
            }
        }
        
        for(int_fast8_t i = 0; i < NUM_COLS; ++i){
            int_fast8_t testMove = middleOut[i];
            test = testboard;
            if((test.SBmakeTestMove(testMove) != IllegalMove)) {
                //int_fast8_t score = -SBnMax(-beta, -alpha, test);
                
                string key = test.mine + test.taken;
                int_fast8_t score;
                
                if(TT.count(key) == 0){
                  score = -SBnMax(-beta, -alpha, test);
                   TT[key] = score;
                }
                else {
                    score = TT.at(key);
                }
                
                
                if(score >= beta){
                    return score;
                }
                if(score > alpha) {
                    alpha = score;
                }
            }
            
        }
    }
    return alpha;
}

bool SBisWin(int col, stringBoard testboard) {
    return testboard.SBmakeMove(col) == Win;
}






/*
 
 
 //BITSETBOARD FUNCTIONS
 int BBgetnMaxCol(Board testboard, int_fast8_t testAlphaVal, int_fast8_t testBetaVal);
 int_fast8_t BBnMax(int_fast8_t alpha, int_fast8_t beta, bitSetBoard& testboard);
 bool BBisWin(int col, bitSetBoard testboard);
 
 //BOOLBOARD FUNCTIONS
 int BooBgetnMaxCol(Board testboard, int_fast8_t testAlphaVal, int_fast8_t testBetaVal);
 int_fast8_t BooBnMax(int_fast8_t alpha, int_fast8_t beta, boolBoard& testboard);
 bool BooBisWin(int col, boolBoard testboard);

////////////BITSETBOARD AI FUNCTIONS//////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
int BBgetnMaxCol(Board testboard, int_fast8_t testAlphaVal, int_fast8_t testBetaVal){
    int moveScores[NUM_COLS];
    int bestMove = 0, bestScore = -420;
    bitSetBoard testBoardAsBitSetBoard(testboard);
    bitSetBoard test;
    Result notIllegal;
    int numTests = 0;
    
    for(int i = 0; i < NUM_COLS; ++i){
        
        
        if(numTests % 2 == 0){
            TT.clear();
        }
        
        test = testBoardAsBitSetBoard;
        int testMove = middleOut[i];
        notIllegal = test.BBmakeMove(testMove);
        
        
        if(notIllegal != IllegalMove){
            moveScores[testMove] = -BBnMax(testAlphaVal, testBetaVal, test);
            numTests += 1;
            
        }
        else{
            moveScores[testMove] = 420;
        }
    }
    
    //TT.erase(TT.begin(), TT.find(key));
    
    for(int j = 0; j < NUM_COLS; ++j){
        if((moveScores[j]  > bestScore) && (moveScores[j]  != 420)){
            bestScore = moveScores[j];
            bestMove = j;
        }
    }
    
    return bestMove;
}

int_fast8_t BBnMax(int_fast8_t alpha, int_fast8_t beta, bitSetBoard& testboard) {
    
    if(alpha < beta){
        bitSetBoard test = testboard;
        if(test.numMovesPlayed == 42){
            return 0;
        }
        
        for(int_fast8_t i = 0; i < NUM_COLS; ++i){
            int_fast8_t testMove = middleOut[i];
            test = testboard;
            if(BBisWin(testMove, test)){
                return ((43 - test.numMovesPlayed) / 2) ;
            }
        }
        
        int_fast8_t max = ((41 - testboard.numMovesPlayed) / 2) ;
        if(beta > max) {
            beta = max;
            if(alpha >= beta) {
                return beta;
            }
        }
        
        for(int_fast8_t i = 0; i < NUM_COLS; ++i){
            int_fast8_t testMove = middleOut[i];
            test = testboard;
            if((test.BBmakeTestMove(testMove) != IllegalMove)) {
                //int_fast8_t score = -BBnMax(-beta, -alpha, test);
                
                string key = test.mine.to_string() + test.taken.to_string();
                if(test.numMovesPlayed % 2 == 0){
                    key += 'O';
                }
                else {
                    key += 'X';
                }
                int_fast8_t score;
                
                if(TT.count(key) == 0){
                    score = -BBnMax(-beta, -alpha, test);
                    //TT.insert(make_pair(key, score));
                    TT[key] = score;
                }
                else {
                    score = TT.at(key);
                }
                
                
                if(score >= beta){
                    return score;
                }
                if(score > alpha) {
                    alpha = score;
                }
            }
            
        }
    }
    return alpha;
}

bool BBisWin(int col, bitSetBoard testboard) {
    return testboard.BBmakeMove(col) == Win;
}




////////////BOOLBOARD AI FUNCTIONS//////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
int BooBgetnMaxCol(Board testboard, int_fast8_t testAlphaVal, int_fast8_t testBetaVal){
    int moveScores[NUM_COLS];
    int bestMove = 0, bestScore = -420;
    boolBoard testBoolBoard(testboard);
    boolBoard test;
    Result notIllegal;
    int numTests = 0;
    
 
     string key = test.mine.to_string() + test.taken.to_string();
     if(test.numMovesPlayed % 2 == 0){
     key += 'O';
     }
     else {
     key += 'X';
     }
    
    for(int i = 0; i < NUM_COLS; ++i){
        
        
        if(numTests % 2 == 0){
            TT.clear();
        }
        
        test = testBoolBoard;
        int testMove = middleOut[i];
        notIllegal = test.BooBmakeMove(testMove);
        
        
        if(notIllegal != IllegalMove){
            moveScores[testMove] = -BooBnMax(testAlphaVal, testBetaVal, test);
            numTests += 1;
            
        }
        else{
            moveScores[testMove] = 420;
        }
    }
    
    //TT.erase(TT.begin(), TT.find(key));
    
    for(int j = 0; j < NUM_COLS; ++j){
        if((moveScores[j]  > bestScore) && (moveScores[j]  != 420)){
            bestScore = moveScores[j];
            bestMove = j;
        }
    }
    
    return bestMove;
}

int_fast8_t BooBnMax(int_fast8_t alpha, int_fast8_t beta, boolBoard& testboard) {
    
    if(alpha < beta){
        boolBoard test = testboard;
        if(test.numMovesPlayed == 42){
            return 0;
        }
        
        for(int_fast8_t i = 0; i < NUM_COLS; ++i){
            int_fast8_t testMove = middleOut[i];
            test = testboard;
            if(BooBisWin(testMove, test)){
                return ((43 - test.numMovesPlayed) / 2) ;
            }
        }
        
        int_fast8_t max = ((41 - testboard.numMovesPlayed) / 2) ;
        if(beta > max) {
            beta = max;
            if(alpha >= beta) {
                return beta;
            }
        }
        
        for(int_fast8_t i = 0; i < NUM_COLS; ++i){
            int_fast8_t testMove = middleOut[i];
            test = testboard;
            if((test.BooBmakeTestMove(testMove) != IllegalMove)) {
                int_fast8_t score = -BooBnMax(-beta, -alpha, test);
                
 
                string key = test.mine + test.taken;
                int_fast8_t score;
                
                if(TT.count(key) == 0){
                    score = -BooBnMax(-beta, -alpha, test);
                    //TT.insert(make_pair(key, score));
                    TT[key] = score;
                }
                else {
                    score = TT.at(key);
                }
 
                
                if(score >= beta){
                    return score;
                }
                if(score > alpha) {
                    alpha = score;
                }
            }
            
        }
    }
    return alpha;
}

bool BooBisWin(int col, boolBoard testboard) {
    return testboard.BooBmakeMove(col) == Win;
}


*/









