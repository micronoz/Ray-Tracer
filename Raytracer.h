class Raytracer
{
  public:
    float aspect, invheight, invwidth, angle;
    int height, width;
    vector<Shape *> *sh;
    Raytracer(int height, int width, float angle, vector<Shape *> *sh)
    {
        this->width = width;
        this->height = height;
        this->invheight = 1 / float(height);
        this->invwidth = 1 / float(width);
        this->angle = tan(M_PI * 0.5 * angle / 180.);
        this->aspect = width / float(height);
        this->sh = sh;
    };
    ~Raytracer(){};

    Shape *trace(vec3 &orig, vec3 &dir)
    {
        Shape *choice = NULL;
        dir = glm::normalize(dir);
        float all[3];
        float t0, t1;
        float nearest = -1;
        bool touches = false;
        for (vector<Shape *>::iterator it = this->sh->begin(); it != this->sh->end(); it++)
        {
            if ((*it)->istriangle)
                touches = (*it)->intersect(orig, dir, all);
            else
                touches = (*it)->intersect(orig, dir, all);
                
            if (touches)
            {
                if (nearest < 0)
                {
                    nearest = all[0];
                    choice = *it;
                }
                else if (all[0] < nearest && all[0] > 0)
                {
                    nearest = all[0];
                    choice = *it;
                }
            }
        }
        return choice;
    };

    vec3 *render()
    {
        vec3 *buffer = new vec3[this->width * this->height];
        vec3 *results = buffer;
        Shape *choice = NULL;
        vec3 orig(0., 0., 0.);
        for (int j = 0; j < h; j++)
        {
            for (int i = 0; i < w; i++)
            {
                float xx, yy;
                choice = NULL;
                xx = (2 * ((i + 0.5) * this->invwidth) - 1) * this->angle * this->aspect;
                yy = (1 - 2 * ((j + 0.5) * this->invheight)) * this->angle;
                vec3 dir(xx, yy, -1.0f);
                choice = this->trace(orig, dir);
                if (choice != NULL)
                {
                    *results = vec3(choice->ambient[0], choice->ambient[1], choice->ambient[2]);
                }

                results++;
            }
        }
        return buffer;
    };
};