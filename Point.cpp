#include "Point.hpp"


std::ostream & operator<<(std::ostream & out, Point & p)
{
  //gnuplotstyle
  out << (p.x()*SCALEXY) << " " << (p.y()*SCALEXY) << " " << (p.z()*SCALEZ);
  return out;
}

