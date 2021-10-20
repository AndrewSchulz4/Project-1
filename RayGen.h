
//This function to be called from a for loop in main
glm::vec3 raygen (glm::vec3 cameraPos, int row, int col, int max_wid, int max_height) {
            glm::vec3 viewDirection = {0, 0, 1}; //Temp for now
            glm::vec3 up = {0,1,0};
            glm::vec3 right = {1,0,0}
            float FOV = 3.14/4; //FOV is double this number, FOV at 90 degrees rn, (pi/4 = 45)


            //Here we are trying to get an angle to rotate the vector 
            //We use the FOV and pixels row/col to find how much to rotate by

            float newWid = max_wid / 2;
            float sidewaysRatio = 0;
            if (col < newWid) { //Trying to get a ratio from 0-1 where 0 represents centerline and 1 the boundary
                sidewaysRatio = (col / newWid) - 1;
                sidewaysRatio = FOV * sidewaysRatio;
            } else {
                sidewaysRatio = (col / newWid) - 1; 
                sidewaysRatio = FOV * sidewaysRatio;
            }

            

            
            float newHeight = max_height / 2;
            float upwaysRatio = 0;
            if (col < newWid) {
                upwaysRatio = (row / newHeight) - 1;
                upwaysRatio = FOV * upwaysRatio;
            } else {
                upwaysRatio = (row / newHeight) - 1; 
                upwaysRatio = FOV * upwaysRatio;
            }

            //uncomment these for testing 
            //std::cout << "oldView: " << viewDirection.x << "," << viewDirection.y << "," << viewDirection.z << std::endl;

            viewDirection =  glm::rotate(viewDirection, upwaysRatio, up);
            viewDirection =  glm::rotate(viewDirection, upwaysRatio, right);


            glm::vec3 newRay = cameraPos + viewDirection; //gives us a parrellel ray pointing in view direction
           // std::cout << "newView: " << viewDirection.x << "," << viewDirection.y << "," << viewDirection.z<< std::endl;
            return newRay;


    
}
