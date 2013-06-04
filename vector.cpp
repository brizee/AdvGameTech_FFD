#include <cmath>
#include "vector.h"
vector::vector(){
                x = 0;
                y = 0;
                z = 0;
        }
        vector vector::operator*=(const vector &rhs){
                float tx, ty, tz;
                tx = (y*rhs.z) - (z*rhs.y);
                ty = (x*rhs.z) - (z*rhs.x);
                tz = (x*rhs.y) - (y*rhs.x);
                x = tx;
                y = ty;
                z = tz;
                return *this;
        }
        vector vector::operator*=(const float &rhs){
                x *= rhs;
                y *= rhs;
                z *= rhs;
                return *this;
        }
        vector vector::operator*(const float &rhs){
                vector result = *this;
                result *= rhs;
                return result;
        }

        vector vector::operator/(const float &rhs){
                vector result = *this;
                result.x /= rhs;
                result.y /= rhs;
                result.z /= rhs;
                return result;
        }
        vector vector::operator*(const vector &rhs){
                vector result = *this;
                result *= rhs;
                return result;
        }
        vector vector::operator+=(const vector &rhs){
                x += rhs.x;
                y += rhs.y;
                z += rhs.z;
                return *this;
        }
        vector vector::operator+(const vector &rhs){
                vector result = *this;
                result += rhs;
                return result;
        }
        void vector::Normalise(){
                float mag = sqrt((x*x) + (y*y) + (z*z));
                x /= mag;
                y /= mag;
                z /= mag;
        }
        vector vector::GetNormal(){
                vector result = *this;
                result.Normalise();
                return result;
        }

                vector vector::operator-=(const vector &rhs){
                x -= rhs.x;
                y -= rhs.y;
                z -= rhs.z;
                return *this;
        }
        vector vector::operator-(const vector &rhs){
                vector result = *this;
                result -= rhs;
                return result;
        }

        GLfloat* vector::toArray(){
                ArrayForm[0] = x;
                ArrayForm[1] = y;
                ArrayForm[2] = z;
                ArrayForm[3] = 0.0f;
                return ArrayForm;
        }