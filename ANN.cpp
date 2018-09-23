/*
Filename: ANN.cpp
Name: Matthew Riddell-Ide
Contents: This file contains the main functions of control for the ANN.
Functions:
  ANN - This constructor is passed four int values as its parameter, the
        first element is the size of the input layer, the second is the number
        of hidden layers, the third is the size of the hidden layers, the last
        element is the size of the output layer.
  ~ANN - This destructor frees all memory reserved by the class ANN.
*/
#include "ANN.h"
#include "Node.h"
#include <bits/stdc++.h>
#include <vector>

using namespace std;

/**
 * ANN - This function serves as the constructor for the ANN object. It sets the
 *    four basic size values: input, hidden, output, hidden layers. It calls the
 *    init() function afterwards and checks that it executed sucessfully.
 *
 * Assumptions: This function assumes the int array argument contains four valid
 *    integer values to be set.
 *
 * Testing status: Untested.
 */
ANN::ANN(int in[4]) {
  m_input_size = in[0];
  m_hidden_layers = in[1];
  m_hidden_size = in[2];
  m_output_size = in[3];

  bool init_success = init();
  if(!init_success) {
    cout << "There has been a problem with the init function.\n";
  }
}

/**
 * ~ANN - This function serves as the deconstructor for the ANN object. It runs
 *    a for loop itterating through each vector (input/hidden/output) and calls
 *    to delete each Node pointer.
 *
 * Assumptions: This function assumes the delete function is called successfully
 *
 * Testing status: Untested.
 */
ANN::~ANN() {
  for (auto it = ann_i.begin(); it != ann_i.end(); ++it)
    delete *it;
  for (auto it = ann_h.begin(); it != ann_h.end(); ++it)
    delete *it;
  for (auto it = ann_o.begin(); it != ann_o.end(); ++it)
    delete *it;
}

/*
 * init - This function serves to initialize the nodes in the ANN. This version
 *        is the primative version. Ultimately, this should be able to use
 *        recursion to automatically set every value.
 *
 * Assumptions: On start, this function assumes there are valid values for the
 * size of the layers and number of layers. It also assumes each hidden layer is
 * of equal size. On finish, it is to be assumed that the ANN has been
 * completely initialized and the input & output layers are set and can be
 * accessed.
 *
 * Testing status: Untested.
 */
bool ANN::init() {
  Node *tmp, *pmt;
  int a = m_input_size, b = m_hidden_size,
      c = m_output_size, d = m_hidden_layers;

  input_layer_creation(a);
  hidden_layer_creation(b,d);
  output_layer_creation(b,c,d);
  return true;
}

void ANN::input_layer_creation(int a) {
  ///For each node in the input layer.
  for (int i = 0; i < a; i++) {
    tmp = new Node();
    ann_i.push_back(tmp);
  }
}

void ANN::hidden_layer_creation(int b, int d) {
  //For each hidden layers.
  for (int i = 0; i < d; i++) {
    ///For each node in a hidden layer.
    for (int j = 0; j < b; j++) {
      tmp = new Node();
      ann_h.push_back(tmp);
      if (i) {
        int l = (i - 1) * b;
        ///For each node in a hidden layer, add the newly created node to the
        ///vector of edges of the previous layer.
        for (int k = 0; k < b; k++) {
          pmt = ann_h[l+k];
          (*pmt).m_edges.push_back(tmp);
          (*pmt).m_edgeWeight.push_back(0.5);
        }
      }
      else {
        ///For each node in the input layer, add the newly created node to the
        ///vector of edges.
        for (vector<Node*>::iterator it = ann_i.begin() ; it != ann_i.end(); ++it) {
          (*it)->m_edges.push_back(tmp);
          (*it)->m_edgeWeight.push_back(0.5);
        }
      }
    }
  }
}

void ANN::output_layer_creation(int b, int c, int d) {
  int l = (d*b)-b;
  ///For each node in the output layer.
  for (int i = 0; i < c; i++) {
    tmp = new Node();
    ann_o.push_back(tmp);
    ///For each node in the last hidden layer.
    for (int j = 0; j < b; j++) {
      pmt = ann_h[l+j];
      (*pmt).m_edges.push_back(tmp);
      (*pmt).m_edgeWeight.push_back(0.5);
    }
  }
}

/**
 * auto_refine - This function serves as an automatic refining of the ANN to
 *    reach a certain level of error consistantly. It randomly uses true
 *
 *
 *
 * Assumptions:
 *
 * Testing status: Untested.
 */
