#ifndef SHSML_HPP_
#define SHSML_HPP_

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

template <typename T> class SparseMatrix {
public:
  void print();
  virtual T get(int i, int j);
  virtual void set(int i, int j, T element);
  virtual void clear();
  virtual std::vector<T> operator*(std::vector<T> x);

protected:
  int cols, rows;
  std::vector<T> values;
};

template <typename T> class COOMatrix : public SparseMatrix<T> {
public:
  COOMatrix(int cols, int rows);
  void set(int col, int row, T element);
  T get(int i, int j);
  std::vector<T> operator*(std::vector<T> x);

private:
  using SparseMatrix<T>::values;
  std::vector<int> rowsIndices;
  std::vector<int> colsIndices;
};

#define SHSML_IMPLEMENTATION

#ifdef SHSML_IMPLEMENTATION
template <typename T> T SparseMatrix<T>::get(int, int) {
  std::cout << "No data format choosen!" << std::endl;
  return 0;
}

template <typename T> void SparseMatrix<T>::set(int, int, T) {
  std::cout << "No data format choosen!" << std::endl;
}

template <typename T> void SparseMatrix<T>::clear() {
  std::cout << "No data format choosen!" << std::endl;
}

template <typename T>
std::vector<T> SparseMatrix<T>::operator*(std::vector<T> x) {
  std::cout << "No data format choosen!" << std::endl;
}

template <typename T> void SparseMatrix<T>::print() {
  if (values.empty()) {
    std::cout << "Empty matrix" << std::endl;
    return;
  }

  const int maxDisplay = 10;        // Maximum number of rows/columns to display
  const std::string ellipsis = "…"; // Unicode ellipsis character

  // Determine if truncation is needed
  bool truncateRows = rows > maxDisplay;
  bool truncateCols = cols > maxDisplay;

  // Calculate how many rows/cols to show
  int showRows = truncateRows ? maxDisplay : rows;
  int showCols = truncateCols ? maxDisplay : cols;

  for (int i = 0; i < rows; i++) {
    // Skip middle rows if truncating
    if (truncateRows && i >= maxDisplay / 2 && i < rows - maxDisplay / 2) {
      if (i == maxDisplay / 2) {
        std::cout << std::string(4, ' ') << ellipsis << std::endl;
      }
      continue;
    }

    std::cout << "[";
    for (int j = 0; j < cols; j++) {
      // Skip middle columns if truncating
      if (truncateCols && j >= maxDisplay / 2 && j < cols - maxDisplay / 2) {
        if (j == maxDisplay / 2) {
          std::cout << " " << ellipsis << " ";
        }
        continue;
      }

      std::cout << std::setw(4) << get(i, j);

      // Add appropriate spacing
      if (j < cols - 1 && !(truncateCols && j == maxDisplay / 2 - 1)) {
        std::cout << " ";
      }
    }
    std::cout << " ]" << std::endl;
  }
  std::cout << values.size() << std::endl;
}

template <typename T> COOMatrix<T>::COOMatrix(int cols, int rows) {
  this->cols = cols;
  this->rows = rows;
}

template <typename T> void COOMatrix<T>::set(int col, int row, T element) {
  auto it = std::find_if(
      values.begin(), values.end(), [&, idx = -1](const auto &) mutable {
        idx++;
        return rowsIndices[idx] == row && colsIndices[idx] == col;
      });

  if (it != values.end()) {
    // Update the existing value
    int index = std::distance(values.begin(), it);
    values[index] = element;
    // Ignore if the value becomes zero
    if (element == (T)0) {
      rowsIndices.erase(rowsIndices.begin() + index, rowsIndices.end());
      colsIndices.erase(colsIndices.begin() + index);
      values.erase(values.begin() + index);
    }
    return;
  }

  // If adding results in a non-zero value, add new element
  if (element != (T)0) {
    rowsIndices.push_back(row);
    colsIndices.push_back(col);
    values.push_back(element);
  }
}

template <typename T> T COOMatrix<T>::get(int col, int row) {
  auto it = std::find_if(
      values.begin(), values.end(), [&, idx = -1](const auto &) mutable {
        idx++;
        return rowsIndices[idx] == row && colsIndices[idx] == col;
      });

  if (it != values.end()) {
    return *it;
  }
  return 0;
}

template <typename T> std::vector<T> COOMatrix<T>::operator*(std::vector<T> x) {
  if (x.size() != this->cols) {
    throw std::invalid_argument("Input vector dimension mismatched.");
  }

  std::vector<T> result(this->rows, (T)0);

  // Use for_each to multiply
  std::for_each(values.begin(), values.end(), [&, idx = -1](T value) mutable {
    idx++;
    result[colsIndices[idx]] += value * x[rowsIndices[idx]];
  });

  return result;
}

#endif

#endif // SHSML_HPP_
