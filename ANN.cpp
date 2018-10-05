/*
Filename: ANN.cpp
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
#include <utility>
#include <vector>

/**
 * ANN - This function serves as the constructor for the ANN object. It sets the
 *    four basic size values: input, hidden, output, hidden layers. It calls the
 *    init() function afterwards and checks that it executed sucessfully.
 *
 * Parameters:
 *  INT ARRAY in: This contains the four values for building the ANN.
 *              0: Size of the input layer.
 *              1: Size of the hidden layers.
 *              2: Size of the output layer.
 *              3: Number of hidden layers.
 *
 * Assumptions: This function assumes the int array argument contains four valid
 *    integer values to be set.
 *
 * Testing status: Tested. 10-4-18
 */
ANN::ANN(int in[]) {
  m_input_size = in[0];
  m_hidden_layers = in[1];
  m_hidden_size = in[2];
  m_output_size = in[3];

  std::cout << ((init()) ? "init() exited with no errors" : "init() failed to execute!") << std::endl;
}

/**
 * ~ANN - This function serves as the deconstructor for the ANN object. It runs
 *    a for loop itterating through each vector (input/hidden/output) and calls
 *    to delete each Node pointer.
 *
 * Assumptions: This function assumes the delete function is called successfully
 *
 * Testing status: Tested. 10-4-18
 */
