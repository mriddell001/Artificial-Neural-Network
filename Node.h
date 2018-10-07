/*
Filename: Node.h
Contents: This file contains the header for the Node.
Functions:
  Node - This creates the node and sets all applicable values.
  ~ANN - This destructor frees all memory reserved by the class Node.
  DOUBLE gen_rand_num - This creates a random number [0,1] for the weight.
*/
//Node.h
#ifndef NODE_H
#define NODE_H

#include <vector>
#include <random>

class Node {
public:
  Node(){m_weight = gen_rand_num();};
  ~Node();

  double gen_rand_num();            //Returns a random value between 0 & 1.

public:
  std::vector<Node*> m_edges;       //Pointers to nodes in next layer.
  std::vector<double> m_edgeWeight; //Weights of paths to nodes in next layer.
  int bias;							// Threshold Bias
  double activation;				//Activation Value
  double m_weight;                  //Weight of node. Default: Random
};

#endif // Node_H
