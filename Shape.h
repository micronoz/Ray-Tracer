#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>
#include <iostream>

typedef glm::mat3 mat3;
typedef glm::mat4 mat4;
typedef glm::vec3 vec3;
typedef glm::vec4 vec4;

class Shape
{
public:
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  vec3 emission;
  float shininess;
  bool istriangle;
  virtual bool intersect(const vec4 &orig, const vec4 &dir, float *all, vec4 &normal, vec4 &point) = 0;
};