#include <iostream>
#include <fstream>
#include "GLinclude.h"
#include "classes.h"


void sceneInput(std::ifstream input) {
  std::ifstream sceneInput;
  sceneInput.open("scene.txt");
  Plane plane;
  while(sceneInput)
    sceneInput >> plane.normalx >> plane.normaly >> plane.normalz >> plane.px >> plane.py >> plane.pz;

    plane.normal = {plane.normalx, plane.normaly, plane.normalz};
  plane.p = {plane.px, plane.py, plane.pz};
}

