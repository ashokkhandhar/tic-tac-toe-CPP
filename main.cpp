#include<iostream>
using namespace std;

#define SIDE 3

string name1, name2;

void initialise(char board[][SIDE]){
    int c = '1';
    for(int i = 0; i < SIDE; i++){
        for(int j = 0; j < SIDE; j++){
            board[i][j] = c++;
        }
    }
}
bool rowCrossed(char board[][SIDE]){
    for(int i = 0; i < SIDE; i++){
        if(board[i][0] == board[i][1] and board[i][1] == board[i][2])
            return true;
    }
    return false;
}

bool columCrossed(char board[][SIDE]){
    for(int j = 0; j < SIDE; j++){
        if(board[0][j] == board[1][j] and board[1][j] == board[2][j])
            return true;
    }
    return false;
}

bool diagonalCrossed(char board[][SIDE]){
    if(board[0][0] == board[1][1] and board[1][1] == board[2][2])
        return true;
    if(board[0][2] == board[1][1] and board[1][1] == board[2][0])
        return true; 
    return false;
}

bool gameOver(char board[][SIDE]){
    return rowCrossed(board) or columCrossed(board) or diagonalCrossed(board);
}
void showBoard(char board[][SIDE]){
    cout << endl;
    cout << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
    cout << "---------" << endl;
    cout << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
    cout << "---------" << endl;
    cout << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl;
    cout << endl;
}
void play(string Turn){
    char board[SIDE][SIDE];
    initialise(board);
    showBoard(board);
    int totalEntries = 0;
    while(!gameOver(board) and totalEntries != SIDE*SIDE){
        if(Turn == name1) cout << name1;
        else cout << name2;
        cout << " Enter your Position: ";
        int n;
        cin >> n;
        n--; //one based indexing
        int x, y;
        x = n / SIDE;
        y = n % SIDE;
        if(board[x][y] != 'O' and board[x][y] != 'X'){
            if(n >= 0 and n < 9){
                if(Turn == name1){
                    board[x][y] = 'O';
                    Turn = name2;
                }
                else {
                    board[x][y] = 'X';
                    Turn = name1;
                }
                totalEntries++;
                showBoard(board);
            }
            else cout << "\nInvalid position, Enter position in bitween 1-9\n" << endl;
        }
        else cout << "\nPosition is occupied..!\n" << endl;
    }
    if(!gameOver(board) or totalEntries == SIDE*SIDE)  
        cout << "\nDraw..!\n" << endl;
    else {
        cout << "Winner is: ";
        if(Turn == name1) cout << name2 << endl;
        else cout << name1;
        cout << endl;
    }
}

int main(){
    char c;
    do{
        cout << "\n===== TIC TAC TOE =====" << endl;
        cout << "\nEnter first Player's name: ";
        cin >> name1;
        cout << "\nEnter second player's name: ";
        cin >> name2;
        cout << endl;
        cout << name1 << " have 'O'" << endl;
        cout << name2 << " have 'X'" << endl;
        cout << "\nWho wants to start first?\n:";
        string s; cin >> s;
        play(s);
        cout << "\nWants to play again (y/n): ";
        cin >> c;
    }while(c == 'y');
    return 0;
}