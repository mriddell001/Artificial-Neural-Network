#include "Node.h"
#include <vector>

using namespace std;

/**
 * ~Node - This is the deconstructor for the class Node. By using shrink_to_fit,
 *         unlike erase or clear, the memory allocated is released. This process
 *         confirms data is released and sets vectors to a null pointer.
 */
Node::~Node() {
  while (m_edges.capacity()) {
    m_edges.shrink_to_fit();
  }
  while (m_edgeWeight.capacity()) {
    m_edgeWeight.shrink_to_fit();
  }
}
