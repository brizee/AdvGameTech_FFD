#include "Light.h"
#include "stdheader.h"

void Light::ApplyLight(){
        //if(Position[3] != 0)
                //glLightfv(Constant, GL_SPOT_DIRECTION, SpotDirection);
        glLightfv(Constant, GL_AMBIENT,  Ambience);
        glLightfv(Constant, GL_DIFFUSE,  Diffuse);
        //glLightfv(Constant, GL_SPECULAR,  Specular);
        glEnable(Constant);
}