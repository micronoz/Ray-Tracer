
class Light
{
  public:
    vec4 pos_or_dir;
    vec3 color;
    float attenuation[3];
    vector<Shape *> *sh;
    bool isDirectional;

    Light(vec4 pos, vec3 col, float *att, vector<Shape *> *shapes) : pos_or_dir(pos), color(col), sh(shapes)
    {
        for (int i = 0; i < 3; i++)
            attenuation[i] = att[i];
    }

    vec3 trace(vec4 origin, vec3 diff, vec3 spec, vec4 originorm, float shine, vec4 &direction)
    {
        float allval[3];
        vec4 normal, finalp, dir;
        vec3 intensity(0.0f, 0.0f, 0.0f);
        Shape *choice;
        if (this->isDirectional)
        {
            dir = glm::normalize(pos_or_dir);
            origin += kEpsilon * dir;
            for (vector<Shape *>::iterator it = this->sh->begin(); it != this->sh->end(); it++)
            {
                if ((*it)->intersect(origin, dir, allval, normal, finalp))
                    return intensity;
            }
            intensity = color / attenuation[0];
        }
        else
        {

            dir = vec4(glm::normalize(vec3(pos_or_dir - origin)), 0.0f);
            //cout << glm::to_string(dir) << endl;
            //cout << glm::to_string(originorm) << endl;
            origin += kEpsilon * dir;
            float smallest;
            if (dir[0] != 0)
                smallest = (pos_or_dir - origin)[0] / dir[0];
            else if (dir[1] != 0)
                smallest = (pos_or_dir - origin)[1] / dir[1];
            else if (dir[2] != 0)
                smallest = (pos_or_dir - origin)[2] / dir[2];

            for (vector<Shape *>::iterator it = this->sh->begin(); it != this->sh->end(); it++)
            {
                if ((*it)->intersect(origin, dir, allval, normal, finalp) && allval[0] > 0 && allval[0] < smallest)
                {
                    return intensity;
                }
            }
            float dist = glm::length(pos_or_dir - origin);
            intensity = color / (attenuation[0] +
                                 attenuation[1] * dist +
                                 attenuation[2] * dist * dist);
        }
        //cout << glm::dot(dir, originorm) << endl;
        intensity = intensity *
                    (diff * max(glm::dot(dir, originorm), 0.0f) +
                     spec * pow(max(glm::dot(glm::normalize(dir - direction), originorm), 0.0f), shine));

        /*if (originorm[2] == 1)
            std::cout << glm::to_string(intensity) << std::endl;*/

        //std::cout << glm::to_string(intensity) << std::endl;
        return intensity;
    };
};