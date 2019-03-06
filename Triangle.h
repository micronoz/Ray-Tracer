class Triangle : public Shape
{
  public:
    Triangle(vec3 v0, vec3 v1, vec3 v2, mat4 transform)
    {
        this->first = transform * vec4(v0, 1.0f);
        this->second = transform * vec4(v1, 1.0f);
        this->third = transform * vec4(v2, 1.0f);
    };
    ~Triangle(){};
    void applyLookAt(mat4 lookat)
    {
        this->first = lookat * this->first;
        this->second = lookat * this->second;
        this->third = lookat * this->third;
    };
    bool intersect(const vec3 &orig, const vec3 &dir, float *all)
    {
        vec3 v0 = vec3(this->first);
        vec3 v1 = vec3(this->second);
        vec3 v2 = vec3(this->third);
        //std::cout << v2[0] << std::endl;
        vec3 v0v1 = v1 - v0;
        vec3 v0v2 = v2 - v0;
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

        return true;
    };
    vec4 first, second, third;
};