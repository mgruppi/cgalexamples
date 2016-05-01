//Round-off errors

#include <iostream>
#include <CGAL/Simple_cartesian.h>

#include <CGAL/IO/Geomview_stream.h>
#include <CGAL/IO/Triangulation_geomview_ostream_2.h>
#include <CGAL/IO/Triangulation_geomview_ostream_3.h>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <sstream>
typedef CGAL::Exact_predicates_exact_constructions_kernel Kexact;
typedef Kexact::Point_2 Point_2_exact;


typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_2 Point_2_double;
typedef Kernel::Segment_2 Segment_2_double;


using namespace std;
int main()
{
  Point_2_double p(1,1), q(10,10);
  std::cout << "p = " << p << std::endl;
  std::cout << "q = " << q.x() << " " << q.y() << std::endl;

  Segment_2_double s(p,q);
  Point_2_double m(5, 9);

  cout << "m = " << m << endl;


  //Start geomview with bounding box
  CGAL::Geomview_stream gv(CGAL::Bbox_3(-20, -20, -20, 20, 20, 20));

  //White bg color
  gv.set_line_width(4);
  gv.set_bg_color(CGAL::Color(0, 200, 200));

  gv << CGAL::BLUE;
  gv << p << q << m;

  Segment_2_double pq(p,q);
  Segment_2_double qm(q,m);
  gv << CGAL::RED;
  gv << pq << qm;


  std::cout << "p, q, and m ";
  switch (CGAL::orientation(p,q,m)){
  case CGAL::COLLINEAR:
    std::cout << "are collinear\n";
    break;
  case CGAL::LEFT_TURN:
    std::cout << "make a left turn\n";
    break;
  case CGAL::RIGHT_TURN:
    std::cout << "make a right turn\n";
    break;
  }

cout << "Press key to continue...\n";
cin.get();


cout << "Using a <double> Kernel:\n";
{
  Point_2_double p(0, 0.3), q(1, 0.6), r(2, 0.9);
  cout << p << " " << q << " " << r;
  gv.clear();
  gv << p << q << r;
  cin.get();
  std::cout << (CGAL::collinear(p,q,r) ? "collinear\n" : "not collinear\n");
}
{
  Point_2_double p(0, 1.0/3.0), q(1, 2.0/3.0), r(2, 1);
  cout << p << " " << q << " " << r;
  gv.clear();
  gv << p << q << r;
  cin.get();
  std::cout << (CGAL::collinear(p,q,r) ? "collinear\n" : "not collinear\n");
}
{
  Point_2_double p(0,0), q(1, 1), r(2, 2);
  cout << p << " " << q << " " << r;
  gv.clear();
  gv << p << q << r;
  cin.get();
  std::cout << (CGAL::collinear(p,q,r) ? "collinear\n" : "not collinear\n");
}


cout << "Using exact Kernel:\n";
{
  Point_2_exact p(0, 0.3),q, r(2, 0.9);
  q = CGAL::midpoint(p,r);
  cout << p << " " << q << " " << r;
  gv.clear();
  gv << p << q << r;
  cin.get();
  std::cout << (CGAL::collinear(p,q,r) ? "collinear\n" : "not collinear\n");
}


cout << "\nFinished...\n";
cin.get();

  return 0;
}
