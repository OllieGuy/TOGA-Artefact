#include "Player.h"

Player::Player(Navigation navPass)
{
    nav = navPass;
    currentXPos = 1; //defaults the player position to 1,1
    currentYPos = 1;
    coinTotal = 0;
    desiredCoins = 0;
}

int Player::getPlayerX()
{
    return currentXPos;
}

int Player::getPlayerY()
{
    return currentYPos;
}

void Player::movePlayer(int dir)
{
    vector<vector<int>> directions = { {0, 1},{1, 0},{0, -1},{-1, 0} }; //up right down left
    if (nav.positionAvailable(getPlayerX(), getPlayerY(), dir)) //see if the desired position in the direction specified is accessible
    {
        currentXPos = currentXPos + directions[dir][0];
        currentYPos = currentYPos + directions[dir][1];
    }
}

void Player::coinAdd() //when a coin is collected, increment the amount
{
    coinTotal = coinTotal + 1;
}

void Player::movementKey(int keyPress) 
{
    switch (keyPress)
    {
    case KEY_UP:
        movePlayer(2);
        break;
    case KEY_RIGHT:
        movePlayer(1);
        break;
    case KEY_DOWN:
        movePlayer(0);
        break;
    case KEY_LEFT:
        movePlayer(3);
        break;
    default:
        break; //any other character will result in nothing happening
    }
}

void Player::setDesiredCoins(int desired)
{
    desiredCoins = desired; //changes the coins that need to be collected to the one specified by the options
}

void Player::play()
{
    nav.display(currentXPos, currentYPos, false); //diplay the initial grid
    cout << "Coins: " << coinTotal << "/" << desiredCoins;
    int keyPress = 0; //keypress defaults to no press
    while (coinTotal < desiredCoins)
    {
        keyPress = 0;
        keyPress = _getch();
        movementKey(keyPress);
        if (nav.pointReached(getPlayerX(),getPlayerY()) == 2) //if the player reaches a coin
        {
            coinAdd();
        }
        nav.display(currentXPos, currentYPos, false);
        cout << "Coins: " << coinTotal << "/" << desiredCoins;
    }
    while (nav.pointReached(currentXPos, currentYPos) != 1) //when the player hasnt reached the end point once all the coins have been collected
    {
        keyPress = 0;
        keyPress = _getch();
        movementKey(keyPress);
        nav.display(currentXPos, currentYPos, true);
    }
}