void ANN::auto_refine(istream &instream, ostream &outstream) {
  priority_queue<pair<double, string> > tests;
  string t, error_loc;
  double error_target;
  stream >> error_target;
  while(stream >> t) {
    tests.push(make_pair(1.0,t));
  }
  while(tests.size()) {
    pair<double, string> test = tests.top();
    if (test.first <= error_target) {
      tests.pop();
    }
    else {
      //Pop
      tests.pop();
      //Open file.
      std::ifstream test_stream (test.second, std::ifstream::in);
      //Prime input.
      bool primed = prime_input(test_stream);
      if(primed) {
        //Run test.
        bool tested = run_test();
      }
      else {
        while(tests.size()) {tests.pop();}
        error_loc = "Priming";
        emergency_exit(error_loc);
      }
      //Measure distance.
      //Backtracking.
      //Measure distance.
      //Push
    }

  }

}

/**
 * prime_input - This function serves to set the input layer to the values used
 *    by the current test investigated. This can be used to train the network or
 *    to use it in its finished form.
 *
 * Assumptions:
 *
 * Testing status: Untested.
 */
bool ANN::prime_input(istream &stream) {
  double tmp;
  for (vector<Node*>::iterator it = ann_i.begin() ; it != ann_i.end(); ++it) {
    stream >> tmp;
    (*it)->m_weight = tmp;
  }
  return true;
}

/*
void Node::Calculate_layers() {
    // Calculate activation function.
    for (int i = 0; i < data_vector.size(); i++) {
        DataNode *tmp = data_vector[i];
        double weight = (*tmp).node_weight;
        weight = 1.0 / (1.0 + pow(e, (-weight)));
        (*tmp).node_weight = weight;

        // Preform activation across hidden layers.
        if (i < (*hidden_layers.end())) {
            for (int j = 0; j < (*tmp).edge_weight.size(); j++) {
                DataNode *hidden_node = (*tmp).input_edges[j];
                (*hidden_node).node_weight = (*hidden_node).node_weight + (*tmp).node_weight * (*tmp).edge_weight[j];
            }
        }
        // Preform activation to output layer.
        else {
            for (int j = 0; j < (*tmp).edge_weight.size(); j ++) {
                OutputNode *output_node = (*tmp).output_edges[j];
                (*output_node).node_weight = (*output_node).node_weight + (*tmp).node_weight * (*tmp).edge_weight[j];
            }
        }
    }

    for (int i = 0; i < output_vector.size(); i++) {
        OutputNode *tmp = output_vector[i];
        double weight = (*tmp).node_weight;
        weight = 1.0 / (1.0 + pow(e, (-weight)));
        (*tmp).node_weight = weight;
    }
}*/


bool ANN::run_test() {
  bool passed = input_to_hidden();
  if (passed) {
    passed = hidden_to_hidden();
    if (passed) {
      passed = hidden_to_output();
      if (passed) {
        return true;
      }
      emergency_exit("Hidden to Output");
    }
    emergency_exit("Hidden to Hidden");
  }
  emergency_exit("Input to Hidden");
}

bool ANN::input_to_hidden() {
  for (int i = 0; i < m_hidden_size; i++) {
    double sums;
    for (int j = 0; j < ann_i.size(); j++) {
      sums += ann_i[j].m_edgeWeight[i] * ann_i[j].m_weight;
    }
    sums += ann_h[i].m_weight;
    double sigmoid = 1.0 / (1.0 + pow(e, (-sums)));
    ann_h[i].m_weight = sigmoid;
  }
  return true;
}

bool ANN::hidden_to_hidden() {
  int l = m_hidden_layers, s = m_hidden_size;
  for (int i = 1; i < l; i++) {
    for (int j = 0; j < s; j++) {
      double sums;
      for (int k = 0; k < s; k++) {
        sums += ann_h[(i-1)*s + k].m_edgeWeight[j] * ann_h[(i-1)*s + k].m_weight;
      }
      sums += ann_h[i*s + j].m_weight;
      double sigmoid = 1.0 / (1.0 + pow(e, (-sums)));
      ann_h[i*s + j].m_weight = sigmoid;
    }
  }
  return true;
}

bool ANN::hidden_to_output() {
  int l = m_hidden_layers, s = m_hidden_size, o = m_output_size;
  for (int i = 0; i < o; i++) {
    double sums;
    for (int j = 0; j < s; j++) {
      sums += ann_h[(l-1)*s+j].m_edgeWeight[i] * ann_h[(l-1)*s+j].m_weight;
    }
    sums += ann_o[i].m_weight;
    double sigmoid = 1.0 / (1.0 + pow(e, (-sums)));
    ann_o[i].m_weight = sigmoid;
  }
  return true;
}

void ANN::emergency_exit(string error_message) {
  ~ANN();
  cout << "Error located in: " << error_message << endl;
  exit (1);
}
