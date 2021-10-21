#include <iostream>
//#include "GLInclude.h"
//#include "classes.h"

using namespace std;

//think all I need are given ray and plane as inputs
//plane will be determined by what Darin brings as an input
//can return bool, may want to return value of x which would be a glm::vec3?
bool collision(Ray ray, Plane ground_plane)
{
    float t;
    //vector for collision point (collision location)
    //not vec3, will change later
    glm::vec3 x;

    //solve for n /*dot product*/ d as it will be used twice (efficiency)
    float n_dot_d = glm::dot(ray.getDirection(), ground_plane.normal);

    //solve for t
    //((a-p).n)/(d.n)
    //what is a?
    glm::vec3 a_p = ground_plane.p - ray.getPosition();
    float  ap_dot_n = glm::dot(a_p, ground_plane.normal)
    t = ap_dot_n/n_dot_d;

    //a == center of plane? , n = normal to plane held in Plane

    //colliison occurs if d.n != 0 and t > 0
    if(n_dot_d != 0 && t > 0 && t < 50)
    {
        //plug t into ray equation to find collision point x (will have normal n)
        x = ray.getPosition() + (t * ray.getDirection());
        return true;
    }
    return false;
}