#include <cstdlib>

class Raytracer
{
  public:
    float aspect, invheight, invwidth, angle;
    float height, width;
    vector<Shape *> *sh;
    vector<Light *> *lt;
    mat4 lookatmat, invlookat;
    Raytracer(int height, int width, float angle, vector<Shape *> *sh, vector<Light *> *lt, mat4 &lookat)
    {
        this->width = float(width);
        this->height = float(height);
        this->invheight = 1 / float(height);
        this->invwidth = 1 / float(width);
        this->angle = tan(glm::radians(angle * 0.5));
        this->aspect = width / float(height);
        //std::cout << this->aspect << "sssssssssssss"<<std::endl;
        this->sh = sh;
        this->lt = lt;
        this->lookatmat = lookat;
        this->invlookat = glm::inverse(lookat);
    };
    ~Raytracer(){};

    vec3 trace(vec4 orig, vec4 direction, int depth)
    {
        vec3 color(0.0f, 0.0f, 0.0f);
        //std::cout << maxdepth << std::endl;
        if (depth > maxdepth)
            return color;
        Shape *choice = NULL;
        float allval[3];
        float nearest = INFINITY;
        bool touches = false;
        direction = glm::normalize(direction);
        float t;
        vec4 normal, finaldir, point, finalpoint;
        orig += (kEpsilon / 10.0f) * direction;
        for (vector<Shape *>::iterator it = this->sh->begin(); it != this->sh->end(); it++)
        {
            touches = (*it)->intersect(orig, direction, allval, normal, point);
            t = allval[0];

            if (touches && t <= nearest && t > 0)
            {
                nearest = t;
                choice = *it;
                finaldir = normal;
                finalpoint = point;
            }
        }
        if (choice != NULL)
        {
            finaldir = glm::normalize(finaldir);
            color = choice->ambient + choice->emission;
            for (vector<Light *>::iterator it = this->lt->begin(); it != this->lt->end(); it++)
                color += (*it)->trace(finalpoint, choice->diffuse, choice->specular, finaldir, choice->shininess, direction);

            return color + choice->specular * this->trace(finalpoint, direction + 2.0f * (glm::dot(-direction, finaldir) * finaldir), depth + 1);
        }
        else
        {
            return color;
        }
    };

    vec3 *render()
    {
        vec3 *buffer = new vec3[int(this->width) * int(this->height)];
        vec3 *results = buffer;

        //vec4 orig = invlookat * vec4(0., 0., 0., 1.);
        vec4 orig = vec4(eyeinit, 1.0f);
        //std::cout << glm::to_string(eyeinit) << std::endl;
        vec3 uvec(lookatmat[0][0], lookatmat[1][0], lookatmat[2][0]);
        vec3 vvec(lookatmat[0][1], lookatmat[1][1], lookatmat[2][1]);
        vec3 wvec(lookatmat[0][2], lookatmat[1][2], lookatmat[2][2]);
        //float LO = -0.000001;
        //float HI = 0.000001;
        float xdir, ydir;
        float xx, yy;
        //float r3;
        #pragma omp parallel for
        for (int j = 0; j < int(this->height); j++)
        {
            #pragma omp parallel for
            for (int i = 0; i < int(this->width); i++)
            {
          //      r3 = LO + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (HI - LO)));
                xx = (2 * (i + 0.5) / (float)(this->width) - 1) * this->aspect * this->angle;
                
                //xdir = this->angle * this->aspect * (float(i + r3) - (this->width / 2.0f)) / (this->width / 2.0f);
            //    r3 = LO + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (HI - LO)));
                yy = (1 - 2 * (j - 0.5) / (float)(this->height)) * this->angle;
                //ydir = this->angle * ((this->height / 2.0f) - float(j + r3)) / (this->height / 2.0f);
                vec4 direction = vec4(glm::normalize(xx * uvec + yy * vvec - wvec), 0.0f);

                *(results + (j * int(this->width)) + i) = this->trace(orig, direction, 0);

                //results++;
            }
        }
        return buffer;
    };
};