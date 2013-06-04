/*
AG0800A Semester 2 Coursework   -       2010
Brian Beacom (0900305)

The SceneBuilder class manages the positioning of models

NOT INHERITABLE
SINGLE INSTANCE
CONTAINED
*/
#pragma once
#include "stdheader.h"
#include "Model.h"
#include "vector.h"
#include "Light.h"
#include "material.h"
#include "camera.h"
class _SceneBuilder{
private:
        GLuint SkyBox[6];
        Model* MDL_FLOOR1;
        Model* MDL_FLOOR2;
        GLuint MDL_FENCE1;
        GLuint MDL_FENCE2;
        void DrawSkybox();

        Light Flickers[8];
        Material WindowMatter;

public:
        Light Sun;
        vector _SceneBuilder::getPoint(float u, float v);
        vector _SceneBuilder::getNormal(float u, float v);
        void PreloadScene();
        void RenderScene();
        void ApprovePosition(vector& position);
        void RenderWindow();
};