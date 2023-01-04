// TOGA Artefact.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <stack>
#include <random>
#include <algorithm>
#include <vector>
#include <time.h>
#include <chrono>
#include <thread>
#include <string>
#include "Node.h"
#include "Grid.h"
#include "Navigation.h"
#include "Player.h"
using namespace std;

bool isValidNumber(string input) //abstracted from the rest of the functions as it is called so many times
{
    for (int i = 0; i < input.length(); i++) //for all the characters in the input string
    {
        if (!isdigit(input[i])) //basically checking if any of the characters ARENT numbers, it will return false
        {
            cout << "Please enter a valid number\n";
            return false;
        }
    }
    return true;
}
vector<int> options() //to be printed when the user selects that they want to use custom settings
{
    vector<int> returnVec = { 5,0,0,0 }; //sets up return vector, even if the user somehow manages not to input anything, these are still valid settings
    string size;
    int sizeInt;
    string pepper;
    int pepperInt;
    string coins;
    char randEnd;
    int coinsInt;
    int numCheck;
    bool valid = false;
    while (valid == false)
    {
        cout << "Grid size (3-20): ";
        cin >> size;
        if (isValidNumber(size)) //if the users size is a number
        {
            sizeInt = stoi(size); //cast it to an int
            if (sizeInt <= 20 && sizeInt >= 3)
            {
                returnVec[0] = sizeInt; //set the setting in the return vector to the input
                valid = true;
            }
            else
            {
                cout << "Between 3 and 20" << "\n";
            }
        }
    }
    numCheck = ((sizeInt * sizeInt) / 2); //creates an arbitary upper limit to the amount of peppering and coins. Chosen because if the grid is size 3, the program will not work if any more peppering than this is inputted
    valid = false;
    while (valid == false)
    {
        cout << "Peppering (up to " << numCheck << "): ";
        cin >> pepper;
        if (isValidNumber(pepper))
        {
            pepperInt = stoi(pepper);
            if (pepperInt <= ((sizeInt * sizeInt) / 2))
            {
                returnVec[1] = pepperInt;
                valid = true;
            }
            else
            {
                cout << "Up to " << numCheck << "\n";
            }
        }
    }
    valid = false;
    while (valid == false)
    {
        cout << "Coins (up to " << numCheck << "): ";
        cin >> coins;
        if (isValidNumber(coins))
        {
            coinsInt = stoi(coins);
            if (coinsInt <= numCheck)
            {
                returnVec[2] = coinsInt;
                valid = true;
            }
            else
            {
                cout << "Up to " << numCheck << "\n";
            }
        }
    }
    valid = false;
    while (valid == false)
    {
        cout << "Random finish point? Y/N: ";
        cin >> randEnd;
        randEnd = tolower(randEnd); //as it is a string, both upper and lower case inputs of the same character should work
        if (randEnd == 'y' || randEnd == 'n')
        {
            break;
        }
        cout << "You may only type 'y' or 'n'.\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    if (randEnd == 'y') //the default value is false, so theres no need to assign that value again if the user selects no
    {
        returnVec[3] = 1;
    }
    return returnVec; //the format for this vector is -> size, pepper, coins, random end
}
void run(vector<int> selections) //abstracted so the game can be played multiple times without restarting the program
{
    Grid grid1;
    Node startNode(0, 0);
    grid1.setSize(selections[0]);
    grid1.generateGrid(startNode, 0);
    grid1.compileGrid();
    grid1.pepperGrid(selections[1]);
    grid1.createOtherObjects(selections[2], selections[3]);
    Navigation navPass(grid1.returnGrid(), grid1.returnOtherInfoGrid());
    Player player1(navPass);
    player1.setDesiredCoins(selections[2]);
    player1.play();
}
void printInstructions() //output the instructions
{
    cout << "\033[2J\033[1;1HWelcome to Ollie's maze game! Here are the instructions: \n - Use the arrow keys to move yourself (#) \n - Collect all the coins (O) to unlock the exit (F) \n - Your coin count is displayed under the grid";
    cout << "\n\nSetup instuctions: \n - In the setup menu, you will be asked for 4 inputs - size, pepper, coins, and random end \n    - Size       -> The size of the maze when it is generated. The final output will be just over double that size \n    - Peppering  -> Random walls that are turned into traversable squares. More pepper -> easier to traverse around \n    - Coins      -> How many coins will be around the maze that you must collect before the exit unlocks \n    - Random End -> Choose if the finishing spot once the coins are collected is randomised, or in the bottom right\n\n";
    system("pause"); //stop the program until any key is pressed so it looks nicer. I am aware this is bad practice, but it does exactly what I want it to do
}
void menu()
{
    cout << "Welcome to the maze game!\n\nEPILEPSY WARNING - The program uses a display technique that may flicker while updating/while you play\n\n";
    system("pause");
    bool play = true;
    string choice;
    while (play)
    {
        cout << "\033[2J\033[1;1HWhat would you like to do? \n 1. Play with default settings \n 2. Play with customised settings \n 3. How to play \n 4. Quit\n"; //the funky character at the start basically just clears the console
        cin >> choice;
        if (isValidNumber(choice))
        {
            int choiceInt = stoi(choice);
            switch (choiceInt)
            {
            case 1: //run with default settings
                run({ 5,3,5,0 });
                break;
            case 2: //run with custom settings
                run(options());
                break;
            case 3: //print the instructions
                printInstructions();
                break;
            case 4: //quit
                cout << "Thanks for playing!";
                play = false;
                break;
            default: //anything else
                cout << "Not a valid option";
                break;
            }
        }
    }
}
void main()
{
    menu(); //I know the menu could be put in main, but isn't it prettier like this?
}