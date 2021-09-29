#include <cmath>
#include <cstdint>
#include <stdexcept>

struct vector2
{
  float x = 0.f, y = 0.f;

  vector2() = default;
  explicit vector2(float x) : x(x) {}
  explicit vector2(float x, float y) : x(x), y(y) {}

  float magnitude();

  vector2 normalize();

  const float &operator[](uint64_t index);
};

#include "./vector2.inl"
