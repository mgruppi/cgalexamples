//CGAL Basic Point Orientation
//You may need to install libboost-all-dev
//sudo apt-get install libboost-all-dev

#include <iostream>
#include <CGAL/Simple_cartesian.h>

#include <CGAL/IO/Geomview_stream.h>
#include <CGAL/IO/Triangulation_geomview_ostream_2.h>
#include <CGAL/IO/Triangulation_geomview_ostream_3.h>

#include <CGAL/intersections.h>

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_2 Point_2;
typedef Kernel::Segment_2 Segment_2;
typedef Kernel::Triangle_2 Triangle_2;
typedef Kernel::Circle_2 Circle_2;
typedef Kernel::Intersect_2 Intersect_2;

//3D
typedef Kernel::Point_3 Point_3;
typedef Kernel::Vector_3 Vector_3;
typedef Kernel::Segment_3 Segment_3;
typedef Kernel::Triangle_3 Triangle_3;
typedef Kernel::Circle_3 Circle_3;
typedef Kernel::Sphere_3 Sphere_3;

using namespace std;

//For determining intersection
struct Intersection_visitor {
  typedef void result_type;
  void operator()(const Point_2& p) const
  {
    std::cout << p << std::endl;
  }
  void operator()(const Segment_2& s) const
  {
    std::cout << s << std::endl;
  }
};


int main()
{
  Point_2 p(1,1), q(10,10), r(5,5), s(2,5), t(7,3), u(10,0);

  cout << "Points p(1,1) q(10,10) r(5,5) s(2,5) t(7,3) u(10,0)\n";

  CGAL::Geomview_stream gv(CGAL::Bbox_3(-10, -10, -10, 10, 10, 10));

  gv.set_line_width(2);
  gv.set_bg_color(CGAL::Color(0, 200, 200));

  gv << CGAL::BLUE;

  gv << p << q << r << s << t << u;

  cout << "Press to proceed to segments.\n";

  gv << CGAL::RED;
  Segment_2 pq(p,q);
  cout << "\nSegment pq created.\n";
  Segment_2 pu(p,u);
  cout << "Segment pu created.\n";

  gv << pq;
  sleep(2);
  gv << pu;

  cout << "\nPress return to continue...\n";
  cin.get();

  Triangle_2 pqr(p,q,r);
  cout << "\nTriangle_2 pqr created.\n";
  if(pqr.is_degenerate())
    cout << "pqr is degenerate (pqr are collinear).\n";
  Triangle_2 pqs(p,q,s);
  cout << "\nTriangle_2 pqs created.\n";
  if(!pqs.is_degenerate())
    cout << "pqs is not degenerate.\n";

    gv << CGAL::GREEN;
    gv << pqs;

    cout <<"\nPress return to continue...\n";
    cin.get();

  Point_2 pc = CGAL::centroid(pqs);
  cout << "\ncentroid(pqs) = ("<<pc.x() << ","<<pc.y()<<")\n";

  gv << CGAL::ORANGE;
  gv << pc;

  Circle_2 c(pc,3);
  cout << "Circle c(centroid(pqs),3)\n";

  cout << "\nPress return key to begin intersection tests...\n\n";
  cin.get();

  //How to know the result type of an intersection?
  //Ex: Segment_2 x Segment_2 can return a point or a segment.
  //Ex2: Triangle_2 x Triangle_2 can return a point, a segment, triangle, or vector<Point_2> (as if it return a polygon)

  cout << "Do pq x pu intersect? ";

  bool do_int = CGAL::do_intersect(pq,pu);
  if(do_int) cout << "Yes!\n";
  else cout << "No!\n";

  //Generic type of intersection between segments

  //CGAL::cpp11::result_of<Intersect_2(Segment_2,Segment_2)>::type result = intersection(pq,pu);

  //C++11
  //Now we have to test whether the result is a segment or a point

  // CGAL::Object result = intersection(pq,pu);
  //
  // const Segment_2* seg;
  // const Point_2* psect;
  // assign(psect,result);
  // cout << "wtf;";
  // if(psect != NULL)
  // {
  //   cout << "Point = ";
  //   cout << (*psect) << endl;
  //   gv << CGAL::VIOLET;
  //   gv << (*psect);
  // }
  // else{
  //     assign(seg,result);
  //       cout << "Segment = ";
  //       cout << *seg << endl;
  //       gv << CGAL::VIOLET;
  //       gv << (*seg);
  // }
  //
   cout << "Press key to clear and draw 3D.\n";
   cin.get();

   gv.clear();

   CGAL::Bbox_3 bb(-10,-10,-10,10,10,10);
   gv << CGAL::BLACK;
   gv << bb;
   gv.set_wired(true);

   gv.set_line_width(2);
   gv.set_bg_color(CGAL::Color(0, 200, 200));



   Point_3 p1(-8.0,-3.0,1.0), p2(-2.0,-1.0,0.0), p3(5.0,2.0,2.0), p4(8.0,9.0,-4.0), p5(7.0, 1.0, 3.0), p6(6.0,-2.0,-5.0),p7(-7,9,-5);

   gv << CGAL::BLUE;
   gv << p1;
   sleep(2);
   gv << p2;
   sleep(2);
   gv << p3;
   sleep(2);
   gv << p4;
   sleep(2);
   gv << p5;
   sleep(2);
   gv << p6;
   sleep(2);
   gv << p7;
   sleep(2);


   Segment_3 seg1(p1,p2);
   Segment_3 seg2(p2,p3);
   Segment_3 seg3(p3,p4);
   Segment_3 seg4(p4,p5);
   Segment_3 seg5(p5,p6);

   gv << CGAL::RED;
   gv << seg1;
   sleep(2);
   gv << seg2;
   sleep(2);
   gv << seg3;
   sleep(2);
   gv << seg4;
   sleep(2);
   gv << seg5;
   sleep(3);

   Triangle_3 tri(p1,p2,p3);
   Triangle_3 tri2(p2,p3,p4);
   Triangle_3 tri3(p3,p4,p5);
   Triangle_3 tri4(p4,p5,p6);
   Sphere_3 sp(p7,4);

   gv << CGAL::VIOLET;
   gv << sp;
   sleep(2);

   //Here we set different color for every face and set edges as red
   gv << CGAL::GREEN;
   gv.set_edge_color(CGAL::RED);
   gv << tri;
   sleep(1);
   gv << CGAL::ORANGE;
   gv.set_edge_color(CGAL::RED);
   gv << tri2;
   sleep(1);
   gv << CGAL::BLUE;
   gv.set_edge_color(CGAL::RED);
   gv << tri3;
   gv << CGAL::WHITE;
   gv.set_edge_color(CGAL::RED);
   gv << tri4;


   cout <<"\nFinished. Press key.\n";
   cin.get();

    //Did we get a result?
    // if(const Segment_2* s = boost::get<Segment_2>(&*result)) //Try to cast result into Segment_2
    // {
    //   cout << "\t->Result is a segment.\n"
    // }
    // else{
    //   //const Point_2* p = boost:get<Point_2>(&*result);
    //   //cout << "\t->Result is a point p =(" << p->x() <<","<<p->y()<<")\n";
    // }



  return 0;
}
