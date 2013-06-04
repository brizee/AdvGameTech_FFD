#include "stdheader.h"
#include "vector.h"
#include "camera.h"

#define deg2rad(deg) ((deg / 180.0)*3.14159)




void camera::SwitchMode(Mode m){
        switch(m)
        {
        case Third:
                        ClampPitch(80,0);
                        ClampYaw(0,0);
                        ClampRoll(0,0);
                        Pitch = 50;
                break;
        case First:
                ClampPitch(80,-80);
                        ClampYaw(0,0);
                        ClampRoll(0,0);
                        Pitch = 0;
                break;
        case FlyThrough:
                ClampPitch(0,0);
                        ClampYaw(0,0);
                        ClampRoll(0,0);
                break;
        }
        if(CurMode == Third && m != Third){
                vector t = Vector_LookAt.GetNormal();
                t *= 10;
                Vector_Position = t;
                Pitch *= -1;
        }
        if(m == First)
                Vector_Position.y = 3;
        if((CurMode == Third && m != Third) || CurMode != Third && m == Third)
                IncreaseYaw(180);

        CurMode = m;
}
void camera::Switch()
{
        vector Position = Vector_LookAt.GetNormal();

        if(CurMode == Third){
                Position *= 100;
                gluLookAt(Position.x, Position.y, Position.z,Vector_Position.x,Vector_Position.y,Vector_Position.z,Vector_Up.x,Vector_Up.y,Vector_Up.z);

        }
        else
                gluLookAt(Vector_Position.x, Vector_Position.y, Vector_Position.z,Vector_LookAt.x,Vector_LookAt.y,Vector_LookAt.z,Vector_Up.x,Vector_Up.y,Vector_Up.z);

}
void camera::SetPosition(int i, int j, int k)
{
        Vector_Position.x = i;
        Vector_Position.y = j;
        Vector_Position.z = k;
}
void camera::Update(){
        float cosR, cosP, cosY;         //temp values for sin/cos from
        float sinR, sinP, sinY;         //the inputed roll/pitch/yaw

        // ôcamö is an object  created to store the vectors for
        // the camera.
        // Only Want to calculate these values once.
        // For speeds sake.
        cosY = cosf(Yaw*3.1415/180);
        cosP = cosf(Pitch*3.1415/180);
        cosR = cosf(Roll*3.1415/180);
        sinY = sinf(Yaw*3.1415/180);
        sinP = sinf(Pitch*3.1415/180);
        sinR = sinf(Roll*3.1415/180);

        Vector_Forward.x = sinY * cosP*360;
        Vector_Forward.y = sinP*360;
        Vector_Forward.z = (cosP * -cosY) *360;
        Vector_LookAt = Vector_Forward + Vector_Position;

        Vector_Up.x = -cosY * sinR - sinY * sinP * cosR;
        Vector_Up.y = cosP * cosR;
        Vector_Up.z = -sinY * sinR - sinP * cosR * -cosY;

        Vector_Right = Vector_Forward * Vector_Up;
}
void camera::SetRotation(float _Pitch, float _Yaw, float _Roll){
        Pitch = _Pitch;
        Yaw = _Yaw;
        Roll = _Roll;
        Update();
}
void camera::IncreasePitch(float Rad){
    if((Pitch + Rad > m_PitchMin && Pitch+ Rad < m_PitchMax) || (m_PitchMax == m_PitchMin && m_PitchMin == 0)){
        Pitch += Rad;
        Update();
        }
}
void camera::IncreaseYaw(float Rad){
        if((Yaw + Rad > m_YawMin && Yaw+ Rad < m_YawMax) || (m_YawMax == m_YawMin && m_YawMin == 0)){
        Yaw += Rad;
        Update();
        }
}
void camera::IncreaseRoll(float Rad){
        if((Roll + Rad > m_RollMin && Roll+ Rad < m_RollMax) || (m_RollMax == m_RollMin && m_RollMin == 0)){
        Roll += Rad;
        Update();
        }
}
void camera::MoveForward(float Amount)
{
        vector Step = Vector_Forward.GetNormal();
        if(CurMode == First)
                Step.y=0;
        Step *= Amount;
        Vector_Position += Step;
        Update();
}
void camera::MoveRight(float Amount)
{
        vector Step = Vector_Right.GetNormal();
        if(CurMode == First)
                Step.y=0;
        Step *= Amount;
        Vector_Position += Step;
        Update();
}

void camera::ClampPitch(float max, float min){
m_PitchMax = max;
m_PitchMin = min;
}

void camera::ClampYaw(float max, float min){
m_YawMax = max;
m_YawMin = min;
}

void camera::ClampRoll(float max, float min){
m_RollMax = max;
m_RollMin = min;
}