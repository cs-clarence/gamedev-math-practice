// Free operator overloads
inline vector3 operator*(const vector3 &v, float scalar)
{
  return vector3(v.x * scalar, v.y * scalar, v.z * scalar);
}

inline vector3 operator*=(vector3 &v, float scalar) { return v = v * scalar; }

inline vector3 operator/(const vector3 &v, float scalar)
{
  return vector3(v.x / scalar, v.y / scalar, v.z / scalar);
}

inline vector3 operator/=(vector3 &v, float scalar) { return v = v / scalar; }

inline vector3 operator+(const vector3 &v1, const vector3 &v2)
{
  return vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

inline vector3 operator+=(vector3 &v1, const vector3 &v2)
{
  return v1 = v1 + v2;
}

inline vector3 operator-(const vector3 &v1, const vector3 &v2)
{
  return vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

inline vector3 operator-=(vector3 &v1, const vector3 &v2)
{
  return v1 = v1 - v2;
}

inline vector3 operator-(const vector3 &v) { return vector3(-v.x, -v.y, -v.z); }

// Member functions
inline float vector3::magnitude()
{
  return std::sqrt(
    std::pow(this->x, 2) + std::pow(this->y, 2) + std::pow(this->z, 2));
}

inline vector3 vector3::normalize() { return *this / this->magnitude(); }

inline const float &vector3::operator[](uint64_t index)
{
  if (index < 0 || index >= 3)
  {
    throw std::out_of_range("vector2 can only accept index of 0, 1, or 2");
  }
  return (&x)[index];
}
