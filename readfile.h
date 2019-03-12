// Readfile definitions
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>
#include <iostream>

typedef glm::mat3 mat3;
typedef glm::mat4 mat4; 
typedef glm::vec3 vec3; 
typedef glm::vec4 vec4;

using namespace std;
constexpr float kEpsilon = 1e-3;

#include "Shape.h"
//#include "Transform.h"
#include "Light.h"
#include "Sphere.h"
#include "Triangle.h"
#include "variables.h"

void matransform(stack<mat4> &transfstack, float *values);
void rightmultiply(const mat4 M, stack<mat4> &transfstack);
bool readvals(stringstream &s, const int numvals, float *values);
void readfile(const char *filename);
