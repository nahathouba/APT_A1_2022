
#include "Node.h"

Node::Node(int row, int col, int distanceToS)
{
   this->row = row;
   this->col = col;
   this->distanceToS = distanceToS;
}

Node::~Node()
{
   // TODO
}

int Node::getRow()
{
   return row;
}

int Node::getCol()
{
   return col;
}

int Node::getDistanceToS()
{
   return distanceToS;
}

void Node::setDistanceToS(int distanceToS)
{
   this->distanceToS = distanceToS;
}

void Node::printNode()
{
   std::cout << getRow() << ",";
   std::cout << getCol() << ",";
   std::cout << getDistanceToS() << std::endl;
}

bool Node::sameNode(Node *givenNode)
{
   bool sameRow = row == givenNode->getRow();
   bool sameCol = col == givenNode->getCol();

   if (sameRow == true && sameCol == true)
   {
      return true;
   }
   return false;
}

int Node::getEstimatedDist2Goal(Node *goal)
{
   // Calculate Manhattan_distance and assign.
   int manhattanDis = calculateManhatDis(goal);
   // Estimated distance = distance_travelled of node p + Manhattan distance from p to G
   return distanceToS + manhattanDis;
}

int Node::calculateManhatDis(Node *goalNode)
{
   // Manhattan_distance = |colp−colG| + |rowp−rowG|
   return abs(col - goalNode->getCol()) + abs(row - goalNode->getRow());
}