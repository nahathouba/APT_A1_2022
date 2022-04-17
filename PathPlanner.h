
#ifndef COSC_ASS_ONE_PATH_PLANNING
#define COSC_ASS_ONE_PATH_PLANNING

#include "Node.h"
#include "NodeList.h"
#include "Types.h"

class PathPlanner
{
public:
   /*                                           */
   /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
   /*                                           */

   // Initialise with a given Env of size (rows,cols)
   PathPlanner(Env env, int rows, int cols);

   // Clean-up
   ~PathPlanner();

   // Set The initial and ending position
   void initialPosition(int row, int col);

   // Method for Milestone 2
   // Return a DEEP COPY of the NodeList of all node's
   //    that the robot can reach with distances
   NodeList *getReachableNodes();

   // Method for Milestone 3
   // Get the path from the starting position to the given goal co-ordinate
   //    The path should be a DEEP COPY
   NodeList *getPath();

   /*                                           */
   /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
   /*                                           */

   // Set the ending position
   void endingPosition(int row, int col);

private:
   Env env;
   int rows;
   int cols;

   // Initial (S) position (i.e row & col)
   int sRow;
   int sCol;

   // Ending position (G)
   int goalRow;
   int goalCol;

   // Nodes explored in forward search algorithm
   NodeList *nodesExplored;

   // Nodes that are open for Robot to move
   NodeList *openNodes;

   // Execute forward search algorithm
   void forwardSearch();

   // Finds open space in the environment for the given Node and adds in the openNodes
   void findOpenSpace(Env env, int row, int col, int disTraveled);

   // Finds the smallest estimated distance Node
   Node *findSmallestEstDis();

   // FInds neighbour of a given Node in the given list
   Node *findNeighbour(NodeList *givenList, Node *givenNode);

   // Sorts the given Nodelist in the Ascending order
   void sortNodeAscen(NodeList *givenNodeList, bool whichBased);

   // Finds the Node that are same in the Estimate Distance
   Node *findSameEstDisNode(NodeList *copyOpenNodes);
};

#endif // COSC_ASS_ONE_PATH_PLANNING
