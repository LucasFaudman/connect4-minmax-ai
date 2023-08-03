#include "board.h"
#include "color.h"
#include <bitset>
#include <vector>
Board::Board() {
    numMovesPlayed = 0;
    for(int col = 0; col < NUM_COLS; ++ col){
        for(int row = 0; row < NUM_ROWS; ++ row){
            data[row][col] = Empty;
        }
    }
    
    nextPlayer_to_move = Player1;
    
}

Board::Board(const string &fen) {
    string empty;
    int numEmpty;
    numMovesPlayed = 0;
    
    int indexrow = 0;
    int indexcol = 0;
    
    for(int col = 0; col < NUM_COLS; ++ col){
        for(int row = 0; row < NUM_ROWS; ++ row){
            data[row][col] = Empty;
        }
    }
    
    
    for(int i = 0; i < (fen.length() - 2) ; ++i){
        
        if(fen[i] == PLAYER1_TOKEN){
            data[indexrow][indexcol] = Player1;
            numMovesPlayed += 1;
            indexcol += 1;
        }
        else if(fen[i] == PLAYER2_TOKEN){
            data[indexrow][indexcol] = Player2;
            numMovesPlayed += 1;
            indexcol += 1;
        }
        else{
            if(fen[i] == '/'){
                indexrow +=1;
                
            }
            else{
                
                
                empty = fen[i];
                numEmpty = stoi(empty);
                for(int j = 0; j < numEmpty; ++j){
                    data[indexrow][indexcol + j] = Empty;
                }
                indexcol += numEmpty;
            }
            indexrow = 0;
        }
        
        
    }
    
    if(fen[fen.length() - 1] == PLAYER1_TOKEN){
        nextPlayer_to_move = Player1;
    }
    else {
        nextPlayer_to_move = Player2;
    }
}

void Board::printBoard_as_FENstring(ostream &os) const {
    for (int row = 0; row < NUM_ROWS; ++row)  {
        int numEmpty = 0;
        for (int col = 0; col < NUM_COLS; ++col)   {
            
            
            
            if (data[row][col] == Player1){
                
                if(numEmpty > 0){
                    os << numEmpty;
                }
                os <<  PLAYER1_TOKEN;
                numEmpty = 0;
            }
            else if (data[row][col] == Player2) {
                
                if(numEmpty > 0){
                    os << numEmpty;
                }
                os << PLAYER2_TOKEN;
                numEmpty = 0;
            }
            else {
                numEmpty += 1;
            }
        }
        
        if(numEmpty > 0){
            os << numEmpty;
        }
        if(row < (NUM_ROWS - 1)){
            os << "/";
        }
    }
}





PieceType Board::atLocation(int row, int col) {
    return data[row][col];
}

void Board::prettyPrintBoard(ostream &os) const {
    os << endl;
    for (int row = NUM_ROWS - 1; row >= 0; row--)  {
        os << "     +---+---+---+---+---+---+---+"
        << endl
        << "    ";
        
        for (int col = 0; col < NUM_COLS; col++)   {
            os << " | " ;
            if ( data[row][col] == Player1)
                os <<  PLAYER1_TOKEN;
            else if (data[row][col] == Player2)
                os << PLAYER2_TOKEN;
            else
                os << EMPTY_TOKEN;
        }
        os << " |" << endl;
    }
    os << "     +---+---+---+---+---+---+---+" << endl
    <<"  col  1   2   3   4   5   6   7" << endl;
    return;
}

