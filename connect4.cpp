#include "connect4.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "ai.h"
using namespace std;

int winsAI = 0;
int winsPlayer =0;

string getName(int player_number);

///RUNS PLAYER VS PLAYER GAMES
void terminalPlayColor(){
    string namePlayer1 = "";
    string namePlayer2 = "";
    string menuChoice = "";
    
    int colChoice = 0;
    
    Board board, boardToPrint;
    Result game = NoResult;
    
    
    
    string winningPlayer = "";
    
    set_color(LIGHTCYAN_CODE);
    board = getBoard(namePlayer1, namePlayer2);
    reset_color();
    boardToPrint = board;
    

    while((menuChoice != "q") && (game != Win) &&
          (game != Draw) ){
        
        printTitle2();
        reset_color();
        boardToPrint.prettyPrintBoardColor(cout);
        set_color(LIGHTCYAN_CODE);
        cout << "\nEnter: the column to move, q to quit, s to save" << endl;
        
        if (board.toMove() == 1 ){
            set_color(LIGHTRED_CODE);
            cout << namePlayer1;
            cout <<  " enter your move: ";
            reset_color();
        }
        else  {
            set_color(LIGHTBLUE_CODE);
            cout << namePlayer2;
            cout <<  " enter your move: ";
            reset_color();
        }
        
        
        cin >> menuChoice;
        
        if(menuChoice == "s"){
            saveBoard(namePlayer1, namePlayer2, board);
        }
        else if (menuChoice == "q") {
            set_color(LIGHTMAGENTA_CODE);
            cout << endl << "Thanks for playing!"<< endl;
        }
        else {
            
            if((menuChoice != "1") && (menuChoice != "2") && (menuChoice != "3")
               && (menuChoice != "4") && (menuChoice != "5") &&
               (menuChoice != "6") && (menuChoice != "7")){
                set_color(LIGHTMAGENTA_CODE);
                cout << "ILLEGAL MOVE: Try again" << endl;
                reset_color();
            }
            
            else {
                colChoice = stoi(menuChoice) - 1;
                
                boardToPrint = board;
                game = board.makeMove(colChoice);
                setLastMove(boardToPrint, board);
                
               
                if(game == IllegalMove) {
                    set_color(LIGHTMAGENTA_CODE);
                    cout << "ILLEGAL MOVE: Try again" << endl;
                    reset_color();
                }
                else if (game == Draw){
                    set_color(LIGHTMAGENTA_CODE);
                    cout << "Draw!" << endl;
                    reset_color();
                    board.prettyPrintBoardColor(cout);
                    
                }
                else if (game == Win){
                    if (board.toMove() == 2) {
                        winningPlayer = namePlayer1;
                        set_color(LIGHTREDBL);
                    }
                    else {
                        winningPlayer = namePlayer2;
                        set_color(LIGHTBLUEBL);
                    }
                    cout << "Congratulations " << winningPlayer;
                    cout << "! You won!" << endl;
                    reset_color();
                    board.prettyPrintBoardColor(cout);
                    char choice;
                    set_color(LIGHTCYAN_CODE);
                    cout << "Press ANY KEY then ENTER to Continue...";
                    while(!(cin >> choice)){
                        cin.clear();
                    }                }
            }
        }
    }
    reset_color();
    menuChoice = "";
    
    
    
}

