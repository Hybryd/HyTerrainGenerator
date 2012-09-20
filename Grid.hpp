#ifndef GRID_HPP
#define GRID_HPP

#include <iostream>
#include <vector>
#include "Square.hpp"

class Grid
{
protected:
  std::vector< std::vector<Square *> > grid;
  int aDepth;

public:
  Grid(Point * A, Point * B, Point * C, Point * D, float e, float h);
  ~Grid();
  
  std::vector< std::vector<Square *> > & gridd() {return grid;}
  int size() {return grid.size();}
  
  void iterate();
  void lakify(float z);
  void smooth();
  
  void clean();
};

std::ostream & operator<<(std::ostream & out, Grid & g);

#endif
