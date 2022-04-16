
#include "PathPlanner.h"

#include <iostream>

PathPlanner::PathPlanner(Env env, int rows, int cols)
{

    for (int row = 0; row < ENV_DIM; row++)
    {
        for (int col = 0; col < ENV_DIM; col++)
        {
            // Initilising the Enviroment and assignning their respective values
            this->env[row][col] = 0;
            this->env[row][col] = env[row][col];
        }
    }
    this->rows = rows;
    this->cols = cols;

    openNodes = new NodeList();
    nodesExplored = new NodeList();
}

PathPlanner::~PathPlanner()
{
}

void PathPlanner::initialPosition(int row, int col)
{
    this->sRow = row;
    this->sCol = col;
}
void PathPlanner::endingPosition(int row, int col)
{
    this->goalRow = row;
    this->goalCol = col;
}
NodeList *PathPlanner::getReachableNodes()
{
    return new NodeList(*nodesExplored);
}

NodeList *PathPlanner::getPath()
{
    NodeList *list = getReachableNodes();
    NodeList *backList = new NodeList();
    NodeList *finalList = new NodeList();
    Node *nextNode = new Node(*list->get(list->getLength() - 1));
    bool notReached = true;

    // Add the Goal Node
    backList->addBack(nextNode);

    while (notReached)
    {
        nextNode = findNeighbour(list, nextNode);
        backList->addBack(new Node(*nextNode));

        if (nextNode != nullptr)
        {
            // Checks the current Node reached the Start Node
            if (nextNode->sameNode(list->get(0)))
            {
                notReached = false;
            }
        }
    }

    // Sorts the list Ascending order based on Distance Travel
    sortNodeAscen(backList, false);

    finalList = new NodeList(*backList);
    return finalList;
}

void PathPlanner::forwardSearch()
{
    Node *selectedNode = nullptr;
    bool check = true;

    openNodes->addBack(new Node(sRow, sCol, 0));

    /*
        // Reads to find the Starting point(S) in the environment
        for (int row = 0; row < ENV_DIM; ++row)
        {
            for (int col = 0; col < ENV_DIM; ++col)
            {
                if (env[row][col] == SYMBOL_START)
                {
                    // Initialise the Start location
                    openNodes->addBack(new Node(row, col, 0));
                }
                else if (env[row][col] == SYMBOL_GOAL)
                {
                    // Set the Goal location
                    goalLoc = new Node(row, col, 0);
                }
            }
        }
        */

    while (check)
    {
        if (openNodes->getLength() == 1)
        {
            // Checks is up cordinates empty for current open Node
            findOpenSpace(env, openNodes->get(0)->getRow() - 1, openNodes->get(0)->getCol(), openNodes->get(0)->getDistanceToS());
            // Checks is right cordinates empty for current open Node
            findOpenSpace(env, openNodes->get(0)->getRow(), openNodes->get(0)->getCol() + 1, openNodes->get(0)->getDistanceToS());
            // Checks is down cordinates empty for current open Node
            findOpenSpace(env, openNodes->get(0)->getRow() + 1, openNodes->get(0)->getCol(), openNodes->get(0)->getDistanceToS());
            // Checks is left cordinates empty for current open Node
            findOpenSpace(env, openNodes->get(0)->getRow(), openNodes->get(0)->getCol() - 1, openNodes->get(0)->getDistanceToS());

            nodesExplored->addBack(new Node(*(openNodes->get(0))));

            if (openNodes->get(0)->sameNode(new Node(goalRow, goalCol, 0)) == true)
            {
                check = false;
            }
        }
        else
        {
            selectedNode = findSmallestEstDis();

            // Checks is up cordinates empty for current open Node
            findOpenSpace(env, selectedNode->getRow() - 1, selectedNode->getCol(), selectedNode->getDistanceToS());
            // Checks is right cordinates empty for current open Node
            findOpenSpace(env, selectedNode->getRow(), selectedNode->getCol() + 1, selectedNode->getDistanceToS());
            // Checks is down cordinates empty for current open Node
            findOpenSpace(env, selectedNode->getRow() + 1, selectedNode->getCol(), selectedNode->getDistanceToS());
            // Checks is left cordinates empty for current open Node
            findOpenSpace(env, selectedNode->getRow(), selectedNode->getCol() - 1, selectedNode->getDistanceToS());

            nodesExplored->addBack(new Node(*(selectedNode)));

            if (selectedNode->sameNode(new Node(goalRow, goalCol, 0)) == true)
            {
                check = false;
            }
        }
    }
    delete selectedNode;
}

