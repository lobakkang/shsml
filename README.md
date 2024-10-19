# SHSML
## C++ Single Header Sparse Matrix Library

SHSML is a high-performance, header-only C++ library for sparse matrix operations. It provides an efficient and easy-to-use implementation of common sparse matrix formats and operations, all contained in a single header file for maximum portability.

### Features

- **Header-only**: Just include and use - no compilation or linking required
- **Multiple Matrix Formats**:
  - **COO (Coordinate)**: Optimal for matrix construction and modification
  - **CSR (Compressed Sparse Row)** [WIP]: Efficient for row-oriented operations
  - **CSC (Compressed Sparse Column)** [WIP]: Ideal for column operations and linear solvers
- **Optimized Operations**:
  - Fast matrix-vector multiplication
  - Iterative matrix solvers (Work in Progress)
  - Bulk data processing optimization

### Installation

Simply include the header file in your project:
```cpp
#define SHSML_IMPLEMENTATION
#include <SHSML.hpp>
```

### Quick Example

```cpp
int main(int argc, char *argv[]) {
    // Initialize a 10x8 sparse matrix in COO format
    COOMatrix<int> matrix(10, 8);
    
    // Set some values
    matrix.set(1, 2, 10);
    matrix.set(0, 0, 3);
    matrix.set(2, 0, 2);
    matrix.set(0, 3, 4);
    matrix.set(2, 4, 5);
    
    // Print matrix contents
    matrix.print();
    
    // Perform matrix-vector multiplication
    std::vector<int> x = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> y = matrix * x;
    
    // Display result
    for_each(y.begin(), y.end(), [](int i) { std::cout << i << " "; });
    std::cout << std::endl;
    return 0;
}
```

### Performance

The library is designed with performance in mind, optimizing operations for bulk data processing while maintaining a clean and intuitive interface.

---
Note: Features marked with [WIP] are currently under development.
