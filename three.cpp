//Convex Hull - Delaunay Triangulation - Voronoi Diagram

#include <CGAL/Cartesian.h>
#include <iostream>
#ifndef CGAL_USE_GEOMVIEW
int main()
{
  std::cout << "Geomview doesn't work on Windows, so..." << std::endl;
  return 0;
}
#else
#include <fstream>
#include <unistd.h> // for sleep()
#include <CGAL/Projection_traits_xy_3.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Delaunay_triangulation_3.h>
#include <CGAL/IO/Geomview_stream.h>
#include <CGAL/IO/Triangulation_geomview_ostream_2.h>
#include <CGAL/IO/Triangulation_geomview_ostream_3.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/convex_hull_2.h>
#include <CGAL/convex_hull_3.h>
#include <CGAL/intersections.h>
typedef CGAL::Simple_cartesian<double>  K;
typedef K::Point_2 Point2;
typedef K::Point_3 Point3;
typedef K::Vector_3 Vector3;
typedef CGAL::Delaunay_triangulation_2<K>   Delaunay;
typedef Delaunay::Edge_iterator  Edge_iterator;
typedef Delaunay::Point          Point;
typedef CGAL::Delaunay_triangulation_3<K>   Delaunay3d;
//typedef Gt3::Point Point3;

using namespace std;
int main()
{
  CGAL::Geomview_stream gv(CGAL::Bbox_3(-10, -10, -10, 10, 10, 10));

  Point2 p1(0.0,-1.0), p2(1.0,-1.0), p3(2.0,3.0), p4(1.0,4.0), p5(-3,4), p6(-3,2), p7(-5,1);



  //Point3 pa(1.0,-1.0,0.0), pb(1.0,1.0,1.0),pc(-1,0,1),pd(1,-1,1),pe(-1,-1,-1);


  std::vector<Point2> points;
  std::vector<Point3> points3;
  std::vector<Point2> chull;

  points.push_back(p1);
  points.push_back(p2);
  points.push_back(p3);
  points.push_back(p4);
  points.push_back(p5);
  points.push_back(p6);
  points.push_back(p7);

  //Mkae sure the convex hull will haves pace to store every point
  for(int i = 0;i<points.size();++i) chull.push_back(points[i]);



  gv.set_line_width(2);
  // gv.set_trace(true);
  gv.set_bg_color(CGAL::Color(0, 200, 200));

  gv << CGAL::BLUE;
  for(int i = 0; i < points.size(); ++i) gv << points[i];

  gv << CGAL::RED;
  for(int i =0;i<points3.size();++i) gv << points3[i];

  // CGAL::set_ascii_mode(std::cin);
  // CGAL::set_ascii_mode(std::cout);
  // std::istream_iterator< Point2 >  in_start( std::cin );
  // std::istream_iterator< Point2 >  in_end;
  // std::ostream_iterator< Point2 >  out( std::cout, "\n" );


  std::vector<Point2>::iterator i_start(points.begin());
  std::vector<Point2>::iterator i_end(points.end());
  //Initial iterator to output
  std::vector<Point2>::iterator i_out(chull.begin());
  std::vector<Point2>::iterator e_out; //Iterator to output end

  //Get convex hull. Start is i_out, end is e_out.
  e_out = CGAL::convex_hull_2( i_start, i_end, i_out );

  //Print chull
  gv.set_vertex_radius(10);
  gv << CGAL::ORANGE;
  for(vector<Point2>::iterator it = i_out; it != e_out; ++it)
  {
    //gv << (*it);
    cout << (*it) << " ";
  }
  cout << endl;

  Delaunay D;

  for(int i = 0; i < points.size(); ++i)
    D.insert(points[i]);

  //TURN WIRED MODE ON SO WE CAN SEE TRIANGLE EDGES
  gv.set_wired(true);
  gv << D;

  cout << "Press key to proceed to Voronoi Diagram (D's dual)\n";
  cin.get();

  gv << CGAL::RED;

  //Draw D's dual on gv. That is, D's Voronoi Diagram.
  D.draw_dual(gv);

  int nr=0,ns=0;
  Edge_iterator eit = D.edges_begin();
  //Visit edges of the triangulation
  for(; eit != D.edges_end(); ++eit)
  {
    CGAL::Object o = D.dual(eit); //Get D's dual for edge eit, that is, voronoi's diagram.
    //Attempt to cast o into segment or ray
    if(CGAL::object_cast<K::Segment_2>(&o)) {ns++;} //Managed to cast o into Segment_2
    else if (CGAL::object_cast<K::Ray_2>(&o)) {nr++;} //Not Segment_2 but Ray_2


  }
  cout << "Voronoi's Diagram has " << ns << " segments and " << nr << " rays.\n";


  std::cout << "Enter a key to finish" << std::endl;
  char ch;
  cin.get();
  return 0;
}
#endif
