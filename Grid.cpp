#include "Grid.hpp"



Grid::Grid(Point * A, Point * B, Point * C, Point * D, float e, float h)
{
  aDepth = 0;
  Square * s = new Square(A,B,C,D,e,h);
  std::vector<Square *> row;
  row.push_back(s);
  grid.push_back(row);
}

Grid::~Grid()
{
  for(int i=0;i<grid.size();++i)
    for(int j=0;j<grid[i].size();++j)
      SAFE_DELETE(grid[i][j]);
}



/*
  Same as the destructor, but for the member "grid"
*/
 
void Grid::clean()
{
  for(int i=0;i<grid.size();++i)
  {
    for(int j=0;j<grid[i].size();++j)
      SAFE_DELETE(grid[i][j]);
    grid[i].clear();
  }
  grid.clear(); 
}


/*
  Iteration of the algorithm :
  - Split all the squares
  - Refresh the links to reconstruct the neighborhood of each square (forming a torus)
  - "Stick" the edges that could have different altitudes, due to the random factor
*/

void Grid::iterate()
{
  
  Square * s = NULL;

  // Here, we just split all the squares a put them in a new grid grid2
  std::vector< std::vector<Square *> > grid2;
  for(unsigned int i=0;i<grid.size();++i)
  {
    std::vector<Square *> row1;
    std::vector<Square *> row2;
    for(unsigned int j=0;j<grid[i].size();++j)
    {
      Square * s = grid[i][j];
      std::vector< Square * > splitted = grid[i][j]->split();
      row1.push_back(splitted[0]);
      row1.push_back(splitted[1]);
      row2.push_back(splitted[2]);
      row2.push_back(splitted[3]);
    }
    grid2.push_back(row1);
    grid2.push_back(row2);
  }

  // Then, we update the neigborhood. Here, we suppose that we have at least 4 squares
  s = NULL;
  unsigned int n=grid2.size();

  for(unsigned int i=0;i<grid2.size();++i)
  {
    if(i==0)
    {
      for(unsigned int j=1;j<grid2[i].size()-1;++j)
      {
        s = grid2[i][j];
        s->setNU(grid2[n-1][j]);
        s->setNR(grid2[i][j+1]);
        s->setND(grid2[i+1][j]);
        s->setNL(grid2[i][j-1]);
      }
      // j==0
      s = grid2[0][0];
      s->setNU(grid2[n-1][0]);
      s->setNR(grid2[0][1]);
      s->setND(grid2[1][0]);
      s->setNL(grid2[0][n-1]);
      
      // j==n-1
      s = grid2[0][n-1];
      s->setNU(grid2[n-1][n-1]);
      s->setNR(grid2[0][0]);
      s->setND(grid2[1][n-1]);
      s->setNL(grid2[0][n-2]);
    }
    else if (i==n-1)
    {
      for(unsigned int j=1;j<grid2[i].size()-1;++j)
      {
        s = grid2[i][j];
        s->setNU(grid2[i-1][j]);
        s->setNR(grid2[i][j+1]);
        s->setND(grid2[0][j]);
        s->setNL(grid2[i][j-1]);
      }
       // j==0
      s = grid2[n-1][0];
      s->setNU(grid2[n-2][0]);
      s->setNR(grid2[n-1][1]);
      s->setND(grid2[0][0]);
      s->setNL(grid2[n-1][n-1]);
      
      // j==n-1
      s = grid2[n-1][n-1];
      s->setNU(grid2[n-2][n-1]);
      s->setNR(grid2[0][n-1]);
      s->setND(grid2[0][n-1]);
      s->setNL(grid2[n-2][n-1]);
    }
    // i!=0 && i!=(n-1)
    else
    {
      for(unsigned int j=1;j<grid2[i].size()-1;++j)
      {
        s = grid2[i][j];
        s->setNU(grid2[i-1][j]);
        s->setNR(grid2[i][j+1]);
        s->setND(grid2[i+1][j]);
        s->setNL(grid2[i][j-1]);
      }
      // j==0
      s = grid2[i][0];
      s->setNU(grid2[i-1][0]);
      s->setNR(grid2[i][1]);
      s->setND(grid2[i+1][0]);
      s->setNL(grid2[i][n-1]);
      
       // j==n-1
      s = grid2[i][n-1];
      s->setNU(grid2[i-1][n-1]);
      s->setNR(grid2[i][0]);
      s->setND(grid2[i+1][n-1]);
      s->setNL(grid2[i][n-2]);
    }    
  }


  // We now set the z component of (almost) each splitted edge
  s = NULL;
  
  // cycle variables :
  // If you want a cylinder (in X axis) topology, use cycleX=0 and use cycleX=1 otherwise.
  // If you want a cylinder (in Y axis) topology, use cycleY=0 and use cycleY=1 otherwise.
  // For a spherical topology, use cycleX = cycleY = 0.
  
  int cycleX = 0;
  int cycleY = 0;
  
  for(unsigned int i=0;i<grid2.size()-cycleX;++i)
  {
    for(unsigned int j=0;j<grid2[i].size()-cycleY;++j)
    {
      s = grid2[i][j];
      float moy = (s->C()->z() +
                  s->getNR()->D()->z() +
                  s->getNR()->getND()->A()->z() +
                  s->getND()->B()->z())/4.0;
                  
                  
      s->C()->z(moy);
      s->getNR()->D()->z(moy);
      s->getNR()->getND()->A()->z(moy);
      s->getND()->B()->z(moy);
    }
  }

  // And we fill the initial grid
  grid = grid2;
  
}

