#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

typedef glm::mat3 mat3;
typedef glm::mat4 mat4;
typedef glm::vec3 vec3;
typedef glm::vec4 vec4;
typedef glm::vec2 vec2;

class Scene
{
    Scene(float eyex, float eyey, float eyez,
          float centerx, float centery, float centerz,
          float upx, float upy, float upz,
          float resx, float resy);
    ~Scene();
    vec3 eye;
    vec3 up;
    vec3 center;
    vec2 res;
};