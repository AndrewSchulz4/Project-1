  glm::vec4 color(Collisionpoint point, Camera c, Light l) {

    GLfloat constantAttenuation = 0.5f;
    GLfloat linearAttenuation = 0.1f;
    GLfloat quadraticAttenuation = 0.05f;
    GLfloat rho = 100.0f; //causes sphere weird shading when above 0

    GLfloat dist = distance(point.getPosition(), l.getPosition());    

    GLfloat totalAttenuation = 1;// / (constantAttenuation + linearAttenuation * dist + quadraticAttenuation * pow(dist, 2));

    //vectors take light - point and normalize
    //glm::normalize
    glm::vec3 toLight = glm::normalize(l.getPosition() - point.getPosition());
    glm::vec3 toCamera = glm::normalize(point.getPosition() - c.getPosition());

    //reflected ray to vector
    // r = d - 2(d * n) * n
    glm::vec3 reflectedRay = toLight - (2 * glm::dot(toLight, point.getNormal())) * point.getNormal();
    //glm::vec3 reflectedRay = reflect(toLight, point.getNormal()) - point.getPosition();
    //ambient correct
    glm::vec3 ambient = point.materialv().get_k_a() * point.materialv().get_I_a();
    //diffuse correct
    glm::vec3 diffuse = totalAttenuation * point.materialv().get_k_d() * point.materialv().get_I_d() * max(0.0f, dot(toLight, point.getNormal()));
    //specular acting weird, sphere has no specular + plane has odd lighting
    glm::vec3 specular = totalAttenuation * point.materialv().get_k_s() * point.materialv().get_I_s() * pow(max(0.0f, dot(toCamera, reflectedRay)), rho);

    glm::vec3 color3 =  ambient + diffuse + specular;

    glm::vec4 color4 = {color3[0], color3[1], color3[2], 1.0f};
    return color4;
  }