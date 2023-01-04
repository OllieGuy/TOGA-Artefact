#pragma once
#include <iostream>
#include <conio.h>
#include <vector>
#include "Navigation.h"
#include "Grid.h"
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
using namespace std;

class Player
{
private:
	int currentXPos;
	int currentYPos;
	Navigation nav;
	int coinTotal;
	int desiredCoins;
public:
	Player(Navigation navPass);
	int getPlayerX();
	int getPlayerY();
	void movementKey(int keyPress);
	void movePlayer(int dir);
	void coinAdd();
	void setDesiredCoins(int desired);
	void play();
};

