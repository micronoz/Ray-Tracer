class Triangle
{
  public:
    Triangle(vec3 v0, vec3 v1, vec3 v2, mat4 transformation)
    {
        //std::cout << glm::to_string(transformation) << std::endl;
        this->first = transformation * vec4(v0,1.0f);
        this->second = transformation * vec4(v1,1.0f);
        this->third = transformation * vec4(v2,1.0f);
    };
    ~Triangle(){};
    void applyLookAt(mat4 lookat) {
        this->first = lookat * this->first;
        this->second = lookat * this->second;
        this->third = lookat * this->third;
    }
    bool intersect(const vec3 &orig, const vec3 &dir,
                   float &t, float &u, float &v)
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
        u = glm::dot(tvec, pvec) * invDet;
        if (u < 0 || u > 1)
            return false;

        vec3 qvec = glm::cross(tvec, v0v1);
        v = glm::dot(dir, qvec) * invDet;
        if (v < 0 || u + v > 1)
            return false;

        t = glm::dot(v0v2, qvec) * invDet;

        return true;
    };

    vec4 first, second, third;
    float ambient[4];
    float diffuse[4];
    float specular[4];
    float emission[4];
    float shininess;
    mat4 transform;
};