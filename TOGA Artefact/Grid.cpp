#include "Grid.h"

Grid::Grid()
{
    sizeX = 5; //the default size is set up, but will be changed later - this is just a failsafe
    sizeY = 5; //even though the grid is always square, the Y size is still set up so the feature to change both X and Y could be added
    generatedGrid.resize(sizeX); //vector problems being dealt with
    for (int i = 0; i < generatedGrid.size(); i++)
    {
        generatedGrid[i].resize(sizeY);
    }
}
int Grid::getX() //accesses x value
{
    return sizeX;
}
int Grid::getY() //accesses y value
{
    return sizeY;
}
void Grid::setSize(int size) //replace size with whatever the size from the options is
{
    sizeX = size;
    sizeY = size;
    generatedGrid.resize(sizeX); //vector BS
    for (int i = 0; i < generatedGrid.size(); i++)
    {
        generatedGrid[i].resize(sizeY);
    }
}
bool Grid::checkInsideGrid(int x, int y) //checks if the specified x and y positions are in the bounds of the maze
{
    if (x < sizeX && x >= 0 && y < sizeY && y >= 0)
    {
        return true;
    }
    return false; //defaults to not being within the maze
}
bool Grid::checkInsideCompiledGrid(int x, int y) //checks if the specified x and y positions are in the bounds of the compiled grid that is displayed to the user
{
    if (x < sizeX * 2 + 1 && x >= 0 && y < sizeY * 2 + 1 && y >= 0)
    {
        return true;
    }
    return false; //defaults to not being within the maze
}
void Grid::generateGrid(Node current, int seedChanger)
{
    generatedGrid[current.getY()][current.getX()] = current; //generated grid has the position of the current node set to the current node
    generatedGrid[current.getY()][current.getX()].setVisited(); //sets the current to visited
    vector<vector<int>> directions = { {0, 1, 0},{1, 0, 1},{0, -1, 2},{-1, 0, 3} }; //up right down left
    srand(time(NULL) + seedChanger); //creates a new seed every iteration
    for (int i = directions.size() - 1; i > 0; i--) //shuffles the directions
    {
        int n = rand() % (i + 1);
        swap(directions[i], directions[n]);
    }
    for (int i = 0; i < 4; i++) //hard coded i to go to 4 as there will only ever be 4 directions
    {
        if (checkInsideGrid(current.getX() + directions[i][0],current.getY() + directions[i][1] )) //checks if the position in the direction generated is inside the bounds of the grid
        {
            if (!(generatedGrid[current.getY() + directions[i][1]][current.getX() + directions[i][0]]).getVisited()) //checks if the position in the direction generated is visited
            {
                generatedGrid[current.getY()][current.getX()].setWalls(directions[i][2]);
                Node add(current.getX() + directions[i][0], current.getY() + directions[i][1]); //creates a new node that is in the position of the node originally passed into generate
                add.setWalls((directions[i][2] + 2) % 4);
                generateGrid(add, seedChanger + 1); //calls itself with the new node set to be the current
            }
        }
    }
}

void Grid::compileGrid() //converts the generated grid to one that can be traversed by the player and displayed
{
    compiledGrid.resize(sizeY * 2 + 1); //vectors gonna vector
    for (int i = 0; i < compiledGrid.size(); i++)
    {
        compiledGrid[i].resize(sizeX * 2 + 1);
    }
    for (int j = 0; j < sizeY * 2 + 1; j++) //for all the y values
    {
        for (int i = 0; i < sizeX * 2 + 1; i++) //for all the x values
        {
            compiledGrid[j][i] = true; //default all the values to true
        }
    }
    vector<vector<int>> directions = { {0, 1},{1, 0},{0, -1},{-1, 0} };
    for (int j = 0; j < sizeY * 2 + 1; j++) //for all the y values
    {
        for (int i = 0; i < sizeX * 2 + 1; i++) //for all the x values
        {
            if (!(i == 0 || j == 0 || i == sizeX * 2 || j == sizeY * 2)) //the number is within the bounds of the maze
            {
                if (i % 2 == 1 && j % 2 == 1) //when both numbers are odd, it will correlate to a position in the generated grid
                {
                    compiledGrid[j][i] = false;
                    for (int k = 0; k < 4; k++)
                    {
                        if (!generatedGrid[((j - 1) / 2)][((i - 1) / 2)].getWalls(k))
                        {
                            compiledGrid[(j + directions[k][1])][(i + directions[k][0])] = false;
                        }
                    }
                }
            }
        }
    }
}

