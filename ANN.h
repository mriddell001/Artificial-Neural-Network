/*
Filename: ANN.h
Name: Matthew Riddell-Ide
Contents: This file contains the header for the ANN.
Functions:
  ANN - This constructor is passed four int values as its parameter, the
        first element is the size of the input layer, the second is the number
        of hidden layers, the third is the size of the hidden layers, the last
        element is the size of the output layer.
  ~ANN - This destructor frees all memory reserved by the class ANN.
*/

//ANN.h
#ifndef ANN_H
#define ANN_H
#define e 2.71828182845904523536

#include "Node.h"
#include <iostream>
#include <string>

class ANN {
public:
  ANN(int in[]);
  ~ANN();
  void auto_refine(std::istream &instream, std::ostream &outstream);

private:
  bool init();
  bool prime_input(std::istream &stream);
  double elucidian_distance(std::istream &stream);

  bool run_test();
  bool input_to_hidden();
  bool hidden_to_hidden();
  bool hidden_to_output();

  bool backpropagation(double err);
  bool back_output_to_hidden(double err);
  bool back_hidden_to_hidden(double err);
  bool back_hidden_to_input(double err);

  void input_layer_creation(int a);
  void hidden_layer_creation(int b, int d);
  void output_layer_creation(int b, int c, int d);

  void emergency_exit(std::string error_message);
  void save_state(std::ostream &outstream);

  std::vector<std::shared_ptr<Node*> > ann_i;   //Vector of input nodes.
  std::vector<std::shared_ptr<Node*> > ann_h;   //Vector of hidden nodes.
  std::vector<std::shared_ptr<Node*> > ann_o;   //Vector of output nodes.
  int m_input_size;
  int m_hidden_layers;
  int m_hidden_size;
  int m_output_size;
};

#endif // ANN_H
