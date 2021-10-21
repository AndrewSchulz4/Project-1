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
  void init() {
      normal = {normalx, normaly, normalz};
      p = {px, py, pz};
  }
  GLfloat normalx;
  GLfloat normaly;
  GLfloat normalz;
  GLfloat px;
  GLfloat py;
  GLfloat pz;
private:
  glm::vec3 normal = {};
  glm::vec3 p = {};
};