#pragma once
#include<vector>

using namespace std;

class gobang {
public:
    //NULL 0  O 1  X 2  END -1
    vector<vector<int8_t>>Map;
    int Map_Size;

    gobang(int Map_Size) {
        this->Map_Size = Map_Size;
        Map.resize(Map_Size, vector<int8_t>(Map_Size, 0));
    }

    int8_t Check() {
        //O(n^2)查找符合的点
        //动态规划也优不了多少
        /*NoWinner 0 O 1 X 2 END -1*/
        bool empty_space = 0;
        for (int i = 0; i < Map_Size; i++) {
            for (int j = 0; j < Map_Size; j++) {
                if (Map[i][j]) {
                    //横向检测
                    if (j >= 2 && j + 2 < Map_Size && Map[i][j - 1] == Map[i][j] && Map[i][j - 2] == Map[i][j - 1] && Map[i][j + 1] == Map[i][j] && Map[i][j + 2] == Map[i][j + 1]) {
                        int8_t ret = Map[i][j];
                        Map[i][j] = Map[i][j - 1] = Map[i][j - 2] = Map[i][j + 1] = Map[i][j + 2] = -1;
                        return ret;
                    }
                    //纵向检测
                    if (i >= 2 && i + 2 < Map_Size && Map[i - 1][j] == Map[i][j] && Map[i - 2][j] == Map[i - 1][j] && Map[i + 1][j] == Map[i][j] && Map[i + 2][j] == Map[i + 1][j]) {
                        int8_t ret = Map[i][j];
                        Map[i][j] = Map[i - 1][j] = Map[i - 2][j] = Map[i + 1][j] = Map[i + 2][j] = -1;
                        return ret;
                    }
                    //45°斜线检测
                    if (i >= 2 && j >= 2 && i < Map_Size - 2 && j < Map_Size - 2) {
                        if (Map[i][j] == Map[i - 1][j - 1] && Map[i - 2][j - 2] == Map[i - 1][j - 1] && Map[i][j] == Map[i + 1][j + 1] && Map[i + 1][j + 1] == Map[i + 2][j + 2]) {
                            int8_t ret = Map[i][j];
                            Map[i][j] = Map[i - 1][j - 1] = Map[i - 2][j - 2] = Map[i + 1][j + 1] = Map[i + 2][j + 2] = -1;
                            return ret;
                        }
                        if (Map[i][j] == Map[i + 1][j - 1] && Map[i + 2][j - 2] == Map[i + 1][j - 1] && Map[i][j] == Map[i - 1][j + 1] && Map[i - 1][j + 1] == Map[i - 2][j + 2]) {
                            int8_t ret = Map[i][j];
                            Map[i][j] = Map[i + 1][j - 1] = Map[i + 2][j - 2] = Map[i - 1][j + 1] = Map[i - 2][j + 2] = -1;
                            return ret;
                        }
                    }
                }
                else empty_space = 1;
            }
        }
        if (!empty_space)return -1;
        return 0;
    }

    void Redisplay() {
        int row_index = 1;
        for (auto& row : Map) {
            cout << '|';
            for (auto& elem : row) {
                if (elem == 0)cout << ' ' << '|';
                else if (elem == 1)cout << 'O' << '|';
                else if (elem == 2)cout << 'X' << '|';
                else if (elem == -1)cout << '/' << '|';
                else cout << 'E' << '|';
            }
            cout << row_index++ << endl;
        }
        char col_index = 'A';
        cout << ' ';
        for (int i = 0; i < Map_Size; i++) {
            cout << col_index++ << ' ';
        }
        cout << endl;
    }

    bool SetMap(string& index, int which) {
        if (which != 1 && which != 2)return false;
        int c = index[0] - 'A';
        if (c < 0 || c >= Map_Size)return false;
        int r = 0;
        for (int i = 1; i < index.size(); i++) {
            r *= 10;
            r += index[i] - '0';
        }
        r--;
        if (r < 0 || r >= Map_Size)return false;
        if (Map[r][c] != 0)return false;
        Map[r][c] = which;
        return true;
    }
};