Node *PathPlanner::findSmallestEstDis()
{
    NodeList *copyOpenNodes = new NodeList(*openNodes);
    Node *smallNode = nullptr;

    // Sorts the list Ascending order based on Est Dis
    sortNodeAscen(copyOpenNodes, true);

    // Smallest is the first element as Ascending order
    smallNode = new Node(*copyOpenNodes->get(0));

    // Checks the current smallNode has travel distance more than the last explore Node's travel distance
    // TO ensure the selected Node is neighbour of the current position of the Robot
    for (int i = 0; i < openNodes->getLength(); i++)
    {
        if (smallNode->getDistanceToS() > nodesExplored->get(nodesExplored->getLength() - 1)->getDistanceToS())
        {
            if (!(nodesExplored->containsNode(smallNode)))
            {
                return smallNode;
            }
        }
        else if (!(copyOpenNodes->get(i + 1) == nullptr))
        {
            if (!(nodesExplored->containsNode(copyOpenNodes->get(i + 1))))
            {
                smallNode = new Node(*copyOpenNodes->get(i + 1));
            }
        }
        else
        {
            // If here, there are no path with the current path. So, check the same Est Dis Node in the current path
            // And, explore in that another path to find the Goal Node
            smallNode = findSameEstDisNode(copyOpenNodes);
        }
    }
    return smallNode;
}

Node *PathPlanner::findSameEstDisNode(NodeList *copyOpenNodes)
{
    Node *smallNode = nullptr;
    for (int j = 0; j < copyOpenNodes->getLength(); j++)
    {
        for (int k = j + 1; k < copyOpenNodes->getLength(); k++)
        {
            if (copyOpenNodes->get(j)->getEstimatedDist2Goal(new Node(goalRow, goalCol, 0)) == copyOpenNodes->get(k)->getEstimatedDist2Goal(new Node(goalRow, goalCol, 0)))
            {
                if (!(nodesExplored->containsNode(copyOpenNodes->get(k))))
                {
                    smallNode = new Node(*copyOpenNodes->get(k));
                    return smallNode;
                }
            }
        }
    }
    return smallNode;
}

void PathPlanner::findOpenSpace(Env env, int row, int col, int disTraveled)
{
    Node *newNode = nullptr;
    bool isPosExist = false;

    if (env[row][col] == SYMBOL_EMPTY || env[row][col] == SYMBOL_GOAL)
    {
        newNode = new Node(row, col, disTraveled);
        isPosExist = openNodes->containsNode(newNode);

        // Set DistanceTraveled and Add the up cordinate for the current Node if not exist in the openNodes
        if (isPosExist == false)
        {
            newNode->setDistanceToS(disTraveled + 1);
            openNodes->addBack(newNode);
        }
    }
}

Node *PathPlanner::findNeighbour(NodeList *givenList, Node *givenNode)
{
    for (int i = givenList->getLength() - 1; i > -1; i--)
    {
        if (givenList->get(i)->getDistanceToS() < givenNode->getDistanceToS())
        {
            // Checks for UP position
            if (givenNode->getRow() - 1 == givenList->get(i)->getRow() && givenNode->getCol() == givenList->get(i)->getCol())
            {
                return givenList->get(i);
            }

            // Checks for RIGHT position
            if (givenNode->getRow() == givenList->get(i)->getRow() && givenNode->getCol() + 1 == givenList->get(i)->getCol())
            {
                return givenList->get(i);
            }

            // Checks for DOWN position
            if (givenNode->getRow() + 1 == givenList->get(i)->getRow() && givenNode->getCol() == givenList->get(i)->getCol())
            {
                return givenList->get(i);
            }

            // Checks for LEFT position
            if (givenNode->getRow() == givenList->get(i)->getRow() && givenNode->getCol() - 1 == givenList->get(i)->getCol())
            {
                return givenList->get(i);
            }
        }
    }
    return nullptr;
}

void PathPlanner::sortNodeAscen(NodeList *givenNodeList, bool whichBased)
{
    Node *temp = nullptr;

    // WhichBased == false, then sorts based on DistanceTraveled
    if (whichBased == false)
    {
        for (int i = 0; i < givenNodeList->getLength(); ++i)
        {
            for (int j = i + 1; j < givenNodeList->getLength(); ++j)
            {
                if (givenNodeList->get(i)->getDistanceToS() > givenNodeList->get(j)->getDistanceToS())
                {
                    temp = givenNodeList->get(i);
                    givenNodeList->setNode(i, givenNodeList->get(j));
                    givenNodeList->setNode(j, temp);
                }
            }
        }
    }
    else
    {
        // WhichBased == true, the sorts based on Estimated Distance
        for (int i = 0; i < givenNodeList->getLength(); ++i)
        {
            for (int j = i + 1; j < givenNodeList->getLength(); ++j)
            {
                if (givenNodeList->get(i)->getEstimatedDist2Goal(new Node(goalRow, goalCol, 0)) > givenNodeList->get(j)->getEstimatedDist2Goal(new Node(goalRow, goalCol, 0)))
                {
                    temp = givenNodeList->get(i);
                    givenNodeList->setNode(i, givenNodeList->get(j));
                    givenNodeList->setNode(j, temp);
                }
            }
        }
    }
}
