#include <iostream>
#include <fstream>
//#include "GLinclude.h"
//#include "classes.h"


Plane planeMaker(Plane& plane) {
  std::ifstream sceneInput;
  sceneInput.open("scene.txt");    
  while(sceneInput)
    sceneInput >> plane.normalx >> plane.normaly >> plane.normalz >> plane.px >> plane.py >> plane.pz;
  plane.init();
  return plane;
}


