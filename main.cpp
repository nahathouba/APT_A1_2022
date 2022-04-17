#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathPlanner.h"

/*
// Helper test functions
void testNode();

void testNodeList();
*/

// Read a environment from standard input.
void readEnvStdin(Env env);

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printPath(Env env, NodeList *solution);

// Gets the starting position
Node *getStartPosition(Env env);

// Gets the ending position
Node *getGoalPosition(Env env);

int main(int argc, char **argv)
{
    /*
    // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
    // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
    // AS YOU GO ALONG.
    // COMMENT THESE OUT BEFORE YOU SUBMIT!!!
    std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
    testNode();

    testNodeList();
    std::cout << "DONE TESTING" << std::endl
              << std::endl;
    */

    // Load Environment
    Env env;
    readEnvStdin(env);

    // Solve using forwardSearch
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
    PathPlanner *pathplanner = new PathPlanner(env, ENV_DIM, ENV_DIM);
    NodeList *reachablePositions = nullptr;

    // Setting the initial and ending position
    Node *startingNode = getStartPosition(env);
    pathplanner->initialPosition(startingNode->getRow(), startingNode->getCol());
    Node *goalNode = getGoalPosition(env);
    pathplanner->endingPosition(goalNode->getRow(), goalNode->getCol());

    reachablePositions = pathplanner->getReachableNodes();

    // Get the path
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
    NodeList *solution = pathplanner->getPath();

    // print the path
    printPath(env, solution);

    delete startingNode;
    delete pathplanner;
    delete reachablePositions;
    delete solution;
}

void readEnvStdin(Env env)
{
    while (!std::cin.eof())
    {
        for (int row = 0; row < ENV_DIM; ++row)
        {
            for (int col = 0; col < ENV_DIM; ++col)
            {
                std::cin >> env[row][col];
            }
        }
    }
}

void printPath(Env env, NodeList *solution)
{
    // Checking for the which direction
    for (int i = 0; i < solution->getLength(); i++)
    {
        if (i == 0)
        {
            env[solution->get(i)->getRow()][solution->get(i)->getCol()] = SYMBOL_START;
        }
        else if (i == solution->getLength() - 1)
        {
            env[solution->get(i)->getRow()][solution->get(i)->getCol()] = SYMBOL_GOAL;
        }
        else
        {
            for (int j = i + 1; j < solution->getLength(); j++)
            {
                if (solution->get(i)->getRow() - 1 == solution->get(j)->getRow() && solution->get(i)->getCol() == solution->get(j)->getCol())
                {
                    env[solution->get(i)->getRow()][solution->get(i)->getCol()] = SYMBOL_UP;
                }

                if (solution->get(i)->getRow() == solution->get(j)->getRow() && solution->get(i)->getCol() + 1 == solution->get(j)->getCol())
                {
                    env[solution->get(i)->getRow()][solution->get(i)->getCol()] = SYMBOL_RIGHT;
                }

                if (solution->get(i)->getRow() + 1 == solution->get(j)->getRow() && solution->get(i)->getCol() == solution->get(j)->getCol())
                {
                    env[solution->get(i)->getRow()][solution->get(i)->getCol()] = SYMBOL_DOWN;
                }

                if (solution->get(i)->getRow() == solution->get(j)->getRow() && solution->get(i)->getCol() - 1 == solution->get(j)->getCol())
                {
                    env[solution->get(i)->getRow()][solution->get(i)->getCol()] = SYMBOL_LEFT;
                }
            }
        }
    }

    // Printing the Environment
    for (int row = 0; row < ENV_DIM; row++)
    {
        if (row > 0)
        {
            std::cout << std::endl;
        }
        for (int col = 0; col < ENV_DIM; col++)
        {
            std::cout << env[row][col];
        }
    }
}

/*
void printReachablePositions(Env env, NodeList *reachablePositions)
{

}

void testNode()
{
    std::cout << "TESTING Node" << std::endl;

    // Make a Node and print out the contents
    Node *node = new Node(1, 1, 2);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceToS() << std::endl;
    delete node;

    // Change Node and print again
    node = new Node(4, 2, 3);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceToS() << std::endl;
    delete node;
}

void testNodeList()
{
    std::cout << "TESTING NodeList" << std::endl;

    // Make a simple NodeList, should be empty size
    NodeList *nodeList = new NodeList();
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add a Node to the NodeList, print size
    Node *b1 = new Node(1, 1, 1);
    nodeList->addBack(b1);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add second Nodetest
    Node *b2 = new Node(0, 0, 1);
    nodeList->addBack(b2);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Test Get-ith - should be 0,0,1
    Node *getB = nodeList->get(1);
    std::cout << getB->getRow() << ",";
    std::cout << getB->getCol() << ",";
    std::cout << getB->getDistanceToS() << std::endl;

    // Print out the NodeList
    std::cout << "PRINTING OUT A NODELIST IS AN EXERCISE FOR YOU TO DO" << std::endl;
}
*/

Node *getStartPosition(Env env)
{
    // Reads to find the Starting point(S) in the environment
    for (int row = 0; row < ENV_DIM; ++row)
    {
        for (int col = 0; col < ENV_DIM; ++col)
        {
            if (env[row][col] == SYMBOL_START)
            {

                return new Node(row, col, 0);
            }
        }
    }
    return nullptr;
}

Node *getGoalPosition(Env env)
{
    // Reads to find the Ending point(G) in the environment
    for (int row = 0; row < ENV_DIM; ++row)
    {
        for (int col = 0; col < ENV_DIM; ++col)
        {
            if (env[row][col] == SYMBOL_GOAL)
            {
                return new Node(row, col, 0);
            }
        }
    }
    return nullptr;
}
