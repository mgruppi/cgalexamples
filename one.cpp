//CGAL HelloGeom

#include <CGAL/Simple_cartesian.h>
#include <CGAL/Point_2.h>
#include <CGAL/Vector_2.h>

#include <CGAL/IO/Geomview_stream.h>
#include <CGAL/IO/Triangulation_geomview_ostream_2.h>
#include <CGAL/IO/Triangulation_geomview_ostream_3.h>

#include <iostream>
using namespace std;

typedef CGAL::Simple_cartesian<double> Kernel; //Kernel for building on cartesian double coordinates
typedef Kernel::Point_2 Point_2; //Point type for our kernel
typedef Kernel::Segment_2 Segment_2; //Segment type for our kernel
typedef Kernel::Vector_2 Vector_2;

//3D
typedef Kernel::Point_3 Point_3;
typedef Kernel::Vector_3 Vector_3;

int main()
{
  //Now we can use Points with double
  Point_2 p1(1.0,-1.0), p2(4.0,3.0);

  Vector_2 v1(-1,10);
  Vector_2 v2(p1-p2); //Difference between two points returns a Vector

  Point_2 p3(p2+v1);


  cout << "2D:\n";
  cout << "p1(" << p1.x() << "," << p1.y() << ")\n";
  cout << "p2(" << p2.x() << "," << p2.y() << ")\n";
  cout << "p3(" << p3.x() << "," << p3.y() << ")\n";

  cout << "\nSquared distance between p1 and p2: \n" << "sqdist(p1,p2) = " << CGAL::squared_distance(p1,p2) << endl;
  cout << "\nMidpoint between p1 and p2: \n" << "midpoint(p1,p2) = " << CGAL::midpoint(p1,p2) << endl;


  cout << "\nPoint orientation: \n";

  //Return type is CGAL::Orientation
  CGAL::Orientation o = CGAL::orientation(p1,p2,p3);
  if(o == CGAL::COLLINEAR)
    cout << "COLLINEAR\n";
  else if (o == CGAL::LEFT_TURN)
    cout << "LEFT_TURN\n";
  else if (o == CGAL::RIGHT_TURN)
    cout << "RIGHT_TURN\n";




  cout << "Press any key to continue (Vector)...\n";
  cin.get();
  cout << "Vector v2("<< v2.x() << "," << v2.y() << ")\n";
  cout << "3D:\n";
  Vector_3 va(1.0,0.0,0);
  Vector_3 vb(0.0,1.0,0);

  Vector_3 vc = CGAL::cross_product(va,vb);

  double dotP = va*vc;

  cout << "va("<<va.x()<<","<<va.y()<<","<<va.z()<<")\n";
  cout << "vb("<<vb.x()<<","<<vb.y()<<","<<vb.z()<<")\n";

  //Dot (scalar) product and cross product
  cout << "va * vc = " << dotP << endl;
  cout << "va x vc = ("<<vc.x()<<","<<vc.y()<<","<<vc.z()<<")\n";

  vc = 2*vc;
  //Multiplication by scalar and squared_length
  cout << "||2*vc||² = " << vc.squared_length() << endl;


  cout << "Continue to Determinant...\n";
  cin.get();

  //Determinant of vectors
  cout << "[2D] Det(v1,v2) = " << CGAL::determinant(v1,v2) << endl;

  cout << "[3D] Det(va,vb,vb) = " << CGAL::determinant(va,vb,vc) << endl;

  cout << "Press return key to open GeomView.\n";


  //Start geomview with bounding box
  CGAL::Geomview_stream gv(CGAL::Bbox_3(-20, -20, -20, 20, 20, 20));

  //White bg color
  gv.set_line_width(4);
  gv.set_bg_color(CGAL::Color(0, 200, 200));

  gv << CGAL::BLUE;
  gv << p1;
  gv << CGAL::RED;
  gv << p2;
  gv << CGAL::GREEN;
  gv << p3;



  cout << "Press return to close.\n";
  cin.get();

  return 0;
}
