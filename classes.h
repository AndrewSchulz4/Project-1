#include "GLInclude.h"
#ifndef _CLASSES_H
#define _CLASSES_H
class Light {
  public:
  Light() {};
  glm::vec3 getPosition() {return position;};
  glm::vec3 getDirection() {return direction;};

  int getLightType() {return lightType;};

  Light(int lightT, glm::vec3 inputVector){
    lightType = lightT;
    //std::cout << lightType << " new light " << std::endl;
    if (lightType == 0) {position = inputVector;}
    else if (lightType == 1) {direction = inputVector;}
    else {position = {0,5,0};}

  }
      void updatePosition (glm::vec3 newPos){
      position += newPos;
    }

  private:
  glm::vec3 position = {0,10,0}; //used in point light
  glm::vec3 direction; //only used in directional light
  int lightType; //0=point 1=directional
};

class Camera {
  public:
  Camera() {};
  glm::vec3 getPosition() {return position;}
  glm::vec3 getViewDirection() { return viewDirection;}
  glm::vec3 getUpVector() { return up; }
  glm::vec3 getRightVector() { return right; }
  float getR() { return r;}
  float getL() { return l;}
  float getT() { return t;}
  float getB() { return b;}
  float getD() { return d;}

  void setPosition(glm::vec3 pos) {position = pos;}
  void setViewDirection(glm::vec3 w) { viewDirection = w; }
  void setUpVector(glm::vec3 u) {up = u;}
  void setAtVector(glm::vec3 r) {right = r;}

  Camera(glm::vec3 position, glm::vec3 viewDirection, glm::vec3 up, glm::vec3 right, float l, float r, float b, float t, float d) : position(position), viewDirection(viewDirection), up(up), right(right), l(l), r(r), b(b), t(t), d(d) {}
  
    void updatePosition (glm::vec3 newPos){
      position += newPos;
      viewDirection += newPos;
      up += newPos;
      right += newPos;
    }

  
  private:
    float r,l,t,b,d; //Right Left Top Bottom for Camera, d for Distance ie focal length
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
class Material {
  public:
    void setM(glm::vec4 k_A, glm::vec4 k_D, glm::vec4 k_S, glm::vec4 I_A, glm::vec4 I_D, glm::vec4 I_S, GLfloat rho) { k_a = k_A; 
    k_d = k_D;  
    k_s = k_S; 
    I_a = I_A; 
    I_d = I_D; 
    I_s = I_S;
    rho = rho;
     }
  Material() {}
  glm::vec4 get_k_a() {return k_a;}
  glm::vec4 get_k_d() {return k_d;}
  glm::vec4 get_k_s() {return k_s;}
  glm::vec4 get_I_a() {return I_a;}
  glm::vec4 get_I_d() {return I_d;}
  glm::vec4 get_I_s() {return I_s;}
  GLfloat getRho() {return rho;}
  Material(glm::vec4 k_a, glm::vec4 k_d, glm::vec4 k_s, glm::vec4 I_a, glm::vec4 I_d, glm::vec4 I_s) : k_a(k_a), I_a(I_a), k_d(k_d), I_d(I_d), k_s(k_s), I_s(I_s) {}
  Material(glm::vec4 k_a, glm::vec4 k_d, glm::vec4 k_s, glm::vec4 I_a, glm::vec4 I_d, glm::vec4 I_s, GLfloat rho) : k_a(k_a), I_a(I_a), k_d(k_d), I_d(I_d), k_s(k_s), I_s(I_s), rho(rho) {}
  private:
  glm::vec4 k_a;
  glm::vec4 I_a;
  glm::vec4 k_d;
  glm::vec4 I_d;
  glm::vec4 k_s;
  glm::vec4 I_s;
  GLfloat rho = 100.0f;
};

class Plane {
public:
  Plane() {normal = {0, 1, 0}; p = {0, 0, 0};}
  glm::vec3 getN() {return normal; }
  glm::vec3 getP() {return p; }
  Material getM() {return material;}
  void setNorm (glm::vec3 norm) {normal = norm;}
  void setP (glm::vec3 point) {p = point;}
  void setM (Material mat) {material = mat;}
  Plane(glm::vec3 normal, glm::vec3 p) : normal(normal), p(p) {}
private:
  glm::vec3 normal;
  glm::vec3 p;
  Material material;
};

class Sphere {
  public:
  Sphere() {};
  Sphere(int radius, glm::vec3 center, Material material) : radius(radius), center(center), material(material) {animate = true; animateCenter = 1; animateConstant = 1;}
  void change(float r, glm::vec3 c) {radius = r; center = c;}
  float getRadius() { return radius; }
  glm::vec3 getCenter() { return center; }
  Material getM() {return material;}
  void setM(Material m) {material = m; }
  void changeCenter(glm::vec3 newCenter) { center = newCenter; }
   void toggleAnimate()
  {
    if (animate) {animate = false;}
    else {animate = true;}
  }
  void animateFrame(float fElapsedTime){
    if (!animate) {return;}
          center.x += animateConstant * fElapsedTime;
          animateCenter += animateConstant *fElapsedTime;

    if (animateCenter > 5) {
      animateConstant = -1;
    } 
    else if (animateCenter < -5){
      animateConstant = 1;
    }
  }

  private:
  bool animate;
  float animateConstant;
  float animateCenter;

  float radius;
  glm::vec3 center;
  Material material;
};

class Collisionpoint {
  public:
  Collisionpoint(glm::vec3 position, glm::vec3 normal, Material material) : position(position), normal(normal), material(material) {};
  Collisionpoint() {position = {0, 0, 0}; normal = {0, 0, 0}; };
  glm::vec3 getPosition() { return position; }
  glm::vec3 getNormal() { return normal; }
  Material materialv() { return material;}
  private:
  glm::vec3 position;
  glm::vec3 normal;
  Material material;
};

class Shadow {
  public:
  Shadow(GLfloat dist, bool inshade) : dist(dist), inshade(inshade) {};
  GLfloat occlusion() {return dist;}
  bool shade() {return inshade;}

  private:
  GLfloat dist;
  bool inshade;
};
#endif