//RUNS PLAYER VS AI WITH PLAYER GOING FIRST
void terminalPlayColorAI1st(int diffLevel){
    string namePlayer1 = "";
    string lastNameP1 = "";
    string namePlayer2 = "AI";
    string menuChoice = "";
    
    int colChoice = 0;
    
    Board board;
    Board boardToPrint;
    
    Result game = NoResult;
    
    string winningPlayer = "";
    
    string diffName = "";
    
    switch (diffLevel) {
        case 1:
            diffName = "SELF-ESTEEM";
            break;
        case 2:
            diffName = "EASY";
            break;
        case 3:
            diffName = "MEDIUM";
            break;
        case 4:
            diffName = "HARD";
            break;
        default:
            diffName = "BEST";
            break;
    }
    

    set_color(LIGHTCYAN_CODE);
    board = getBoardAI1(namePlayer1, namePlayer2);
    reset_color();
    boardToPrint = board;
    while((menuChoice != "q") && (game != Win) &&
          (game != Draw) ){
        
        reset_color();
        printTitle2();
        boardToPrint.prettyPrintBoardColorAI(cout, winsAI, winsPlayer, diffName);
        set_color(LIGHTCYAN_CODE);
        cout << "\nEnter: the column to move, q to quit, s to save" << endl;
        
        if (board.toMove() == 1 ){
            set_color(LIGHTRED_CODE);
            cout << namePlayer1;
            cout <<  " enter your move: ";
            reset_color();
            cin >> menuChoice;
        }
       
        
        
        if(menuChoice == "s"){
            saveBoard(namePlayer1, namePlayer2, board);
        }
        else if (menuChoice == "q") {
            set_color(LIGHTMAGENTA_CODE);
            cout << endl << "Thanks for playing!"<< endl;
            reset_color();
        }
        else {
            
            if((board.toMove() == 1) && (menuChoice != "1") && (menuChoice != "2") && (menuChoice != "3")
               && (menuChoice != "4") && (menuChoice != "5") &&
               (menuChoice != "6") && (menuChoice != "7")){
                set_color(LIGHTMAGENTA_CODE);
                cout << "ILLEGAL MOVE: Try again" << endl;
                reset_color();
            }
            
            else {
                if(board.toMove() == 1){
                    colChoice = stoi(menuChoice) - 1;
                }
                else {
                    switch (diffLevel) {
                        case 1:
                            colChoice = connect4AISE(board);
                            break;
                        case 2:
                            colChoice = connect4AIE(board);
                            break;
                        case 3:
                            colChoice = connect4AIM(board);
                            break;
                        case 4:
                            colChoice = connect4AIH(board);
                            break;
                        default:
                            colChoice = connect4AI(board);
                            break;
                    }
                }
                
                boardToPrint = board;
                game = board.makeMove(colChoice);
                setLastMove(boardToPrint, board);
                
             
                if(game == IllegalMove) {
                    set_color(LIGHTMAGENTA_CODE);
                    cout << "ILLEGAL MOVE: Try again" << endl;
                    reset_color();
                }
                else if (game == Draw){
                    set_color(LIGHTMAGENTA_CODE);
                    cout << "Draw!" << endl;
                    reset_color();
                    boardToPrint.prettyPrintBoardColorAI(cout, winsAI, winsPlayer, diffName);
                    
                }
                else if (game == Win){
                    if (board.toMove() == 2) {
                        if(diffLevel == 5){
                            winsPlayer += 1;
                        }
                        winningPlayer = namePlayer1;
                        reset_color();
                        boardToPrint.prettyPrintBoardColorAI(cout, winsAI, winsPlayer, diffName);
                        set_color(LIGHTREDBL);
                        cout << endl << "Congratulations " << winningPlayer << "!!";
                        cout << " You just beat our ";
                        set_color(LIGHTBLUEBL);
                        cout << diffName;
                        set_color(LIGHTREDBL);
                        cout << " AI!" << endl;
                        reset_color();
                        set_color(LIGHTRED_CODE);
                        printObamaR();
                        cout << endl;
                        char choice;
                        set_color(LIGHTCYAN_CODE);
                        cout << "Press ANY KEY then ENTER to Continue...";
                        while(!(cin >> choice)){
                            cin.clear();
                        }
                    
                    
                    
                    }
                    else {
                        winsAI += 1;
                        winningPlayer = namePlayer2;
                        reset_color();
                        boardToPrint.prettyPrintBoardColorAI(cout, winsAI, winsPlayer, diffName);
                        set_color(LIGHTBLUEBL);
                        cout << endl << "You just lost to our ";
                        set_color(LIGHTREDBL);
                        cout << diffName << " ";
                        set_color(LIGHTBLUEBL);
                        cout << winningPlayer << "!" << endl;
                        reset_color();
                        set_color(LIGHTRED_CODE);
                        printBrian(namePlayer1);
                        reset_color();
                        char choice;
                        set_color(LIGHTCYAN_CODE);
                        cout << "Press ANY KEY then ENTER to Continue...";
                        while(!(cin >> choice)){
                            cin.clear();
                        }
                        
                    }
                }
            }
        }
    }
    
    reset_color();
    menuChoice = "";
    
    
}

