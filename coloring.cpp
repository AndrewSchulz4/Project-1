  #include "coloring.h"
  #include "collision.h"
  #include <iostream>
  glm::vec4 color(Collisionpoint point, Camera c, std::vector<Light> l) {

    GLfloat constantAttenuation = 0.5f;
    GLfloat linearAttenuation = 0.1f;
    GLfloat quadraticAttenuation = 0.05f;
    GLfloat rho = point.materialv().getRho(); //causes sphere weird shading when above 0

    // Ray* toLight = NULL;
    // if (l.getLightType() == 0){ //point light calcs
      
    //   dist = distance(point.getPosition(), l.getPosition());   
    //   totalAttenuation = 1 / (constantAttenuation + linearAttenuation * dist + quadraticAttenuation * (dist * dist));
    //   toLight = new Ray(point.getPosition(), l.getPosition());

    //   }
    // if (l.getLightType() == 1){
    //   dist = 10;
    //   totalAttenuation = 1 / (constantAttenuation + linearAttenuation * dist + quadraticAttenuation * (dist * dist));
    //   glm::vec3 dirr = point.getPosition() + l.getDirection();
    //   toLight = new Ray(point.getPosition(), dirr);
    // }

    glm::vec3 color3 = {0, 0, 0};
    for(int i = 0; i < l.size(); i++)
    {
      GLfloat dist = .6 * distance(point.getPosition(), l[i].getPosition());
      GLfloat totalAttenuation = 1 / (constantAttenuation + linearAttenuation * dist + quadraticAttenuation * dist * dist);
          //vectors take light - point and normalize
      //glm::normalize
      glm::vec3 toLight = glm::normalize(l[i].getPosition() - point.getPosition());
      glm::vec3 toCamera = glm::normalize(point.getPosition() - c.getPosition());

      //reflected ray to vector
      // r = d - 2(d * n) * n
      glm::vec3 reflectedRay = toLight - (2 * glm::dot(toLight, point.getNormal())) * point.getNormal();
      //glm::vec3 reflectedRay = reflect(toLight, point.getNormal()) - point.getPosition();
      //ambient correct
      glm::vec3 ambient = .5 * point.materialv().get_k_a() * point.materialv().get_I_a();
      //diffuse correct
      glm::vec3 diffuse = totalAttenuation * point.materialv().get_k_d() * point.materialv().get_I_d() * std::max(0.0f, dot(toLight, point.getNormal()));
      //specular acting weird, sphere has no specular + plane has odd lighting
      glm::vec3 specular = totalAttenuation * point.materialv().get_k_s() * point.materialv().get_I_s() * pow(std::max(0.0f, dot(toCamera, reflectedRay)), rho);

      color3 += ambient + diffuse + specular;
    }


    

    glm::vec4 color4 = {color3[0], color3[1], color3[2], 1.0f};

    //delete toLight;
    return color4;
  }
  //tried to implement soft shadowing but in order to look good, I need to sample surrounding pixels
  Shadow inShadow(Collisionpoint& intersect, std::vector<Light> lights, std::vector<Sphere>& spheres_scene)
  {
            Ray* shadowRayPlane = NULL;
            glm::vec3 zero = {0.0, 0.0, 0.0};
            GLfloat occlusion;
            for(int j = 0; j < lights.size(); j++)
            {
              if (lights[j].getLightType() == 0)
                shadowRayPlane = new Ray(intersect.getPosition(), intersect.getPosition() - lights[j].getPosition());  
              //else if (lights[j].getLightType() == 1)
              // shadowRayPlane = new Ray(intersect.getPosition(), intersect.getPosition() + lights[j].getDirection());
              //if ray from plane point to light hits the sphere (in the shadow)
              Collisionpoint intersects = collision_sphere(*shadowRayPlane, spheres_scene[0]);
              if (intersects.getPosition() != zero){
                occlusion = occlusiondist(intersect, intersects, lights[j]);
                Shadow S(occlusion, true);
                return S;
              }
            
              for(int i = 1; i < spheres_scene.size(); i++)
              {
                //if there is a sphere in way of light, need to check both
                Sphere sphere = spheres_scene[i];
                Collisionpoint intersects1 = collision_sphere(*shadowRayPlane, sphere);
                if(intersects.getPosition() == zero)
                {
                  intersects = intersects1;
                  if (intersects.getPosition() != zero){
                    occlusion = occlusiondist(intersect, intersects, lights[j]);
                    Shadow S(occlusion, true);
                    return S;
                  }
                }
                //issue: collision with one sphere and next sphere checked there is no collision, first set intersect = zero and then if 0 do else do nothing, dont change
              }
              // if (intersects.getPosition() != zero){
              //   //if sphere in path return in shadow (T)
              //   occlusion = occlusiondist(intersect, intersects, lights[i])
              //   Shadow S(occlusion, true);
              //   return S;
              // }
            } 
            
            Shadow X(0.0f, false);
            return X;
  }
  //where x is the plane collision, y is collision with sphere, light is to light source
  GLfloat occlusiondist(Collisionpoint x, Collisionpoint y, Light l)
  {
    GLfloat ratio = distance(x.getPosition(), y.getPosition()) / distance(x.getPosition(), l.getPosition());
    return ratio;
  }