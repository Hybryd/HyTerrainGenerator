#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "Square.hpp"
#include "Grid.hpp"


/*
  Hybryd-
  28-01-2012
  
  
  Terrain generator
  
  Generates an artificial terrain. The algorithm is inspired from the 
  Perlin's algorithm.

  Parameters :
  d : the number of iterations.
  l : level of the sea. If the grid is "lakyfied" to the value l, all 
      squares that are under the altitude l are adjusted to this value
      and form a lake. They are not displayed.
  h : factor dividing the parameter e at each iteration (g>1). The higher
      it is, the smoother the map becomes
  e : it is the initial width of the window of freedom for picking 
      random number. It is used to put an altitude to a given point.
      At each iteration, e is devided by g, to keep a "smooth" terrain

  Usage : ./main d l h e
  Then type : gnuplot display.gp
  
  Ex : d=7, l=0, h=2, e=3
*/



int main(int argc, char ** argv)
{
  // Parameters
  
  int d=6;          // number of iteration
  if(argc > 1)
    d = atoi(argv[1]);
    
  float l = 0;      // level of the sea
  if(argc > 2)
    l = atof(argv[2]);
    
  float h=2.3;      // factor for random margin
  if(argc > 3)
    h = atof(argv[3]);
    
    
  float e = 5.0;    // margin for random
  if(argc > 4)
    e = atof(argv[4]);
    
    
  float z = 0.0;    // (initial altitude)
  

  std::cout << "Parameters :" << std::endl;
  std::cout << "d : " << d << "   l : " << l << "   h : " << h << "   e : "<< e << std::endl;

//  srand ( time(NULL) );
  std::ofstream f("out", std::ios::out | std::ios::trunc);
  std::ofstream ff("out2", std::ios::out | std::ios::trunc);
  
  if(f&&ff)
  {
    
    // Create the initial grid
    Point * A = new Point(0,0,z);
    Point * B = new Point(0,1,z);
    Point * C = new Point(1,1,z);
    Point * D = new Point(1,0,z);
    Grid g(A,B,C,D,e,h);
    
    // Iterations
    for(int i=1;i<=d;++i)
    {
      std::cout << "Step : " << i  << " of " << d << std::endl;
      g.iterate();
    }
    
    // Create lakes
    g.lakify(l);
    
    // Save in the file "out"
    std::cout << "Saving data..." << std::endl;
    f << g << std::endl;
    for (int i =0; i<8; ++i)
      g.smooth();
    ff << g << std::endl;
    
    f.close();
  }
  else
    std::cerr << "Error while opening file 'out'" << std::endl;
  
  return 0;
}
