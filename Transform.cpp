// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"

// Helper rotation function.  Please implement this.
mat3 Transform::rotate(const float degrees, const vec3 &axis)
{
    mat3 I = mat3(1.0f);
    vec3 a = glm::normalize(axis);
    //float rad = glm::radians(degrees); //Degree to radian conversion

    float rad = degrees * pi / 180.0f; //Degree to radian conversion
    float x = a[0];
    float y = a[1];
    float z = a[2];

    mat3 aat = mat3(x * x, x * y, x * z, x * y, y * y, y * z, x * z, y * z, z * z);
    mat3 as = mat3(0.0f, z, -y, -z, 0.0f, x, y, -x, 0.0f);
    mat3 rot = (float(cos(rad)) * I) + (float(1.0 - cos(rad)) * aat) + (float(sin(rad)) * as);

    return rot;
}

void Transform::left(float degrees, vec3 &eye, vec3 &up)
{
    eye = rotate(degrees, glm::normalize(up)) * eye;
}

void Transform::up(float degrees, vec3 &eye, vec3 &up)
{
    vec3 cr = glm::cross(eye, up);
    cr = glm::normalize(cr);
    up = rotate(degrees, cr) * up;
    eye = rotate(degrees, cr) * eye;
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up)
{
    
    vec3 w = glm::normalize(eye - center);
    vec3 u = glm::cross(up, w);
    u = glm::normalize(u);
    vec3 v = glm::cross(w, u);
    mat4 rot = mat4(u[0], v[0], w[0], 0.0f,
                    u[1], v[1], w[1], 0.0f,
                    u[2], v[2], w[2], 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f);
    mat4 tr = mat4(1.0f);
    std::cout << glm::to_string(eye) << std::endl;
    tr[3][0] = -eye[0];
    tr[3][1] = -eye[1];
    tr[3][2] = -eye[2];

    mat4 ret = rot * tr;

    return ret;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
    float d = 1.0f / tan(glm::radians(fovy / 2.0f));
    float A = -(zNear + zFar) / (zFar - zNear);
    float B = -2.0f * (zFar * zNear) / (zFar - zNear);
    mat4 ret = mat4(d / aspect, 0.0f, 0.0f, 0.0f,
                    0.0f, d, 0.0f, 0.0f,
                    0.0f, 0.0f, A, -1.0f,
                    0.0f, 0.0f, B, 0.0f);

    return ret;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz)
{
    mat4 ret = mat4(sx, 0.0f, 0.0f, 0.0f,
                    0.0f, sy, 0.0f, 0.0f,
                    0.0f, 0.0f, sz, 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f);
    return ret;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz)
{
    mat4 ret = mat4(1.0f, 0.0f, 0.0f, 0.0f,
                    0.0f, 1.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 1.0f, 0.0f,
                    tx, ty, tz, 1.0f);
    return ret;
}

// To normalize the up direction and construct a coordinate frame.
// As discussed in the lecture.  May be relevant to create a properly
// orthogonal and normalized up.
// This function is provided as a helper, in case you want to use it.
// Using this function (in readfile.cpp or display.cpp) is optional.

vec3 Transform::upvector(const vec3 &up, const vec3 &zvec)
{
    vec3 x = glm::cross(up, zvec);
    vec3 y = glm::cross(zvec, x);
    vec3 ret = glm::normalize(y);
    return ret;
}

Transform::Transform()
{
}

Transform::~Transform()
{
}
