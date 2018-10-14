#include "ANN.h"
#include <fstream>

int main(int argc, char const *argv[]) {
  int test_array[4] = {2, 1, 1, 1};
  for (size_t i = 0; i < 4; i++) {
    std::cout << test_array[i] << " ";
  }
  std::cout << std::endl;

  ANN* ann = new ANN(test_array);

  //For testing purposes.
  if(ann) {
    std::ifstream test_stream ("tests.txt", std::ifstream::in); //Open file.
    ann->testing_cycle(test_stream);
    //ann->print();
  }

  return 0;
}
