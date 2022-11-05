#pragma once
#include <windows.h>
#include"gobang.h"
#include"AI.h"
using namespace std;

class game {
public:
    int Map_Size;

    game(int Map_Size) {
        this->Map_Size = Map_Size;
    }

	void gamemode_0() {
        /*PvP*/
        gobang go(Map_Size);
        while (1) {
            go.Redisplay();
            string input;
            cout << "Player0->";
            cin >> input;
            while (!go.SetMap(input, 1)) {
                cout << "(*)Player0->";
                cin >> input;
            }
            system("cls");
            int winner = go.Check();
            if (winner) {
                if (winner == -1) {
                    go.Redisplay();
                    cout << endl;
                    cout << "All of you are Winner!" << endl;
                    cout << endl;
                    break;
                }
                else {
                    go.Redisplay();
                    cout << endl;
                    cout << "Winner : " << (winner == 1 ? "Player0" : "Player1") << endl;
                    cout << endl;
                    break;
                }
            }
            go.Redisplay();
            cout << "Player1->";
            cin >> input;
            while (!go.SetMap(input, 2)) {
                cout << "(*)Player1->";
                cin >> input;
            }
            system("cls");
            winner = go.Check();
            if (winner) {
                if (winner == -1) {
                    go.Redisplay();
                    cout << endl;
                    cout << "All of you are Winner!" << endl;
                    cout << endl;
                    break;
                }
                else {
                    go.Redisplay();
                    cout << endl;
                    cout << "Winner : " << (winner == 1 ? "Player0" : "Player1") << endl;
                    cout << endl;
                    break;
                }
            }
        }
	}

    void gamemode_1() {
        /*PvE*/
        AI ai(Map_Size,2,1);
        gobang go(Map_Size);
        while (1) {
            go.Redisplay();
            string input;
            cout << "You->";
            cin >> input;
            while (!go.SetMap(input, 1)) {
                cout << "(*)You->";
                cin >> input;
            }
            system("cls");
            int winner = go.Check();
            if (winner) {
                if (winner == -1) {
                    go.Redisplay();
                    cout << endl;
                    cout << "All of you are Winner!" << endl;
                    cout << endl;
                    break;
                }
                else {
                    go.Redisplay();
                    cout << endl;
                    cout << "Winner : " << (winner == 1 ? "You" : "AI") << endl;
                    cout << endl;
                    break;
                }
            }
            go.Redisplay();
            cout << "AI->";
            input = ai.action(go.Map);
            cout << input << endl;
            Sleep(500);
            system("cls");
            if (!go.SetMap(input, 2)) {
                cout << "Error!" << endl;
                return;
            }
            winner = go.Check();
            if (winner) {
                if (winner == -1) {
                    go.Redisplay();
                    cout << endl;
                    cout << "All of you are Winner!" << endl;
                    cout << endl;
                    break;
                }
                else {
                    go.Redisplay();
                    cout << endl;
                    cout << "Winner : " << (winner == 1 ? "You" : "AI") << endl;
                    cout << endl;
                    break;
                }
            }
        }
    }

    void gamemode_2() {
        /*EvE*/
        AI ai0(Map_Size, 1, 2);
        AI ai1(Map_Size, 2, 1);
        gobang go(Map_Size);
        string input;
        while (1) {
            go.Redisplay();
            cout << "AI_O->";
            input = ai0.action(go.Map);
            cout << input << endl;
            Sleep(200);
            system("cls");
            if (!go.SetMap(input, 1)) {
                cout << "Error!" << endl;
                return;
            }
            system("cls");
            int winner = go.Check();
            if (winner) {
                if (winner == -1) {
                    go.Redisplay();
                    cout << endl;
                    cout << "All of you are Winner!" << endl;
                    cout << endl;
                    break;
                }
                else {
                    go.Redisplay();
                    cout << endl;
                    cout << "Winner : " << (winner == 1 ? "AI_O" : "AI_X") << endl;
                    cout << endl;
                    break;
                }
            }
            go.Redisplay();
            cout << "AI_X->";
            input = ai1.action(go.Map);
            cout << input << endl;
            Sleep(200);
            system("cls");
            if (!go.SetMap(input, 2)) {
                cout << "Error!" << endl;
                return;
            }
            winner = go.Check();
            if (winner) {
                if (winner == -1) {
                    go.Redisplay();
                    cout << endl;
                    cout << "All of you are Winner!" << endl;
                    cout << endl;
                    break;
                }
                else {
                    go.Redisplay();
                    cout << endl;
                    cout << "Winner : " << (winner == 1 ? "AI_O" : "AI_X") << endl;
                    cout << endl;
                    break;
                }
            }
        }
    }
};