/*
Filename: ANN.h
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

#include "Layer.h"

class ANN {
public:
  ANN(int in[]);
  //void testing_cycle(std::istream &instream, std::ostream &outstream);
  void testing_cycle(std::istream &instream);
  void print();

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

  void emergency_exit(std::string error_message);
  void save_state(std::ostream &outstream);

  Layer* ann_i;				   //Input Layer.
  std::vector<Layer*> ann_h;   //Vector of hidden Layers.
  Layer* ann_o;				   //Output Layer.
  int m_input_size;
  int m_hidden_layers;
  int m_hidden_size;
  int m_output_size;
};

#endif // ANN_H