void Board::prettyPrintBoardColorAI(ostream &os, int AIWins, int PlayerWins, string dName) const {
    //remove slashes on color_enabled when testing with drive-xcode.o
    //color_enabled(true, true);
    os << endl;
    set_color(LIGHTBLUE_CODE);
    os << "     ";
    cout << "AI Difficulty: ";
    set_color(LIGHTRED_CODE);
    cout <<  dName << endl;    
    set_color(LIGHTRED_CODE);
    os << "     " << "";
    os << "PLAYER WINS: " << PlayerWins;
    set_color(LIGHTBLUE_CODE);
    os << "    AI WINS: " << AIWins << endl;
    
    reset_color();
    for (int row = NUM_ROWS - 1; row >= 0; row--)  {
    
        
        os << "     ";
        set_color(YellowBG);
        os << "+---+---+---+---+---+---+---+";
        reset_color();
        os << endl;
        os << "    ";
        for (int col = 0; col < NUM_COLS; col++)   {
            os << " ";
            set_color(YellowBG);
            os << "| " ;
            reset_color();
            if ( data[row][col] == Player1 || data[row][col] == Player1LM){
                if (isWinPrint(row, col) || data[row][col] == Player1LM){
                    set_color(P1Blink);
                }
                else {
                set_color(P1);
                }
                os << 'X';
                reset_color();
                set_color(YellowBG);
            }
            
            else if (data[row][col] == Player2 || data[row][col] == Player2LM){
                if (isWinPrint(row, col) || data[row][col] == Player2LM){
                    set_color(P2Blink);
                }
                else {
                    set_color(P2);
                }
                os << 'O';
                reset_color();
                set_color(YellowBG);
            }
            else {
                set_color(YellowBG);
                os << EMPTY_TOKEN; }
        }
        set_color(YellowBG);
        os << " |";
        reset_color();
        os << endl;
    }
    
    os << "     ";
    set_color(YellowBG);
    os << "+---+---+---+---+---+---+---+";
    reset_color();
    os << endl;
    os <<"  ";
    set_color(LIGHTBLUE_CODE);
    os << "col  1   2   3   4   5   6   7";
    reset_color();
    os << endl;
    
    return;
}

void Board::prettyPrintBoardColor(ostream &os) const {
    //remove slashes on color_enabled when testing with drive-xcode.o
    //color_enabled(true, true);
    //os << endl;
    //os << "     " << "     ";
    //set_color(LIGHTBLUE_CODE);
    //os << "EECS183 CONNECT 4!" << endl;
    //reset_color();
    for (int row = NUM_ROWS - 1; row >= 0; row--)  {
        
        
        os << "     ";
        set_color(YellowBG);
        os << "+---+---+---+---+---+---+---+";
        reset_color();
        os << endl;
        os << "    ";
        for (int col = 0; col < NUM_COLS; col++)   {
            os << " ";
            set_color(YellowBG);
            os << "| " ;
            reset_color();
            if ( data[row][col] == Player1 || data[row][col] == Player1LM){
                if (isWinPrint(row, col) || data[row][col] == Player1LM){
                    set_color(P1Blink);
                }
                else {
                    set_color(P1);
                }
                os << 'X';
                reset_color();
                set_color(YellowBG);
            }
            
            else if (data[row][col] == Player2 || data[row][col] == Player2LM){
                if (isWinPrint(row, col) || data[row][col] == Player2LM){
                    set_color(P2Blink);
                }
                else {
                    set_color(P2);
                }
                os << 'O';
                reset_color();
                set_color(YellowBG);
            }
            else {
                set_color(YellowBG);
                os << EMPTY_TOKEN; }
        }
        set_color(YellowBG);
        os << " |";
        reset_color();
        os << endl;
    }
    
    os << "     ";
    set_color(YellowBG);
    os << "+---+---+---+---+---+---+---+";
    reset_color();
    os << endl;
    os <<"  ";
    set_color(LIGHTBLUE_CODE);
    os << "col  1   2   3   4   5   6   7";
    reset_color();
    os << endl;
    return;
}



int_fast8_t Board::toMove() const {
    if (nextPlayer_to_move == Player1) {
        return 1;
    }
    else {
        return 2;    }
}


