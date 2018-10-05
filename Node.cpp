/*
Filename: Node.cpp
Contents: This file contains the main functions of control for the Node.
Functions:
  Node - This creates the node and sets all applicable values.
  ~ANN - This destructor frees all memory reserved by the class Node.
  DOUBLE gen_rand_num - This creates a random number [0,1] for the weight.
*/
#include "Node.h"

/**
 * ~Node - This is the deconstructor for the class Node. By using shrink_to_fit,
 *         unlike erase or clear, the memory allocated is released. This process
 *         confirms data is released and sets vectors to a null pointer.
 */
Node::~Node() {
  while (m_edgeWeight.capacity()) {
    m_edgeWeight.resize(0);
    m_edgeWeight.shrink_to_fit();
  }
}

double Node::gen_rand_num()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> distribution(0, 1);
	return distribution(gen);
}
