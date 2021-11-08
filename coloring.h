  glm::vec4 color(Collisionpoint point, Camera c, Light l) {

    GLfloat constantAttenuation = 0.5f;
    GLfloat linearAttenuation = 0.1f;
    GLfloat quadraticAttenuation = 0.05f;
    GLfloat rho = 0.5f;

    GLfloat dist = distance(point.getPosition(), l.getPosition());    

    GLfloat totalAttenuation = 1 / (constantAttenuation + linearAttenuation * dist + quadraticAttenuation * pow(dist, 2));
    Ray toLight(point.getPosition(), l.getPosition());
    Ray toCamera(point.getPosition(), c.getPosition());
    Ray reflectedRay(point.getPosition(), reflect(toLight.getDirection(), point.getNormal()));
    glm::vec3 color3 = ((point.materialv().get_k_a() * point.materialv().get_I_a() + (totalAttenuation * point.materialv().get_k_d() * point.materialv().get_I_d() * max(0.0f, dot(toLight.getDirection(), point.getNormal()))) + (totalAttenuation * point.materialv().get_k_s() * point.materialv().get_I_s() * pow(max(0.0f, dot(reflectedRay.getDirection(), toCamera.getDirection())), rho))));

    glm::vec4 color4 = {color3[0], color3[1], color3[2], 1.0f};
    return color4;
  }