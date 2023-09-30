#include<iostream>
#include<climits>
using namespace std;

#define SIDE 3
#define COMPUTER 0
#define HUMAN 1

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
    system("cls");
    cout << "========= TIC TAC TOE =========\n" << endl;
    cout << "\t-------------" << endl;
    cout << "\t| " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << " |" << endl;
    cout << "\t-------------" << endl;
    cout << "\t| " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << " |" << endl;
    cout << "\t-------------" << endl;
    cout << "\t| " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << " |" << endl;
    cout << "\t-------------" << endl;
    cout << endl;
}
void play(){
    string name1, name2;
    cout << "\nEnter first Player's name: ";
    cin >> name1;
    cout << "\nEnter second player's name: ";
    cin >> name2;
    cout << endl;
    cout << name1 << " have 'O'" << endl;
    cout << name2 << " have 'X'" << endl;
    cout << "\nWho wants to start first?\n:";
    string turn; cin >> turn;
    char board[SIDE][SIDE];
    initialise(board);
    showBoard(board);
    int totalEntries = 0;
    while(!gameOver(board) and totalEntries != SIDE*SIDE){
        if(turn == name1) cout << name1;
        else cout << name2;
        cout << " enter your position: ";
        int n;
        cin >> n;
        n--; //one based indexing
        int x, y;
        x = n / SIDE;
        y = n % SIDE;
        if(board[x][y] != 'O' and board[x][y] != 'X'){
            if(n >= 0 and n < 9){
                if(turn == name1){
                    board[x][y] = 'O';
                    turn = name2;
                }
                else {
                    board[x][y] = 'X';
                    turn = name1;
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
        if(turn == name1) cout << name2 << endl;
        else cout << name1;
        cout << endl;
    }
}
int minimax(char board[][SIDE], int depth, bool isAI){
    int score = 0, bestscore = 0;
    if(gameOver(board)){
        if(isAI) return -10;
        return 10;
    }
    else{
        if(depth < 9){
            if(isAI){
                bestscore = -999;
                for(int i = 0; i < SIDE; i++){
                    for(int j = 0; j < SIDE; j++){
                        if(board[i][j] != 'O' and board[i][j] != 'X'){
                            char temp = board[i][j];
                            board[i][j] = 'O';
                            score = minimax(board, depth+1, false); 
                            board[i][j] = temp;
                            if(score > bestscore) bestscore = score;
                        }
                    }
                }
                return bestscore;
            }
            else {
                bestscore = 999;
                for(int i = 0; i < SIDE; i++){
                    for(int j = 0; j < SIDE; j++){
                        if(board[i][j] != 'O' and board[i][j] != 'X'){
                            char temp = board[i][j];
                            board[i][j] = 'O';
                            score = minimax(board, depth+1, true); 
                            board[i][j] = temp;
                            if(score < bestscore) bestscore = score;
                        }
                    }
                }
                return bestscore;
            }
        }
        else return 0;
    }
}
int bestMove(char board[][SIDE], int totalEntries){
    int x = -1, y = -1;
    int score = 0, bestscore = INT_MIN;
    for(int i = 0; i < SIDE; i++){
        for(int j = 0; j < SIDE; j++){
            if(board[i][j] != 'O' and board[i][j] != 'X'){
                char temp = board[i][j];
                board[i][j] = 'O';
                score = minimax(board, totalEntries+1, false); 
                // if score == -10 then human won, 0 then tie, 10 then computer won
                board[i][j] = temp;
                if(score > bestscore){
                    bestscore = score;
                    x = i;
                    y = j;
                }
            }
        }
    }
    return x*3 + y;
}
void play(int turn){
    char board[SIDE][SIDE];
    initialise(board);
    showBoard(board);
    int totalEntries = 0;
    while(!gameOver(board) and totalEntries != SIDE*SIDE){
        int n;
        if(turn == COMPUTER){
            n = bestMove(board, totalEntries);
        }
        else{
            cout << "Enter your position: ";
            cin >> n;
            n--; //one based indexing
        }
        int x, y;
        x = n / SIDE;
        y = n % SIDE;
        if(board[x][y] != 'O' and board[x][y] != 'X'){
            if(n >= 0 and n < 9){
                if(turn == COMPUTER){
                    board[x][y] = 'O';
                    turn = HUMAN;
                }
                else {
                    board[x][y] = 'X';
                    turn = COMPUTER;
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
        if(turn == COMPUTER) cout << "You won." << endl;
        else cout << "Computer won." << endl;
    }
}
int main(){
    char c;
    do{
        system("cls");
        cout << "\n===== TIC TAC TOE =====" << endl;
        cout << "\n1. Play with Computer" << endl;
        cout << "2. Play with Friend" << endl;
        cout << "\nEnter your choice: ";
        int choice; cin >> choice;
        if(choice == 1) {
            cout << "Do you want to start first? (y/n): ";
            char ch; cin >> ch;
            if(ch == 'y') play(HUMAN);
            else play(COMPUTER);
        }
        else if(choice == 2){
            play();
        }
        else break;
        cout << "\nPlay again (y/n): ";
        cin >> c;
    }while(c == 'y');
    return 0;
}