
#ifndef COSC_ASS_ONE_NODE
#define COSC_ASS_ONE_NODE

#include "Types.h"
#include <iostream>

class Node
{
public:
    /*                                           */
    /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
    /*                                           */

    // get row-co-ordinate
    int getRow();

    // get Column-co-ordinate
    int getCol();

    // getters and setters for distance to source
    int getDistanceToS();
    void setDistanceToS(int distanceToS);

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */

    // Constructor/Destructor
    Node(int row, int col, int distanceToS);
    ~Node();

    // Prints Node details
    void printNode();

    // Checks weather the given node is same or not
    bool sameNode(Node *givenNode);

    // getter for estimated dist to goal - need to return -> Manhatten distance + distance traveled
    int getEstimatedDist2Goal(Node *goal);

private:
    int row;
    int col;
    int distanceToS;

    // to calculate Manhattan distance
    int calculateManhatDis(Node *goalNode);
};

/*                                           */
/* DO NOT MOFIFY THIS TYPEDEF                */
/*                                           */
// Pointer to a Position-Distance
typedef Node *NodePtr;

#endif // COSC_ASS_ONE_NODE
