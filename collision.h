#ifndef _collision_
#define _collision_
#include "GLInclude.h"
#include "classes.h"

Collisionpoint collision(Ray& ray, Plane& ground_plane);
Collisionpoint collision_sphere(Ray& ray, Sphere& sphere);

#endif