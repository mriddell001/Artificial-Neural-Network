#ifndef LAYER_H
#define LAYER_H

#include "Node.h"

#define INPUT_LAYER 1
#define HIDDEN_LAYER 2
#define OUTPUT_LAYER 3

class Layer
{
public:
	Layer() = delete;
	Layer(int type, int index, Layer* prevLayer, size_t in_layer_size, size_t hidden_layer_size, size_t out_layer_size, size_t hidden_layer_amount);
	~Layer();

	size_t get_size();
	unsigned int get_type();

private:
	bool init();

public:
	std::vector<Node*> neurons;

private:
	int m_type;					//One of the following: INPUT_LAYER, OUTPUT_LAYER or HIDDEN_LAYER.
	int m_index;				//If it's a hidden layer then it's the index of this layer in the hidden layer vector (starting from 0).
	size_t m_size;				//Size of the current layer.
	size_t m_next_layer_size;	//Size of the next layer (0 if it's the output layer).
	Layer* m_prevLayer;			//Pointer to the next layer (NULL if it's the output layer).
};

#endif // Layer_H