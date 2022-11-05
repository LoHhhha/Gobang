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
        //���������㷨
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
        int personNum; // ��������ӵĸ���
        int botNum; // AI�����ӵĸ���
        int emptyNum; // ������հ�λ�ĸ���

        score.clear();
        score.resize(Map_Size, vector<int>(Map_Size, 0));

        for (int row = 0; row < Map_Size; row++) {
            for (int col = 0; col < Map_Size; col++) {
                // ��������հ׵�
                if (Map[row][col] == 0) {
                    // �˸�����
                    for(auto next:dir) {
                        int x = next[0], y = next[1];
                        // ����
                        personNum = 0;
                        botNum = 0;
                        emptyNum = 0;

                        // ����
                        // ��б��
                        for (int i = 1; i <= 4; i++) {
                            // other
                            if (row + i * y >= 0 && row + i * y < Map_Size &&
                                col + i * x >= 0 && col + i * x < Map_Size &&
                                Map[row + i * y][col + i * x] == other) personNum++;
                            // �հ�λ
                            else if (row + i * y >= 0 && row + i * y < Map_Size &&
                                col + i * x >= 0 && col + i * x < Map_Size &&
                                Map[row + i * y][col + i * x] == 0) {
                                emptyNum++;
                                break;//�Ѿ����� �����˳�
                            }
                            // ���߽�
                            else break;
                        }
                        // ��б��
                        for (int i = 1; i <= 4; i++){
                            // other
                            if (row - i * y >= 0 && row - i * y < Map_Size &&
                                col - i * x >= 0 && col - i * x < Map_Size &&
                                Map[row - i * y][col - i * x] == other) {
                                personNum++;
                            }
                            // �հ�λ
                            else if (row - i * y >= 0 && row - i * y < Map_Size &&
                                col - i * x >= 0 && col - i * x < Map_Size &&
                                Map[row - i * y][col - i * x] == 0) {
                                emptyNum++;
                                break;//�Ѿ����� �����˳�
                            }
                            // ���߽�
                            else break;           
                        }

                        //���ȷ���
                        if (personNum == 1) score[row][col] += 10;
                        else if (personNum == 2){
                            if (emptyNum == 1) score[row][col] += 30;//ֻ��һ��
                            else if (emptyNum == 2) score[row][col] += 40;//���˶���
                        }
                        else if (personNum == 3){
                            if (emptyNum == 1) score[row][col] += 60;
                            else if (emptyNum == 2) score[row][col] += 1200;
                        }
                        else if (personNum == 4) score[row][col] += 10100;//���Ҫ����

                        // ����һ�����
                        emptyNum = 0;

                        // ����
                        // ��б��
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
                        // ��б��
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

                        //����
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