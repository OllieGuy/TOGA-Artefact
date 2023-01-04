#pragma once
#include <iostream>
#include <stack>
#include <random>
#include <algorithm>
#include <vector>
#include <time.h>
#include <chrono>
#include <thread>
#include <conio.h>
#include "Node.h"

class Grid
{
private:
    vector<vector<Node>> generatedGrid;
    vector<vector<bool>> compiledGrid;
    vector<vector<int>> otherInfoGrid;
protected:
    int sizeX;
    int sizeY;
    bool checkInsideGrid(int x, int y);
    bool checkInsideCompiledGrid(int x, int y);
public:
    Grid();
    int getX();
    int getY();
    void setSize(int size);
    void generateGrid(Node current, int seedChanger);
    void compileGrid();
    void pepperGrid(int amount);
    void createOtherObjects(int amount, bool randEnd);
    vector<vector<bool>> returnGrid();
    vector<vector<int>> returnOtherInfoGrid();
};