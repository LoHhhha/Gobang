#include <iostream>
#include <vector>
#include"gobang.h"
#include"game.h"
using namespace std;

#define Map_Size 15

int menu() {
	system("cls");
	cout << "Gobang" << endl;
	cout << "1.Player0 Vs Player1" << endl;
	cout << "2.Player Vs AI" << endl;
	cout << "3.AI_O Vs AI_X" << endl;
	cout << "0.Exit" << endl;
	int type = -1;
	do {
		cout << "You->";
		cin >> type;
	} while (type < 0 && type>2);
	game g(Map_Size);
	system("cls");
	switch (type) {
	case 1:
		g.gamemode_0();
		break;
	case 2:
		g.gamemode_1();
		break;
	case 3:
		g.gamemode_2();
		break;
	case 0:
		return 0;
	}
	system("pause");
	return 1;
}

int main(){
	while (menu());
	cout << "Have a good day!" << endl;
}
