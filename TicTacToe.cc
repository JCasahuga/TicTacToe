#include <iostream>
#include <vector>
using namespace std;

//Current Turn and Table Global Variables
int turn = 1;
int table[9] = {};

//Move Properties: Position and Value of the Move
class Move {
public:
    int id;
    int score;
};

//Checks Board State
int checkState(int cTable[]) {
    //Horizontal Win/Lose?
    for(int i = 0; i < 7; i+=3) {
        if(cTable[i] == cTable[i+1] && cTable[i+1] == cTable[i+2] && cTable[i] != 0) {
            return cTable[i];
        }
    }
    //Vertical Win/Lose?
    for(int i = 0; i < 3; i++) {
        if(cTable[i] == cTable[i+3] && cTable[i+3] == cTable[i+6] && cTable[i] != 0) {
            return cTable[i];
        }
    }
    //Diagonal Win/Lose?
    if(cTable[0] == cTable[4] && cTable[4] == cTable[8] && cTable[0] != 0) {
            return cTable[0];
    } else if (cTable[2] == cTable[4] && cTable[4] == cTable[6] && cTable[2] != 0) {
            return cTable[2];
    }
    //Continue?
    for(int i = 0; i < 9; i++){
        if(cTable[i] == 0) {
            return 2;
        }
    }
    //Tie
    return 0;
}

//Minimax
Move minimax(int cTurn, int cTable[]) {
    //Checks Current State
    int s = checkState(cTable);
    if(s != 2) {
        Move move;
        if (s == 1) move.score = 1;
        else if (s == -1) move.score = -1;
        else move.score = 0;
        return move;
    }
    //Moves Vector
    vector<Move> moves;
    //Possible Moves
    for(int i = 0; i < 9; i++) {
        if(cTable[i] == 0) {
            Move move = Move();
            move.id = i;
            cTable[i] = cTurn;
            move.score = minimax(-1 * cTurn, cTable).score;
            moves.push_back(move);
            cTable[i] = 0;
            if(move.score == cTurn) return move;
        }
    }
    //Minimize and Maximizes Score
    int bMove = 0;
    if(cTurn == 1){
        int bScore = -10;
        for(int i = 0; i < moves.size(); i++){
            if (moves[i].score > bScore) {
                bMove = i;
                bScore = moves[i].score;
            }
        }
    } else {
        int bScore = 10;
        for(int i = 0; i < moves.size(); i++){
            if (moves[i].score < bScore) {
                bMove = i;
                bScore = moves[i].score;
            }
        }
    }
    return moves[bMove];
}

//Displays Board
void displayGame(int t[]) {
    char tD[9] = {};
    for(int i = 0; i < 9; i++){
        if(t[i] == 0) tD[i] = '-';
        else if(t[i] == 1) tD[i] = 'O';
        else tD[i] = 'X';
    }
    cout << tD[0] << " | " << tD[1] << " | " << tD[2] << endl;
    cout << tD[3] << " | " << tD[4] << " | " << tD[5] << endl;
    cout << tD[6] << " | " << tD[7] << " | " << tD[8] << endl;
}

//Keeps Track of Turns and Plays
void game() {
    bool allEmpty = true;
    for(int i = 0; i < 9; i++) {
        if(table[i] != 0) allEmpty = false; 
    }
    //Checks Current State
    int s = checkState(table);
    if(s != 2){
        if (s == 1) cout << "You LOST!" << endl;
        else if (s == -1) cout << "You WON!" << endl;
        else cout << "TIE!" << endl;
        return;
    }
    //Turn 1 = CPU / Turn -1 = Human
    if(turn == 1){
        cout << "CPU PLAY:" << endl;
        table[minimax(turn, table).id] = 1;
        cout << it << endl;
        displayGame(table);
        turn = -1;
        game();
    } else {
        if(allEmpty) { 
            cout << "YOUR TURN:" << endl;
            displayGame(table);
        }
        int m;
        cin >> m;
        if (m > 9 || m < 0 || table[m] != 0){
            game();
            return;
        }
        table[m] = -1;
        turn = 1;
        game();
    }
}

//Main
int main() {
    cout << "Do you want yo start? Type Y to comnfirm or N to deny" << endl;
    char i;
    cin >> i;
    if (i == 'Y' || i == 'y') turn = -1;
    game();
}
