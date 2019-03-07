#include <math.h>
class Sphere : public Shape
{
  public:
    Sphere(float x, float y, float z, float radius, mat4 transformat)
    {
        this->inversetrans = glm::inverse(transformat);
        this->transformat = transformat;
        this->centerp = vec4(x, y, z, 1.0f);
        this->rad = radius;
    }

    bool solveQuadratic(const float &acc, const float &bcc, const float &ccc, float &x0, float &x1)
    {
        float discr = bcc * bcc - 4.0 * acc * ccc;
        if (discr < 0)
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

        return true;
    }

    bool intersect(const vec4 orig, const vec4 dir, float *allval, vec4 direction)
    {
        /*std::cout << "Origin: " <<glm::to_string(vec4(orig, 1.0f)) << std::endl;
        std::cout << "Inverse origin: " << glm::to_string(inverse * vec4(orig, 1.0f)) << std::endl;
        std::cout << "Dir: " <<glm::to_string(vec4(dir, 0.0f)) << std::endl;
        std::cout << "Inverse dir: " << glm::to_string(inverse * vec4(dir, 0.0f)) << std::endl;*/
        vec3 rayorig = vec3(inversetrans * orig);
        vec3 raydir = vec3(glm::normalize(inversetrans * dir));
        
        float radius2 = this->rad * this->rad;
        float t0, t1;

        vec3 L = rayorig - vec3(this->centerp);
        float acc = glm::dot(raydir, raydir);
        float bcc = 2 * glm::dot(raydir, L);
        float ccc = glm::dot(L, L) - radius2;

        if (!solveQuadratic(acc, bcc, ccc, t0, t1))
            return false;

        float minum = min(t0, t1);
        if (minum <= 0) {
            minum = max(t0, t1);
        }
        if (minum <= 0) return false;
        t0 = minum;
        vec4 point = transformat * (vec4(rayorig, 1.0) + t0 * vec4(raydir, 0.0));
        //std::cout << glm::to_string(point) << std::endl;
        allval[0] = glm::length(point - orig);

        return true;
    }

    void applyLookAt(mat4 &lookat)
    {
        //this->center = lookat * this->center;
    };

    vec4 centerp;
    mat4 inversetrans, transformat;
    float rad;
};