//#include "GLInclude.h"
//#include "classes.h"

using namespace std;
//------------------------------------
// Will return a point of collision and noraml if collision is detected, for now bool
//------------------------------------

//think all I need are given ray and plane as inputs
//plane will be determined by what Darin brings as an input
//can return bool, may want to return value of x which would be a glm::vec3?
bool collision_plane(Ray ray, Plane ground_plane)
{
    float t;
    //vector for collision point (collision location)
    //not vec3, will change later
    glm::vec3 x;

    //solve for n /*dot product*/ d as it will be used twice (efficiency)
    float n_dot_d = glm::dot(ray.getDirection(), ground_plane.getN());
    // std::cout << n_dot_d << endl;
    //solve for t
    //((a-p).n)/(d.n)
    //what is a? -- it is any arbitrary point on plane, using center
    glm::vec3 a_p = ground_plane.getP() - ray.getOrigin();
    float  ap_dot_n = glm::dot(a_p, ground_plane.getN());
    t = ap_dot_n/n_dot_d;
    std:: cout << ap_dot_n << " " << n_dot_d << endl;
    //a == center of plane? , n = normal to plane held in Plane

    //colliison occurs if d.n != 0 and t > 0
    if(n_dot_d != 0 && t > 0 && t < 1000)
    {
        //plug t into ray equation to find collision point x (will have normal n)
        x = ray.getOrigin() + (t * ray.getDirection());
        return true;
    }
    return false;
}

//sphere class needs center/origin and radius (subsequent getters and setters)
//will also utilize the ray class

bool collision_sphere(Ray ray, Sphere sphere)
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
    glm::vec3 A = direction * direction;
    glm::vec3 B = 2 * direction * (origin - center);
    glm::vec3 C = ((origin - center) * (origin - center)) - (radius * radius);

    //run quadratic formula and return min value for t

    t = (-b + sqrt((B*B) - 4 * A * C)) / (2 * A);
    x = (-b - sqrt((B*B) - 4 * A * C)) / (2 * A);
    //negative means no collision
    //first collision point will be smaller value (min)
    //-------------------------------------------
    //thoughts
    //plug t,x back into equation to see if there is collision with value greater than 0?
    //vectors in equation how would you compare this to an arbitrary value of 0?
    //min(x,t) is collision vector, do you plug both of these into equation to see if greater than 0?
    
    //normal given as n = x-c/r
}