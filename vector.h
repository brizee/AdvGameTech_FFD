#pragma once
#include "stdheader.h"
class vector{
public:
        float x,y,z;
        vector();
        vector operator*=(const vector &rhs);
        vector operator*=(const float &rhs);
        vector operator*(const vector &rhs);
        vector operator*(const float &rhs);
        vector operator/(const float &rhs);
        vector operator+=(const vector &rhs);
        vector operator+(const vector &rhs);
        vector operator-=(const vector &rhs);
        vector operator-(const vector &rhs);
        void Normalise();
        vector GetNormal();

        GLfloat* toArray();
private:
        GLfloat ArrayForm[4];
};