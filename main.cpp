#include<iostream>
#include<string>
#include "board.h"
#include "connect4.h"

using namespace std;
void print_menu(string diffName);
int getDifficulty(string& diffName);
int getPlayerNum();
void printTitle();

int main() {
    string diffName = "BEST";
    print_menu(diffName);
    char choice;
    int diffLevel = 0, firstToMove = 1;
    while ((cin >> choice) && (choice != '5')) {
        cin.clear();
        switch (choice) {
            case '1': {
                terminalPlayColor();
                break; }
            case '2': {
                int playerNum = getPlayerNum();
                
                if(playerNum == 1) {
                    terminalPlayColorAI1st(diffLevel);
                }
                else {
                    terminalPlayColorAI2nd(diffLevel);
                }
                break; }
            case '3': {
                diffLevel = getDifficulty(diffName);
                break; }
            case '4': {
                color_enabled(true, true);
                break; }
            case '9': {
                AIbattle();
                break;}
            default: {
                set_color(LIGHTMAGENTA_CODE);
                cout << endl << "Invalid Choice: Please actually choose from the menu" << endl;
            
                break; }
        }
        cout << endl;
        print_menu(diffName);
    }
    
    set_color(LIGHTMAGENTA_CODE);
    cout << "Thanks for playing!"<< endl;
    reset_color();
    
    return 0;
}

void print_menu(string diffName) {
    printTitle();
    
    reset_color();
    set_color(LIGHTBLUE_CODE);
    cout << "Menu Options:" << endl;
    set_color(YELLOW_CODE);
    cout << "-----------------------" << endl;
     set_color(LIGHTBLUE_CODE);
    cout << "AI Difficulty: ";
    set_color(LIGHTRED_CODE);
    cout <<  diffName << endl << endl;
    set_color(LIGHTBLUE_CODE);
    
    set_color(YELLOW_CODE);
    cout << "(";
    set_color(LIGHTRED_CODE);
    cout << "1";
    set_color(YELLOW_CODE);
    cout << ")";
    set_color(LIGHTBLUE_CODE);
    cout << " Player vs. Player" << endl;
    
    set_color(YELLOW_CODE);
    cout << "(";
    set_color(LIGHTRED_CODE);
    cout << "2";
    set_color(YELLOW_CODE);
    cout << ")";
    set_color(LIGHTBLUE_CODE);
    cout << " Player vs. AI" << endl;
    
    set_color(YELLOW_CODE);
    cout << "(";
    set_color(LIGHTRED_CODE);
    cout << "3";
    set_color(YELLOW_CODE);
    cout << ")";
    set_color(LIGHTBLUE_CODE);
    cout << " Change AI Difficulty" << endl;
    
    set_color(YELLOW_CODE);
    cout << "(";
    set_color(LIGHTRED_CODE);
    cout << "4";
    set_color(YELLOW_CODE);
    cout << ")";
    set_color(LIGHTBLUE_CODE);
    cout << " Enable Color" << endl;
    set_color(YELLOW_CODE);
    cout << "(";
    set_color(LIGHTRED_CODE);
    cout << "5";
    set_color(YELLOW_CODE);
    cout << ")";
    set_color(LIGHTBLUE_CODE);
    cout << " Quit Game" << endl;
    cout << endl;
    cout << "Choice";
    set_color(LIGHTRED_CODE);
    cout << " --> ";
    set_color(LIGHTBLUE_CODE);
}

int getDifficulty(string& diffName) {
    int choice;
    cout << endl;
    
    reset_color();
    set_color(LIGHTBLUE_CODE);
    cout << "Select AI Difficulty:" << endl;
    set_color(YELLOW_CODE);
    cout << "-----------------------" << endl;
    set_color(LIGHTBLUE_CODE);
    cout << "Current: ";
    set_color(LIGHTRED_CODE);
    cout <<  diffName << endl << endl;
    set_color(LIGHTBLUE_CODE);
    
    set_color(YELLOW_CODE);
    cout << "(";
    set_color(LIGHTRED_CODE);
    cout << "1";
    set_color(YELLOW_CODE);
    cout << ")";
    set_color(LIGHTBLUE_CODE);
    cout << " Self-Esteem Boost" << endl;
    
    set_color(YELLOW_CODE);
    cout << "(";
    set_color(LIGHTRED_CODE);
    cout << "2";
    set_color(YELLOW_CODE);
    cout << ")";
    set_color(LIGHTBLUE_CODE);
    cout << " Easy" << endl;
    
    set_color(YELLOW_CODE);
    cout << "(";
    set_color(LIGHTRED_CODE);
    cout << "3";
    set_color(YELLOW_CODE);
    cout << ")";
    set_color(LIGHTBLUE_CODE);
    cout << " Medium" << endl;
    
    set_color(YELLOW_CODE);
    cout << "(";
    set_color(LIGHTRED_CODE);
    cout << "4";
    set_color(YELLOW_CODE);
    cout << ")";
    set_color(LIGHTBLUE_CODE);
    cout << " Hard" << endl;
    set_color(YELLOW_CODE);
    cout << "(";
    set_color(LIGHTRED_CODE);
    cout << "5";
    set_color(YELLOW_CODE);
    cout << ")";
    set_color(LIGHTBLUE_CODE);
    cout << " Best (Default)" << endl;
    cout << endl;
    
    
    set_color(LIGHTRED_CODE);
    cout << "Choice";
    set_color(LIGHTBLUE_CODE);
    cout << " --> ";
    cin >> choice;
    
    
    
    switch (choice) {
        case 1:
            diffName = "SELF-ESTEEM BOOST";
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
    reset_color();
    return choice;
}

int getPlayerNum(){
    int choice = 1;
    set_color(LIGHTCYAN_CODE);
    cout << endl << "Which player would you like to be? (Enter 1 or 2)" << endl << endl;
    set_color(YELLOW_CODE);
    cout << "(";
    set_color(LIGHTRED_CODE);
    cout << "1";
    set_color(YELLOW_CODE);
    cout << ")";
    set_color(LIGHTRED_CODE);
    cout << " Player 1: ";
    set_color(LIGHTREDBL);
    cout << "X" << endl;
    reset_color();
    
    set_color(YELLOW_CODE);
    cout << "(";
    set_color(LIGHTBLUE_CODE);
    cout << "2";
    set_color(YELLOW_CODE);
    cout << ")";
    set_color(LIGHTBLUE_CODE);
    cout << " Player 2: ";
    set_color(LIGHTBLUEBL);
    cout << "O" << endl << endl;
    reset_color();
    
    set_color(LIGHTRED_CODE);
    cout << "Choice";
    set_color(LIGHTBLUE_CODE);
    cout << " --> ";
    cin >> choice;
    
    
    return choice;
}



void printTitle(){
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
