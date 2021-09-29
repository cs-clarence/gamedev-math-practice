#include <functional>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <type_traits>

// member functions for matrix2
template<uint64_t rows, uint64_t cols, class Type>
matrix2<rows, cols, Type>::matrix2(
  std::initializer_list<std::initializer_list<Type>> init)
{
  if (init.size() > rows)
  {
    throw std::length_error("matrix2: initializer_list number of rows are "
                            "larger than the specified capacity");
  }

  uint64_t i = 0, j = 0;
  for (const auto &row : init)
  {
    if (row.size() > cols)
    {
      throw std::length_error(
        "matrix2: oneinitializer_list number of columns in a row is larger "
        "than the specified capacity");
    }

    j = 0;
    for (const auto col_item : row)
    {
      (*this)(i, j) = col_item;
      ++j;
    }
    ++i;
  }
}

template<uint64_t rows, uint64_t cols, class Type>
matrix2<cols, rows, Type> matrix2<rows, cols, Type>::transpose()
{
  using T = const int &;
  T &x = 5;

  matrix2<cols, rows> mat;

  for (uint64_t row = 0; row < cols; ++row)
    for (uint64_t col = 0; col < rows; ++col)
      mat(row, col) = this->_mat[col][row];

  return mat;
}

template<uint64_t rows, uint64_t cols, class Type>
inline Type &matrix2<rows, cols, Type>::operator()(uint64_t row, uint64_t col)
{
  return const_cast<Type &>(
    static_cast<const std::remove_pointer_t<decltype(this)> &>(*this)(
      row, col));
}

template<uint64_t rows, uint64_t cols, class Type>
inline const Type &
matrix2<rows, cols, Type>::operator()(uint64_t row, uint64_t col) const
{
  // no need to check for 0, it uses uint64_t which is unsigned so no negatives
  if (row >= rows || col >= cols) throw std::out_of_range("invalid index");
  return this->_mat[row][col];
}

// helper matrix2 functions
// boilerplate for doing a simple binary operation on two matrices
template<uint64_t rows, uint64_t cols, class Type>
matrix2<rows, cols, Type> _mtx_bin_op(
  const matrix2<rows, cols, Type> &m1,
  const matrix2<rows, cols, Type> &m2,
  std::function<Type(Type, Type)> op)
{
  matrix2<rows, cols, Type> res;

  for (uint64_t i = 0; i < rows; ++i)
  {
    for (uint64_t j = 0; j < cols; ++j) { res(i, j) = op(m1(i, j), m2(i, j)); }
  }
  return res;
}

// boilerplate for doing a simple unary operation on a matrix2
template<uint64_t rows, uint64_t cols, class Type>
matrix2<rows, cols, Type>
_mtx_una_op(const matrix2<rows, cols, Type> &m, std::function<Type(Type)> op)
{
  matrix2<rows, cols, Type> res;

  for (uint64_t i = 0; i < rows; ++i)
  {
    for (uint64_t j = 0; j < cols; ++j) { res(i, j) = op(m(i, j)); }
  }

  return res;
}

// Helper function for doing a simple binary operation on matrix to scalar
template<uint64_t rows, uint64_t cols, class Type>
matrix2<rows, cols, Type> _mtx2scr_bin_op(
  const matrix2<rows, cols, Type> &m1,
  Type scalar,
  std::function<Type(Type, Type)> op)
{
  matrix2<rows, cols, Type> res;
  for (uint64_t i = 0; i < rows; ++i)
  {
    for (uint64_t j = 0; j < cols; ++j) { res(i, j) = op(m1(i, j), scalar); }
  }
  return res;
}

// basic mathematical operations for matrix
// matrix addition
template<uint64_t rows, uint64_t cols, class Type>
inline matrix2<rows, cols, Type> operator+(
  const matrix2<rows, cols, Type> &m1, const matrix2<rows, cols, Type> &m2)
{
  return _mtx_bin_op<rows, cols, Type>(m1, m2, std::plus<Type>());
}

// matrix subtraction
template<uint64_t rows, uint64_t cols, class Type>
inline matrix2<rows, cols, Type> operator-(
  const matrix2<rows, cols, Type> &m1, const matrix2<rows, cols, Type> &m2)
{
  return _mtx_bin_op<rows, cols, Type>(m1, m2, std::minus<Type>());
}

// matrix-scalar multiplication
template<uint64_t rows, uint64_t cols, class Type>
inline matrix2<rows, cols, Type>
operator*(const matrix2<rows, cols, Type> &m, Type scalar)
{
  return _mtx2scr_bin_op<rows, cols, Type>(m, scalar, std::multiplies<Type>());
}

// matrix multiplication
template<
  uint64_t rows1,
  uint64_t cols1,
  uint64_t rows2,
  uint64_t cols2,
  class Type>
std::enable_if_t<cols1 == rows2, matrix2<rows1, cols2>> operator*(
  const matrix2<rows1, cols1, Type> &m1, const matrix2<rows2, cols2, Type> &m2)
{
  matrix2<rows1, cols2, Type> res;

  for (uint64_t i = 0; i < rows1; ++i)
  {
    for (uint64_t j = 0; j < cols2; ++j)
    {
      Type sum = 0;
      for (uint64_t k = 0; k < cols1; ++k) { sum += m1(i, k) * m2(k, j); }
      res(i, j) = sum;
    }
  }

  return res;
}

// matrix-scalar division
template<uint64_t rows, uint64_t cols, class Type>
inline matrix2<rows, cols, Type>
operator/(const matrix2<rows, cols, Type> &m, Type scalar)
{
  return _mtx2scr_bin_op<rows, cols, Type>(m, scalar, std::divides<Type>());
}

// matrix negation
template<uint64_t rows, uint64_t cols, class Type>
inline matrix2<rows, cols, Type> operator-(const matrix2<rows, cols, Type> &m)
{
  return _mtx_una_op<rows, cols, Type>(m, std::negate<Type>());
}

// cout insertion operator overload
template<uint64_t rows, uint64_t cols, class Type>
std::ostream &
operator<<(std::ostream &out, const matrix2<rows, cols, Type> &mat)
{
  for (uint64_t row = 0; row < rows; ++row)
  {
    for (uint64_t col = 0; col < cols; ++col)
    {
      out << std::setw(8) << std::left << mat(row, col);
    }

    if (row != rows - 1) std::cout << std::endl;
  }
  return out;
}
