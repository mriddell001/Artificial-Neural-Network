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
#include <math.h>
#include <iostream>
#include <string>

#define e 2.71828182845904523536

class Node {
public:
  Node(int next_layer_amount, Layer* prevLayer);
  Node(int next_layer_amount);
  Node() = delete;  //deleted the default constructor, you can do nothing but use my own constructors! Mwahahahahah!
  ~Node();

  double gen_rand_double();			//Returns a random value between 0 & 1.
  int gen_rand_int();				//Returns a random value between 0 & 100.
  void set_activation(double act);  //Sets the Activation to a certain Value (to be used when setting up input layer)
  double get_activation();			//Gets the Activation
  double calc_activation();			//Calculates the Activation

public:
  std::vector<Node*> m_edges;       //Pointers to nodes in next layer.
  std::vector<double> m_edgeWeight; //Weights of paths to nodes in next layer.

private:
	double sigmoid(double x);		//Sigmoid Function

private:
  double m_activation;				//Activation Value
  int m_bias;						//Threshold Bias

  Layer* m_prevLayer;				//Pointer to the Previous Layer
  
};

#endif // Node_H