Result Board::makeMove(uint_fast8_t col) {
    int openRow;
    openRow = getFirstFreeRow(col);
    
    
    if(inBounds(openRow, col)){
        data[openRow][col] = updateToMove();
        numMovesPlayed += 1;
        if(isWin(openRow, col)){
            return Win;
        }
        else if(isBoardFull()){
            return Draw;
        }
        else {
            return NoResult;
        }
    }
    
    else {
        return IllegalMove;
    }
}


Result Board::makeTestMove(uint_fast8_t col) {
    uint_fast8_t openRow;
    openRow = getFirstFreeRow(col);
    
    
    if(inBounds(openRow, col)){
        data[openRow][col] = updateToMove();
        numMovesPlayed += 1;
        return NoResult;
    }
    
    else {
        return IllegalMove;
    }
}



uint_fast8_t Board::getFirstFreeRow(uint_fast8_t col) const {
    for(int row = 0; row < NUM_ROWS; ++row){
        
        if(data[row][col] == Empty){
            return row;
        }
    }
    
    return NUM_ROWS;
}

PieceType Board::updateToMove() {
    if (nextPlayer_to_move == Player1) {
        nextPlayer_to_move = Player2;
        return Player1;
    }
    else {
        nextPlayer_to_move = Player1;
        return Player2;    }
}

bool Board::isBoardFull() const {
    int numEmpty = 0;
    
    for(int col = 0; col < NUM_COLS; ++ col){
        for(int row = 0; row < NUM_ROWS; ++ row){
            if(data[row][col] == Empty) {
                numEmpty += 1;
            }
        }
    }
    
    return numEmpty == 0;
}

bool Board::inBounds(int row, int col) const {
    return !( (row < 0) || (row >= NUM_ROWS) || (col < 0) || (col >= NUM_COLS));
}

uint_fast8_t Board::piecesInDirection(uint_fast8_t row, uint_fast8_t col, int_fast8_t dRow, int_fast8_t dCol) const {
    
    int numSame = 0;
    
    for(int i = 1; i < 4; ++i){
        int newRow = row + (i * dRow);
        int newCol = col + (i * dCol);
        
        if(inBounds(newRow, newCol) && data[row][col] == data[newRow][newCol]){
            numSame += 1;
            }
           else {
               return numSame;
        }
        
    }
    return numSame;
}

bool Board::isWin(uint_fast8_t row, uint_fast8_t col) const {
    int countN, countE, countS, countW, countNE,
    countSE, countNW, countSW, countEW, countNS,
    countSWNE, countSENW;
    
    countE = piecesInDirection(row, col, 0, 1);
    countW = piecesInDirection(row, col, 0, -1);
    countN = piecesInDirection(row, col, 1, 0);
    countS = piecesInDirection(row, col, -1, 0);
    
    countNE = piecesInDirection(row, col, 1, 1);
    countSE = piecesInDirection(row, col, 1, -1);
    countNW = piecesInDirection(row, col, -1, 1);
    countSW = piecesInDirection(row, col, -1, -1);
    
    countEW = countE + countW;
    
    countNS = countS + countN;
    countSWNE = countSW + countNE;
    countSENW = countSE + countNW;
    
    return ((countN >= 3) || (countE >= 3) || (countS >= 3) || (countW >= 3) ||
            (countNW >= 3) || (countSW >= 3) || (countSE >= 3) || (countNE >= 3)
            || (countEW >= 3) || (countSWNE >= 3) || (countSENW >= 3) || (countNS >= 3));
}



///CHECKING FUNCTIONS USED ONLY FOR PRINTING
uint_fast8_t Board::piecesInDirectionPrint(uint_fast8_t row, uint_fast8_t col, int_fast8_t dRow, int_fast8_t dCol) const {
    
    int numSame = 0;
    
    for(int i = 1; i < 4; ++i){
        int newRow = row + (i * dRow);
        int newCol = col + (i * dCol);
        
        if(inBounds(newRow, newCol) && ( ((data[row][col] == Player1 || data[row][col] == Player1LM) && (data[newRow][newCol] == Player1 || data[newRow][newCol] == Player1LM) ) || ((data[row][col] == Player2 || data[row][col] == Player2LM) && (data[newRow][newCol] == Player2 || data[newRow][newCol] == Player2LM))) ){
            numSame += 1;
        }
        else {
            return numSame;
        }
        
    }
    return numSame;
}

