
<a name="readme-top"></a>



<!-- PROJECT LOGO -->
<br />
<div align="center">
  

<h3 align="center">HyTerrainGenerator</h3>

  <p align="center">
    Genereates a procedural 3D terrain    
  </p>
</div>

![Example](https://github.com/Hybryd/HyTerrainGenerator/blob/master/example.png?raw=true)



<!-- ABOUT THE PROJECT -->
## About The Project


This is an implementation of the Perlin noise algorithm to generate a simple procedural terrain.

The output can be displayed with gnuplot.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



### Built With

* ![C++][C++]


<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- GETTING STARTED -->
## Getting Started

To get a local copy up and running follow these simple example steps.

### Prerequisites

This is an example of how to list things you need to use the software and how to install them.

* g++
  ```sh
  sudo apt-get install g++
  ```
* gnuplot
  ```sh
  sudo apt-get install gnuplot
  ```


<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Installation

1. Clone the repo
   ```sh
   git clone https://github.com/Hybryd/HyTerrainGenerator.git
   ```
2. Go in the repo
    ```sh
    cd HyTerrainGenerator
    ```
3. Compile
   ```sh
   g++ *.cpp -o main
   ```

<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Usage



1. Run the program
   ```sh
   ./main [d] [l] [h] [e]
   ```
   
  Optional parameters :

  * <b>d</b> : the number of iterations. The rendering with gnuplot can be slow with d > 7
  * <b>l</b> : level of the sea. If the grid is "lakyfied" to the value l, all 
       squares that are under the altitude l are adjusted to this value
       and form a lake. They are displayed in blue
  * <b>h</b> : factor dividing the parameter e at each iteration (h>1). The higher,   the smoother
  * <b>e</b> : the initial width of the range for picking 
      random number. It is used to put an altitude to a given point.
      At each iteration, e is devided by h, to keep a smooth terrain
  
   Example :
   ``` sh
   ./main 7 1 2.3 5
   ```
2. Run gnuplot's script to render the terrain
   ```sh
   gnuplot ./display.gp
   ```

<p align="right">(<a href="#readme-top">back to top</a>)</p>





<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->

[C++]: https://img.shields.io/badge/g++-9.4.0-blue.svg?style=flat&logo=g%2B%2B

