#include "Node.h"

Node::Node(int xIn, int yIn) //node constructor used for the real nodes
{
    x = xIn;
    y = yIn;
    walls;
    visited;
}
Node::Node() //this is used when certain vectors are resized so it has something to default to
{
    walls;
    visited;
}
void Node::setWalls(int wallToRemove) //removes a specific wall that is passed to it
{
    walls[wallToRemove] = false;
}
bool Node::getWalls(int check) //checks a wall
{
    return walls[check];
}
int Node::getX()
{
    return x;
}
int Node::getY()
{
    return y;
}
void Node::setVisited() //marks a node as visited
{
    visited = true;
}
bool Node::getVisited()
{
    return visited;
}