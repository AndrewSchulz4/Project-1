#include <iostream>
//#include "GLInclude.h"
//#include "classes.h"

using namespace std;


std::ostream& operator<<(ostream& os, const glm::vec3 v) {
  os << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")";
  return os;
}

//think all I need are given ray and plane as inputs
//plane will be determined by what Darin brings as an input
//can return bool, may want to return value of x which would be a glm::vec3?
bool collision(Ray& ray, Plane& ground_plane)
{
    float t;
    //vector for collision point (collision location)
    //not vec3, will change later
    glm::vec3 x;

    //solve for n /*dot product*/ d as it will be used twice (efficiency)
    float n_dot_d = glm::dot(ray.getDirection(), ground_plane.getN());

    //solve for t
    //((a-p).n)/(d.n)
    //what is a?
    glm::vec3 a_p = ground_plane.getP() - ray.getOrigin();
    float  ap_dot_n = glm::dot(a_p, ground_plane.getN());
    t = ap_dot_n/n_dot_d;

    //a == center of plane? , n = normal to plane held in Plane

    //colliison occurs if d.n != 0 and t > 0

    static size_t i = 0;
  //  std::cout << "Ray i: " << i << std::endl;
 //   std::cout << ray.getOrigin() << " , " << ray.getDirection() << std::endl;

    //std::cout << "Plane p " << ground_plane.getP() << " , " << ground_plane.getN() << std::endl;
   // std::cout << "n_dot_d " << n_dot_d << " , " << ap_dot_n << " , " << t << std::endl;

    if(n_dot_d != 0 && t > 0 && t < 1000)
    {
        //plug t into ray equation to find collision point x (will have normal n)
        x = ray.getOrigin() + (t * ray.getDirection());
        //cout << to_string(x) << endl;
        return true;
    }
    return false;
}

bool collision_sphere(Ray& ray, Sphere& sphere)
{
    //solving for t
    float t;
    float x;
    float collides;
    //retrieving values for sphere for calculations
    float radius = sphere.getRadius();
    glm::vec3 center = sphere.getCenter();
    //same for the ray
    glm::vec3 origin = ray.getOrigin();
    glm::vec3 direction = ray.getDirection();
    //similar to collision with plane but with substituted equation

    //(x-c)^2 - r^2 = 0 c = center r = radius
    //(p+td-c)^2 - r^2 = 0
    //(t^2d^2) + 2td * (p-c) + (p-c)^2 - r^2 = 0
    //A = d^2 ----- B = 2d * (p-c) ----- C = (p-c)^2-r^2

    //equation to solve for A B and C
    glm::vec3 difference = origin - center;
    float A = glm::dot(direction, direction);
    float B = 2 * glm::dot(direction, difference);
    float C = glm::dot(difference, difference) - (radius * radius);

    //use discriminant and see if greater than 0, if so, collision
    float collision = ((B * B) - (4 * A * C));

    if(collision < 0)
    {
      return false;
    }
    else{
      //t value is minimum solution to the quadratic formula
      float min_t = min((-B + sqrt(collision))/(2*A), (-B - sqrt(collision))/(2*A));
      //finding collision point with nearest value of t (min)
      glm::vec3 x = origin + (min_t * direction);
      glm::vec3 normal = (x-center)/radius;

      return true;
      //run ADS coloring to figure out color based on collision point normal and location
      //color(normal, ray)
    }
}