/*
  Elevate all squares that are under the altitude z
*/

void Grid::lakify(float z)
{
  Square * s=NULL;
  bool a = false;
  bool b = false;
  bool c = false;
  bool d = false;
  
  for(unsigned int i=0;i<grid.size();++i)
  {
    for(unsigned int j=0;j<grid[i].size();++j)
    {
      s = grid[i][j];
      if(s->A()->z() < z)
      {
        a = true;
        s->A()->z(z);
      }
      if(s->B()->z() < z)
      {
        b = true;
        s->B()->z(z);
      }
      if(s->C()->z() < z)
      {
        c = true;
        s->C()->z(z);
      }
      if(s->D()->z() < z)
      {
        d = true;
        s->D()->z(z);
      }
      
      if (a && b && c && d)
        s->isLake(true);
      a = false;
      b = false;
      c = false;
      d = false;
    }
  }
}


/*
  Mean of the 8 neigbors
  A B A B
  D C D C
  A B A B
  D C D C
  
*/

void Grid::smooth()
{
  Square * s=NULL;
  Square * sn=NULL;
  float sum = 0;
  int div = 1;
  for(unsigned int i=0;i<grid.size();++i)
  {
    for(unsigned int j=0;j<grid[i].size();++j)
    {
      s=grid[i][j];
      if(!s->isLake() && !s->getNR()->isLake() && !s->getND()->isLake() && !s->getNR()->getNR()->isLake())
      {
//        std::cerr << "---" << std::endl << (*s) << std::endl;
        sum = (s->A()->z() + s->B()->z() + s->C()->z() + s->D()->z());
        div = 4;
        
        // Neighbor Right
        sn = s->getNR();
//        std::cerr << "Right : " << std::endl << (*sn) << std::endl;
//        if(!sn->isLake())
        {
          sum += sn->B()->z() + sn->C()->z();
          div += 2;
        }
        
        // Neighbor Down
        sn = s->getND();
//        std::cerr << "Down : " << std::endl << (*sn) << std::endl;
//        if(!sn->isLake())
        {
          sum += sn->C()->z() + sn->D()->z();
          div += 2;
        }
        
        // Neighbor DownRight
        sn = s->getND()->getNR();
//        if(!sn->isLake())
        {
          sum += sn->C()->z();
          div += 1;
        }
        sum /= div;
        
        
        // Update the coordinate
        s->setCz(sum);
        
        // Neighbor Right
        s->getNR()->setDz(sum);
        
        // Neighbor Down
        s->getND()->setBz(sum);
        
        // Neighbor DownRight
        s->getND()->getNR()->setAz(sum);
        
      }
    }
  }


}


std::ostream & operator<<(std::ostream & out, Grid & g)
{
  for(int i=0;i<g.size();++i)
  {
    for(int j=0;j<g.gridd()[i].size();++j)
    {
    // AFFICHAGE POUR GNUPLOT
/*
        out << (* (g.gridd()[i][j])->A()) << std::endl << (* (g.gridd()[i][j])->B()) << std::endl << std::endl << (* (g.gridd()[i][j])->D()) << std::endl << (* (g.gridd()[i][j])->C()) << std::endl << std::endl << std::endl;
//*/


    // AFFICHAGE POUR CAMERA3D
///*
    if(g.gridd()[i][j]->isLake())
    {
      out << "-water";
    }
    else
    {
      out << "-floor";
    }
    
      out << std::endl << (* (g.gridd()[i][j])->A()) << std::endl << (* (g.gridd()[i][j])->B()) << std::endl << (* (g.gridd()[i][j])->C()) << std::endl << (* (g.gridd()[i][j])->D()) << std::endl;
//*/
    }
  }
  return out;
}



