#define SHSML_IMPLEMENTATION
#include <SHSML.hpp>

int main(int argc, char *argv[]) {
  COOMatrix<int> matrix(10, 8);
  matrix.set(1, 2, 10);
  matrix.set(0, 0, 3);
  matrix.set(2, 0, 2);
  matrix.set(0, 3, 4);
  matrix.set(2, 4, 5);
  matrix.print();

  std::vector<int> x = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::vector<int> y = matrix * x;

  for_each(y.begin(), y.end(), [](int i) { std::cout << i << " "; });
  std::cout << std::endl;

  return 0;
}
