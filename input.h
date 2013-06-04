#include <windows.h>
#ifndef INPUT
#define INPUT

struct Button
{
        bool Pressed;
        bool Down();
        bool Up();
void ProcessClick(bool);
private:
        bool _Down;
        bool _Up;
} ;
struct Mouse
{
        int x,y;
        int _xDrag, _yDrag;
        int xDrag();
        int yDrag();
        Button Left;
        Button Right;
        Button Middle;
        void Update(int,int);
};

struct Key{
        bool Pressed;
        void Update(bool);
        bool Up();
        bool Down();
private:
        bool _Down;
        bool _Up;
};

typedef struct Input
{
        Mouse mouse;
        Key keys[256];
        bool MsgProc(HWND, UINT, WPARAM, LPARAM);

        void null(){
                mouse.Left.Pressed = false;
                mouse.Right.Pressed = false;
                mouse.Middle.Pressed = false;
                for(int i = 0;i<256;i++)
                {
                keys[i].Pressed = false;
                }
        }
} Input;
#endif