bool Board::isWinPrint(uint_fast8_t row, uint_fast8_t col) const {
    int countN, countE, countS, countW, countNE,
    countSE, countNW, countSW, countEW, countNS,
    countSWNE, countSENW;
    
    countE = piecesInDirectionPrint(row, col, 0, 1);
    countW = piecesInDirectionPrint(row, col, 0, -1);
    countN = piecesInDirectionPrint(row, col, 1, 0);
    countS = piecesInDirectionPrint(row, col, -1, 0);
    
    countNE = piecesInDirectionPrint(row, col, 1, 1);
    countSE = piecesInDirectionPrint(row, col, 1, -1);
    countNW = piecesInDirectionPrint(row, col, -1, 1);
    countSW = piecesInDirectionPrint(row, col, -1, -1);
    
    countEW = countE + countW;
    
    countNS = countS + countN;
    countSWNE = countSW + countNE;
    countSENW = countSE + countNW;
    
    return ((countN >= 3) || (countE >= 3) || (countS >= 3) || (countW >= 3) ||
            (countNW >= 3) || (countSW >= 3) || (countSE >= 3) || (countNE >= 3)
            || (countEW >= 3) || (countSWNE >= 3) || (countSENW >= 3) || (countNS >= 3));
}


///STANDARD BOARD AI HELPER FUNCTIONS////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
uint_fast8_t Board::usablePiecesInDirection(PieceType notPlayer, uint_fast8_t row, uint_fast8_t col, int_fast8_t dRow, int_fast8_t dCol) const {
    
    int numSame = 0;
    
    for(int i = 1; i < 4; ++i){
        int newRow = row + (i * dRow);
        int newCol = col + (i * dCol);
        
        if(inBounds(newRow, newCol) && (data[newRow][newCol] != notPlayer)){
            numSame += 1;
        }
        else {
            return numSame;
        }

    }
    
    return numSame;
}


uint_fast8_t Board::AIpiecesInDirection(PieceType player, uint_fast8_t row, uint_fast8_t col, int_fast8_t dRow, int_fast8_t dCol) const {

    int numSame = 0;
    PieceType notPlayer;
    if(player == Player1){
        notPlayer = Player2;
    }
    else{
        notPlayer = Player1;
    }
    
    for(int i = 1; i < 4; ++i){
        int newRow = row + (i * dRow);
        int newCol = col + (i * dCol);
        
        if(inBounds(newRow, newCol) && (data[newRow][newCol] == player)){
            numSame += 1;
        }
        if(inBounds(newRow, newCol) && (data[newRow][newCol] == notPlayer)){
            return numSame;
        }

    }
    
    return numSame;
}




/////////STRINGBOARD CONSTRUCTORS AND MEMBER FUNCTIONS////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

stringBoard::stringBoard() {
     //numMovesPlayed = 0;
    //for(int i = 0; i < 42; ++i){
      //  mine += '0';
        //taken += '0';
    //}
   
}

stringBoard::stringBoard(Board& testboard){
    
    PieceType player, notPlayer;
    numMovesPlayed = testboard.numMovesPlayed;
    int indexNum = 0;
    
    
    for(int i = 0; i < 42; ++i){
        mine += '0';
        taken += '0';
    }
    
    if(testboard.nextPlayer_to_move == Player1){
        player = Player1;
        notPlayer = Player2;
    }
    else{
        player = Player2;
        notPlayer = Player1;
    }
    
    for(int col = 0; col < NUM_COLS; ++col){
        for(int row = 0; row < NUM_ROWS; ++row){
            indexNum = (6 * col) + row;
            if(testboard.atLocation(row, col) == notPlayer){
                taken[indexNum] = '1';
            }
            if(testboard.atLocation(row, col) == player){
                taken[indexNum] = '1';
                mine[indexNum] = '1';
            }
        }
    }
}



