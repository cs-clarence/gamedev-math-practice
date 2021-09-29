#include <cstdint>
#include <initializer_list>
#include <type_traits>

// easy writing of type of the context object
// can only be used in instance methods

template<uint64_t size, class Type = float>
class vector
{
private:
  // SFINAE - only allow arithmetic types for this generic
  static_assert(
    std::is_arithmetic_v<Type>,
    "vector: the 'Type' parameter should be an arithmetic type");

  static_assert(size > 0, "vector: the 'size' parameter cannot be zero");

  // Store the data as an array instead of a pointer to an array in the heap
  Type _arr[size] {}; // zero initialize it

public:
  vector() = default;
  vector(std::initializer_list<Type> initlist);
  Type &operator[](uint64_t index);
  const Type &operator[](uint64_t index) const;
  Type magnitude() const;
  vector<size, Type> normalize() const;

  // utility alias template, to be used when culling some template members
  template<uint64_t min, uint64_t max, class U>
  using size_in_range_t = std::enable_if_t<size >= min && size <= max, U>;

  // cullable template members (only template members can be culled)
  // these are alternatives for accessing the array containing the vector's components
  //
  template<class U = Type>
  size_in_range_t<1, 3, U> set_x(Type val)
  {
    return this->_arr[0] = val;
  }

  template<class U = Type>
  size_in_range_t<1, 3, U> x() const
  {
    return this->_arr[0];
  }

  template<class U = Type>
  size_in_range_t<2, 3, U> set_y(Type val)
  {
    return this->_arr[1] = val;
  }

  template<class U = Type>
  size_in_range_t<2, 3, U> y() const
  {
    return this->_arr[1];
  }

  template<class U = Type>
  size_in_range_t<3, 3, U> set_z(Type val)
  {
    return this->_arr[2] = val;
  }

  template<class U = Type>
  size_in_range_t<3, 3, U> z() const
  {
    return this->_arr[2];
  }
};

#include "./vector.inl"
