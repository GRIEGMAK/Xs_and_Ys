#include <iostream>
#include <ctime>
#include <map>
#include <algorithm>
#include <math.h>
#include <fstream>
#include <cstdlib>
#include <string>
#include <clocale>
#include <sstream>

using namespace std;

char board[9] = {};
char computer_char = 'O';
char get_char = 'X';
char empty_char = '-';
int best = 11111111;
int X_win = 0;
int O_win = 0;
int Win_Win = 0;

map <string, int> positions = {
    {"user_value", -100}, 
    {"computer_value", 100},
    {"draw", 0}
};

void checkFile(string file_name) {
    ifstream inf(file_name);
    if (!inf)
    {
        ofstream inf(file_name);
    }
}

void write_file(string file_name) {
    ofstream myfile;
    myfile.open(file_name);
    myfile << X_win << "," << O_win << "," << Win_Win;
    myfile.close();
}

void clearboard() {
    for (int i = 0; i < 9; i++) {
        board[i] = '-';
    }
};

void board_output() {
    cout << endl;
    cout << "-" << board[0] << "-|-" << board[1] << "-|-" << board[2] << "-" << endl;
    cout << "-" << board[3] << "-|-" << board[4] << "-|-" << board[5] << "-" << endl;
    cout << "-" << board[6] << "-|-" << board[7] << "-|-" << board[8] << "-" << endl;
}

void option_output() {
    cout << endl;
    cout << " options: " << endl;
    cout << "-1-|-2-|-3-" << endl;
    cout << "-4-|-5-|-6-" << endl;
    cout << "-7-|-8-|-9-" << endl;
    cout << "\n";
}

bool wins_end(char player) {
    int wins[][3] = { {0,1,2}, {3,4,5}, {6,7,8}, {0,3,6}, {1,4,7}, {2,5,8}, {0,4,8}, {2,4,6} };
    for (int i = 0; i < 8; i++) {
        int count = 0;
        for (int j = 0; j < 3; j++) {
            if (board[wins[i][j]] == player) {
                count++;
            }
        }
        if (count == 3) {
            return true;
        }
    }
    return false;
}

bool check_move(int move) {
    while (move > 9 || move < 1) {
        cout << "\n Enter value 1-9" << endl;
        return false;
    }
    while (board[move - 1] == get_char || board[move - 1] == computer_char) {
        cout << "\n Enter free value" << endl;
        return false;
    }
    return true;
};

int get_move() {
    int move;
    cin >> move;
    while(!check_move(move)){
        cin >> move;
    }
    return move;
};

int minimax(int depth, bool is_max ) {
    int best_position;
    if (wins_end(computer_char)) {
        return positions["computer_value"];
    } else if(wins_end(get_char)) {
        return positions["user_value"];
    }
    else {
        return positions["draw"];
    };
    if (is_max) {
        best_position = -1 * best;
        int position;
        for (int i = 0; i < 9; i++) {
            if (board[i] == empty_char) {
                board[i] = computer_char;
                position = minimax(depth + 1, false);
                board[i] = empty_char;
                best_position = max(best_position, position);
            }
        }
    } else {
        best_position = best;
        int position;
        for (int i = 0; i < 9; i++) {
            if (board[i] == empty_char) {
                board[i] = get_char;
                position = minimax(depth + 1, true);
                board[i] = empty_char;
                best_position = min(best_position, position);
            }
        }
    }
    return best;
}

int get_computer_move() {
    int move = 0;
    int best_position = -1*best;
    int position = 0;
    for (int i = 0; i < 9; i++) {
        if (board[i] == empty_char) {
            cout << board[i]<< "Ste1" << endl;
            board[i] = computer_char;
            position = minimax(0, false);
            board[i] = empty_char;
            if (position > best_position) {
                best_position = position;
                move = i + 1;
            }
        }
    }
    cout << "comp vidal: " << move << endl;
    return move;
}

int get_compute_move() {
    int move;
    srand(time(NULL));
    move = rand() % 10;
    while (!check_move(move)) {
        move = rand() % 10;
    }
    return move;
}

char playerwin() {
    int step = 0;
    while (!wins_end(computer_char) && !wins_end(get_char)) {
        system("cls");
        cout << "Step " << step << endl;
        int move;
        if (step % 2 == 0) {
            option_output();
            board_output();
            move = get_move();
            board[move - 1] = get_char;
            if (wins_end(get_char)) {
                system("cls");
                board_output();
                cout << "Player "<< get_char << " win" << endl;
                X_win++;
                system("pause");
                return 0;
            }
        }
        else {
            option_output();
            board_output();
            move = get_computer_move();
            board[move - 1] = computer_char;
            if (wins_end(computer_char)) {
                system("cls");
                board_output();
                cout << "Player " << computer_char << " win" << endl;
                O_win++;
                system("pause");
                return 0;
            }
        }
        step++;
        if (step >= 9) {
            system("cls");
            board_output();
            cout << "Win - win";
            Win_Win++;
            system("pause");
            return 0;
        }
    };
}

int game_process() {
    clearboard();
    playerwin();
    board_output();
    return 0;
}

int main() {
    string data;
    data = "data.csv";
    write_file(data);
    while (true) {
        game_process();
        write_file(data);
    }
    return 0;
};
