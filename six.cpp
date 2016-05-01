#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;
typedef Kernel::Point_2 Point_2;
int main()
{
  Point_2 p(0, 0.3), q, r(2, 0.9);
  {
    q  = Point_2(1, 0.6);
    std::cout << (CGAL::collinear(p,q,r) ? "collinear\n" : "not collinear\n");
  }


  return 0;
}
