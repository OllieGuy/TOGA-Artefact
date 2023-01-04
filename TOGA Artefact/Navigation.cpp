#include "Navigation.h"

Navigation::Navigation()
{
}
Navigation::Navigation(vector<vector<bool>>passedGrid, vector<vector<int>>passedOtherInfoGrid)
{
    sizeX = passedGrid[0].size();
    sizeY = passedGrid.size();
	navigableGrid = passedGrid;
    otherInfoGrid = passedOtherInfoGrid;
}

bool Navigation::positionAvailable(int curX, int curY, int dir)
{
	vector<vector<int>> directions = { {0, 1},{1, 0},{0, -1},{-1, 0} };
	if (checkInsideCompiledGrid(curX + directions[dir][0], curY + directions[dir][1]))
	{
		if(!navigableGrid[curY + directions[dir][1]][curX + directions[dir][0]])
		{
			return true;
		}
	}
	return false;
}

int Navigation::pointReached(int curX, int curY)
{
    int endX = -1;
    int endY = -1;
    for (int j = 0; j < getY(); j++) //for all the squares in the grid
    {
        for (int i = 0; i < getX(); i++)
        {
            if (otherInfoGrid[j][i] == 1)
            {
                endX = i;
                endY = j;
            }
        }
    }
    if (otherInfoGrid[curY][curX] == 2)
    {
        otherInfoGrid[curY][curX] = 0;
        return 2;
    }
	if (curX == endX && curY == endY)
	{
		return 1;
	}
	return 0;
}

void Navigation::display(int playerPosX, int playerPosY, bool endUnlocked) //display is a separate function so that it can be expanded upon later
{
    cout << "\033[2J\033[1;1H"; //clears the console so that the updated maze can be shown (using a special character)
    for (int j = 0; j < getY(); j++) //for all the squares in the grid
    {
        for (int i = 0; i < getX(); i++)
        {
            //this part just interprets the grid to be something to print
            if (navigableGrid[j][i]) //reverse indexing
            {
                cout << char(219u) << char(219u); //these characters just form a box
            }
            else if (i == playerPosX && j == playerPosY) //if the player is in that position
            {
                cout << "# ";
            }
            else if (otherInfoGrid[j][i] == 2) //if a coin has been decided to be in that position
            {
                cout << "O ";
            }
            else if (otherInfoGrid[j][i] == 1 && endUnlocked) //if the end is in that position and all coins have been collected
            {
                cout << "F ";
            }
            else
            {
                cout << "  "; //the same space as a box, essentially just outputs a traversable square
            }
        }
        cout << "\n";
    }
}