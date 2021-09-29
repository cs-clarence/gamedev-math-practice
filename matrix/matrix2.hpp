#include <cstdint>
#include <initializer_list>
#include <type_traits>

template<uint64_t rows, uint64_t cols, class Type = float>
class matrix2
{
  static_assert(
    std::is_arithmetic_v<Type>,
    "matrix2: the paramter 'Type' should be an arithmetic type");

private:
  Type _mat[rows][cols];

public:
  matrix2() = default;
  explicit matrix2(std::initializer_list<std::initializer_list<Type>> init);

  static constexpr uint64_t cols_size = cols;
  static constexpr uint64_t rows_size = rows;

  matrix2<cols, rows, Type> transpose();
  Type &operator()(uint64_t row, uint64_t col);
  const Type &operator()(uint64_t row, uint64_t col) const;
};

#include "./matrix2.inl"
