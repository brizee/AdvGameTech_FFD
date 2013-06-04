/*
AG0800A Semester 2 Coursework   -       2010
Brian Beacom (0900305)

GameManager.h and Gamemanager_*.cpp contain the Game Manager class which is the top level class concerned with maintaining the Update/Render Loop.

This file pertains to the operations neccessary to initialise the game
*/
#include "stdheader.h"
#include "GameManager.h"

// Window Parameters - these defines set the Parameters for the Window
#define WIN_HEIGHT 600
#define WIN_WIDTH 800
#define WIN_CLASS "OpenGLWindow"
#define WIN_TITLE "OpenGL Playground (0900305)"

#define GL_COLOUR_DEPTH 16
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);


 _GameManager GameManager;


bool _GameManager::CreateGameWindow(HINSTANCE h){
        HWND hwnd;

        // Create a Window Class, essentially a template for the windows appearance
        WNDCLASS wcex;

        memset(&wcex, 0, sizeof(WNDCLASS));
        wcex.style                      = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc        = WndProc;
        wcex.hInstance          = h;
        wcex.hIcon                      = LoadIcon(NULL, IDI_APPLICATION);;
        wcex.hCursor            = LoadCursor(NULL, IDC_ARROW);
        wcex.hbrBackground      = (HBRUSH) (COLOR_WINDOW+1);
        wcex.lpszMenuName       = NULL;
        wcex.lpszClassName      = WIN_CLASS;


        RegisterClass(&wcex);// Register the class

        DWORD dwStyle;  // Set some options for getting the window the right size
        dwStyle = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

        hInst = h;

        //Set the Client area of the window to be our resolution.
        RECT glwindow;
        glwindow.left           = 0;
        glwindow.right          = WIN_WIDTH;
        glwindow.top            = 0;
        glwindow.bottom         = WIN_HEIGHT;

        AdjustWindowRect( &glwindow, dwStyle, false);

        //Create the window using the class we made and the size calculated earlier
        hwnd = CreateWindow(    WIN_CLASS,
                WIN_TITLE,
                dwStyle,
                0,
                0,
                glwindow.right  - glwindow.left,
                glwindow.bottom - glwindow.top,
                NULL,
                NULL,
                hInst,
                NULL
                );

        if(!hwnd){
                MessageBox(NULL, "hwnd returned as NULL", "Windows Creation Failed", MB_OK | MB_ICONERROR);
                return false;
        }// If we couldn't get a handle to the window, return false and put up an error message

        ShowWindow(hwnd, SW_SHOWNORMAL);        // Otherwise set it going
        UpdateWindow(hwnd);
        SetFocus(hwnd);
        hWnd = hwnd;


        hdc = GetDC(hwnd);
        ScreenBuffer = CreateCompatibleBitmap(hdc,WIN_WIDTH,WIN_HEIGHT);
        return true;
}


bool _GameManager::InitOpenGL(){
        // Obtain the windows dimensions

        GetClientRect(hWnd, &gRect);


        // Find a template that best meets our requirements for Pixel Depth and Information
        PIXELFORMATDESCRIPTOR pfd = {0};
        int pixelformat;

        pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);      // Set the size of the structure
        pfd.nVersion = 1;                                                       // Always set this to 1
        // Pass in the appropriate OpenGL flags
        pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        pfd.dwLayerMask = PFD_MAIN_PLANE;                       // standard mask (this is ignored anyway)
        pfd.iPixelType = PFD_TYPE_RGBA;                         // RGB and Alpha pixel type
        pfd.cColorBits = GL_COLOUR_DEPTH;                               // Here we use our #define for the color bits
        pfd.cDepthBits = GL_COLOUR_DEPTH;                               // Ignored for RBA
        pfd.cAccumBits = 0;                                                     // nothing for accumulation
        pfd.cStencilBits = 0;                                           // nothing for stencil

        //Gets a best match on the pixel format as passed in from device
        if ( (pixelformat = ChoosePixelFormat(hdc, &pfd)) == false )
        {
                MessageBox(NULL, "ChoosePixelFormat failed", "Error", MB_OK);
                return false;
        }

        //sets the pixel format if its ok.
        if (SetPixelFormat(hdc, pixelformat, &pfd) == false)
        {
                MessageBox(NULL, "SetPixelFormat failed", "Error", MB_OK);
                return false;
        }


        hrc = wglCreateContext(hdc);    //  creates a hardware rendering context from  hdc
        wglMakeCurrent(hdc, hrc);               //      Use this HRC.


        // Tell OpenGL where to position the OpenGL window
        glViewport(0,0,WIN_WIDTH,WIN_HEIGHT);

        // Setup the Projection Matrix
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        //calculate aspect ratio
        gluPerspective(45.0f,(GLfloat)WIN_WIDTH/(GLfloat)WIN_HEIGHT,0.01,100.0);

        glMatrixMode(GL_MODELVIEW);// Select The Modelview Matrix
        glLoadIdentity();// Reset The Modelview Matrix


        // Load Textures and Models here
        SceneBuilder.PreloadScene();

        //OpenGL settings
        glShadeModel(GL_SMOOTH);                                                        // Enable Smooth Shading
        glClearColor(0.2f, 0.2f, 0.2f, 0.5f);                           // Black Background
        glClearDepth(1.0f);                                                                     // Depth Buffer Setup
        glEnable(GL_DEPTH_TEST);                                                        // Enables Depth Testing
        glDepthFunc(GL_LEQUAL);                                                         // The Type Of Depth Testing To Do
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);      // Really Nice Perspective Calculations
        glDisable(GL_LIGHTING);
        glEnable(GL_TEXTURE_2D);                                                        //Enable texturing!
        glDisable(GL_CULL_FACE);
        //Also, do any other setting ov variables here for your app if you wish.
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);// Linear Filtering
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);// Linear Filtering

}


void _GameManager::ResizeGLWindow(int width, int height)// Initialize The GL Window
{
        if (height==0)// Prevent A Divide By Zero error
        {
                height=1;// Make the Height Equal One
        }
        GetClientRect(hWnd, &gRect);
        glViewport(0,0,width,height);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        //calculate aspect ratio
        gluPerspective(60.0f,(GLfloat)width/(GLfloat)height,1.0,100.0);

        glMatrixMode(GL_MODELVIEW);// Select The Modelview Matrix
        glLoadIdentity();// Reset The Modelview Matrix
}