//Node.h
#ifndef NODE_H
#define NODE_H

#include <vector>
#include <memory>
#include <random>

class Node {
public:
  Node(){m_weight = gen_rand_num();}; //weights start at a random value rather than 0.5
  ~Node();

  double gen_rand_num(); //function that returns a random value between 0 & 1

  std::vector<std::shared_ptr<Node*> > m_edges;       //Pointers to nodes in next layer.
  std::vector<double> m_edgeWeight; //Weights of paths to nodes in next layer.
  double m_weight;                  //Weight of node. Default: 0.5
};

#endif // Node_H
