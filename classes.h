#include "GLInclude.h"

class Ray {
    public:
    glm::vec3 getOrigin() { return origin; }
    glm::vec3 getDirection() { return direction; }
    Ray(glm::vec3 origin, glm::vec3 direction) { origin = origin; direction = direction;}
    
    private:
    glm::vec3 origin;
    glm::vec3 direction;
};

class Plane {
    public:
    glm::vec3 getN() {return normal; }
    private:
    //need value for a? or is it a computation?
    glm::vec3 length;
    glm::vec3 width;
    glm::vec3 normal;
};