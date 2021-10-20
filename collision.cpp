#include <iostream>

using namespace std;

//for now return t/f for if collision with plane exists
//think all I need are given ray and plane as inputs
bool collision(Ray ray, Plane ground_plane)
{
    double t;
    //vector for collision point (collision location)
    //not vec3, will change later
    vec3 x;
    double n_dot_d;
    //trace ray and find intersection with plane

    //(p + td - a).n = 0
    //solve for n /*dot product*/ d as it will be used twice (efficiency)
    n_dot_d = //dot product of n and d
    //solve for t
    //((a-p).n)/(d.n)
    t = ((ground_plane.a - ray.p)/*dot product*/groudn_plane.n)/(ray.d/*dot product*/ground_plane.n);

    //a == center of plane? , n = normal to plane held in Plane

    //colliison occurs if d.n != 0 and t > 0
    if(d/*dot product*/n != 0 && t > 0)
    {
        //plug t into ray equation to find collision point x (will have normal n)

    }
}