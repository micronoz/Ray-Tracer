class Triangle : public Shape
{
  public:
    Triangle(vec4 &v0, vec4 &v1, vec4 &v2, mat4 &transform)
    {
        this->v0 = vec3(transform * v0);
        this->v1 = vec3(transform * v1);
        this->v2 = vec3(transform * v2);
        this->inverse = glm::inverse(transform);
    };
    ~Triangle(){};
    void applyLookAt(mat4 &lookat)
    {
    };
    bool intersect(const vec4 origin, const vec4 direction, float *all, vec4 finaldir)
    {
        vec3 v0v1 = v1 - v0;
        vec3 v0v2 = v2 - v0;
        vec3 orig = vec3(origin);
        vec3 dir = vec3(direction);
        vec3 pvec = glm::cross(dir, v0v2);
        float det = glm::dot(v0v1, pvec);
        if (fabs(det) < kEpsilon)
            return false;

        float invDet = 1 / det;

        vec3 tvec = orig - v0;
        all[1] = glm::dot(tvec, pvec) * invDet;
        if (all[1] < 0 || all[1] > 1)
            return false;

        vec3 qvec = glm::cross(tvec, v0v1);
        all[2] = glm::dot(dir, qvec) * invDet;
        if (all[2] < 0 || all[1] + all[2] > 1)
            return false;

        all[0] = glm::dot(v0v2, qvec) * invDet;
        finaldir = direction;

        // all[0] = min(all[0], all[1]);
        // all[0] = min(all[0], all[2]);

        return true;
    };
    vec3 v0, v1, v2;
    mat4 inverse;
};