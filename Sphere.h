#include <math.h>

class Sphere
{
  public:
    Sphere(float x, float y, float z, float radius)
    {
        this->center = vec3(x, y, z);
        this->r = radius;
    }
    bool intersect(const vec3 &rayorig, const vec3 &raydir, float &t0, float &t1) 
    {
        float radius2 = this->r * this->r;
        vec3 l = center - rayorig; 
        float tca = glm::dot(l, raydir); 
        if (tca < 0) return false; 
        float d2 = glm::dot(l, l) - tca * tca; 
        if (d2 > radius2) return false; 
        float thc = sqrt(radius2 - d2); 
        t0 = tca - thc; 
        t1 = tca + thc; 
 
        return true; 
    }

    vec3 center;
    float r;
};