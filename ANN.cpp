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
#include <memory>
#include <utility>
#include <vector>

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
ANN::ANN(int in[]) {
  m_input_size = in[0];
  m_hidden_layers = in[1];
  m_hidden_size = in[2];
  m_output_size = in[3];

  bool init_success = init();
  if(!init_success) {
    std::cout << "There has been a problem with the init function.\n";
  }
  else {
    std::cout << "There has been no problems with the init function.\n";
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
  while (ann_i.capacity()) {
    ann_i.resize(0);
    ann_i.shrink_to_fit();}
  while (ann_h.capacity()) {
    ann_h.resize(0);
    ann_h.shrink_to_fit();}
  while (ann_o.capacity()) {
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
 * Testing status: Untested.
 */
bool ANN::init() {
  int a = m_input_size, b = m_hidden_size,
      c = m_output_size, d = m_hidden_layers;

  input_layer_creation(a);
  hidden_layer_creation(b,d);
  output_layer_creation(b,c,d);
  return true;
}

void ANN::input_layer_creation(int a) {
  ///For each node in the input layer.
  std::cout << "Input Layer Creation" << std::endl;
  for (int i = 0; i < a; i++) {
    std::shared_ptr<Node*> tmp = std::make_shared<Node*>();
    ann_i.push_back(std::move(tmp));
  }
}

//Error in hidden_layer_creation!!
void ANN::hidden_layer_creation(int b, int d) {
  //For each hidden layers.
  std::cout << "Hidden Layer Creation" << std::endl;
  for (int i = 0; i < d; i++) {
    ///For each node in a hidden layer.
    for (int j = 0; j < b; j++) {
      std::shared_ptr<Node*> tmp = std::make_shared<Node*>();
      ann_h.push_back(std::move(tmp));
      if (i) {
        int l = (i - 1) * b;
        ///For each node in a hidden layer, add the newly created node to the
        ///vector of edges of the previous layer.
        for (int k = 0; k < b; k++) {
          std::shared_ptr<Node*> pmt (ann_h[l+k]);
          (*pmt)->m_edges.push_back(std::move(tmp));
          (*pmt)->m_edgeWeight.push_back(0.5);
        }
      }
      else {
        ///For each node in the input layer, add the newly created node to the
        ///vector of edges.
        for (std::vector<std::shared_ptr<Node*> >::iterator it = ann_i.begin() ; it != ann_i.end(); ++it) {
          (**it)->m_edges.push_back(std::move(tmp));
          (**it)->m_edgeWeight.push_back(0.5);
        }
      }
    }
  }
}

void ANN::output_layer_creation(int b, int c, int d) {
  std::cout << "Output Layer Creation" << std::endl;
  int l = (d*b)-b;
  ///For each node in the output layer.
  for (int i = 0; i < c; i++) {
    std::shared_ptr<Node*> tmp = std::make_shared<Node*>();
    ann_o.push_back(std::move(tmp));
    ///For each node in the last hidden layer.
    for (int j = 0; j < b; j++) {
      std::shared_ptr<Node*> pmt (ann_h[l+j]);
      (*pmt)->m_edges.push_back(std::move(tmp));
      (*pmt)->m_edgeWeight.push_back(0.5);
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
