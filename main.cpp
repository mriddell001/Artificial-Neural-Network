#include <iostream>
#include <memory>

int main(int argc, char const *argv[]) {
  int test_array[4] = {2, 1, 1, 1};
  std::unique_ptr<ANN> ann = std::make_unique<ANN>(test_array);
  return 0;
}
