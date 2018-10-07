/*
Filename: Node.cpp
Contents: This file contains the main functions of control for the Node.
Functions:
  Node - This creates the node and sets all applicable values.
  ~ANN - This destructor frees all memory reserved by the class Node.
  DOUBLE gen_rand_num - This creates a random number [0,1] for the weight.
*/
#include "Node.h"

/*
	this constructor captures the weights in the previous layer
	and initialises the weights to the next
*/
Node::Node(int next_layer_amount, std::vector<double> prevLayerWeight)
{
	m_inWeights = prevLayerWeight;
	for (int i = 0; i < next_layer_amount; i++)
		m_edgeWeight.emplace_back(gen_rand_num());
}

//Default constructor
Node::Node()
{

}

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

double Node::sigmoid(double x)
{
	return 1 / (1 + pow(e, x));
}

void Node::calc_activation()
{
	
}

double Node::get_activation()
{
	return m_activation;
}

void Node::set_activation(double act)
{
	//if the value given is not in range [1, 0] then don't change it;
	m_activation = ((act > 1) || (act < 0)) ? m_activation : act;
}