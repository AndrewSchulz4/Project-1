  glm::vec4 colorPlane(glm::vec3 point, Plane p, Camera c, Light l) {

    GLfloat constantAttenuation = 0.5f;
    GLfloat linearAttenuation = 0.1f;
    GLfloat quadraticAttenuation = 0.05f;
    GLfloat rho = 0.5f;

    GLfloat dist = distance(point, l.getPosition());    

    GLfloat totalAttenuation = 1 / (constantAttenuation + linearAttenuation * dist + quadraticAttenuation * pow(dist, 2));
    Ray toLight(point, l.getPosition());
    Ray toCamera(point, c.getPosition());
    Ray reflectedRay(p.getP(), reflect(toLight.getDirection(), p.getN()));
    glm::vec3 color3 = ((p.get_k_a() * p.get_I_a() + (totalAttenuation * p.get_k_d() * p.get_I_d() * max(0.0f, dot(toLight.getDirection(), p.getN()))) + (totalAttenuation * p.get_k_s() * p.get_I_s() * pow(max(0.0f, dot(reflectedRay.getDirection(), toCamera.getDirection())), rho))));

    glm::vec4 color4 = {color3[0], color3[1], color3[2], 1.0f};
    return color4;
  }

glm::vec4 colorSphere(glm::vec3 point, Sphere s, Camera c, Light l) {

GLfloat constantAttenuation = 0.5f;
GLfloat linearAttenuation = 0.1f;
GLfloat quadraticAttenuation = 0.05f;
GLfloat rho = 0.5f;

GLfloat dist = distance(point, l.getPosition());    

GLfloat totalAttenuation = 1 / (constantAttenuation + linearAttenuation * dist + quadraticAttenuation * pow(dist, 2));
Ray toLight(point, l.getPosition());
Ray toCamera(point, c.getPosition());
//not sure if I use point or center of sphere (position for plane)
Ray reflectedRay(point, reflect(toLight.getDirection(), ((point-s.getCenter())/s.getRadius())));
glm::vec3 color3 = ((s.get_k_a() * s.get_I_a() + (totalAttenuation * s.get_k_d() * s.get_I_d() * max(0.0f, dot(toLight.getDirection(), (point-s.getCenter())/s.getRadius()))) + (totalAttenuation * s.get_k_s() * s.get_I_s() * pow(max(0.0f, dot(reflectedRay.getDirection(), toCamera.getDirection())), rho))));

glm::vec4 color4 = {color3[0], color3[1], color3[2], 1.0f};
return color4;
}