#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

bool win_game_row(char arr[3][3]){
    for(int i = 0; i < 3; i++){
        bool res = true;
        char same = arr[i][0];

        if(same == '-') {
            continue;
        }
        for(int j = 1; j < 3; j++){
            if (arr[i][j] != same){
                res = false;
                break;
            }
        }
        if(res == true){
            return res;
        }
    }
    return false;
}

bool win_game_col(char arr[3][3]){
    for(int i = 0; i < 3; i++){
        bool res = true;
        char same = arr[0][i];
            
        if (same == '-'){
            continue;
        }

        for(int j = 1; j < 3; j++){
            if (arr[j][i] != same){
                res = false;
                break;
            }
        }
        if(res == true){
            return res;
        }
    }
    return false;
}

bool win_game_diag(char arr[3][3]){
    char same = arr[0][0];
    if(same == '-'){
        return false;
    }
    for(int i = 1; i < 3; i++){
        if (arr[i][i] != same){
            return false;
        }
    }
    return true;
}

bool win_game_diag2(char arr[3][3]){
    char same = arr[0][2];
    if(same == '-'){
        return false;
    }
    for(int i = 1; i < 3; i++){
        if(arr[i][2-i] != same){
            return false;
        }
    }
    return true;
}

void display(char arr[3][3]){
    cout << "\n";
    cout << arr[0][0] << " | " << arr[0][1] << " | " << arr[0][2] << endl;
    cout << "---------" << endl;
    cout << arr[1][0] << " | " << arr[1][1] << " | " << arr[1][2] << endl;
    cout << "---------" << endl;
    cout << arr[2][0] << " | " << arr[2][1] << " | " << arr[2][2] << endl;
}

bool completelyFilled(char arr[3][3]) {
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if (arr[i][j] == '-'){
                return false;
            }
        }
    }
    return true;
}

void change(char arr[3][3], int row, int col, int turn){
    if(turn == 0){
        arr[row][col] = 'O';
    }
    else{
        arr[row][col] = 'X';
    }
}

bool check_win(char arr[3][3]) {
    return win_game_row(arr) || win_game_col(arr) || win_game_diag(arr) || win_game_diag2(arr);
}

void cpuMove(char arr[3][3]) {
    int row, col;
    do {
        row = rand() % 3;
        col = rand() % 3;
    } while (arr[row][col] != '-');
    arr[row][col] = 'X';
    cout << "CPU chose row " << row << " and column " << col << ".\n";
}

int main() {
    srand(time(0)); // Seed random number generator

    char board[3][3] = { {'-', '-', '-'},
                         {'-', '-', '-'},
                         {'-', '-', '-'} };
    
    int turn = 0; // 0 for Player, 1 for CPU
    int row, col;
    
    while(true) {
        display(board);
        
        if(turn == 0) {
            cout << "Your turn (O)." << endl;
            cout << "Enter row and column (0-2): ";
            cin >> row >> col;
            
            if(row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != '-') {
                cout << "Invalid move. Try again." << endl;
                continue;
            }

            change(board, row, col, turn);
        } else {
            cpuMove(board);
        }
        
        if(check_win(board)) {
            display(board);
            cout << (turn == 0 ? "You win!" : "CPU wins!") << endl;
            break;
        }

        if(completelyFilled(board)) {
            display(board);
            cout << "It's a draw!" << endl;
            break;
        }

        turn = 1 - turn; // Toggle turn between player and CPU
    }
    
    return 0;
}
