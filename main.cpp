//Windows Example Code
//Matthew Bett 2005
//Shazam!
#include "stdheader.h"
#include "GameManager.h"







LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
        switch (message)
        {

        case WM_SIZE:
                //resize the open gl window when the window is resized
                GameManager.ResizeGLWindow(LOWORD(lParam),HIWORD(lParam));
                break;
        case WM_DESTROY:
                PostQuitMessage(0);
                break;
        }
        return DefWindowProc (hwnd, message, wParam, lParam);

}
bool FOG;
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
        PSTR szCmdLine, int nCmdShow)
{
        HWND            hwnd;
        MSG         msg;

        //initialise and create window
        if(!GameManager.CreateGameWindow(hInstance)) return true;       // Attempt to Create a Window for the game exiting the app if unsuccessful
        //GameManager.DisplayLoadScreen();
        GameManager.InitOpenGL();
        //GameManager.DisplayLoadScreen();
        return GameManager.Invoke();
        return msg.wParam ;
}