void Grid::pepperGrid(int amount) //converts the generated grid to one that can be traversed by the player and displayed
{
    int seedChanger = 0;
    while (amount > 0)
    {
        srand(time(NULL) + seedChanger); //creates a new seed every iteration
        int posToTryX = rand() % (sizeX * 2 + 1);
        int posToTryY = rand() % (sizeY * 2 + 1);
        if (!(posToTryX == 0 || posToTryY == 0 || posToTryX == sizeX * 2 || posToTryY == sizeY * 2)) //the number is within the bounds of the maze
        {
            if (posToTryX % 2 == 1 && posToTryY % 2 == 0 || posToTryX % 2 == 0 && posToTryY % 2 == 1) //when both numbers are odd, it will correlate to a position in the generated grid
            {
                if (compiledGrid[posToTryY][posToTryX])
                {
                    compiledGrid[posToTryY][posToTryX] = false;
                    amount = amount - 1; //decrements the amount left to put into the grid
                }
            }
        }
        seedChanger = seedChanger + 1; //increments the seed changer because time based seeds are god's mistake
    }
}

void Grid::createOtherObjects(int amount, bool randEnd) //creates a grid of objects that can be displayed to the player. It is separated from pepper as they look for different attributes in the squares they try
{
    otherInfoGrid.resize(sizeY * 2 + 1); //vectors gonna vector
    for (int i = 0; i < otherInfoGrid.size(); i++)
    {
        otherInfoGrid[i].resize(sizeX * 2 + 1);
    }
    int seedChanger = 0;
    if (randEnd) //the loop will need to be run an extra time if the user wants a randomised finish. There is only ever 1 finish so it is unnecessary to code for more than just adding 1 iteration
    {
        amount = amount + 1;
    }
    while (amount > 0)
    {
        srand(time(NULL) + seedChanger); //creates a new seed every iteration
        int posToTryX = rand() % (sizeX * 2 + 1);
        int posToTryY = rand() % (sizeY * 2 + 1);
        if (checkInsideCompiledGrid(posToTryX,posToTryY)) //the number is within the bounds of the maze
        {
            if (!(posToTryX % 2 == 0 && posToTryY % 2 == 0) && !(posToTryX == 1 && posToTryY == 1)) //when both numbers are odd, it will correlate to a position in the generated grid
            {
                if (!compiledGrid[posToTryY][posToTryX] && otherInfoGrid[posToTryY][posToTryX] == 0)
                {
                    if (amount == 1 && randEnd) //if the user wants a random end, use the same algorithm as generating coins to generate the end - if it aint broke dont fix it
                    {
                        otherInfoGrid[posToTryY][posToTryX] = 1;
                        amount = amount - 1;
                    }
                    else
                    {
                        otherInfoGrid[posToTryY][posToTryX] = 2;
                        amount = amount - 1; //decrements the amount left to put into the grid
                    }
                    
                }
            }
        }
        seedChanger = seedChanger + 1; //increments the seed changer because time based seeds are god's mistake
    }
    if (!randEnd) //if the user doesn't want a random end point, set it to the bottom right
    {
        otherInfoGrid[sizeY * 2 - 1][sizeX * 2 - 1] = 1;
    }
    
}

vector<vector<bool>> Grid::returnGrid()
{
    return compiledGrid; //this is a weird implementation but this is so the correct grid can be taken in by nav and therefore the nav object in player. The main thing is that it works
}

vector<vector<int>> Grid::returnOtherInfoGrid()
{
    return otherInfoGrid;
}

