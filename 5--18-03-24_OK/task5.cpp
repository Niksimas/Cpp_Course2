#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class StorekeeperRobot {
private:
    vector<vector<int>> data;
    int n, m, min, start_pos_row, start_pos_col, limit_rotate;
public:
    StorekeeperRobot() {
        ifstream file("../5--18-03-24/input.txt");
        if (file.is_open()) {
            file >> n >> m ;
            if (n>20 || m>20) {
                cout << "Размер склада превышает допустимые нормы!";
            }
            int val;
            for (int i = 0; i < n; i++) {
                data.emplace_back(vector<int>());
                for (int j = 0; j < m; j++) {
                    file >> val;
                    data[i].emplace_back(val);
                    if (val == 2) {
                        start_pos_col = j;
                        start_pos_row = i;
                    }
                }
            }
            file >> limit_rotate;
        }else {
            cout << "Файл не найден!\n";
        }
        file.close();
    }

    void start_search_path() {
        ofstream file("../5--18-03-24_OK/output.txt");
        min = 1000000000;
        if (search_path(start_pos_row, start_pos_col, 0, 0, 0, 0)) {
            file << min;
        }else {
            file << -1;
        }
        file.close();
    }

    int search_path(int row, int col, int k, int change_row, int change_col, int turn_act) {
        if (turn_act > limit_rotate) return 0;
        if (data[row][col] == 3) {
            if (k < min) {min = k;}
            return 1;
        }
        data[row][col] = 4;
        if (row - 1 >= 0) {
            if (data[row - 1][col] != 1 && data[row - 1][col] != 4) {
                if (change_col == -1) {
                    if (search_path(row - 1, col, k + 1, -1, 0, turn_act + 1)) {
                        return 1;
                    }
                }else {
                    if(search_path(row - 1, col, k + 1, -1, 0, turn_act)) {
                        return 1;
                    }
                }
            }
        }
        if (row + 1 < n) {
            if (data[row + 1][col] != 1 && data[row + 1][col] != 4) {
                if (change_col == 1) {
                    if(search_path(row + 1, col, k + 1, 1, 0, turn_act + 1)) {
                        return 1;
                    }
                }else {
                    if (search_path(row + 1, col, k + 1, 1, 0, turn_act)) {
                        return 1;
                    }
                }
            }
        }
        if (col - 1 >= 0) {
            if (data[row][col - 1] != 1 && data[row][col - 1] != 4) {
                if (change_row == 1) {
                    if (search_path(row, col - 1, k + 1, 0, -1, turn_act + 1)) {
                        return 1;
                    }
                }else {
                    if (search_path(row, col - 1, k + 1, 0, -1, turn_act)){
                        return 1;
                    }
                }
            }
        }
        if (col + 1 < m) {
            if (data[row][col + 1] != 1 && data[row][col + 1] != 4) {
                if (change_row == -1) {
                    if(search_path(row, col + 1, k + 1, 0, 1, turn_act + 1)){
                        return 1;
                    }
                }else {
                    if(search_path(row, col + 1, k + 1, 0, 1, turn_act)) {
                        return 1;
                    }
                }
            }
        }
        data[row][col] = 0;
        return 0;
    }
};

int main() {
    StorekeeperRobot robot1;
    robot1.start_search_path();
    return 0;
}
