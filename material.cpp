#include "material.h"
void Material::SetAmbience(float r, float g, float b, float a)
        {
                Ambience[0] = r;
                Ambience[1] = g;
                Ambience[2] = b;
                Ambience[3] = a;
        }
        void Material::SetDiffuse(float r, float g, float b, float a)
        {
                Diffuse[0] = r;
                Diffuse[1] = g;
                Diffuse[2] = b;
                Diffuse[3] = a;
        }
        void Material::SetSpecular(float r, float g, float b, float a)
        {
                Specular[0] = r;
                Specular[1] = g;
                Specular[2] = b;
                Specular[3] = a;
        }
        void Material::SetShininess(float shine)
        {
                Shininess = shine;
        }

        void Material::ApplyMaterial(){
                glMaterialfv(GL_FRONT, GL_AMBIENT, Ambience);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, Diffuse);
                glMaterialfv(GL_FRONT, GL_SPECULAR, Specular);
                glMaterialf(GL_FRONT, GL_SHININESS, Shininess);
        }