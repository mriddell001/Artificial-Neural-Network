#include "ANN.h"
#include <iostream>
#include <memory>

int main(int argc, char const *argv[]) {
  int test_array[4] = {2, 1, 1, 1};
  for (size_t i = 0; i < 4; i++) {
    std::cout << test_array[i] << " ";
  }
  std::cout << std::endl;
  ANN *ann = new ANN(test_array);
  if (ann) {
    std::cout << "Test" << std::endl;
  }
  delete ann;
  return 0;
}
