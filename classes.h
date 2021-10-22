//#include "GLInclude.h"

class Ray {
    public:
    glm::vec3 getOrigin() { return origin; }
    glm::vec3 getDirection() { return direction; }
    Ray(glm::vec3 ori, glm::vec3 dir) { origin = ori; direction = dir;}
    
    private:
    glm::vec3 origin;
    glm::vec3 direction;
};

class Plane {
public:

  Plane(){
    normalx,normaly,normalz,px,py,pz = 0;
  }
  void init() {
      normal = {normalx, normaly, normalz};
      p = {px, py, pz};
  }

  void planeMaker() {
  std::ifstream sceneInput;
  sceneInput.open("scene.txt");    
  while(sceneInput)
    sceneInput >> normalx >> normaly >> normalz >> px >> py >> pz;
    std::cout << "normal: " << "{" << normalx << "," << normaly << "," <<normalz << "point: " << px << "," << py << "," << pz << std::endl;
  init();
  //return plane;
}

  glm::vec3 getN() {return normal; }
  glm::vec3 getP() {return p; }
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