#include <cmath>
#include <functional>
#include <stdexcept>

// ctors
template<uint64_t size, class Type>
inline vector<size, Type>::vector(std::initializer_list<Type> initlist)
{
  if (initlist.size() > size)
  {
    throw std::length_error("vector: the number of elements in the initializer "
                            "is greater than the size "
                            "of the vector");
  }

  uint64_t i = 0;
  for (const auto &el : initlist) { this->_arr[i++] = el; }
}

// member operator overloads for vector_base
template<uint64_t size, class Type>
inline Type &vector<size, Type>::operator[](uint64_t index)
{
  return const_cast<Type &>(
    static_cast<const std::remove_pointer_t<decltype(this)> &>(*this)[index]);
}

template<uint64_t size, class Type>
inline const Type &vector<size, Type>::operator[](uint64_t index) const
{
  if (index >= size) throw std::out_of_range("invalid index");
  return this->_arr[index];
}

// method implementations for vector
// get the length/magnitude of the vector
template<uint64_t size, class Type>
Type vector<size, Type>::magnitude() const
{
  Type sum {};
  for (uint64_t i = 0; i < size; ++i) { sum += std::pow(this->_arr[i], 2); }
  return std::sqrt(sum);
}

// get the unit vector from this instance
template<uint64_t size, class Type>
inline vector<size, Type> vector<size, Type>::normalize() const
{
  return _vtr2scr_bin_op<size, Type>(
    *this, this->magnitude(), std::divides<Type>());
}

// Free helper functions for vector
// Vector to Scalar Binary Operation Helper Function
template<uint64_t size, class Type>
vector<size, Type> _vtr2scr_bin_op(
  const vector<size, Type> &v, Type scalar, std::function<Type(Type, Type)> op)
{
  vector<size, Type> res;
  for (uint64_t i = 0; i < size; ++i) { res[i] = op(v[i], scalar); }
  return res;
}

template<class Type>
vector<1, Type> _vtr2scr_bin_op(
  const vector<1, Type> &v, Type scalar, std::function<Type(Type, Type)> op)
{
  return vector<1, Type> {op(v.x(), scalar)};
}

template<class Type>
vector<2, Type> _vtr2scr_bin_op(
  const vector<2, Type> &v, Type scalar, std::function<Type(Type, Type)> op)
{
  return vector<2, Type> {op(v.x(), scalar), op(v.y(), scalar)};
}

template<class Type>
vector<3, Type> _vtr2scr_bin_op(
  const vector<3, Type> &v, Type scalar, std::function<Type(Type, Type)> op)
{
  return vector<3, Type> {
    op(v.x(), scalar), op(v.y(), scalar), op(v.z(), scalar)};
}

// Vector Binary Operation Helper Function
template<uint64_t size, class Type>
vector<size, Type> _vtr_bin_op(
  const vector<size, Type> &v1,
  const vector<size, Type> &v2,
  std::function<Type(Type, Type)> op)
{
  vector<size, Type> res;
  for (uint64_t i = 0; i < size; ++i) { res[i] = op(v1[i], v2[i]); }
  return res;
}

template<class Type>
vector<1, Type> _vtr_bin_op(
  const vector<1, Type> &v1,
  const vector<1, Type> &v2,
  std::function<Type(Type, Type)> op)
{
  return vector<1, Type> {op(v1.x(), v2.x())};
}

template<class Type>
vector<2, Type> _vtr_bin_op(
  const vector<2, Type> &v1,
  const vector<2, Type> &v2,
  std::function<Type(Type, Type)> op)
{
  return vector<2, Type> {op(v1.x(), v2.x()), op(v1.y(), v2.y())};
}

template<class Type>
vector<3, Type> _vtr_bin_op(
  const vector<3, Type> &v1,
  const vector<3, Type> &v2,
  std::function<Type(Type, Type)> op)
{
  return vector<2, Type> {
    op(v1.x(), v2.x()), op(v1.y(), v2.y()), op(v1.z(), v2.z())};
}

// Vector Binary Operation Helper Function
template<uint64_t size, class Type>
vector<size, Type>
_vtr_una_op(const vector<size, Type> &v, std::function<Type(Type)> op)
{
  vector<size, Type> res;
  for (uint64_t i = 0; i < size; ++i) { res[i] = op(v[i]); }
  return res;
}

template<class Type>
vector<1, Type>
_vtr_una_op(const vector<1, Type> &v, std::function<Type(Type)> op)
{
  return vector<1, Type> {op(v.x())};
}

template<class Type>
vector<2, Type>
_vtr_una_op(const vector<2, Type> &v, std::function<Type(Type)> op)
{
  return vector<2, Type> {op(v.z()), op(v.y())};
}

template<class Type>
vector<3, Type>
_vtr_una_op(const vector<3, Type> &v, std::function<Type(Type)> op)
{
  return vector<3, Type> {op(v.z()), op(v.y()), op(v.z())};
}

// Free operator overloads
template<uint64_t size, class Type>
inline vector<size, Type> operator*(const vector<size, Type> &v, Type scalar)
{
  return _vtr2scr_bin_op<size, Type>(v, scalar, std::multiplies<Type>());
}