void stringBoard::switchPlayer() {
    string mineCopy = mine;
    
    for(int i = 0; i < 42; ++i){
        if(taken[i] == '1'){
            if(mineCopy[i] == '0'){
                mine[i] = '1';
            }
            if(mineCopy[i] == '1'){
                mine[i] = '0';
            }
        }
    }
}

bool stringBoard::inBounds(uint_fast8_t row, uint_fast8_t col) const{
    return !( (row < 0) || (row >= NUM_ROWS) || (col < 0) || (col >= NUM_COLS));
}

Result stringBoard::SBmakeMove(uint_fast8_t col){
    uint_fast8_t openRow;
    openRow = SBgetFirstFreeRow(col);
    
    uint_fast8_t indexNum = (6 * col) + openRow;
    
    if(inBounds(openRow, col)){
        taken[indexNum] = '1';
        mine[indexNum] = '1';
        numMovesPlayed += 1;
        if(SBisWin(openRow, col)){
            return Win;
        }
        else {
            switchPlayer();
            return NoResult;
        }
    }
    
    else {
        return IllegalMove;
    }
}

Result stringBoard::SBmakeTestMove(uint_fast8_t col){
    uint_fast8_t openRow = SBgetFirstFreeRow(col);
    
    uint_fast8_t indexNum = (6 * col) + openRow;
    
    if(inBounds(openRow, col)){
        taken[indexNum] = '1';
        mine[indexNum] = '1';
        numMovesPlayed += 1;
        switchPlayer();
        if(numMovesPlayed == 42){
            return Draw;
        }
        return NoResult;
    }
    
    else {
        return IllegalMove;
    }
}

////NEED TO FIX
bool stringBoard::SBtestWinMove(uint_fast8_t col){
    uint_fast8_t openRow = SBgetFirstFreeRow(col);
    if(SBisWin(openRow, col)){
        numMovesPlayed += 1;
        return true;
    }
    return false;
}


uint_fast8_t stringBoard::SBpiecesInDirection(uint_fast8_t row, uint_fast8_t col, int_fast8_t dRow, int_fast8_t dCol) const{
    uint_fast8_t numSame = 0;
    //uint_fast8_t IndexNum = (6 * col) + row;
    
    for(uint_fast8_t i = 1; i < 4; ++i){
        int_fast8_t newRow = row + (i * dRow);
        int_fast8_t newCol = col + (i * dCol);
        uint_fast8_t newIndexNum = (6 * newCol) + newRow;
        
        if(inBounds(newRow, newCol) && mine[newIndexNum] == '1'){
            numSame += 1;
        }
        else {
            return numSame;
        }
    }
    return numSame;
}






bool stringBoard::SBisWin(uint_fast8_t row, uint_fast8_t col) const{
    uint_fast8_t countN, countE, countS, countW, countNE,
    countSE, countNW, countSW, countEW, countNS,
    countSWNE, countSENW;
    
    
    countE = SBpiecesInDirection(row, col, 0, 1);
    countW = SBpiecesInDirection(row, col, 0, -1);
    countN = SBpiecesInDirection(row, col, 1, 0);
    countS = SBpiecesInDirection(row, col, -1, 0);
    
    countNE = SBpiecesInDirection(row, col, 1, 1);
    countSE = SBpiecesInDirection(row, col, -1, 1);
    countNW = SBpiecesInDirection(row, col, 1, -1);
    countSW = SBpiecesInDirection(row, col, -1, -1);
    
    
    
    countEW = countE + countW;
    countNS = countS + countN;
    countSWNE = countSW + countNE;
    countSENW = countSE + countNW;
    
    return ((countN >= 3) || (countE >= 3) || (countS >= 3) || (countW >= 3) ||
            (countNW >= 3) || (countSW >= 3) || (countSE >= 3) || (countNE >= 3)
            || (countEW >= 3) || (countSWNE >= 3) || (countSENW >= 3) || (countNS >= 3));
}



