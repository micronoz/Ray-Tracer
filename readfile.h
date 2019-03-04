// Readfile definitions
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>
#include <vector>

using namespace std;

constexpr float kEpsilon = 1e-8;

#include "Transform.h"
#include "Sphere.h"
#include "Triangle.h"
#include "variables.h"

void matransform(stack<mat4> &transfstack, float *values);
void rightmultiply(const mat4 &M, stack<mat4> &transfstack);
bool readvals(stringstream &s, const int numvals, float *values);
void readfile(const char *filename);