template<uint64_t size, class Type>
inline vector<size, Type> operator*=(vector<size, Type> &v, Type scalar)
{
  return v = v * scalar;
}

template<uint64_t size, class Type>
inline vector<size, Type> operator/(const vector<size, Type> &v, Type scalar)
{
  return _vtr2scr_bin_op<size, Type>(v, scalar, std::divides<Type>());
}

template<uint64_t size, class Type>
inline vector<size, Type> operator/=(vector<size, Type> &v, Type scalar)
{
  return v = v / scalar;
}

template<uint64_t size, class Type>
inline vector<size, Type>
operator+(const vector<size, Type> &v1, const vector<size, Type> &v2)
{
  return _vtr_bin_op<size, Type>(v1, v2, std::plus<Type>());
}

template<uint64_t size, class Type>
inline vector<size, Type>
operator+=(vector<size, Type> &v1, const vector<size, Type> &v2)
{
  return v1 = v1 + v2;
}

template<uint64_t size, class Type>
inline vector<size, Type>
operator-(const vector<size, Type> &v1, const vector<size, Type> &v2)
{
  return _vtr_bin_op<size, Type>(v1, v2, std::minus<Type>());
}

template<uint64_t size, class Type>
inline vector<size, Type>
operator-=(vector<size, Type> &v1, const vector<size, Type> &v2)
{
  return v1 = v1 + v2;
}

template<uint64_t size, class Type>
inline vector<size, Type> operator-(const vector<size, Type> &v)
{
  return _vtr_una_op<size, Type>(v, std::negate<Type>());
}

// Dot product function for vector class, general case
// one use for dot product is to measure how alike two vectors are
// it is used in tandem with unit vectors
// if the dot product of two unit vectors is 1, then they are parallel (pointing
// to the same direction) if -1 then parallel but the other is pointing to the
// other direction if 0 then they are perpendicular (90 degree in planar angle)
// in general, if the angle between the two angles is greather than 90 degrees,
// then the result is a negative number if less than 90 degrees, the result is a
// positive number
template<uint64_t size, class Type>
Type dot(const vector<size, Type> &v1, const vector<size, Type> &v2)
{
  Type sum {};
  for (uint64_t i = 0; i < size; ++i) sum += v1[i] * v2[i];
  return sum;
}

// faster dot function overload for vector<1>
template<class Type>
inline Type dot(const vector<1, Type> &v1, const vector<1, Type> &v2)
{
  return v1.x() * v2.x();
}

// faster dot function overload for vector<2>
template<class Type>
inline Type dot(const vector<2, Type> &v1, const vector<2, Type> &v2)
{
  return v1.x() * v2.x() + v1.y() * v2.y();
}

// faster dot function overload for vector<3>
template<class Type>
inline Type dot(const vector<3, Type> &v1, const vector<3, Type> &v2)
{
  return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
}

// helper function for cross(), moves and index forward but also wraps-around if
// index goes beyond the boundary
inline uint64_t _move_forward_wrap(uint64_t index, size_t size)
{
  return (index + 1) % (size);
}

// Cross product function for vector class, general case
template<uint64_t size, class Type>
vector<size, Type>
cross(const vector<size, Type> &v1, const vector<size, Type> &v2)
{
  vector<size, Type> v {};
  uint64_t i = 0;
  uint64_t j = _move_forward_wrap(i, size);
  uint64_t k = _move_forward_wrap(j, size);

  while (i < size)
  {
    v[i++] = v1[j] * v2[k] - v1[k] * v2[j];

    j = _move_forward_wrap(i, size);
    k = _move_forward_wrap(j, size);
  }
  return v;
}

// faster cross() implementation for vector<1>
template<class Type>
vector<1, Type> cross(const vector<1, Type> &v1, const vector<1, Type> &v2)
{
  return vector<1, Type> {v1.x() * v2.x() - v1.x() * v2.x()};
}

// faster cross() implementation for vector<2>
template<class Type>
vector<2, Type> cross(const vector<2, Type> &v1, const vector<2, Type> &v2)
{
  return vector<2, Type> {
    v1.y() * v2.x() - v1.x() * v2.y(), v1.x() * v2.y() - v1.y() * v2.x()};
}

// faster cross() implementation for vector<3>
template<class Type>
vector<3, Type> cross(const vector<3, Type> &v1, const vector<3, Type> &v2)
{
  return vector<3, Type> {
    v1.y() * v2.z() - v1.z() * v2.y(),
    v1.z() * v2.x() - v1.x() * v2.z(),
    v1.x() * v2.y() - v1.y() * v2.x(),
  };
}

// cout insertion operator overload
template<uint64_t size, class Type>
std::ostream &operator<<(std::ostream &out, const vector<size, Type> &v)
{
  std::cout << "[";
  for (uint64_t i = 0; i < size; ++i)
  {
    std::cout << v[i] << (i == size - 1 ? "" : ", ");
  }
  std::cout << "]";
  return out;
}
