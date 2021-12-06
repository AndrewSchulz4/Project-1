////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief Contains main function to create a window and run engine that
///        repeatedly generates a framebuffer and displays it.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes

// STL
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <omp.h>
//#include <fstream>
#include <iomanip>
#include <vector>
// Engine
#include "GLInclude.h"
#include "classes.h"
#include "collision.h"
#include "coloring.h"
#include "input.h"
#include "raygen.h"


////////////////////////////////////////////////////////////////////////////////
// Global variables - avoid these
Plane mainPlane;
Camera mainCamera;
Light mainLight;
std::vector<Light> lights;
std::vector<Sphere> spheres_scene;

// Window
int g_width{900};
int g_height{768};

// Framebuffer
std::unique_ptr<glm::vec4[]> g_frame{nullptr}; ///< Framebuffer

// Frame rate
const unsigned int FPS = 60;
float g_frameRate{0.f};
std::chrono::high_resolution_clock::time_point g_frameTime{
  std::chrono::high_resolution_clock::now()};
float g_delay{0.f};
float g_framesPerSecond{0.f};

////////////////////////////////////////////////////////////////////////////////
// Functions

  //UNCOMMENT FOR DEBUGGING
  //   std::cout << "plane_norm: " << plane.getN()[0] << " " << plane.getN()[1] << " " << plane.getN()[2] << std::endl;
  //   std::cout << "plane_point: " << plane.getP()[0] << " " << plane.getP()[1] << " " << plane.getP()[2] << std::endl;


  // std::cout << "position: " << camera.getPosition()[0] << " " << camera.getPosition()[1] << " " << camera.getPosition()[2] << std::endl;
  // std::cout << "viewDirection: " << camera.getViewDirection()[0] << " " << camera.getViewDirection()[1] << " " << camera.getViewDirection()[2] << std::endl;
  // std::cout << "up: " << camera.getUpVector()[0] << " " << camera.getUpVector()[1] << " " << camera.getUpVector()[2] << std::endl;

  // std::cout << "right: " << camera.getRightVector()[0] << " " << camera.getRightVector()[1] << " " << camera.getRightVector()[2] << std::endl;

