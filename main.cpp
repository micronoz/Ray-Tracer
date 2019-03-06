#define MAINPROGRAM
#include "readfile.h"
#include <FreeImage.h>
#include "Raytracer.h"

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

    vec3 *framebuffer;
    Raytracer *tracer = new Raytracer(h, w, fovy, &shapes);
    vec3 orig(0.0f);
    mat4 lookat = Transform::lookAt(eyeinit, center, upinit);
    vec3 defaultcol(1, 0, 0);
    for (vector<Shape *>::iterator u = shapes.begin(); u != shapes.end(); u++)
        (*u)->applyLookAt(lookat);

    framebuffer = tracer->render();

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
