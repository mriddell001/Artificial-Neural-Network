/*
Filename: Node.cpp
Contents: This file contains the main functions of control for the Node.
Functions:
  Node - This creates the node and sets all applicable values.
  ~ANN - This destructor frees all memory reserved by the class Node.
  DOUBLE gen_rand_num - This creates a random number [0,1] for the weight.
*/
#include "Node.h"
#include "Layer.h"
/*
this constructor captures the previous layer
and initialises the weights to the next
*/
Node::Node(int next_layer_amount, int index, Layer *prevLayer)
{
	m_prevLayer = prevLayer;
	m_index = index;
	m_bias = gen_rand_int();
	m_activation = 0;
	for (int i = 0; i < next_layer_amount; i++)
		m_edgeWeight.emplace_back(gen_rand_double());
}

/*
This constructor is to be used for the input layer.
it takes no previous layer and the activation must
be set manually through set_activation(double act).
*/
Node::Node(int next_layer_amount, int index)
{
	m_index = index;
	m_bias = gen_rand_int();
	m_activation = 0;
	for (int i = 0; i < next_layer_amount; i++)
		m_edgeWeight.emplace_back(gen_rand_double());
}

/**
 * ~Node - This is the deconstructor for the class Node. By using shrink_to_fit,
 *         unlike erase or clear, the memory allocated is released. This process
 *         confirms data is released and sets vectors to a null pointer.
 */
Node::~Node() {
  while (m_edgeWeight.capacity())
  {
    m_edgeWeight.resize(0);
    m_edgeWeight.shrink_to_fit();
  }
}

/*
Returns a random double within the interval [0, 1];
Purpose: setting weights to the next layer.
*/
double Node::gen_rand_double()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> distribution(0, 1);
	return distribution(gen);
}

/*
Returns a random integer within the interval [0, 100];
Purpose: setting the bias of the current neuron.
*/
int Node::gen_rand_int()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distribution(0, 100);
	return distribution(gen);
}

//Sigmoid function.
double Node::sigmoid(double x)
{
	return 1 / (1 + pow(e, -x));
}

/*
This Function calculates the activation of this neuron and returns it
Rather than setting it straight to activation in case the need arises
To calculate the activation again in real-time or call it from outside
this class.
*/
double Node::calc_activation()
{
	double weight_activtion_product = 0;
	for (size_t i = 0; i < (m_prevLayer->neurons.size()); i++)
		weight_activtion_product += (m_prevLayer->neurons[i]->get_activation() * m_prevLayer->neurons[i]->m_edgeWeight[m_index]);
	return sigmoid(weight_activtion_product - m_bias);
}

//Returns the Activation.
double Node::get_activation()
{
	return m_activation;
}

//Returns the Bias.
double Node::get_bias()
{
	return m_bias;
}

std::vector<double> Node::get_edgeWeights()
{
	return m_edgeWeight;
}

//Sets The Activation.
void Node::set_activation(double act)
{
	//if the value given is not in range [1, 0] then don't change it;
	m_activation = ((act > 1) || (act < 0)) ? m_activation : act;
}
