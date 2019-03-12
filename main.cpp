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
    if (argc != 2)
    {
        cerr << "Usage: raytracer [scenefile]\n";
        exit(-1);
    }
    readfile(argv[1]);

    FreeImage_Initialise();
    FIBITMAP *bitmap = FreeImage_Allocate(screenwidth, screenheight, BPP);
    RGBQUAD color;

    vec3 *framebuffer;

    mat4 lookat = glm::lookAt(eyeinit, center, upinit);
    Raytracer *tracer = new Raytracer(screenheight, screenwidth, fovy, &shapes, &lights, lookat);

    //for (vector<Shape *>::iterator u = shapes.begin(); u != shapes.end(); u++)
    //    (*u)->applyLookAt(lookat);

    framebuffer = tracer->render();

    for (int j = 0; j < screenheight; j++)
    {
        for (int i = 0; i < screenwidth; i++)
        {
            color.rgbRed = (255 * framebuffer[(screenwidth * j) + i].x);
            color.rgbGreen = (255 * framebuffer[(screenwidth * j) + i].y);
            color.rgbBlue = (255 * framebuffer[(screenwidth * j) + i].z);
            FreeImage_SetPixelColor(bitmap, i, screenheight - j, &color);
        }
    }
    if (FreeImage_Save(FIF_PNG, bitmap, filen, 0))
        std::cout << "Done!" << std::endl;
    else
        std::cout << "Error" << std::endl;
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
    delete[] framebuffer;
    return 0;
}
