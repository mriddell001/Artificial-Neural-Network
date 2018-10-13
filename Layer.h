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
	Layer(int type, int index, Layer* prevLayer, size_t in_layer_size,
		 		size_t hidden_layer_size, size_t out_layer_size,
				size_t hidden_layer_amount);
	~Layer();

	size_t get_size();
	unsigned int get_type();

private:
	bool init();

public:
	std::vector<Node*> neurons;

private:
	int m_type;								//Either: INPUT_LAYER, OUTPUT_LAYER or HIDDEN_LAYER.
	int m_index;							//If hidden layer then hidden layer index.
	size_t m_size;						//Size of the current layer.
	size_t m_next_layer_size;	//Size of the next layer.
	Layer* m_prevLayer;				//Pointer to the next layer.
};

#endif // Layer_H
