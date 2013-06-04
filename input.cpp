#include "input.h"
#pragma region "Mouse Functions"
bool Button::Down()
{
        bool temp = _Down;
        _Down = false;
        return temp;
}
bool Button::Up(){
        bool temp = _Up;
        _Up = false;
        return temp;
}
void Button::ProcessClick(bool ButtonPressed)
{
        if(ButtonPressed && !_Down)
        {
                Pressed = true;
                _Down = true;
        }
        else if(!ButtonPressed && Pressed)
        {
                _Up = true;
                Pressed = false;
        }
        else
        {
                Pressed = ButtonPressed;
        }
}

void Mouse::Update(int _x, int _y)
{
        _xDrag = _x - x;
        _yDrag = _y - y;
        x = _x;
        y = _y;
}
#pragma endregion

#pragma region "Keys"
void Key::Update(bool pressed)
{
        Pressed = pressed;
        if(pressed && !_Down)
        {
                _Down = true;
        }
        if(!pressed && _Down)
        {
                _Up = true;
        }
}
bool Key::Down()
{
        bool temp = _Down;
        _Down = false;
        return temp;
}
bool Key::Up()
{
        bool temp = _Up;
        _Up = false;
        return temp;
}
#pragma endregion

bool Input::MsgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
        bool handled = true;
switch (message)
    {
                case WM_KEYDOWN:
                        keys[wParam].Update(true);
                        break;

                case WM_KEYUP:
                        keys[wParam].Update(false);
                        break;

                case WM_MOUSEMOVE:
                        mouse.Update(LOWORD (lParam),HIWORD (lParam));
                        break;
                case WM_MBUTTONDOWN:
                        mouse.Middle.ProcessClick(true);
                        break;
                case WM_MBUTTONUP:
                        mouse.Middle.ProcessClick(false);
                        break;
                case WM_RBUTTONDOWN:
                        mouse.Right.ProcessClick(true);
                        break;
                case WM_RBUTTONUP:
                        mouse.Right.ProcessClick(false);
                        break;
                case WM_LBUTTONDOWN:
                        mouse.Left.ProcessClick(true);
                        break;
                case WM_LBUTTONUP:
                        mouse.Left.ProcessClick(false);
                        break;
                default:
                        handled = false;
                        break;
        }
return handled;
}