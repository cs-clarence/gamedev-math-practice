#include "./matrix/matrix2.hpp"
#include "./vector/vector.hpp"

#define PRINT_EXPRESSION(expression) \
  std::cout << #expression << ": \n" << expression << "\n" << std::endl

int main()
try
{
  vector<2> v1 {1, 2};
  vector<2> v2 {2, 1};

  PRINT_EXPRESSION(v1);
  PRINT_EXPRESSION(v1 + v1);
  PRINT_EXPRESSION(dot(v1, v1));
  PRINT_EXPRESSION(dot(v1.normalize(), v1.normalize()));
  PRINT_EXPRESSION(v1.magnitude());
  PRINT_EXPRESSION(v1.normalize());
  PRINT_EXPRESSION(v1.normalize().magnitude());
  PRINT_EXPRESSION(cross(v1, v2));

  matrix2<3, 3> mat {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  PRINT_EXPRESSION(mat);

  auto matT = mat.transpose();
  PRINT_EXPRESSION(matT);
  PRINT_EXPRESSION(mat * matT);

  return 0;
}
catch (std::length_error &err)
{
  std::cerr << err.what() << std::endl;
}
catch (std::out_of_range &err)
{
  std::cerr << err.what() << std::endl;
}
catch (...)
{
  std::cerr << "caught an unkown error" << std::endl;
}