//RUNS PLAYER VS AI WITH AI GOING FIRST
void terminalPlayColorAI2nd(int diffLevel){
    string namePlayer1 = "AI";
    string lastNameP1 = "";
    string namePlayer2 = "";
    string menuChoice = "";
    
    int colChoice = 0;
    
    Board board;
    Board boardToPrint;
    
    Result game = NoResult;
    
    string winningPlayer = "";
    
    string diffName = "";
    switch (diffLevel) {
        case 1:
            diffName = "SELF-ESTEEM";
            break;
        case 2:
            diffName = "EASY";
            break;
        case 3:
            diffName = "MEDIUM";
            break;
        case 4:
            diffName = "HARD";
            break;
        default:
            diffName = "BEST";
            break;
    }
    
    
    set_color(LIGHTCYAN_CODE);
    board = getBoardAI2(namePlayer1, namePlayer2);
    reset_color();
    boardToPrint = board;
    while((menuChoice != "q") && (game != Win) &&
          (game != Draw) ){
        printTitle2();
        reset_color();
        boardToPrint.prettyPrintBoardColorAI(cout, winsAI, winsPlayer, diffName);
        set_color(LIGHTCYAN_CODE);
        cout << "\nEnter: the column to move, q to quit, s to save" << endl;
        
        if (board.toMove() == 2 ){
            set_color(LIGHTBLUE_CODE);
            cout << namePlayer2;
            cout <<  " enter your move: ";
            reset_color();
            cin >> menuChoice;
        }
        
        
        
        if(menuChoice == "s"){
            saveBoard(namePlayer1, namePlayer2, board);
        }
        else if (menuChoice == "q") {
            set_color(LIGHTMAGENTA_CODE);
            cout << endl << "Thanks for playing!"<< endl;
            reset_color();
        }
        else {
            
            if((board.toMove() == 2) && (menuChoice != "1") && (menuChoice != "2") && (menuChoice != "3")
               && (menuChoice != "4") && (menuChoice != "5") &&
               (menuChoice != "6") && (menuChoice != "7")){
                set_color(LIGHTMAGENTA_CODE);
                cout << "ILLEGAL MOVE: Try again" << endl;
                reset_color();
            }
            
            else {
                if(board.toMove() == 2){
                    colChoice = stoi(menuChoice) - 1;
                }
                else {
                    switch (diffLevel) {
                        case 1:
                            colChoice = connect4AISE(board);
                            break;
                        case 2:
                            colChoice = connect4AIE(board);
                            break;
                        case 3:
                            colChoice = connect4AIM(board);
                            break;
                        case 4:
                            colChoice = connect4AIH(board);
                            break;
                        default:
                            colChoice = connect4AI(board);
                            break;
                    }
                }
                
                boardToPrint = board;
                game = board.makeMove(colChoice);
                setLastMove(boardToPrint, board);
                
                
                if(game == IllegalMove) {
                    set_color(LIGHTMAGENTA_CODE);
                    cout << "ILLEGAL MOVE: Try again" << endl;
                    reset_color();
                }
                else if (game == Draw){
                    set_color(LIGHTMAGENTA_CODE);
                    cout << "Draw!" << endl;
                    reset_color();
                    boardToPrint.prettyPrintBoardColorAI(cout, winsAI, winsPlayer, diffName);
                    
                }
                else if (game == Win){
                    if (board.toMove() == 1) {
                        if(diffLevel == 5){
                        winsPlayer += 1;
                        }
                        winningPlayer = namePlayer2;
                        
                        reset_color();
                        boardToPrint.prettyPrintBoardColorAI(cout, winsAI, winsPlayer, diffName);
                        set_color(LIGHTBLUEBL);
                        cout << endl;
                        cout << endl << "Congratulations " << winningPlayer << "!!";
                        cout << " You just beat our ";
                        set_color(LIGHTREDBL);
                        cout << diffName;
                        set_color(LIGHTBLUEBL);
                        cout << " AI!" << endl;
                        reset_color();
                        set_color(LIGHTBLUE_CODE);
                        printObamaB();
                        cout << endl;
                        char choice;
                        set_color(LIGHTCYAN_CODE);
                        cout << "Press ANY KEY then ENTER to Continue...";
                        while(!(cin >> choice)){
                            cin.clear();
                        }

                        
                        
                    }
                    else {
                        winsAI += 1;
                        winningPlayer = namePlayer1;
                        reset_color();
                        boardToPrint.prettyPrintBoardColorAI(cout, winsAI, winsPlayer, diffName);
                        set_color(LIGHTREDBL);
                        cout << endl << "You just lost to our ";
                        set_color(LIGHTBLUEBL);
                        cout << diffName << " ";
                        set_color(LIGHTREDBL);
                        cout << winningPlayer << "!" << endl;
                        reset_color();
                        printBrian(namePlayer2);
                        reset_color();
                        char choice;
                        set_color(LIGHTCYAN_CODE);
                        cout << "Press ANY KEY then ENTER to Continue...";
                        while(!(cin >> choice)){
                            cin.clear();
                        }
                        
                    }
                }
            }
        }
    }
    
    reset_color();
    menuChoice = "";
    
    
}



