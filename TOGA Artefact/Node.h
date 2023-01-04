#pragma once
#include <iostream>
#include <stack>
#include <random>
#include <algorithm>
#include <vector>
#include <time.h>
#include <chrono>
#include <thread>
using namespace std;

class Node
{
    private:
        int x;
        int y;
        bool walls[4] = { true, true, true, true }; // UP RIGHT DOWN LEFT
        bool visited = false;
    public:
        Node(int xIn, int yIn);
        Node();
        void setWalls(int wallToRemove);
        bool getWalls(int check);
        int getX();
        int getY();
        void setVisited();
        bool getVisited();
};