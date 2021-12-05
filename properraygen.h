//This function to be called from a for loop in main
Ray raygen (Camera& cam, glm::vec3 cameraPos, int i, int j, int max_wid, int max_height, int view) {
            // glm::vec3 viewDirection = {0, 0, -1}; //Temp for now
            // glm::vec3 up = {0,1,0};
            // glm::vec3 right = {1,0,0};
    //float FOV = glm::pi<float>()/4; //FOV is double this number, FOV at 90 degrees rn, (pi/4 = 45)

    float r,l,t,b,d;
    d = cam.getD();
    r = cam.getR();
    l = cam.getL(); 
    t = cam.getT();
    b = cam.getB();
   // std::cout << "LRBTD" << l << " , " << r << " , " << b << " , " << t << " , " << d << " , " << std::endl;

    float theta = l + ((r-l)/(float)max_wid) * ((float)i+0.5); //Sigma Theta need to be switched for some reason? 
    float sigma = b + ((t-b)/(float)max_height) * ((float)j+0.5);
    
    glm::vec3 w_ray(0,0,1);
    glm::vec3 u_ray(0,1,0);
    glm::vec3 v_ray(1,0,0);


    if (view == 0) {
    w_ray = w_ray * d * -1;
    u_ray = u_ray * theta;
    v_ray = v_ray * sigma;

    glm::vec3 dir_ray = {w_ray.x + u_ray.x + v_ray.x, w_ray.y + u_ray.y + v_ray.y, w_ray.z + u_ray.z + v_ray.z};
    Ray newRay (cam.getPosition(), dir_ray);
    return newRay;
    }
    else {
        glm::vec3 dir_ray = u_ray * -1;
        glm::vec3 ray_origin = {u_ray.x + v_ray.x, u_ray.y + v_ray.y, u_ray.z + v_ray.z};
        Ray newRay (ray_origin, dir_ray);
        return newRay;

    }
}
