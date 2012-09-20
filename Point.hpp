#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>

#define SAFE_DELETE(a) { delete (a); (a) = NULL; }
#define SCALEXY 3
#define SCALEZ 10

class Point
{
protected:
  float ax;
  float ay;
  float az;


public:

  Point(float xx, float yy, float zz): ax(xx),ay(yy),az(zz) {}
  Point(Point & p): ax(p.ax),ay(p.ay),az(p.az) {}
  
  float x(void) {return ax;}
  float y(void) {return ay;}
  float z(void) {return az;}
  
  void x(float xx) {ax=xx;}
  void y(float yy) {ay=yy;}
  void z(float zz) {az=zz;}

};

std::ostream & operator<<(std::ostream & out, Point & p);

#endif
