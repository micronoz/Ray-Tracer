#define MAINPROGRAM
#include "readfile.h"
#include <FreeImage.h>
#include "Raytracer.h"

#define BPP 24

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

    FreeImage_Initialise();
    FIBITMAP *bitmap = FreeImage_Allocate(w, h, BPP);
    RGBQUAD color;

    vec3 *framebuffer;
    Raytracer *tracer = new Raytracer(h, w, fovy, &shapes);

    mat4 lookat = Transform::lookAt(eyeinit, center, upinit);

    for (vector<Shape *>::iterator u = shapes.begin(); u != shapes.end(); u++)
        (*u)->applyLookAt(lookat);

    framebuffer = tracer->render();

    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            color.rgbRed = (255 * clamp(0, 1, framebuffer[(w * j) + i].x));
            color.rgbGreen = (255 * clamp(0, 1, framebuffer[(w * j) + i].y));
            color.rgbBlue = (255 * clamp(0, 1, framebuffer[(w * j) + i].z));
            FreeImage_SetPixelColor(bitmap, i, h - j, &color);
        }
    }

    if (FreeImage_Save(FIF_PNG, bitmap, "test.png", 0))
        std::cout << "Done!" << std::endl;
    FreeImage_DeInitialise();

    // std::ofstream ofs(argv[2], std::ios::out | std::ios::binary);
    // ofs << "P6\n"
    //     << w << " " << h << "\n255\n";
    // for (int i = 0; i < h * w; ++i)
    // {
    //     char r = (char)(255 * clamp(0, 1, framebuffer[i].x));
    //     char g = (char)(255 * clamp(0, 1, framebuffer[i].y));
    //     char b = (char)(255 * clamp(0, 1, framebuffer[i].z));
    //     ofs << r << g << b;
    // }

    // ofs.close();
    return 0;
}
