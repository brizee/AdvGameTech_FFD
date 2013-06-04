#pragma once

class Light{
public:
float Ambience[4];
float Diffuse[4];
float Specular[4];
float Position[4];
float SpotDirection[4];

int Constant;
bool Spot;
void ApplyLight();
};