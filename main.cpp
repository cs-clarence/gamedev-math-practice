#include "./matrix/matrix2.hpp"
#include "./vector/vector.hpp"

#define PRINT_EXPRESSION(expression) \
  std::cout << #expression << ": \n" << expression << "\n" << std::endl

int main()
try
{
  vector<3> v1 {1, 2, 3};
  vector<3> v2 {3, 2, 1};

  PRINT_EXPRESSION(v1);
  PRINT_EXPRESSION(v1 + v1);
  PRINT_EXPRESSION(dot(v1, v1));
  PRINT_EXPRESSION(dot(v1.normalize(), v1.normalize()));
  PRINT_EXPRESSION(v1.magnitude());
  PRINT_EXPRESSION(v1.normalize());
  PRINT_EXPRESSION(v1.normalize().magnitude());
  PRINT_EXPRESSION(cross(v1, v2));
  PRINT_EXPRESSION(
    dot(vector<2> {10.f, 10.f}.normalize(), vector<2> {10.f, 0.f}.normalize()));

  matrix2<3, 3> mat {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  PRINT_EXPRESSION(mat);

  auto matT = mat.transpose();
  PRINT_EXPRESSION(matT);
  PRINT_EXPRESSION(mat * matT);

  matrix2<3, 3> symmetric_matrix {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

  PRINT_EXPRESSION(symmetric_matrix);
  PRINT_EXPRESSION(symmetric_matrix.transpose());

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