Board getBoard(string &p1, string &p2) {
    ifstream loadFile;
    string fileName = "game1.txt" ;
    string fen;
    
    char menuChoice;
    
    cout << endl;
    cout << "Enter L to load a game, or P to play: " << flush;
    cin >> menuChoice;
    cout << endl;
    
    menuChoice = toupper(menuChoice);
    
    if (menuChoice == 'P'){
        p1 = getName(1);
        cin.clear();
        cout << endl;
        p2 = getName(2);
        
        return Board();
    }
    else {
        cout << "Enter the filename: " << flush;
        cin >> fileName;
        loadFile.open(fileName);
        
        getline(loadFile, p1);
        getline(loadFile, p2);
        getline(loadFile, fen);
        
        if(fen > "              "){
            return Board(fen);
        }
        else{
            set_color(LIGHTMAGENTA_CODE);
            cout << endl << "Invalid File. Setting Empty Board" << endl;
            reset_color();
            return Board();
        }
    }
}

Board getBoardAI1(string &p1, string &p2) {
    ifstream loadFile;
    string fileName = "game1.txt" ;
    string fen;
    
    char menuChoice;
    cout << endl;
    cout << "Enter L to load a game, or P to play: " << flush;
    cin >> menuChoice;
    cout << endl;
    menuChoice = toupper(menuChoice);
    
    if (menuChoice == 'P'){
        set_color(LIGHTRED_CODE);
        p1 = getName(3);
        cin.clear();
        cout << endl;
        p2 = "AI";
        
        return Board();
    }
    else {
        cout << "Enter the filename: " << flush;
        cin >> fileName;
        loadFile.open(fileName);
        
        getline(loadFile, p1);
        getline(loadFile, p2);
        getline(loadFile, fen);
        
        if(fen > "              "){
            return Board(fen);
        }
        else{
            set_color(LIGHTMAGENTA_CODE);
            cout << endl << "Invalid File. Setting Empty Board" << endl;
            reset_color();
            set_color(LIGHTRED_CODE);
            return Board();
        }
    }
}

