  glm::vec4 color(Collisionpoint point, Camera c, Light l) {

    GLfloat constantAttenuation = 0.5f;
    GLfloat linearAttenuation = 0.1f;
    GLfloat quadraticAttenuation = 0.05f;
    GLfloat rho = 0.3f; 
    GLfloat dist = 0;
    GLfloat totalAttenuation = 0;

    Ray* toLight = NULL;
    if (l.getLightType() == 0){ //point light calcs
      
      dist = distance(point.getPosition(), l.getPosition());   
      totalAttenuation = 1 / (constantAttenuation + linearAttenuation * dist + quadraticAttenuation * (dist * dist));
      toLight = new Ray(point.getPosition(), l.getPosition());

      }
      if (l.getLightType() == 1){
        dist = 10;
        totalAttenuation = 1 / (constantAttenuation + linearAttenuation * dist + quadraticAttenuation * (dist * dist));
        glm::vec3 dirr = point.getPosition() + l.getDirection();
        toLight = new Ray(point.getPosition(), dirr);
      }

      

    Ray toCamera(point.getPosition(), c.getPosition());
    Ray reflectedRay(point.getPosition(), reflect(toLight->getDirection(), point.getNormal()));
    glm::vec3 color3 = ((point.materialv().get_k_a() * point.materialv().get_I_a() + (totalAttenuation * point.materialv().get_k_d() * point.materialv().get_I_d() * max(0.0f, dot(toLight->getDirection(), point.getNormal()))) + (totalAttenuation * point.materialv().get_k_s() * point.materialv().get_I_s() * pow(max(0.0f, dot(toCamera.getDirection(), reflectedRay.getDirection())), rho))));

    glm::vec4 color4 = {color3[0], color3[1], color3[2], 1.0f};

    delete toLight;
    return color4;
  }