#pragma once
#include "stdheader.h"
class Material {

public:
        GLfloat Ambience[4];
        GLfloat Diffuse[4];
        GLfloat Specular[4];
        GLfloat Shininess;
        enum Colours{Red,Green,Blue};
        void SetAmbience(float r, float g, float b, float a = 1.0);
        void SetDiffuse(float r, float g, float b, float a= 1.0);
        void SetSpecular(float r, float g, float b, float a = 1.0);
        void SetShininess(float shine);
        void ApplyMaterial();
};