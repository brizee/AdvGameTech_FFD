/*
AG0800A Semester 2 Coursework   -       2010
Brian Beacom (0900305)

GameManager.h and Gamemanager_*.cpp contain the Game Manager class which is the top level class concerned with maintaining the Update/Render Loop.

NOT INHERITABLE
SINGLE INSTANCE
SUPERGLOBAL (can extern)
*/

#ifndef __GameMan__
#define __GameMan__

#include "stdheader.h"  // Basic components of OpenGL programming are included in this header
#include "SceneBuilder.h"       // The following files include the core classes that make up the GameManager
class _GameManager {
private:
        HINSTANCE hInst;
        HWND hWnd;
        HDC hdc;
        HGLRC hrc;
        HBITMAP ScreenBuffer;
        RECT gRect;
        bool Controls;
public:
        bool CreateGameWindow(HINSTANCE h);     // Creates a WinAPI Window for the application - Return value indicate success
        //void DisplayLoadScreen();     // Displays a simple image based splash screen whilst the heavy lifting is done
        //void DisplayControlScreen();  // Displays a simple image based splash screen with the controls
        void HideLoadScreen();  // Hides the image based splash screen again
        bool InitOpenGL();              // Initialise OpenGL - Return value indicates success
        int Invoke();                   // Invoke the main Update/Render Loop of the Game - Return value indicates whether the game finished cleanly or not
        void Cleanup();                 // Open GL cleanup routine
        void ResizeGLWindow(int width, int height); // Called when resizing the Window containing OpenGL
        _SceneBuilder SceneBuilder;             // The games instance of the SceneBuilder class
};
extern _GameManager GameManager;
#endif