Board getBoardAI2(string &p1, string &p2) {
    ifstream loadFile;
    string fileName = "game1.txt" ;
    string fen;
    
    char menuChoice;
    cout << endl;
    cout << "Enter L to load a game, or P to play: " << flush;
    cin >> menuChoice;
    cout << endl;
    menuChoice = toupper(menuChoice);
    
    if (menuChoice == 'P'){
        set_color(LIGHTBLUE_CODE);
        p2 = getName(3);
        cin.clear();
        cout << endl;
        p1 = "AI";
        
        return Board();
    }
    else {
        cout << "Enter the filename: " << flush;
        cin >> fileName;
        loadFile.open(fileName);
        
        getline(loadFile, p1);
        getline(loadFile, p2);
        getline(loadFile, fen);
        
        if(fen > "              "){
            return Board(fen);
        }
        else{
            set_color(LIGHTMAGENTA_CODE);
            cout << endl << "Invalid File. Setting Empty Board" << endl;
            reset_color();
            set_color(LIGHTBLUE_CODE);
            p2 = getName(3);
            cin.clear();
            cout << endl;
            p1 = "AI";
            
            return Board();
        }
    }
}


void saveBoard(string p1, string p2, const Board &board) {
    ofstream saveFile;
    string fileName = "game1.txt";
    char playerToMove = 'x';
    
    if(board.toMove() == 2){
        playerToMove = 'o';
    }
    
    cout << "Enter the filename: ";
    cin >> fileName;
    
    saveFile.open(fileName);
    
    saveFile << p1 << endl << p2 << endl;
    board.printBoard_as_FENstring(saveFile);
    
    
    saveFile << ' ' << playerToMove;
    saveFile.close();
    
    
}

string getName(int player_number){
    string p1Name;
    string p2Name;
    string p1LastName;
    string p2LastName;
    string noresponse = "          ";
    
    if(player_number == 1){
        cout << "Player " << player_number << ", enter your name: " << flush;
        cin >> p1Name;
        getline(cin, p1LastName);
        p1Name = p1Name + p1LastName;
        if (p1Name < noresponse) {
            p1Name = "Lil Dicky";
            
        }
        return p1Name;
    }
    else if (player_number == 2) {
        cout << "Player " << player_number << ", enter your name: " << flush;
        cin >> p2Name;
        getline(cin, p2LastName);
        p2Name = p2Name + p2LastName;
        if (p2Name < noresponse) {
            p2Name = "Rich Homie Quan";
            
        }
        return p2Name;
    }
    else if (player_number == 3) {
        cout << "Player, enter your name: " << flush;
        cin >> p2Name;
        getline(cin, p2LastName);
        p2Name = p2Name + p2LastName;
        if (p2Name < noresponse) {
            p2Name = "Rich Homie Quan";
            
        }
        return p2Name;
    }
    
    return 0;
}


//Use to set the last move on BoardToPrint
void setLastMove(Board& boardToPrint, Board newBoard){
    for(int col =0; col < NUM_COLS; ++col){
        for(int row =0; row < NUM_ROWS; ++row){
            if(newBoard.atLocation(row, col) == Player1 && boardToPrint.atLocation(row, col) == Empty) {
                boardToPrint.data[row][col] = Player1LM;
            }
            if(newBoard.atLocation(row, col) == Player2 && boardToPrint.atLocation(row, col) == Empty) {
                boardToPrint.data[row][col] = Player2LM;
            }
        }
    }
}




