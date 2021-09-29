#include <cmath>
#include <cstdint>
#include <stdexcept>

struct vector3
{
  float x = 0.f, y = 0.f, z = 0.f;

  vector3() = default;
  explicit vector3(float x) : x(x) {}
  explicit vector3(float x, float y) : x(x), y(y) {}
  explicit vector3(float x, float y, float z) : x(x), y(y), z(z) {}

  float magnitude();

  vector3 normalize();

  const float &operator[](uint64_t index);
};

#include "./vector3.inl"
