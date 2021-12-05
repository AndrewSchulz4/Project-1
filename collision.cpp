//think all I need are given ray and plane as inputs
//plane will be determined by what Darin brings as an input
//can return bool, may want to return value of x which would be a glm::vec3?
#include "collision.h"
Collisionpoint collision(Ray& ray, Plane& ground_plane)
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

    //collisison occurs if d.n != 0 and t > 0

    static size_t i = 0;
    
    if(n_dot_d != 0 && t > 0)
    {
        //plug t into ray equation to find collision point x (will have normal n)
        x = ray.getOrigin() + (t * ray.getDirection());
    }
    Collisionpoint collis(x, ground_plane.getN(), ground_plane.getM());
    return collis;

  }

Collisionpoint collision_sphere(Ray& ray, Sphere& sphere)
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
      glm::vec3 zero = {0.0, 0.0, 0.0};
      Material M;
      Collisionpoint nocollis(zero, zero, M);
      return nocollis;
    }
    else{
      //t value is minimum solution to the quadratic formula
      //not minimum, take smallest t > 0, camera inside the sphere
      //if/else statements
      float tval1 = (-B + sqrt(collision))/(2*A);
      float tval2 = (-B - sqrt(collision))/(2*A);
      float min_t;
      if(tval1 < tval2 && tval1 > 0)
      {
        min_t = tval1;
      }
      else
        min_t = tval2;
      // if(tval1 > tval2 && tval2 > 0)
      // {}

      
      //finding collision point with nearest value of t (min)
      glm::vec3 x = origin + (min_t * direction);
      //glm::vec3 normal = (x-center)/radius;
      Collisionpoint collis(x, ((x-sphere.getCenter())/sphere.getRadius()), sphere.getM());
      return collis;
      //run ADS coloring to figure out color based on collision point normal and location
      //color(normal, ray)
    }
}