///USE For testing AIs
void AIbattle(){
    string namePlayer1 = "";
    string namePlayer2 = "";
    string menuChoice = "";
    
    int colChoice = 0;
    
    Board board, boardToPrint;
    Result game = NoResult;
    
    string winningPlayer = "";
    
    set_color(LIGHTCYAN_CODE);
    
    
    
    
    board = getBoard(namePlayer1, namePlayer2);
    reset_color();
    
    while((menuChoice != "q") && (game != Win) &&
          (game != Draw) ){
        reset_color();
        boardToPrint = board;
        boardToPrint.prettyPrintBoardColor(cout);
        set_color(LIGHTCYAN_CODE);
        cout << "\nEnter: the column to move, q to quit, s to save" << endl;
        
        if (board.toMove() == 1 ){
            colChoice = connect4AI(board);
        }
        else  {
            colChoice = connect4AI2(board);
        }
    
        game = board.makeMove(colChoice);
        setLastMove(boardToPrint, board);
        
        if(game == IllegalMove) {
            set_color(LIGHTMAGENTA_CODE);
            if (board.toMove() == 1 ){
                cout << namePlayer1 << "Tried to make an ";
                menuChoice = "q";
            }
            else  {
                cout << namePlayer2 << "Tried to make an ";
                menuChoice = "q";
            }
            
            cout << "ILLEGAL MOVE: Try again" << endl;
            reset_color();
        }
        else if (game == Draw){
            set_color(LIGHTMAGENTA_CODE);
            cout << "Draw!" << endl;
            reset_color();
            board.prettyPrintBoardColor(cout);
            
        }
        else if (game == Win){
            if (board.toMove() == 2) {
                winningPlayer = namePlayer1;
                set_color(LIGHTREDBL);
                cout << "Congratulations " << winningPlayer;
                cout << "! You won!" << endl;
                reset_color();
                board.prettyPrintBoardColor(cout);
                
                
                
            }
            else {
                winningPlayer = namePlayer2;
                set_color(LIGHTBLUEBL);
                cout << "Congradulations " << winningPlayer;
                cout << "! You Won!" << endl;
                reset_color();
                board.prettyPrintBoardColor(cout);
                
            }
        }
    }
    
    
    reset_color();
    
    
    
}

void printBrian(string loserName){
    reset_color();
    set_color(LIGHTRED_CODE);
    cout << endl << "Wow " << loserName << ", that was pretty sad... " << endl;
    cout << "You really didn't see that coming?" << endl << endl;
    
    set_color(BLACK_CODE);
    cout <<"╭━┳━╭━╭━╮╮"<< endl;
    cout <<"┃┈┈┈┣▅╋▅┫┃"<< endl;
    cout <<"┃┈┃┈╰━╰━━━━━━╮"<< endl;
    cout <<"╰┳╯┈┈┈┈┈┈┈┈┈◢▉◣"<< endl;
    cout <<"╲┃┈┈┈┈┈┈┈┈┈┈▉▉▉"<< endl;
    cout <<"╲┃┈┈┈┈┈┈┈┈┈┈◥▉◤"<< endl;
    cout <<"╲┃┈┈┈┈╭━┳━━━━╯"<< endl;
    cout <<"╲┣" ;
    set_color(LIGHTRED_CODE);
    cout << "━━" ;
    set_color(YELLOW_CODE);
    cout << "ф";
    set_color(LIGHTRED_CODE);
    cout << "━━━";
    set_color(BLACK_CODE);
    cout << "┫"<< endl << endl;
    set_color(LIGHTRED_CODE);
    cout << "Brian doesnt think you'll ever win... Can you prove him wrong?" << endl;
    cout << endl;
    reset_color();
    
}

