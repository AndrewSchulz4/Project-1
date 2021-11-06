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
glm::vec3 collision(Ray ray, Plane ground_plane)
{
    float t;
    //vector for collision point (collision location)
    //not vec3, will change later
    glm::vec3 x = {0.0, 0.0, 0.0};

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
        return x;
    }
    return x;
}