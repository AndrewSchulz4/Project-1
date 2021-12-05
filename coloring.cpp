  #include "coloring.h"
  #include "collision.h"
  #include <iostream>
  glm::vec4 color(Collisionpoint point, Camera c, std::vector<Light> l) {

    GLfloat constantAttenuation = 0.5f;
    GLfloat linearAttenuation = 0.1f;
    GLfloat quadraticAttenuation = 0.05f;
    GLfloat rho = 50.0f; //causes sphere weird shading when above 0
    GLfloat rho = point.materialv().getRho(); //causes sphere weird shading when above 0

    // Ray* toLight = NULL;
    // if (l.getLightType() == 0){ //point light calcs
@ -25,7 +26,7 @@
    glm::vec3 color3 = {0, 0, 0};
    for(int i = 0; i < l.size(); i++)
    {
      GLfloat dist = .5 * distance(point.getPosition(), l[i].getPosition());
      GLfloat dist = .6 * distance(point.getPosition(), l[i].getPosition());
      GLfloat totalAttenuation = 1 / (constantAttenuation + linearAttenuation * dist + quadraticAttenuation * dist * dist);
          //vectors take light - point and normalize
      //glm::normalize
@ -54,11 +55,12 @@
    //delete toLight;
    return color4;
  }

  bool inShadow(Collisionpoint& intersect, std::vector<Light> lights, std::vector<Sphere>& spheres_scene)
  //tried to implement soft shadowing but in order to look good, I need to sample surrounding pixels
  Shadow inShadow(Collisionpoint& intersect, std::vector<Light> lights, std::vector<Sphere>& spheres_scene)
  {
            Ray* shadowRayPlane = NULL;
            glm::vec3 zero = {0.0, 0.0, 0.0};
            GLfloat occlusion;
            for(int j = 0; j < lights.size(); j++)
            {
              if (lights[j].getLightType() == 0)
@ -67,8 +69,12 @@
              // shadowRayPlane = new Ray(intersect.getPosition(), intersect.getPosition() + lights[j].getDirection());
              //if ray from plane point to light hits the sphere (in the shadow)
              Collisionpoint intersects = collision_sphere(*shadowRayPlane, spheres_scene[0]);
              if (intersects.getPosition() != zero)
                return true;
              if (intersects.getPosition() != zero){
                occlusion = occlusiondist(intersect, intersects, lights[j]);
                Shadow S(occlusion, true);
                return S;
              }
            
              for(int i = 1; i < spheres_scene.size(); i++)
              {
                //if there is a sphere in way of light, need to check both
@ -77,15 +83,28 @@
                if(intersects.getPosition() == zero)
                {
                  intersects = intersects1;
                  if (intersects.getPosition() != zero)
                    return true;
                  if (intersects.getPosition() != zero){
                    occlusion = occlusiondist(intersect, intersects, lights[j]);
                    Shadow S(occlusion, true);
                    return S;
                  }
                }
                //issue: collision with one sphere and next sphere checked there is no collision, first set intersect = zero and then if 0 do else do nothing, dont change
              }
              if (intersects.getPosition() != zero){
                //if sphere in path return in shadow (T)
                return true;
              }
              // if (intersects.getPosition() != zero){
              //   //if sphere in path return in shadow (T)
              //   occlusion = occlusiondist(intersect, intersects, lights[i])
              //   Shadow S(occlusion, true);
              //   return S;
              // }
            } 
              return false;
            
            Shadow X(0.0f, false);
            return X;
  }
  //where x is the plane collision, y is collision with sphere, light is to light source
  GLfloat occlusiondist(Collisionpoint x, Collisionpoint y, Light l)
  {
    GLfloat ratio = distance(x.getPosition(), y.getPosition()) / distance(x.getPosition(), l.getPosition());
    return ratio;
  }