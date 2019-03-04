#define MAINPROGRAM
#include "Scene.h"
#include "readfile.h"
#include <FreeImage.h>

inline float clamp(const float &lo, const float &hi, const float &v)
{
    return std::max(lo, std::min(hi, v));
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cerr << "Usage: raytracer [scenefile] [output name]\n";
        exit(-1);
    }
    readfile(argv[1]);
    vec3 v0(-1, -1, -5);
    vec3 v1(1, -1, -5);
    vec3 v2(0, 1, -5);
    //triangles.push_back(new Triangle(v0, v1, v2));
    std::cout << triangles.size() << std::endl;
    vec3 cols[3] = {{0.6, 0.4, 0.1}, {0.1, 0.5, 0.3}, {0.1, 0.3, 0.7}};
    vec3 *framebuffer = new vec3[w * h];
    vec3 *pix = framebuffer;
    float angle = tan(M_PI * 0.5 * fovy / 180.);
    //std::cout << scale << std::endl;
    float AspectRatio = float(w) / float(h);
    float invWidth = 1 / float(w), invHeight = 1 / float(h);
    vec3 orig(0.0f);
    mat4 lookat = Transform::lookAt(eyeinit, center, upinit);
    vec3 defaultcol(1, 0, 0);
    for (vector<Triangle *>::iterator u = triangles.begin(); u != triangles.end(); u++)
        (*u)->applyLookAt(lookat);

    void *choice;
    bool touches = false;
    bool istriangle = false;

    for (int j = 0; j < h; j++)
    {
        for (int i = 0; i < w; i++)
        {
            choice = NULL;
            float xx = (2 * ((i + 0.5) * invWidth) - 1) * angle * AspectRatio;
            float yy = (1 - 2 * ((j + 0.5) * invHeight)) * angle;
            vec3 dir(xx, yy, -1.0f);
            dir = glm::normalize(dir);
            float t, u, v;
            float nearest = -1;
            for (vector<Triangle *>::iterator it = triangles.begin(); it != triangles.end(); it++)
            {
                touches = (*it)->intersect(orig, dir, t, u, v);
                if (touches)
                {
                    if (nearest < 0)
                    {
                        nearest = t;
                        choice = *it;
                        istriangle = true;
                    }
                    else if (t < nearest && t > 0)
                    {
                        nearest = t;
                        choice = *it;
                        istriangle = true;
                    }
                }
            }

            if (choice != NULL)
            {
                *pix = vec3(((Triangle*)choice)->ambient[0], ((Triangle*)choice)->ambient[1], ((Triangle*)choice)->ambient[2]);
            }

            pix++;
        }
    }
    std::ofstream ofs(argv[2], std::ios::out | std::ios::binary);
    ofs << "P6\n"
        << w << " " << h << "\n255\n";
    for (uint32_t i = 0; i < h * w; ++i)
    {
        char r = (char)(255 * clamp(0, 1, framebuffer[i].x));
        char g = (char)(255 * clamp(0, 1, framebuffer[i].y));
        char b = (char)(255 * clamp(0, 1, framebuffer[i].z));
        ofs << r << g << b;
    }

    ofs.close();
    return 0;
}
