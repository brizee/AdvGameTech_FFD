/*
AG0800A Semester 2 Coursework   -       2010
Brian Beacom (0900305)

GameManager.h and Gamemanager_*.cpp contain the Game Manager class which is the top level class concerned with maintaining the Update/Render

This file pertains to the operations neccessary to run the game
*/

#include "GameManager.h"
//#include <iostream>
int WindowDump(void);
int _GameManager::Invoke(){
        MSG         msg;
        while(true){
                if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
                {
                        if (msg.message==WM_QUIT)
                                break;
                        TranslateMessage (&msg);
                        DispatchMessage (&msg);
                }
                else{
                        if(GetAsyncKeyState(VK_ESCAPE))
                                return 0;

                        int fps = 30;
                        int nFrameStartTime = GetTickCount();

                        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Clear The Screen And The Depth Buffer
                        glMatrixMode(GL_MODELVIEW);
                                glLoadIdentity();// load Identity Matrix

                                SceneBuilder.RenderScene();
                                //glFlush();
                                //WindowDump();
                                SwapBuffers(hdc);// Swap the frame buffers
                                int frameTime = GetTickCount() - nFrameStartTime;
                                //double afps = 1000.0/(frameTime);
                                //char buff[] = "00000.00000";
                                //sprintf(buff, "%f\n", afps);
                                //OutputDebugString(buff);
        while (GetTickCount()-nFrameStartTime < 1000/fps) { Sleep(0); }
                }
        }
        //PlayerManager.CleanDirectInput();
        Cleanup();
        return msg.wParam;
}



void _GameManager::Cleanup()
{
        if (hrc)
        {
                wglMakeCurrent(NULL, NULL);     // free rendering memory
                wglDeleteContext(hrc);          // Delete our OpenGL Rendering Context
        }

        if (hdc)
                ReleaseDC(hWnd, hdc);                   // Release our HDC from memory

        UnregisterClass("FirstWindowClass", hInst);// Free the window class

        PostQuitMessage (0);            // Post a QUIT message to the window
}