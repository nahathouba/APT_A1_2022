
#include "NodeList.h"
#include <iostream>

NodeList::NodeList()
{
    this->length = 0;
    // initiliseNodeList();
    for (int i = 0; i < NODE_LIST_ARRAY_MAX_SIZE; i++)
    {
        nodes[i] = nullptr;
    }
}

NodeList::~NodeList()
{
    for (int i = 0; i < NODE_LIST_ARRAY_MAX_SIZE; i++)
    {
        if (nodes[i] != nullptr)
            delete nodes[i];
    }
}

NodeList::NodeList(NodeList &other)
{
    length = other.length;
    for (int i = 0; i < NODE_LIST_ARRAY_MAX_SIZE; i++)
    {
        nodes[i] = nullptr;
    }

    for (int i = 0; i < length; i++)
    {
        nodes[i] = new Node(*other.nodes[i]);
    }
}

int NodeList::getLength()
{
    return length;
}

NodePtr NodeList::get(int i)
{
    return nodes[i];
}

void NodeList::addBack(NodePtr newNode)
{
    nodes[length] = newNode;
    length++;
}

bool NodeList::containsNode(NodePtr node)
{
    for (int i = 0; i < length; i++)
    {
        // Checks whether the given node is same or not
        bool isSame = node->sameNode(nodes[i]);

        if (isSame == true)
            return true;
    }
    return false;
}

void NodeList::clear()
{
    // TODO
}

void NodeList::initiliseNodeList()
{
    for (int i = 0; i < NODE_LIST_ARRAY_MAX_SIZE; i++)
    {
        if (nodes[i] != 0)
            nodes[i] = 0;
    }
}

void NodeList::removeNode(int i)
{
    delete nodes[i];
    length--;
}

void NodeList::setNode(int index, Node *newNode)
{
    nodes[index] = newNode;
}