
#include <fstream>
#include <iostream>
#include "classes.h"
void materialAndSphereInput(Plane& plane, Sphere& s) {
      std::ifstream input;
      input.open("materialsandsphere.txt");
      glm::vec4 plane_k_a;
      glm::vec4 plane_k_d;
      glm::vec4 plane_k_s;
      glm::vec4 plane_I_a;
      glm::vec4 plane_I_d;
      glm::vec4 plane_I_s;
      glm::vec3 spherePos;
      GLfloat val1;
      GLfloat val2;
      GLfloat val3;
      GLfloat val4;
      GLfloat radius;
      std::string category;
      std::string type;
      while(input >> category >> type >> val1 >> val2 >> val3 >> val4) {
        if (category == "Plane") {
          if (type == "k_a") {
            plane_k_a = {val1, val2, val3, val4};
          }
          if (type == "k_d") {
            plane_k_d = {val1, val2, val3, val4};
          }
          if (type == "k_s") {
            plane_k_s = {val1, val2, val3, val4};
          }
          if (type == "I_a") {
            plane_I_a = {val1, val2, val3, val4};
          }
          if (type == "I_d") {
            plane_I_d = {val1, val2, val3, val4};
          }
          if (type == "I_s") {
            plane_I_s = {val1, val2, val3, val4};
          }
        }
        if (category == "Sphere") {
          if (type == "sphere_values") {
            radius = val1;
            spherePos = {val2, val3, val4};
          }
        }
      }
      
      Material M(plane_k_a, plane_k_d, plane_k_s, plane_I_a, plane_I_d, plane_I_s);
      plane.setM(M);
      std::cout << to_string(plane.getM().get_I_a()) << std::endl;
      s.change(radius, spherePos);
      s.setM(M);
      std::cout << to_string(s.getM().get_I_a()) << std::endl;
}
void sceneInput(Plane& plane, Camera& camera, Light& light) {
  std::ifstream input;
  std::string category;
  std::string type;
  GLfloat val1;
  GLfloat val2;
  GLfloat val3;


  glm::vec3 planeNorm;
  glm::vec3 planePoint;
  glm::vec3 camPosition;
  glm::vec3 camViewDirection;
  glm::vec3 camUp;
  glm::vec3 camRight;
  glm::vec3 lightPosition;
  int lightType;

  float l,r,b,t,d;
  
  input.open("scene.txt");
  while(input >> category >> type >> val1 >> val2 >> val3) {

    if (category == "Plane") {
      if (type == "plane_normal"){
        planeNorm = {val1, val2, val3};
      }
      if (type == "plane_point") {
        planePoint = {val1, val2, val3};
      }
    }
    else if (category == "Camera") {
      if (type == "camera_position") {
        camPosition = {val1, val2, val3};
      }
      if (type == "camera_viewDirection") {
        camViewDirection = {val1, val2, val3};
      }
      if (type == "camera_up") {
        camUp = {val1, val2, val3};
      }
      if (type == "camera_right") {
        camRight = {val1, val2, val3};
      }
      if (type == "camera_LR") {
        l = val1;
        r = val2;
      }
      if (type == "camera_TB"){
        t = val1;
        b = val2;
      }
      if (type == "camera_D")
      {
      d = val1;
      }
  
    }
    else if (category == "Light") {
      if (type == "light_position") {
        lightPosition = {val1, val2, val3};
      }
      if (type == "light_type"){
        lightType = val1;
      }
    }
  }
    plane = Plane(planeNorm, planePoint);
    camera = Camera(camPosition, camViewDirection, camUp, camRight, l, r, b, t, d);
    light = Light(lightType, lightPosition);
}