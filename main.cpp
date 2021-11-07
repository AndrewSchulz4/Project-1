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
//#include <fstream>
#include <iomanip>
// Engine
#include "GLInclude.h"
#include "classes.h"
#include "collision.h"
#include "properraygen.h"
#include "input.h"
////////////////////////////////////////////////////////////////////////////////
// Global variables - avoid these
Plane mainPlane;
Camera mainCamera;
Light mainLight;
Sphere sphere1;
// Window
int g_width{1360};
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

  glm::vec4 colorPlane(glm::vec3 point, Plane p, Camera c, Light l) {

    GLfloat constantAttenuation = 0.5f;
    GLfloat linearAttenuation = 0.1f;
    GLfloat quadraticAttenuation = 0.05f;
    GLfloat rho = 0.5f;

    // glm::vec4 k_a = {0.9f, 0.4f, 0.2f, 1.0f};
    // glm::vec4 I_a = {0.3f, 0.3f, 0.3f, 1.0f};
    // glm::vec4 k_d = k_a;
    // glm::vec4 I_d = {0.8f, 0.8f, 0.8f, 0.0f};
    // glm::vec4 k_s = {0.7f, 0.7f, 0.7f, 0.5f};
    // glm::vec4 I_s = I_d;
    //glm::vec3 lightPos = {0.0f, 5.0f, 0.0f};
    

    GLfloat dist = distance(point, l.getPosition());    

    GLfloat totalAttenuation = 1 / (constantAttenuation + linearAttenuation * dist + quadraticAttenuation * pow(dist, 2));
    Ray toLight(point, l.getPosition());
    Ray toCamera(point, c.getPosition());
    Ray reflectedRay(p.getP(), reflect(toLight.getDirection(), p.getN()));
    glm::vec3 color3 = ((p.get_k_a() * p.get_I_a() + (totalAttenuation * p.get_k_d() * p.get_I_d() * max(0.0f, dot(toLight.getDirection(), p.getN()))) + (totalAttenuation * p.get_k_s() * p.get_I_s() * pow(max(0.0f, dot(reflectedRay.getDirection(), toCamera.getDirection())), rho))));

    glm::vec4 color4 = {color3[0], color3[1], color3[2], 1.0f};
    return color4;
  }

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

  sceneInput(mainPlane, mainCamera, mainLight);
  materialAndSphereInput(mainPlane, sphere1);

  //Plane plane;
  //sceneInput(plane);
  //std::cout << plane.normalx << " " << plane.normaly << " " << plane.normalz;

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
    g_frame[i] = glm::vec4(0.f, 0.0f, 0.f, 0.f);

  //////////////////////////////////////////////////////////////////////////////
  // Draw

  // Simple static :P

//  for(int i = 0; i < g_width*g_height; i++)
//    g_frame[i] = glm::vec4(float(rand())/RAND_MAX, float(rand())/RAND_MAX, float(rand())/RAND_MAX, 1.f);

  glm::vec3 zero = {0.0, 0.0, 0.0};
  std::cout << mainPlane.get_k_a()[0] << " " << mainPlane.get_k_a()[1] << " " << mainPlane.get_k_a()[2] << " " << mainPlane.get_k_a()[3] << std::endl;
   for(int row = 0;  row < g_height; row++){
     for (int col = 0; col < g_width; col++){
        Ray mainRay = raygen(mainCamera, mainCamera.getPosition(), row, col, g_width, g_height);

        glm::vec3 hitPlane = collision(mainRay, mainPlane);
        glm::vec3 hitSphere = collision_sphere(mainRay, sphere1);
        if (hitPlane != zero){
          Ray shadowRayPlane(hitPlane, mainLight.getPosition());
          if (collision_sphere(shadowRayPlane, sphere1) != zero){
            g_frame[(row*g_width) + col] = glm::vec4(0.23f, 0.22f, 0.23f, 1.0f);

          }
          else {
            g_frame[(row*g_width)+col] = colorPlane(hitPlane, mainPlane, mainCamera, mainLight);

          }
        }
        //plane rendering as color white
        // sphere should render as color red
        if (hitSphere != zero){
          Ray shadowRaySphere(hitSphere, mainLight.getPosition());
          if(collision_sphere(shadowRaySphere, sphere1) != zero) {
            g_frame[(row*g_width)+col] = glm::vec4(0.31f,0.09f,0.41f, 1.f);

          }
          else {
            g_frame[(row*g_width) + col] = glm::vec4(0.23f, 0.22f, 0.23f, 1.0f);

          }
        }
     }      
   }

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
      case GLFW_KEY_LEFT:
      case GLFW_KEY_RIGHT:
        break;
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
