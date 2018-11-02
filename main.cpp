#include "ANN.h"
#include <fstream>

int main(int argc, char const *argv[]) {
  bool testing_save = false; //Set to true for testing save/load.

  if (testing_save) {
    int test_array[4] = {4, 5, 5, 4};
    for (size_t i = 0; i < 4; i++) {
      std::cout << test_array[i] << " ";
    }
    std::cout << std::endl;

    ANN* ann = new ANN(test_array);
    std::vector<double> inputs_1 = { 0.526, 0.485, 0.127, 0.852 };
    std::vector<double> inputs_2 = { 0.321, 0.589, 0.721, 0.159 };

    ann->prime_input(inputs_1);
    ann->run_test();
    ann->save_state("save_file_1.txt");

    ann->prime_input(inputs_2);
    ann->run_test();
    ann->save_state("save_file_2.txt");

    ann->load_state("save_file_1.txt");
    ann->save_state("save_file_3.txt");

    delete ann;
  }
  else {
    int test_array[4] = {2, 1, 1, 1};
    for (size_t i = 0; i < 4; i++) {
      std::cout << test_array[i] << " ";
    }
    std::cout << std::endl;
    ANN* ann = new ANN(test_array);
    std::string test_stream = argv[1];
    std::fstream fs;
    fs.open (test_stream, std::fstream::in);
    ann->testing_cycle(fs);
  }

  return 0;
}