ANN::~ANN() {
//<<<<<<< HEAD
  while (ann_i.capacity()) {
    ann_i.resize(0);
    ann_i.shrink_to_fit();}
  while (ann_h.capacity()) {
	  ann_h.resize(0);
    ann_h.shrink_to_fit();}
  while (ann_o.capacity()) {
//=======
//  while(ann_i.capacity()) {
//    ann_i.resize(0);
//    ann_i.shrink_to_fit();}
//  while(ann_h.capacity()) {                              what are these? they give me syntax errors
//    ann_h.resize(0);
//    ann_h.shrink_to_fit();}
//  while(ann_o.capacity()) {
//>>>>>>> 2189c49575453157d3a90009a039d7d5bf5921d1
    ann_o.resize(0);
    ann_o.shrink_to_fit();}
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
 * Returns BOOLEAN: Currently serves as proof it has completed.
 *
 * Testing status: Functioning.
 */
bool ANN::init() {

  input_layer_creation(m_input_size);
  hidden_layer_creation(m_hidden_size, m_hidden_layers);
  output_layer_creation(m_hidden_size, m_output_size, m_hidden_layers);
  return true;
}

/*
 * input_layer_creation - This function serves to initialize the input nodes in
 *                        the ANN.
 *
 * Parameters:
 *    INT a: The size of the input layer.
 *
 * Assumptions: On start, this function assumes there are valid values for the
 * size of the input layer. On finish, it is to be assumed that the input layer
 * has been completely initialized and the input layer is set and can be
 * accessed. At this point, there are no edges to other layers, since no other
 * layers exist at this time;
 *
 * Testing status: Functioning.
 */
void ANN::input_layer_creation(int a) {
  for (int i = 0; i < a; i++) {
    Node* tmp = new Node();
    ann_i.push_back(tmp);
  }
}

/*
 * hidden_layer_creation - This function serves to initialize the hidden nodes
 *                         in the ANN. It connects each hidden node to all the
 *                         nodes in the previous layer.
 *
 * Parameters:
 *    INT b: The size of each hidden layer.
 *    INT c: The number of the hidden layers.
 *
 * Assumptions: On start, this function assumes there are valid values for the
 * size of the layers and the number of nodes in a hidden layer. On finish, it
 * is to be assumed that the hidden layers have been completely initialized and
 * the edges between each previous layer are currently connected and can be
 * traversed/accessed.
 *
 * Testing status: Functioning.
 */
void ANN::hidden_layer_creation(int b, int c) {
  for (int i = 0; i < c; i++) {
    for (int j = 0; j < b; j++) {
      Node* tmp = new Node();
      ann_h.push_back(tmp);
      if (i) {
        int l = (i - 1) * b;
        for (int k = 0; k < b; k++) {
          Node* pmt = ann_h[l+k];
          (*pmt).m_edges.push_back(tmp);
          (*pmt).m_edgeWeight.push_back(0.5);
        }
      }
      else {
        for (int i = 0; i < ann_i.size(); i++) {
          ann_i[i]->m_edges.push_back(tmp);
          ann_i[i]->m_edgeWeight.push_back(0.5);
        }
      }
    }
  }
}

/*
 * output_layer_creation - This function serves to initialize the hidden nodes
 *                         in the ANN. It connects each hidden node to all the
 *                         nodes in the previous layer.
 *
 * Parameters:
 *    INT b: The size of each hidden layer.
 *    INT c: The size of the output layer.
 *    INT d: The number of the hidden layers.
 *
 * Assumptions: On start, this function assumes there are valid values for the
 * size of the layers and the number of nodes in a hidden layer. On finish, it
 * is to be assumed that the output layers have been completely initialized and
 * the edges between each previous layer are currently connected and can be
 * traversed/accessed.
 *
 * Testing status: Functioning.
 */
void ANN::output_layer_creation(int b, int c, int d) {
  int l = (d*b)-b;
  for (int i = 0; i < c; i++) {
    Node* tmp = new Node();
    ann_o.push_back(tmp);
    for (int j = 0; j < b; j++) {
      Node * pmt = ann_h[l+j];
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
void ANN::auto_refine(std::istream &instream, std::ostream &outstream) {
  /*
  priority_queue<std::pair<double, std::string> > tests;
  std::string t, error_loc;
  double error_target;
  instream >> error_target;
  while(instream >> t) {
    tests.push(std::make_pair(1.0,t));
  }
  while(tests.size()) {
    std::pair<double, std::string> test = tests.top();
    if (test.first <= error_target) {
      tests.pop();
    }
    else {
      tests.pop(); //Remove top record.
      std::ifstream test_stream (test.second, std::ifstream::in); //Open file.
      bool primed = prime_input(test_stream); //Prime input.
      if(primed) {
        //Run test.
        bool tested = run_test();
        if (tested) {
          //Measure distance.
          double e_dist = elucidian_distance(test_stream);
          if (e_dist > error_target) {
            //Backtracking.
            bool updated = backtracking(e_dist);
            //Update Error
            //Push
          }
        }
      }
      else {
        while(tests.size()) {tests.pop();}
        error_loc = "Priming";
        emergency_exit(error_loc);
      }
    }

  }
  */
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
bool ANN::prime_input(std::istream &stream) {
  /*
  double tmp;
  for (std::vector<Node*>::iterator it = ann_i.begin() ; it != ann_i.end(); ++it) {
    stream >> tmp;
    (*it)->m_weight = tmp;
  }
  return true;
  */
  return true;
}

bool ANN::run_test() {
  /*
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
  */
  return true;
}

bool ANN::input_to_hidden() {
  /*
  for (int i = 0; i < m_hidden_size; i++) {
    double sums;
    for (int j = 0; j < ann_i.size(); j++) {
      sums += ann_i[j].m_edgeWeight[i] * ann_i[j].m_weight;
    }
    sums += ann_h[i].m_weight;
    double sigmoid = 1.0 / (1.0 + pow(e, (-sums)));
    ann_h[i].m_weight = sigmoid;
  }
  */
  return true;
}

bool ANN::hidden_to_hidden() {
  /*
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
  */
  return true;
}

bool ANN::hidden_to_output() {
  /*
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
  */
  return true;
}

double ANN::elucidian_distance(std::istream &stream) {
  /*
  double sum, tmp;
  std::vector<double> diffs;
  for (std::vector<Node*>::iterator it = ann_o.begin() ; it != ann_o.end(); ++it) {
    stream >> tmp;
    double diff = tmp - (*it)->m_weight;
    diffs.push_back(diff*diff);
  }

  for (int i = 0; i < diffs.size(); i++) {
    sum += diffs;
  }
  double error = sqrt(sum);
  return error;
  */
  return 0.0;
}

bool ANN::backpropagation(double err) {

  return true;
}

bool ANN::back_output_to_hidden(double err) {
  return true;
}

bool ANN::back_hidden_to_hidden(double err) {
  return true;
}

bool ANN::back_hidden_to_input(double err) {
  return true;
}

void ANN::emergency_exit(std::string error_message) {
  //~ANN();
  std::cout << "Error located in: " << error_message << std::endl;
  exit (1);
}

void ANN::print() {
  for (int i = 0; i < m_input_size; i++) {
    std::cout << "Input Node[" << i << "] connections:" << std::endl;
    for (int j = 0; j < m_hidden_size; j++) {
      if (ann_i[i]->m_edges[j] == ann_h[j]) {
        std::cout << "\tann_h[" << j << "] - confirmed" << std::endl;
      }
    }
  }
}
