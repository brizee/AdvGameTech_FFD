#pragma once
#include "vector.h"

class camera {
public:
        enum Mode{ First, Third, FlyThrough };
        enum Vectors{ Position, Forward, LookAt, Up, Right };
        vector Vector_Position;
        vector Vector_Forward;
        vector Vector_LookAt;
        vector Vector_Up;
        vector Vector_Right;


        void SwitchMode(Mode);
        void Switch();
        void Update();

        void SetPosition(int i, int j, int k);
        void SetRotation(float _Pitch, float _Yaw, float _Roll);

        void ClampPitch(float max, float min);
        void ClampYaw(float max, float min);
        void ClampRoll(float max, float min);

        void IncreasePitch(float Rad);
        void IncreaseYaw(float Rad);
        void IncreaseRoll(float Rad);

        void AdjustFov(float amount);
        void SetAspectRatio(float ratio);

        void MoveForward(float Amount);
        void MoveRight(float Amount);
        float Pitch, Yaw, Roll;
private:
        float fov, aspect;

        float m_PitchMax, m_PitchMin;
        float m_YawMax, m_YawMin;
        float m_RollMax, m_RollMin;
        Mode CurMode;
} ;