uint_fast8_t stringBoard::SBgetFirstFreeRow(uint_fast8_t col) const{
    uint_fast8_t indexNum = 0;
    
    for(uint_fast8_t row = 0; row < NUM_ROWS; ++row){
        indexNum = (6 * col) + row;
        if(taken[indexNum] == '0') {
            return row;
        }
    }
    
    return NUM_ROWS;
}

/*
/////////BITBOARD CONSTRUCTORS AND MEMBER FUNCTIONS////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

bitSetBoard::bitSetBoard() {
    mine.reset();
    taken.reset();
    numMovesPlayed = 0;
}

bitSetBoard::bitSetBoard(Board& testboard){
    
    PieceType player, notPlayer;
    numMovesPlayed = testboard.numMovesPlayed;
    int indexNum = 0;
    mine.reset();
    taken.reset();
    
    if(testboard.nextPlayer_to_move == Player1){
        player = Player1;
        notPlayer = Player2;
    }
    else{
        player = Player2;
        notPlayer = Player1;
    }
    
    for(int col = 0; col < NUM_COLS; ++col){
        for(int row = 0; row < NUM_ROWS; ++row){
            indexNum = (6 * col) + row;
            if(testboard.atLocation(row, col) == notPlayer){
                taken.set(indexNum);
            }
            if(testboard.atLocation(row, col) == player){
                mine.set(indexNum);
                taken.set(indexNum);
            }
        }
    }
}



void bitSetBoard::switchPlayer() {
    for(int i = 0; i < 42; ++i){
        if(taken[i] == 1){
            mine.flip(i);
        }
    }
}

bool bitSetBoard::inBounds(uint_fast8_t row, uint_fast8_t col) const{
    return !( (row < 0) || (row >= NUM_ROWS) || (col < 0) || (col >= NUM_COLS));
}

Result bitSetBoard::BBmakeMove(uint_fast8_t col){
    uint_fast8_t openRow;
    openRow = BBgetFirstFreeRow(col);
    
    uint_fast8_t indexNum = (6 * col) + openRow;
    
    if(inBounds(openRow, col)){
        mine.set(indexNum);
        taken.set(indexNum);
        numMovesPlayed += 1;
        if(BBisWin(openRow, col)){
            return Win;
        }
        else {
            switchPlayer();
            return NoResult;
        }
    }
    
    else {
        return IllegalMove;
    }
}

Result bitSetBoard::BBmakeTestMove(uint_fast8_t col){
    uint_fast8_t openRow = BBgetFirstFreeRow(col);
    
    uint_fast8_t indexNum = (6 * col) + openRow;
    
    if(inBounds(openRow, col)){
        mine.set(indexNum);
        taken.set(indexNum);
        numMovesPlayed += 1;
        switchPlayer();
        if(numMovesPlayed == 42){
            return Draw;
        }
        return NoResult;
    }
    
    else {
        return IllegalMove;
    }
}

////NEED TO FIX
bool bitSetBoard::testWinMove(uint_fast8_t col){
    uint_fast8_t openRow = BBgetFirstFreeRow(col);
    if(BBisWin(openRow, col)){
        numMovesPlayed +=1;
        return true;
    }
    return false;
}


uint_fast8_t bitSetBoard::BBpiecesInDirection(uint_fast8_t row, uint_fast8_t col, int_fast8_t dRow, int_fast8_t dCol) const{
    uint_fast8_t numSame = 0;
    //uint_fast8_t IndexNum = (6 * col) + row;
    
    for(uint_fast8_t i = 1; i < 4; ++i){
        int_fast8_t newRow = row + (i * dRow);
        int_fast8_t newCol = col + (i * dCol);
        uint_fast8_t newIndexNum = (6 * newCol) + newRow;
        
        if(inBounds(newRow, newCol) && mine[newIndexNum] == 1){
            numSame += 1;
        }
        else {
            return numSame;
        }
    }
    return numSame;
}

u_long bitSetBoard::getKey(){
    
    
    return 0;
}




bool bitSetBoard::BBisWin(uint_fast8_t row, uint_fast8_t col) const{
    uint_fast8_t countN, countE, countS, countW, countNE,
    countSE, countNW, countSW, countEW, countNS,
    countSWNE, countSENW;
    
    
    countE = BBpiecesInDirection(row, col, 0, 1);
    countW = BBpiecesInDirection(row, col, 0, -1);
    countN = BBpiecesInDirection(row, col, 1, 0);
    countS = BBpiecesInDirection(row, col, -1, 0);
    
    countNE = BBpiecesInDirection(row, col, 1, 1);
    countSE = BBpiecesInDirection(row, col, -1, 1);
    countNW = BBpiecesInDirection(row, col, 1, -1);
    countSW = BBpiecesInDirection(row, col, -1, -1);
    
    
    
    countEW = countE + countW;
    countNS = countS + countN;
    countSWNE = countSW + countNE;
    countSENW = countSE + countNW;
    
    return ((countN >= 3) || (countE >= 3) || (countS >= 3) || (countW >= 3) ||
            (countNW >= 3) || (countSW >= 3) || (countSE >= 3) || (countNE >= 3)
            || (countEW >= 3) || (countSWNE >= 3) || (countSENW >= 3) || (countNS >= 3));
}



uint_fast8_t bitSetBoard::BBgetFirstFreeRow(uint_fast8_t col) const{
    uint_fast8_t indexNum = 0;
    
    for(uint_fast8_t row = 0; row < NUM_ROWS; ++row){
        indexNum = (6 * col) + row;
        if(taken[indexNum] == 0) {
            return row;
        }
    }
    
    return NUM_ROWS;
}










/////////BoolBOARD CONSTRUCTORS AND MEMBER FUNCTIONS////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

boolBoard::boolBoard() {
    numMovesPlayed = 0;
    for(int i = 0; i < 42; ++i){
        mine[i] = false;
        taken[i] = false;
    }
    
}

boolBoard::boolBoard(Board& testboard){
    
    PieceType player, notPlayer;
    numMovesPlayed = testboard.numMovesPlayed;
    int indexNum = 0;
    
    
    for(int i = 0; i < 42; ++i){
        mine[i] = false;
        taken[i] = false;
    }
    
    if(testboard.nextPlayer_to_move == Player1){
        player = Player1;
        notPlayer = Player2;
    }
    else{
        player = Player2;
        notPlayer = Player1;
    }
    
    for(int col = 0; col < NUM_COLS; ++col){
        for(int row = 0; row < NUM_ROWS; ++row){
            indexNum = (6 * col) + row;
            if(testboard.atLocation(row, col) == notPlayer){
                taken[indexNum] = true;
            }
            if(testboard.atLocation(row, col) == player){
                taken[indexNum] = true;
                mine[indexNum] = true;
            }
        }
    }
}



void boolBoard::switchPlayer() {
    bool copyMine[42];
    
    for(int i = 0; i < 42; ++i){
        if(mine[i] == true){
            copyMine[i] = true;
        }
        else{
            copyMine[i] = false;
        }
    }
    
    
    for(int i = 0; i < 42; ++i){
        if(taken[i] == true && copyMine[i] == false){
            mine[i] = true;
            }
        if(taken[i] == true && copyMine[i] == true){
            mine[i] = false;
        }
        }
    }


bool boolBoard::inBounds(uint_fast8_t row, uint_fast8_t col) const{
    return !( (row < 0) || (row >= NUM_ROWS) || (col < 0) || (col >= NUM_COLS));
}

Result boolBoard::BooBmakeMove(uint_fast8_t col){
    uint_fast8_t openRow;
    openRow = BooBgetFirstFreeRow(col);
    
    uint_fast8_t indexNum = (6 * col) + openRow;
    
    if(inBounds(openRow, col)){
        taken[indexNum] = 1;
        mine[indexNum] = 1;
        numMovesPlayed += 1;
        if(BooBisWin(openRow, col)){
            return Win;
        }
        else {
            switchPlayer();
            return NoResult;
        }
    }
    
    else {
        return IllegalMove;
    }
}

Result boolBoard::BooBmakeTestMove(uint_fast8_t col){
    uint_fast8_t openRow = BooBgetFirstFreeRow(col);
    
    uint_fast8_t indexNum = (6 * col) + openRow;
    
    if(inBounds(openRow, col)){
        taken[indexNum] = 1;
        mine[indexNum] = 1;
        numMovesPlayed += 1;
        switchPlayer();
        if(numMovesPlayed == 42){
            return Draw;
        }
        return NoResult;
    }
    
    else {
        return IllegalMove;
    }
}

////NEED TO FIX
bool boolBoard::BooBtestWinMove(uint_fast8_t col){
    uint_fast8_t openRow = BooBgetFirstFreeRow(col);
    if(BooBisWin(openRow, col)){
        numMovesPlayed +=1;
        return true;
    }
    return false;
}


uint_fast8_t boolBoard::BooBpiecesInDirection(uint_fast8_t row, uint_fast8_t col, int_fast8_t dRow, int_fast8_t dCol) const{
    uint_fast8_t numSame = 0;
    //uint_fast8_t IndexNum = (6 * col) + row;
    
    for(uint_fast8_t i = 1; i < 4; ++i){
        int_fast8_t newRow = row + (i * dRow);
        int_fast8_t newCol = col + (i * dCol);
        uint_fast8_t newIndexNum = (6 * newCol) + newRow;
        
        if(inBounds(newRow, newCol) && mine[newIndexNum] == 1){
            numSame += 1;
        }
        else {
            return numSame;
        }
    }
    return numSame;
}






bool boolBoard::BooBisWin(uint_fast8_t row, uint_fast8_t col) const{
    uint_fast8_t countN, countE, countS, countW, countNE,
    countSE, countNW, countSW, countEW, countNS,
    countSWNE, countSENW;
    
    
    countE = BooBpiecesInDirection(row, col, 0, 1);
    countW = BooBpiecesInDirection(row, col, 0, -1);
    countN = BooBpiecesInDirection(row, col, 1, 0);
    countS = BooBpiecesInDirection(row, col, -1, 0);
    
    countNE = BooBpiecesInDirection(row, col, 1, 1);
    countSE = BooBpiecesInDirection(row, col, -1, 1);
    countNW = BooBpiecesInDirection(row, col, 1, -1);
    countSW = BooBpiecesInDirection(row, col, -1, -1);
    
    
    
    countEW = countE + countW;
    countNS = countS + countN;
    countSWNE = countSW + countNE;
    countSENW = countSE + countNW;
    
    return ((countN >= 3) || (countE >= 3) || (countS >= 3) || (countW >= 3) ||
            (countNW >= 3) || (countSW >= 3) || (countSE >= 3) || (countNE >= 3)
            || (countEW >= 3) || (countSWNE >= 3) || (countSENW >= 3) || (countNS >= 3));
}



uint_fast8_t boolBoard::BooBgetFirstFreeRow(uint_fast8_t col) const{
    uint_fast8_t indexNum = 0;
    
    for(uint_fast8_t row = 0; row < NUM_ROWS; ++row){
        indexNum = (6 * col) + row;
        if(taken[indexNum] == 0) {
            return row;
        }
    }
    
    return NUM_ROWS;
}


*/

