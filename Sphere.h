#include <math.h>
class Sphere : public Shape
{
  public:
    Sphere(float x, float y, float z, float radius, mat4 transform)
    {
        this->center = transform * vec4(x, y, z, 1.0f);
        this->r = radius;
    }
    bool intersect(const vec3 &rayorig, const vec3 &raydir, float *all)
    {
        float radius2 = this->r * this->r;
        vec3 l = vec3(center) - rayorig;
        float tca = glm::dot(l, raydir);
        if (tca < 0)
            return false;
        float d2 = glm::dot(l, l) - tca * tca;
        if (d2 > radius2)
            return false;
        float thc = sqrt(radius2 - d2);
        all[0] = tca - thc;
        all[1] = tca + thc;

        if (all[1] < all[0]) {
            if (all[1] > 0)
            all[0] = all[1];
        }

        return true;
    }

    void applyLookAt(mat4 lookat){
        this->center = lookat * this->center;
    };

    vec4 center;
    float r;
};