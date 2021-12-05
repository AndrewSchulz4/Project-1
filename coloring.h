#ifndef _Coloring_
#define _Coloring_
#include "GLInclude.h"
#include "classes.h"
#include <vector>
//coloring
glm::vec4 color(Collisionpoint point, Camera c, std::vector<Light> l);
bool inShadow(Collisionpoint& intersect, std::vector<Light> lights, std::vector<Sphere>& spheres_scene);
#endif