//#include "GLInclude.h"

class Camera {
  public:
  //Camera();
  glm::vec3 getPosition() {return position;}
  glm::vec3 getViewDirection() { return viewDirection;}
  glm::vec3 getUpVector() { return up; }
  glm::vec3 getRightVector() { return right; }
  void setPosition(glm::vec3 pos) {position = pos;}
  void setViewDirection(glm::vec3 w) { viewDirection = w; }
  void setUpVector(glm::vec3 u) {up = u;}
  void setAtVector(glm::vec3 r) {right = r;}

  //Camera(glm::vec3 viewDirection, glm::vec3 up, glm::vec3 at) : viewDirection(viewDirection), up(up), at(at) {}
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
  // void init() {
  //     normal = {normalx, normaly, normalz};
  //     p = {px, py, pz};
  // }
  // void planeMaker() {
  // std::ifstream sceneInput;
  // sceneInput.open("scene.txt");    
  // while(sceneInput)
  //   sceneInput >> normalx >> normaly >> normalz >> px >> py >> pz;
  //   std::cout << "normal: " << "{" << normalx << "," << normaly << "," <<normalz << "point: " << px << "," << py << "," << pz << std::endl;
  // init();
  //return plane;
//}
  glm::vec3 getN() {return normal; }
  glm::vec3 getP() {return p; }
  void setNorm (glm::vec3 norm) {normal = norm;}
  void setP (glm::vec3 point) {p = point;}
  //Plane(glm::vec3 normal, glm::vec3 p) : normal(normal), p(p) {}
private:
  glm::vec3 normal = {};
  glm::vec3 p = {};
};

