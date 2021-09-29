// Free operator overloads for simple vector operations
inline vector2 operator*(const vector2 &v, float scalar)
{
  return vector2(v.x * scalar, v.y * scalar);
}

inline vector2 operator*=(vector2 &v, float scalar) { return v = v * scalar; }

inline vector2 operator/(const vector2 &v, float scalar)
{
  return vector2(v.x / scalar, v.y / scalar);
}

inline vector2 operator/=(vector2 &v, float scalar) { return v = v / scalar; }

inline vector2 operator+(const vector2 &v1, const vector2 &v2)
{
  return vector2(v1.x + v2.x, v1.y + v2.y);
}

inline vector2 operator+=(vector2 &v1, const vector2 &v2)
{
  return v1 = v1 + v2;
}

inline vector2 operator-(const vector2 &v1, const vector2 &v2)
{
  return vector2(v1.x - v2.x, v1.y - v2.y);
}

inline vector2 operator-=(vector2 &v1, const vector2 &v2)
{
  return v1 = v1 - v2;
}

inline vector2 operator-(const vector2 &v) { return vector2(-v.x, -v.y); }

// Member functions
inline float vector2::magnitude()
{
  return std::sqrt(std::pow(this->x, 2) + std::pow(this->y, 2));
}

inline vector2 vector2::normalize() { return *this / this->magnitude(); }

inline const float &vector2::operator[](uint64_t index)
{
  if (index < 0 || index >= 2)
  {
    throw std::out_of_range("vector2 can only accept index of 0 or 1");
  }
  return (&x)[index];
}
