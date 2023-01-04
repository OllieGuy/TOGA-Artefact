#pragma once
#include <iostream>
#include <stack>
#include <random>
#include <algorithm>
#include <vector>
#include <time.h>
#include <chrono>
#include <thread>
#include "Grid.h"

class Navigation : public Grid
{
private:
    vector<vector<bool>>navigableGrid;
    vector<vector<int>>otherInfoGrid;
public:
    Navigation();
    Navigation(vector<vector<bool>>passedGrid, vector<vector<int>>passedOtherInfoGrid);
    bool positionAvailable(int curX, int curY, int dir);
    int pointReached(int curX, int curY);
    void display(int playerPosX, int playerPosY, bool endUnlocked);
};