void printObamaB(){
    set_color(LIGHTBLUE_CODE);
    cout << endl;
    cout << "░░█▀░░░░░░░░░░░▀▀███████░░░░" << endl;
    cout << "░░█▌░░░░░░░░░░░░░░░▀██████░░░" << endl;
    cout << "░█▌░░░░░░░░░░░░░░░░███████▌░░"<< endl;
    cout << "░█░░░░░░░░░░░░░░░░░████████░░"<< endl;
    cout << "▐▌░░░░░░░░░░░░░░░░░▀██████▌░░"<< endl;
    cout << "░▌▄███▌░░░░▀████▄░░░░▀████▌░░"<< endl;
    cout << "▐▀▀▄█▄░▌░░░▄██▄▄▄▀░░░░████▄▄░"<< endl;
    cout << "▐░▀░░═▐░░░░░░══░░▀░░░░▐▀░▄▀▌▌"<< endl;
    cout << "▐░░░░░▌░░░░░░░░░░░░░░░▀░▀░░▌▌"<< endl;
    cout << "▐░░░▄▀░░░▀░▌░░░░░░░░░░░░▌█░▌▌"<< endl;
    cout << "░▌░░▀▀▄▄▀▀▄▌▌░░░░░░░░░░▐░▀▐▐░"<< endl;
    cout << "░▌░░▌░▄▄▄▄░░░▌░░░░░░░░▐░░▀▐░░"<< endl;
    cout << "░█░▐▄██████▄░▐░░░░░░░░█▀▄▄▀░░"<< endl;
    cout << "░▐░▌▌░░░░░░▀▀▄▐░░░░░░█▌░░░░░░"<< endl;
    cout << "░░█░░▄▀▀▀▀▄░▄═╝▄░░░▄▀░▌░░░░░░"<< endl;
    cout << "░░░▌▐░░░░░░▌░▀▀░░▄▀░░▐░░░░░░░"<< endl;
    cout << "░░░▀▄░░░░░░░░░▄▀▀░░░░█░░░░░░░"<< endl;
    cout << "░░░▄█▄▄▄▄▄▄▄▀▀░░░░░░░▌▌░░░░░░"<< endl;
    cout << "░░▄▀▌▀▌░░░░░░░░░░░░░▄▀▀▄░░░░░"<< endl;
    cout << "▄▀░░▌░▀▄░░░░░░░░░░▄▀░░▌░▀▄░░░"<< endl;
    cout << "░░░░▌█▄▄▀▄░░░░░░▄▀░░░░▌░░░▌▄▄"<< endl;
    cout << "░░░▄▐██████▄▄░▄▀░░▄▄▄▄▌░░░░▄░"<< endl;
    cout << "░░▄▌████████▄▄▄███████▌░░░░░▄"<< endl;
    cout << "░▄▀░██████████████████▌▀▄░░░░"<< endl;
    cout << "▀░░░█████▀▀░░░▀███████░░░▀▄░░"<< endl;
    cout << "░░░░▐█▀░░░▐░░░░░▀████▌░░░░▀▄░"<< endl;
    cout << "░░░░░░▌░░░▐░░░░▐░░▀▀█░░░░░░░▀"<< endl;
    cout << "░░░░░░▐░░░░▌░░░▐░░░░░▌░░░░░░░"<< endl;
    set_color(LIGHTRED_CODE);
    cout << "░╔╗║░╔═╗░═╦═░░░░░╔╗░░╔═╗░╦═╗░"<< endl;
    cout << "░║║║░║░║░░║░░░░░░╠╩╗░╠═╣░║░║░"<< endl;
    cout << "░║╚╝░╚═╝░░║░░░░░░╚═╝░║░║░╩═╝░"<< endl;
    reset_color();
}
void printObamaR(){
    set_color(LIGHTRED_CODE);
    cout << endl;
    cout << "░░█▀░░░░░░░░░░░▀▀███████░░░░" << endl;
    cout << "░░█▌░░░░░░░░░░░░░░░▀██████░░░" << endl;
    cout << "░█▌░░░░░░░░░░░░░░░░███████▌░░"<< endl;
    cout << "░█░░░░░░░░░░░░░░░░░████████░░"<< endl;
    cout << "▐▌░░░░░░░░░░░░░░░░░▀██████▌░░"<< endl;
    cout << "░▌▄███▌░░░░▀████▄░░░░▀████▌░░"<< endl;
    cout << "▐▀▀▄█▄░▌░░░▄██▄▄▄▀░░░░████▄▄░"<< endl;
    cout << "▐░▀░░═▐░░░░░░══░░▀░░░░▐▀░▄▀▌▌"<< endl;
    cout << "▐░░░░░▌░░░░░░░░░░░░░░░▀░▀░░▌▌"<< endl;
    cout << "▐░░░▄▀░░░▀░▌░░░░░░░░░░░░▌█░▌▌"<< endl;
    cout << "░▌░░▀▀▄▄▀▀▄▌▌░░░░░░░░░░▐░▀▐▐░"<< endl;
    cout << "░▌░░▌░▄▄▄▄░░░▌░░░░░░░░▐░░▀▐░░"<< endl;
    cout << "░█░▐▄██████▄░▐░░░░░░░░█▀▄▄▀░░"<< endl;
    cout << "░▐░▌▌░░░░░░▀▀▄▐░░░░░░█▌░░░░░░"<< endl;
    cout << "░░█░░▄▀▀▀▀▄░▄═╝▄░░░▄▀░▌░░░░░░"<< endl;
    cout << "░░░▌▐░░░░░░▌░▀▀░░▄▀░░▐░░░░░░░"<< endl;
    cout << "░░░▀▄░░░░░░░░░▄▀▀░░░░█░░░░░░░"<< endl;
    cout << "░░░▄█▄▄▄▄▄▄▄▀▀░░░░░░░▌▌░░░░░░"<< endl;
    cout << "░░▄▀▌▀▌░░░░░░░░░░░░░▄▀▀▄░░░░░"<< endl;
    cout << "▄▀░░▌░▀▄░░░░░░░░░░▄▀░░▌░▀▄░░░"<< endl;
    cout << "░░░░▌█▄▄▀▄░░░░░░▄▀░░░░▌░░░▌▄▄"<< endl;
    cout << "░░░▄▐██████▄▄░▄▀░░▄▄▄▄▌░░░░▄░"<< endl;
    cout << "░░▄▌████████▄▄▄███████▌░░░░░▄"<< endl;
    cout << "░▄▀░██████████████████▌▀▄░░░░"<< endl;
    cout << "▀░░░█████▀▀░░░▀███████░░░▀▄░░"<< endl;
    cout << "░░░░▐█▀░░░▐░░░░░▀████▌░░░░▀▄░"<< endl;
    cout << "░░░░░░▌░░░▐░░░░▐░░▀▀█░░░░░░░▀"<< endl;
    cout << "░░░░░░▐░░░░▌░░░▐░░░░░▌░░░░░░░"<< endl;
    set_color(LIGHTBLUE_CODE);
    cout << "░╔╗║░╔═╗░═╦═░░░░░╔╗░░╔═╗░╦═╗░"<< endl;
    cout << "░║║║░║░║░░║░░░░░░╠╩╗░╠═╣░║░║░"<< endl;
    cout << "░║╚╝░╚═╝░░║░░░░░░╚═╝░║░║░╩═╝░"<< endl;
    reset_color();
}

