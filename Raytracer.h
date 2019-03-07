class Raytracer
{
  public:
    float aspect, invheight, invwidth, angle;
    float height, width;
    vector<Shape *> *sh;
    mat4 lookatmat, invlookat;
    Raytracer(int height, int width, float angle, vector<Shape *> *sh, mat4 &lookat)
    {
        this->width = float(width);
        this->height = float(height);
        this->invheight = 1 / float(height);
        this->invwidth = 1 / float(width);
        this->angle = tan(glm::radians(angle * 0.5));
        this->aspect = width / float(height);
        //std::cout << this->aspect << "sssssssssssss"<<std::endl;
        this->sh = sh;
        this->lookatmat = lookat;
        this->invlookat = glm::inverse(lookat);
    };
    ~Raytracer(){};

    Shape *trace(vec4 orig, vec4 direction)
    {
        Shape *choice = NULL;
        float allval[3];
        float nearest = -1;
        bool touches = false;
        //std::cout << "STARTING OBJECT CHECK---------------------------------" << std::endl;
        direction = glm::normalize(direction);
        float t;
        for (vector<Shape *>::iterator it = this->sh->begin(); it != this->sh->end(); it++)
        {
            vec4 finaldir;
            touches = (*it)->intersect(orig, direction, allval, finaldir);
            t = allval[0];
            if (touches)
            {
                //if ((*it)->istriangle) std::cout << "Triangle touched" << std::endl;
                //else std::cout << "Sphere touched" << std::endl;
                if (nearest == -1 && t > 0)
                {
                    nearest = t;
                    choice = *it;
                }
                else if (t <= nearest && t > 0)
                {
                    nearest = t;
                    choice = *it;
                }
                //std::cout << "value : "<< t << std::endl;
            }
                
            
        }
        //if (choice == NULL) std::cout << "NOTHING TOUCHED" << std::endl;
        return choice;
    };

    vec3 *render()
    {
        vec3 *buffer = new vec3[int(this->width) * int(this->height)];
        vec3 *results = buffer;
        Shape *choice = NULL;
        //vec4 orig = invlookat * vec4(0., 0., 0., 1.);
        vec4 orig = vec4(eyeinit, 1.0f);
        std::cout << glm::to_string(eyeinit) << std::endl;
        vec3 uvec(lookatmat[0][0], lookatmat[1][0], lookatmat[2][0]);
        vec3 vvec(lookatmat[0][1], lookatmat[1][1], lookatmat[2][1]);
        vec3 wvec(lookatmat[0][2], lookatmat[1][2], lookatmat[2][2]);

        
        for (int j = 0; j < int(this->height); j++)
        {
            for (int i = 0; i < int(this->width); i++)
            {
                float xdir, ydir;
                choice = NULL;
                xdir = this->angle * this->aspect * (float(i) - (this->width / 2.0f)) / (this->width/2.0f);
                ydir = this->angle * ((this->height / 2.0f) - float(j)) / (this->height / 2.0f);
                //vec4 direction(xx, yy, -1.0f, 0.0f);
                vec4 direction;
                direction = vec4(glm::normalize(xdir * uvec + ydir * vvec - wvec), 0.0f);
                //std::cout << glm::to_string(orig) << std::endl;
                choice = this->trace(orig, direction);
                if (choice != NULL)
                {
                    *results = vec3(choice->ambient[0], choice->ambient[1], choice->ambient[2]);
                }
                else
                {
                    *results = vec3(0., 0., 0.);
                }

                results++;
            }
        }
        return buffer;
    };
};