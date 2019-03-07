#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>
#include <iostream>

typedef glm::mat3 mat3;
typedef glm::mat4 mat4; 
typedef glm::vec3 vec3;
typedef glm::vec4 vec4; 

constexpr float kEpsilon = 1e-8;

class Shape
{
  public:
    float ambient[4];
    float diffuse[4];
    float specular[4];
    float emission[4];
    float shininess;
    bool istriangle;
    virtual bool intersect(const vec4 orig, const vec4 dir, float *all, vec4 direction) = 0;
    virtual void applyLookAt(mat4 &lookat) = 0;
};