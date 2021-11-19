///@file
///@brief Utilities for compiling shaders

#ifndef _COMPILE_SHADERS_H
#define _COMPILE_SHADERS_H

#include <string>

#include "GLInclude.h"

///@brief Compile a vertex shader and fragment shader together
///@param _vertexShader Filename of vertex shader
///@param _fragmentShader Filename of fragment shader
///@return GL progam identifier

GLuint compileProgram(const std::string& _vertexShader, const std::string& _fragmentShader);
#endif