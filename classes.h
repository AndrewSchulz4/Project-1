#include "GLInclude.h"
#ifndef _CLASSES_H
#define _CLASSES_H
class Light {
  public:
  Light() {};
  glm::vec3 getPosition() {return position;};
  Light(glm::vec3 position) : position(position) {}
  private:
  glm::vec3 position;
};

class Camera {
  public:
  Camera() {};
  glm::vec3 getPosition() {return position;}
  glm::vec3 getViewDirection() { return viewDirection;}
  glm::vec3 getUpVector() { return up; }
  glm::vec3 getRightVector() { return right; }
  void setPosition(glm::vec3 pos) {position = pos;}
  void setViewDirection(glm::vec3 w) { viewDirection = w; }
  void setUpVector(glm::vec3 u) {up = u;}
  void setAtVector(glm::vec3 r) {right = r;}

  Camera(glm::vec3 position, glm::vec3 viewDirection, glm::vec3 up, glm::vec3 right) : position(position), viewDirection(viewDirection), up(up), right(right) {}
  private:
  glm::vec3 position;
  glm::vec3 viewDirection;
  glm::vec3 up;
  glm::vec3 right;
};
class Ray {
    public:
    glm::vec3 getOrigin() { return origin; }
    glm::vec3 getDirection() { return direction; }
    Ray(glm::vec3 origin, glm::vec3 direction) : origin(origin), direction(direction) {}
    
    private:
    glm::vec3 origin;
    glm::vec3 direction;
};

class Plane {
public:
  Plane() {};
  glm::vec3 getN() {return normal; }
  glm::vec3 getP() {return p; }
  glm::vec4 get_k_a() {return k_a;}
  glm::vec4 get_k_d() {return k_d;}
  glm::vec4 get_k_s() {return k_s;}
  glm::vec4 get_I_a() {return I_a;}
  glm::vec4 get_I_d() {return I_d;}
  glm::vec4 get_I_s() {return I_s;}
  void setNorm (glm::vec3 norm) {normal = norm;}
  void setP (glm::vec3 point) {p = point;}
  Plane(glm::vec3 normal, glm::vec3 p) : normal(normal), p(p) {}

  Plane storeMaterials(glm::vec4 k_A, glm::vec4 k_D, glm::vec4 k_S, glm::vec4 I_A, glm::vec4 I_D, glm::vec4 I_S) {
    k_a = k_A; 
    k_d = k_D;  
    k_s = k_S; 
    I_a = I_A; 
    I_d = I_D; 
    I_s = I_S; 
    return *this;
  }
private:
  glm::vec3 normal = {};
  glm::vec3 p = {};
  glm::vec4 k_a = {};
  glm::vec4 k_d = {};
  glm::vec4 k_s = {};
  glm::vec4 I_a = {};
  glm::vec4 I_d = {};
  glm::vec4 I_s = {};
};

class Sphere {
  public:
  Sphere() {};
  Sphere(float radius, glm::vec3 center) : radius(radius), center(center) {}
  float getRadius() { return radius; }
  glm::vec3 getCenter() { return center; }
  glm::vec4 get_k_a() {return k_a;}
  glm::vec4 get_k_d() {return k_d;}
  glm::vec4 get_k_s() {return k_s;}
  glm::vec4 get_I_a() {return I_a;}
  glm::vec4 get_I_d() {return I_d;}
  glm::vec4 get_I_s() {return I_s;}
  void changeCenter(glm::vec3 newCenter) { center = newCenter; }

  private:
  float radius;
  glm::vec3 center;
  glm::vec4 k_a = {1.0f, 0.0f, 0.0f, 1.0f};
  glm::vec4 I_a = {0.3f, 0.3f, 0.3f, 1.0f};
  glm::vec4 k_d = k_a;
  glm::vec4 I_d = {0.8f, 0.8f, 0.8f, 0.0f};
  glm::vec4 k_s = {0.7f, 0.7f, 0.7f, 0.5f};
  glm::vec4 I_s = {0.8f, 0.8f, 0.8f, 0.0f};
};
#endif