void printTitle2(){
    reset_color();
    set_color(LIGHTBLUE_CODE);
    cout << " ██████╗ ██████╗ ███╗   ██╗███╗   ██╗███████╗ ██████╗████████╗" << endl;
    cout << "██╔════╝██╔═══██╗████╗  ██║████╗  ██║██╔════╝██╔════╝╚══██╔══╝" << endl;
    cout << "██║     ██║   ██║██╔██╗ ██║██╔██╗ ██║█████╗  ██║        ██║" << endl;
    cout << "██║     ██║   ██║██║╚██╗██║██║╚██╗██║██╔══╝  ██║        ██║" << endl;
    cout << "╚██████╗╚██████╔╝██║ ╚████║██║ ╚████║███████╗╚██████╗   ██║" << endl;
    cout << " ╚═════╝ ╚═════╝ ╚═╝  ╚═══╝╚═╝  ╚═══╝╚══════╝ ╚═════╝   ╚═╝" << endl << endl;
    set_color(LIGHTRED_CODE);
    cout << "███████╗ ██████╗ ██╗   ██╗██████╗"<< endl;
    cout << "██╔════╝██╔═══██╗██║   ██║██╔══██╗"<< endl;
    cout << "█████╗  ██║   ██║██║   ██║██████╔╝"<< endl;
    cout << "██╔══╝  ██║   ██║██║   ██║██╔══██╗"<< endl;
    cout << "██║     ╚██████╔╝╚██████╔╝██║  ██║"<< endl;
    cout << "╚═╝      ╚═════╝  ╚═════╝ ╚═╝  ╚═╝"<< endl << endl;
    reset_color();
}
