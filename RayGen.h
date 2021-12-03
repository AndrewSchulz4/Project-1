#ifndef _Rayg_
#define _Rayg_
#include "GLInclude.h"
#include "classes.h"
//raygen
Ray raygen (Camera& cam, glm::vec3 cameraPos, int i, int j, int max_wid, int max_height, int view);
#endif