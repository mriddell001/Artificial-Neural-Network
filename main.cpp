#include "ANN.h"

int main(int argc, char const *argv[]) {
  int test_array[4] = {4, 2, 2, 2};
  for (size_t i = 0; i < 4; i++) {
    std::cout << test_array[i] << " ";
  }
  std::cout << std::endl;

  ANN* ann = new ANN(test_array);

  if(ann) {
    ann->print();
  }

  return 0;
}
