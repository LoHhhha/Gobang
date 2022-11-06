#pragma once
#include<vector>
#include<stdlib.h>
#include<string>

using namespace std;

class AI {
public:
    int Map_Size, self, other;
	vector<vector<int>>score;
    int dir[8][2] = { {-1,0},{0,-1},{0,1},{1,0},{-1,1},{1,-1},{-1,-1},{1,1} };

    AI(int Map_Size, int self, int other) {
		this->Map_Size = Map_Size;
        this->self = self;
        this->other = other;
	}

	string action(vector<vector<int8_t>>& Map) {
        calculate_score(Map);
        //水塘抽样算法
        srand((unsigned int)time(NULL));
        int maxscore = INT_MIN, ret_row = 0, ret_col = 0, max_num = 0;
        for (int row = 0; row < Map_Size; row++) {
            for (int col = 0; col < Map_Size; col++) {
                if(score[row][col]>maxscore){
                    maxscore = score[row][col];
                    ret_row = row, ret_col = col;
                    max_num=1;
                }
                else if (score[row][col] == maxscore) {
                    max_num++;
                    if (rand() % max_num == 0) {
                        ret_row = row, ret_col = col;
                    }
                }
            }
        }
        return (char)(ret_col + 'A') + to_string(ret_row + 1);
	}

    void calculate_score(vector<vector<int8_t>>&Map) {
        int personNum; // 玩家连成子的个数
        int botNum; // AI连成子的个数
        int emptyNum; // 各方向空白位的个数

        score.clear();
        score.resize(Map_Size, vector<int>(Map_Size, 0));

        for (int row = 0; row < Map_Size; row++) {
            for (int col = 0; col < Map_Size; col++) {
                // 仅仅计算空白点
                if (Map[row][col] == 0) {
                    // 八个方向
                    for(auto next:dir) {
                        int x = next[0], y = next[1];
                        // 重置
                        personNum = 0;
                        botNum = 0;
                        emptyNum = 0;

                        // 防御
                        // 正斜线
                        for (int i = 1; i <= 4; i++) {
                            // other
                            if (row + i * y >= 0 && row + i * y < Map_Size &&
                                col + i * x >= 0 && col + i * x < Map_Size &&
                                Map[row + i * y][col + i * x] == other) personNum++;
                            // 空白位
                            else if (row + i * y >= 0 && row + i * y < Map_Size &&
                                col + i * x >= 0 && col + i * x < Map_Size &&
                                Map[row + i * y][col + i * x] == 0) {
                                emptyNum++;
                                break;//已经断了 可以退出
                            }
                            // 出边界
                            else break;
                        }
                        // 负斜线
                        for (int i = 1; i <= 4; i++){
                            // other
                            if (row - i * y >= 0 && row - i * y < Map_Size &&
                                col - i * x >= 0 && col - i * x < Map_Size &&
                                Map[row - i * y][col - i * x] == other) {
                                personNum++;
                            }
                            // 空白位
                            else if (row - i * y >= 0 && row - i * y < Map_Size &&
                                col - i * x >= 0 && col - i * x < Map_Size &&
                                Map[row - i * y][col - i * x] == 0) {
                                emptyNum++;
                                break;//已经断了 可以退出
                            }
                            // 出边界
                            else break;           
                        }

                        //优先防御
                        if (personNum == 1) score[row][col] += 10;
                        else if (personNum == 2){
                            if (emptyNum == 1) score[row][col] += 30;//只有一端
                            else if (emptyNum == 2) score[row][col] += 40;//两端都有
                        }
                        else if (personNum == 3){
                            if (emptyNum == 1) score[row][col] += 60;
                            else if (emptyNum == 2) score[row][col] += 1200;
                        }
                        else if (personNum == 4) score[row][col] += 10100;//务必要拦截

                        // 进行一次清空
                        emptyNum = 0;

                        // 进攻
                        // 正斜线
                        for (int i = 1; i <= 4; i++){
                            if (row + i * y >= 0 && row + i * y < Map_Size &&
                                col + i * x >= 0 && col + i * x < Map_Size &&
                                Map[row + i * y][col + i * x] == self) botNum++;
                            else if (row + i * y >= 0 && row + i * y < Map_Size &&
                                col + i * x >= 0 && col + i * x < Map_Size &&
                                Map[row + i * y][col + i * x] == 0){
                                emptyNum++;
                                break;
                            }
                            else break;
                                
                        }
                        // 负斜线
                        for (int i = 1; i <= 4; i++)
                        {
                            if (row - i * y >= 0 && row - i * y < Map_Size &&
                                col - i * x >= 0 && col - i * x < Map_Size &&
                                Map[row - i * y][col - i * x] == self) botNum++;
                            else if (row - i * y >= 0 && row - i * y < Map_Size &&
                                col - i * x >= 0 && col - i * x < Map_Size &&
                                Map[row - i * y][col - i * x] == 0) {
                                emptyNum++;
                                break;
                            }
                            else break;
                        }

                        //进攻
                        if (botNum == 0) score[row][col] += 5;
                        else if (botNum == 1) score[row][col] += 10;
                        else if (botNum == 2){
                            if (emptyNum == 1) score[row][col] += 25;
                            else if (emptyNum == 2) score[row][col] += 50;
                        }
                        else if (botNum == 3){
                            if (emptyNum == 1) score[row][col] += 55;
                            else if (emptyNum == 2) score[row][col] += 1100;
                        }
                        else if (botNum >= 4) score[row][col] += 10000;
                    }
                }
            }
        }
    }
};
