#include <iostream>
#include "GLInclude.h"

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
    float n_dot_d = glm::dot(ray.getDirection(), ground_plane.getN());

    //solve for t
    //((a-p).n)/(d.n)
    //what is a?
    glm::vec3 a_p = ground_plane.a - ray.getPosition();
    float  ap_dot_n = glm::dot(a_p, ground_plane.getN())
    t = ap_dot_n/n_dot_d;

    //a == center of plane? , n = normal to plane held in Plane

    //colliison occurs if d.n != 0 and t > 0
    if(n_dot_d != 0 && t > 0)
    {
        //plug t into ray equation to find collision point x (will have normal n)
        x = ray.getPosition() + (t * ray.getDirection());
    }
}

class Ray {
    public:
    glm::vec3 getOrigin() { return origin; }
    glm::vec3 getDirection() { return direction; }
    Ray(glm::vec3 origin, glm::vec3 direction) { origin = origin; direction = direction;}

    private:
    glm::vec3 origin;
    glm::vec3 direction;
}

class Plane {
    public:
    glm::vec3 getN() {return normal; }
    private:
    //need value for a? or is it a computation?
    glm::vec3 length;
    glm::vec3 width;
    glm::vec3 normal;
}