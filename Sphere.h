#include <math.h>
class Sphere : public Shape
{
  public:
    Sphere(float &x, float &y, float &z, float &radius, mat4 &transformat)
    {
        this->inversetrans = glm::inverse(transformat);
        this->transformat = transformat;
        this->centerp = vec4(x, y, z, 1.0f);
        this->rad = radius;
    };

    bool solve(const float &acc, const float &bcc, const float &ccc, float &x0, float &x1)
    {
        float discr = bcc * bcc - 4.0 * acc * ccc;
        if (discr < kEpsilon)
            return false;
        else if (discr == 0)
        {
            x0 = x1 = -0.5 * bcc / acc;
        }
        else
        {
            x0 = (-bcc + sqrt(discr)) / (2.0 * acc);
            x1 = (-bcc - sqrt(discr)) / (2.0 * acc);
        }
        if (x0 > x1) std::swap(x0, x1); 
        return true;
    };

    bool intersect(const vec4 &orig, const vec4 &dir, float *allval, vec4 &normal, vec4 &point)
    {
        vec3 rayorig = vec3(inversetrans * orig);
        vec3 raydir = vec3(glm::normalize(inversetrans * dir));
        float radius2 = this->rad * this->rad;
        float t0, t1 = -1;

        vec3 L = rayorig - vec3(this->centerp);
        float acc = glm::dot(raydir, raydir);
        float bcc = 2 * glm::dot(raydir, L);
        float ccc = glm::dot(L, L) - radius2;

        if (!solve(acc, bcc, ccc, t0, t1))
            return false;

 
        if (t0 < kEpsilon) { 
            t0 = t1; 
            if (t0 < kEpsilon) return false;
        } 

        mat3 t = glm::transpose(mat3(inversetrans));

        point = (vec4(rayorig, 1.0) + t0 * vec4(raydir, 0.0));
        normal = vec4(glm::normalize(t * vec3(point - centerp)), 0.0f);
        point = transformat * point;

        allval[0] = glm::length(point - orig);

        return true;
    };


    vec4 centerp;
    mat4 inversetrans, transformat;
    float rad;
};