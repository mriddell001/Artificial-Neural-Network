#include "Layer.h"

Layer::Layer(int type, int index, Layer* prevLayer, size_t in_layer_size, size_t hidden_layer_size, size_t out_layer_size, size_t hidden_layer_amount)
{
	m_type = type;
	m_index = index;
	m_prevLayer = prevLayer;

	if (m_type == INPUT_LAYER)
	{
		m_size = in_layer_size;
		m_next_layer_size = hidden_layer_size;
	}
	else if (m_type == HIDDEN_LAYER && m_index != hidden_layer_amount - 1)
	{
		m_size = hidden_layer_size;
		m_next_layer_size = hidden_layer_size;
	}
	else if (m_type == HIDDEN_LAYER && m_index == hidden_layer_amount - 1)
	{
		m_size = hidden_layer_size;
		m_next_layer_size = out_layer_size;
	}
	else
	{
		m_size = out_layer_size;
		m_next_layer_size = 0;
	}

	std::cout << ((init()) ? "Layer Initialized Successfully" : "There Was A Problem Initializing Layer") << std::endl;
}

bool Layer::init()
{
	for (int i = 0; i < m_size; i++)
	{
		Node* tmp = (m_type == INPUT_LAYER) ? new Node(m_next_layer_size) : new Node(m_next_layer_size, m_prevLayer);
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