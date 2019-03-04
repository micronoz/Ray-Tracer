#include "Scene.h"

Scene::Scene(float eyex, float eyey, float eyez,
             float centerx, float centery, float centerz,
             float upx, float upy, float upz,
             float resx, float resy)
{
    eye = vec3(eyex, eyey, eyez);
    up = vec3(upx, upy, upz);
    center = vec3(centerx, centery, centerz);
    res = vec2(resx, resy);
}

Scene::~Scene() {}
