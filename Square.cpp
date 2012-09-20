#include "Square.hpp"

float alea(float a, float b)
{
  return (( rand()/(float)RAND_MAX ) * (b-a) + a);
}


Square::~Square()
{
  SAFE_DELETE(aA);
  SAFE_DELETE(aB);
  SAFE_DELETE(aC);
  SAFE_DELETE(aD);
}


Point * Square::AB(void)
{
  Point * p = new Point(  aA->x(),
                          (aB->y()+aA->y())/2.0,
                          (aA->z()+aB->z()+aNU->C()->z()+aNU->D()->z())/4.0 + alea(-e,e));
  return p;
}

Point * Square::BC(void)
{
  Point * p = new Point(  (aC->x()+aB->x())/2.0,
                          aB->y(),
                          (aB->z()+aC->z()+aNR->A()->z()+aNR->D()->z())/4.0 + alea(-e,e));
  return p;
}
 
Point * Square::CD(void)
{
  Point * p = new Point(  aC->x(),
                          (aC->y()+aD->y())/2.0,
                          (aC->z()+aD->z()+aND->A()->z()+aND->B()->z())/4.0 + alea(-e,e));
  return p;
}

Point * Square::DA(void)
{
  Point * p = new Point(  (aA->x()+aD->x())/2.0,
                          aD->y(),
                          (aA->z()+aD->z()+aNL->B()->z()+aNL->C()->z())/4.0 + alea(-e,e));
  return p;
}

Point * Square::midd(void)
{
  Point * p = new Point(  (aA->x()+aD->x())/2.0,
                          (aA->y()+aB->y())/2.0,
                          (aA->z()+aB->z()+aC->z()+aD->z())/4.0 + alea(-e,e));
  return p;
}


/*
  Split the square in 4 squares.
  The altitude of the middle of an edge is the average of its two neighbors
  plus a random factor. The middle of the square is the average of the altitude
  of the corners plus a random factor
*/

std::vector< Square * > Square::split(void)
{
  std::vector< Square * > res;
  
  Point * aa = new Point(*aA);
  Point * bb = new Point(*aB);
  Point * cc = new Point(*aC);
  Point * dd = new Point(*aD);
  Point * mid1 = midd();
  Point * mid2 = new Point(*mid1);
  Point * mid3 = new Point(*mid1);
  Point * mid4 = new Point(*mid1);
  Point * ab1 = AB();
  Point * ab2 = new Point(*ab1);
  Point * bc2 = BC();
  Point * bc3 = new Point(*bc2);
  Point * cd3 = CD();
  Point * cd4 = new Point(*cd3);
  Point * da1 = DA();
  Point * da4 = new Point(*da1);
  
  Square * s1 = new Square(aa,ab1,mid1,da1,e/h,h);
  Square * s2 = new Square(ab2,bb,bc2,mid2,e/h,h);
  Square * s3 = new Square(mid3,bc3,cc,cd3,e/h,h);
  Square * s4 = new Square(da4,mid4,cd4,dd,e/h,h);

  res.push_back(s1);
  res.push_back(s2);
  res.push_back(s4);
  res.push_back(s3);

  return res;
}

std::ostream & operator<<(std::ostream & out, Square & s)
{
  out << (*s.A()) << std::endl << (*s.B()) << std::endl << (*s.C()) << std::endl << (*s.D()) << std::endl << (*s.A());
  return out;
}