////////////////////////////////////////////////////////////////////////////////
/// @brief Initialize GL settings
void
initialize(GLFWwindow* _window) {
  glClearColor(0.f, 0.f, 0.f, 1.f);
  Sphere sphere1;
  sceneInput(mainPlane, mainCamera, mainLight);
  materialAndSphereInput(mainPlane, sphere1);
  
  //generating multiple lights and spheres with different colors
    glm::vec4 k_a = {0.0f, 0.0f, 1.0f, 1.0f};
    glm::vec4 I_a = {.3f, .3f, .3f, 1.0f};
    glm::vec4 k_d = k_a;
    glm::vec4 I_d = {.8f, .8f, .8f, 0.0};
    glm::vec4 k_s = {.9f,.9f, .9f, .9f};
    glm::vec4 I_s = {.8f, .8f, .8f, 0.0f};
    glm::vec4 k_a2 = {1.0f, 1.0f, 0.2f, 1.0f};
    Material mat(k_a, k_d, k_s, I_a, I_d, I_s);    
    Material mat2(k_a2, k_a2, k_s, I_a, I_d, I_s);
    glm::vec3 center = {-5.0f, 2.0f, -25.0f};
    glm::vec3 center2 = {5.0f, 2.0f, -20.0f};
    Sphere S(5, center, mat);
    Sphere S2(3, center2, mat2);
    spheres_scene.push_back(S);
    spheres_scene.push_back(S2);
    spheres_scene.push_back(sphere1);
    lights.push_back(mainLight);
    glm::vec3 lightpos = {10, 5, -10};
    Light light1(0, lightpos);
    lights.push_back(light1);

    
  g_frame = std::make_unique<glm::vec4[]>(g_width*g_height);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief Callback for resize of window
///
/// Responsible for setting window size (viewport) and projection matrix.
void resize(GLFWwindow* window, int _w, int _h) {
  g_width = _w;
  g_height = _h;

  // Viewport
  glfwGetFramebufferSize(window, &g_width, &g_height);
  glViewport(0, 0, g_width, g_height);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief Draw function for single frame
void
draw(GLFWwindow* _window, double _currentTime) {
  //////////////////////////////////////////////////////////////////////////////
  // Clear
  glClear(GL_COLOR_BUFFER_BIT);
  for(int i = 0; i < g_width*g_height; ++i)   
    g_frame[i] = glm::vec4(0.f, 0.4f, 0.4f, 0.f);

  //////////////////////////////////////////////////////////////////////////////
  // Draw

  // Simple static :P
  //std::cout << spheres_scene.size();
  glm::vec3 zero = {0.0, 0.0, 0.0};
  //std::cout << mainPlane.get_k_a()[0] << " " << mainPlane.get_k_a()[1] << " " << mainPlane.get_k_a()[2] << " " << mainPlane.get_k_a()[3] << std::endl;
  #pragma omp parallel
  {
   #pragma omp for
   for(int row = 0;  row < g_height; row++){
     for (int col = 0; col < g_width; col++){
       //std::cout << omp_get_thread_num() << std::endl;
       //0 = perspective ray generation, 1 = parallel ray generation
        Ray mainRay = raygen(mainCamera, mainCamera.getPosition(), row, col, g_width, g_height, 0);

        Collisionpoint hitPlane = collision(mainRay, mainPlane);
        glm::vec3 zero = {0, 0, 0};
        //testing for collision for each sphere from ray
        Collisionpoint hitSphere;

        for(int i = 0; i < spheres_scene.size(); i++)
        {
          Sphere sphere = spheres_scene[i];
          Collisionpoint hitSpheret = collision_sphere(mainRay, sphere);
          //if the ray hits both spheres take closer one
          //if(hitSpheret.getPosition() != zero)
            //std::cout << to_string(hitSpheret.getPosition()) << std::endl;
          if(hitSphere.getPosition() == zero && hitSpheret.getPosition() != zero)
            hitSphere = hitSpheret;
          if(hitSphere.getPosition() != zero && hitSpheret.getPosition() != zero)
          {
            //will render closest sphere
            if(distance(mainCamera.getPosition(), hitSphere.getPosition()) > distance(mainCamera.getPosition(), hitSpheret.getPosition()))
            {
                hitSphere = hitSpheret;
            }
          }
        }

          //if plane is hit
          if (hitPlane.getPosition() != zero){
            Shadow shadow = inShadow(hitPlane, lights, spheres_scene);
            if(shadow.shade()){
              glm::vec3 toLight = glm::normalize(mainLight.getPosition() - hitPlane.getPosition());
              glm::vec3 ambient =  (hitPlane.materialv().get_k_a() * hitPlane.materialv().get_I_a()); //* shadow.occlusion()
              g_frame[(row*g_width) + col] = glm::vec4(ambient[0], ambient[1], ambient[2], 1.0f);
            }
            else {
              //if not in shadow color normally
              g_frame[(row*g_width)+col] = color(hitPlane, mainCamera, lights);
            }
          }
            //if the ray has hit a sphere
            if (hitSphere.getPosition() != zero){
              g_frame[(row*g_width) + col] = color(hitSphere, mainCamera, lights);
            //     Ray* shadowRaySphere = NULL;
            // if (mainLight.getLightType() == 0)
            //     shadowRaySphere = new Ray(hitSphere.getPosition(), mainLight.getPosition());
            // if (mainLight.getLightType() == 1)
            //     shadowRaySphere = new Ray(hitSphere.getPosition(), mainLight.getPosition());
            // //if point on
            // Collisionpoint intersect = collision_sphere(*shadowRaySphere, spheres_scene[0]);
            // for(int i = 1; i < spheres_scene.size(); i++)
            // {
            //   Collisionpoint intersect = collision_sphere(*shadowRaySphere, spheres_scene[i]);
            // }
            // if(intersect.getPosition() != zero) {
            //   g_frame[(row*g_width) + col] = color(hitSphere, mainCamera, mainLight);
            // }
            // delete shadowRaySphere;
          }
      } 
   }
  }     
  //std::cout << to_string(spheres_scene[0].getCenter());
  glDrawPixels(g_width, g_height, GL_RGBA, GL_FLOAT, g_frame.get());
}

////////////////////////////////////////////////////////////////////////////////
/// @brief Main application loop
void
run(GLFWwindow* _window) {
  using namespace std::chrono;

  std::cout << "Starting main loop" << std::endl;

  while(!glfwWindowShouldClose(_window)) {
    draw(_window, glfwGetTime());
    ////////////////////////////////////////////////////////////////////////////
    // Show
    glfwSwapBuffers(_window);
    glfwPollEvents();

    ////////////////////////////////////////////////////////////////////////////
    // Record frame time
    high_resolution_clock::time_point time = high_resolution_clock::now();
    g_frameRate = duration_cast<duration<float>>(time - g_frameTime).count();
    g_frameTime = time;
    g_framesPerSecond = 1.f/(g_delay + g_frameRate);
    printf("FPS: %6.2f\n", g_framesPerSecond);

    spheres_scene[1].animateFrame(g_frameRate);
   // spheres_scene[2].animateFrame(g_frameRate);
    //for (int i = 0; i < spheres_scene.size(); i++){
     // spheres_scene[i].animateFrame(g_frameRate);
   //}
    

    ////////////////////////////////////////////////////////////////////////////
    // Delay to fix the frame-rate
    g_delay = std::max(0.f, 1.f/FPS - g_frameRate);
    std::this_thread::sleep_for(std::chrono::microseconds(
        static_cast<long int>(g_delay*1000)));
  }

  std::cout << "Ending main loop" << std::endl;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief Callback function for keyboard input
/// @param _window
/// @param _key Key
/// @param _scancode Platform specific keycode
/// @param _action Action, e.g., pressed or released
/// @param _mods Keyboard modifiers
void
keyCallback(GLFWwindow* _window, int _key, int _scancode,
           int _action, int _mods) {
  if(_action == GLFW_PRESS) {
    switch(_key) {
      // Escape key : quit application
      case GLFW_KEY_ESCAPE:
        std::cout << "Closing window" << std::endl;
        glfwSetWindowShouldClose(_window, GLFW_TRUE);
        break;
        // Arrow keys
      case GLFW_KEY_Z:
      {
        glm::vec3 temp = {0,1,0};
        mainCamera.updatePosition(temp);
        break;
      }
      case GLFW_KEY_X:
      {
        glm::vec3 temp = {0,-1,0};
        mainCamera.updatePosition(temp);
        break;
      }
      case GLFW_KEY_A:
      {
        glm::vec3 temp = {-1,0,0};
        mainCamera.updatePosition(temp);
        break;

      }
      case GLFW_KEY_D:
      {
        glm::vec3 temp = {1,0,0};
        mainCamera.updatePosition(temp);
        break;

      }
      case GLFW_KEY_W:
      {
        glm::vec3 temp = {0,0,-1};
        mainCamera.updatePosition(temp);
        break;

      }
      case GLFW_KEY_S:
      {
        glm::vec3 temp = {0,0,1};
        mainCamera.updatePosition(temp);
        break;

      }
      case GLFW_KEY_I: {
        glm::vec3 temp = {0, 0, -1};
        lights[0].updatePosition(temp);
        break;
      }
      case GLFW_KEY_J: {
        glm::vec3 temp = {-1, 0, 0};
        lights[0].updatePosition(temp);
        break;
      }
      case GLFW_KEY_K: {
        glm::vec3 temp = {0, 0, 1};
        lights[0].updatePosition(temp);
        break;
      }
      case GLFW_KEY_L: {
        glm::vec3 temp = {1, 0, 0};
        lights[0].updatePosition(temp);
        break;
      }
      case GLFW_KEY_O: {
        glm::vec3 temp = {0, -1, 0};
        lights[0].updatePosition(temp);
        break;
      }
      case GLFW_KEY_P: {
        glm::vec3 temp = {0, 1, 0};
        lights[0].updatePosition(temp);
        break;
      }
      case GLFW_KEY_LEFT:
      {
        glm::vec3 newcent = {spheres_scene[0].getCenter()[0] - 1, spheres_scene[0].getCenter()[1], spheres_scene[0].getCenter()[2]};
        spheres_scene[0].changeCenter(newcent);
        break;
      }
      case GLFW_KEY_RIGHT:
      {
        glm::vec3 newcent = {spheres_scene[0].getCenter()[0] + 1, spheres_scene[0].getCenter()[1], spheres_scene[0].getCenter()[2]};
        spheres_scene[0].changeCenter(newcent);
        break;
      }
      case GLFW_KEY_UP:
      {
        glm::vec3 newcent = {spheres_scene[0].getCenter()[0], spheres_scene[0].getCenter()[1], spheres_scene[0].getCenter()[2] - 1};
        spheres_scene[0].changeCenter(newcent);

        break;
      }
      case GLFW_KEY_DOWN:
      {
        glm::vec3 newcent = {spheres_scene[0].getCenter()[0], spheres_scene[0].getCenter()[1], spheres_scene[0].getCenter()[2] + 1};
        spheres_scene[0].changeCenter(newcent);
        break;
      }
      case GLFW_KEY_M:
      {
        glm::vec3 newcent = {spheres_scene[0].getCenter()[0], spheres_scene[0].getCenter()[1] + 1, spheres_scene[0].getCenter()[2]};
        spheres_scene[0].changeCenter(newcent);
        break;
      }
      case GLFW_KEY_N:
      {
        glm::vec3 newcent = {spheres_scene[0].getCenter()[0], spheres_scene[0].getCenter()[1] - 1, spheres_scene[0].getCenter()[2]};
        spheres_scene[0].changeCenter(newcent);
        break;
      }

        // Unhandled
      default:
        std::cout << "Unhandled key: " << _key << std::endl;
        break;
    }
  }
}

////////////////////////////////////////////////////////////////////////////////
// Main

////////////////////////////////////////////////////////////////////////////////
/// @brief main
/// @param _argc Count of command line arguments
/// @param _argv Command line arguments
/// @return Application success status
int
main(int _argc, char** _argv) {
  //////////////////////////////////////////////////////////////////////////////
  // Initialize
  std::cout << "Initializing GLFWWindow" << std::endl;
  // GLFW
  if(!glfwInit()) {
    std::cerr << "GLFW Cannot initialize" << std::endl;
    const char* err_msg;
    int error_code = glfwGetError(&err_msg);
    std::cerr << "Error " << error_code << ": " << err_msg << std::endl;
    return 1;
  }

  GLFWwindow* window = glfwCreateWindow(
    g_width, g_height, "Spiderling: A Rudamentary Game Engine", NULL, NULL);
  if(!window) {
    std::cerr << "GLFW Cannot create window" << std::endl;
    const char* err_msg;
    int error_code = glfwGetError(&err_msg);
    std::cerr << "Error " << error_code << ": " << err_msg << std::endl;
    return 1;
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  glfwGetFramebufferSize(window, &g_width, &g_height);
  glViewport(0, 0, g_width, g_height);  // Initialize viewport


  // Assign callback functions
  std::cout << "Assigning Callback functions" << std::endl;
  glfwSetFramebufferSizeCallback(window, resize);
  glfwSetKeyCallback(window, keyCallback);

  // Program initialize
  std::cout << "Initializing application" << std::endl;
  initialize(window);

  //////////////////////////////////////////////////////////////////////////////
  // Main loop
  run(window);

  //////////////////////////////////////////////////////////////////////////////
  // Cleanup GLFW Window
  std::cout << "Destroying GLFWWindow" << std::endl;
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
