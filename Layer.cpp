#include "Node.h"
#include "Layer.h"

Layer::Layer(int type, int index, Layer* prevLayer, size_t in_layer_size,
	 					 size_t hidden_layer_size, size_t out_layer_size,
						 size_t hidden_layer_amount)
{
	m_type = type;
	m_index = index;
	m_prevLayer = prevLayer;

	if (m_type == INPUT_LAYER)													//if the layer type is an input layer then
	{																			//set its size to the size of an input layer
		m_size = in_layer_size;													//and the size of the next layer to the size
		m_next_layer_size = hidden_layer_size;									//of a hidden layer
	}
	else if (m_type == HIDDEN_LAYER && m_index != hidden_layer_amount - 1)		//However if it's a hidden layer and it's not
	{																			//the last one, then its size and the size of
		m_size = hidden_layer_size;												//the next layer are set to the size of a
		m_next_layer_size = hidden_layer_size;									//hidden layer
	}
	else if (m_type == HIDDEN_LAYER && m_index == hidden_layer_amount - 1)		//But if it's the last hidden layer before the output
	{																			//layer then its size is that of a hidden layer
		m_size = hidden_layer_size;												//and the size of the next is that of an output layer
		m_next_layer_size = out_layer_size;
	}
	else																		//the only case left is if it's an output layer
	{																			//in which case its size is the size of an output
		m_size = out_layer_size;												//layer and there is no next layer, so 0.
		m_next_layer_size = 0;
	}

	std::cout << ((init()) ? "Layer Initialized Successfully"
												 : "There Was A Problem Initializing Layer") << std::endl;
}

bool Layer::init()
{
	for (size_t i = 0; i < m_size; i++)
	{
		Node* tmp = (m_type == INPUT_LAYER) ? (new Node(m_next_layer_size, i))
																				: (new Node(m_next_layer_size, i, m_prevLayer));
		neurons.emplace_back(tmp);
	}

	return true;
}

size_t Layer::get_size()
{
	return m_size;
}

unsigned int Layer::get_type()
{
	return m_type;
}

Layer::~Layer()
{
	while (neurons.capacity())
	{
		neurons.resize(0);
		neurons.shrink_to_fit();
	}
}

bool Layer::set_input(std::vector<double> inputs) {
	if (get_type()==1) {
		for (size_t i = 0; i < m_size; i++) {
			neurons[i]->set_activation(inputs[i]);
		}
		return true;
	}
	else {
		return false;
	}
}
