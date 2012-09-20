#ifndef SQUARE_HPP
#define SQUARE_HPP

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include "Point.hpp"

class Square
{
protected:
  
  Point * aA;
  Point * aB;
  Point * aC;
  Point * aD;

  Square * aNU;
  Square * aNR;
  Square * aND;
  Square * aNL;
  
  float e;
  float h;
  bool aLake; // is it a lake?

public:
  Square(Point * AA, Point * BB, Point * CC, Point * DD, float ee, float hh) : aA(AA), aB(BB), aC(CC), aD(DD),
                                                           aNU(this), aNR(this), aND(this), aNL(this), e(ee), h(hh), aLake(false) {}
  ~Square();
  
  Point * A(void) {return aA;}
  Point * B(void) {return aB;}
  Point * C(void) {return aC;}
  Point * D(void) {return aD;}
  
  void setAz(float zz) {aA->z(zz);}
  void setBz(float zz) {aB->z(zz);}
  void setCz(float zz) {aC->z(zz);}
  void setDz(float zz) {aD->z(zz);}
  
  Point * AB(void);
  Point * BC(void);
  Point * CD(void);
  Point * DA(void);
  
  Point * midd(void);
  
  std::vector< Square * > split(void);
  
  Square * getNU() {return aNU;}
  Square * getNR() {return aNR;}
  Square * getND() {return aND;}
  Square * getNL() {return aNL;}
  
  void setNU(Square * s) {aNU = s;}
  void setNR(Square * s) {aNR = s;}
  void setND(Square * s) {aND = s;}
  void setNL(Square * s) {aNL = s;}
  
  bool isLake() {return aLake;}
  void isLake(bool b) {aLake = b;}

  

};


std::ostream & operator<<(std::ostream & out, Square & s);


#endif
