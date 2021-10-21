//file for lighting and possibly shadows
//will need class for light, material
glm::vec4 getColor(const vector<Light>& lights,
                    const Material& material, 
                    const glm::vec3& point,
                    const glm::vec3& normal) {
    glm::vec4 final_color;
    for(const Light& light : lights)
    {
        glm::vec4 ambient =
        glm::vec4 diffuse = 
        glm::vec4 specular = 
        final_color = ambient + diffuse + specular;
    }
    return final_color;
}

bool isShadow(){
    //draw ray from collision with object to light
    //if ray intersects with an object 
};