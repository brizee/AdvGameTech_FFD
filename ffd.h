/*
Freeform Deformation
Brian Beacom
*/
#include "vector.h"

#ifndef FFD_H
#define FFD_H
class FFD{
private:
        // Control Point Declarations
        vector ControlPoints[4][4][4];
        bool held8,held9,held4,held6,held2,held3,held5,moveMode;
public:
        // Deform Function
        vector lerp(vector a, vector b, float t){
                return a*(1-t) + b*t;
        }
        int sX,sY,sZ;
        FFD(){
                setControlPoints();
                sX = 0;
                sY = 0;
                sZ = 0;
        }
        void setControlPoints(){
                for(int a = 0; a < 4; a++){
                        for(int b = 0; b < 4; b++){
                                for(int c = 0; c < 4;c++){
                                        vector nPoint;
                                        nPoint.x =  b * 0.1;
                                        nPoint.z = c * 0.25;
                                        nPoint.y = a * 0.5;
                                        ControlPoints[a][b][c] = nPoint;
                                }

                        }

                }

        }

        void pushWings(){
                vector origin;
                origin.x = 0.375;
                origin.y = 0.375;
                origin.z = 0.375;
                for(int a = 2; a < 4; a++)
                {
                        for(int b = 0; b < 4; b++){
                                for(int c = 0; c < 4;c++){
                                        vector nPoint = ControlPoints[a][b][c] - origin;
                                        nPoint.z *= 2;
                                        nPoint.x = 0;
                                        nPoint.y = -10;
                                        ControlPoints[a][b][c] += nPoint.GetNormal()/350;
                                }

                        }

                }
        }


        void explodeCP(){
                vector origin;
                origin.x = 0.375;
                origin.y = 0.375;
                origin.z = 0.375;
                for(int a = 0; a < 4; a++)
                {
                        for(int b = 0; b < 4; b++){
                                for(int c = 0; c < 4;c++){
                                        vector nPoint = ControlPoints[a][b][c] - origin;
                                        ControlPoints[a][b][c] += nPoint.GetNormal()/350;
                                }

                        }

                }
        }
        void bezierShips(){
                for(int a = 0; a < 4; a++)
                {
                        for(int b = 0; b < 4; b++){
                                for(int c = 0; c < 4;c++){
                                        switch(a){
                                        case 0:
                                        case 3:

                                                break;
                                        case 1:
                                                ControlPoints[a][b][c].x += 0.01;
                                                break;
                                        case 2:
                                                ControlPoints[a][b][c].x -= 0.01;
                                                break;

                                        }

                                }

                        }

                }
        }


        void drawCP(){
                if(GetAsyncKeyState(VK_NUMPAD6))
                {
                        if(moveMode && !held6){
                                vector n;
                                n.y = 0.04;
                                ControlPoints[sX][sY][sZ] += n;
                        }
                        else
                                sX= held6?sX:(sX+1)%4;
                        held6 = true;
                }
                else
                        held6 = false;
                if(GetAsyncKeyState(VK_NUMPAD4)){
                        if(moveMode && !held4){
                                vector n;
                                n.y = -0.04;
                                ControlPoints[sX][sY][sZ] += n;
                        }
                        else
                                sX= held4?sX: (sX-1)%4;
                        held4 = true;
                }
                else
                        held4 = false;

                if(GetAsyncKeyState(VK_NUMPAD8)){
                        if(moveMode && !held8){
                                vector n;
                                n.z = 0.04;
                                ControlPoints[sX][sY][sZ] += n;
                        }
                        else
                                sZ= held8?sZ: (sZ+1)%4;
                        held8 = true;
                }
                else
                        held8 = false;
                if(GetAsyncKeyState(VK_NUMPAD2))
                {
                        if(moveMode && !held2){
                                vector n;
                                n.z = -0.04;
                                ControlPoints[sX][sY][sZ] += n;
                        }
                        else
                                sZ=held2?sZ: (sZ-1)%4;
                        held2 = true;
                }
                else
                        held2 = false;
                if(GetAsyncKeyState(VK_NUMPAD9)){
                        sY= held9?sY:(sY+1)%4;
                        if(moveMode && !held9){
                                vector n;
                                n.x = 0.04;
                                ControlPoints[sX][sY][sZ] += n;
                        }
                        else
                                held9 = true;
                }
                else
                        held9 = false;

                if(GetAsyncKeyState(VK_NUMPAD3)){
                        if(moveMode && !held3){
                                vector n;
                                n.x = -0.04;
                                ControlPoints[sX][sY][sZ] += n;
                        }
                        else
                                sY=held3?sY:(sY-1)%4;
                        held3 = true;
                }
                else
                        held3 = false;

                if(GetAsyncKeyState(VK_NUMPAD5)){
                        if(!held5)
                                moveMode = !moveMode;
                        held5 = true;
                }
                else
                        held5 = false;

                for(int a = 0; a < 4; a++)
                {
                        for(int b = 0; b < 4; b++){
                                for(int c = 0; c < 4;c++){
                                        glPushMatrix();
                                        if(c == sZ && b == sY && a == sX)
                                                glColor3f(0.1,1.0,0.1);
                                        else
                                                glColor3f(1.0,0.1,0.1);
                                        glTranslatef(ControlPoints[a][b][c].z,ControlPoints[a][b][c].x,ControlPoints[a][b][c].y);
                                        gluSphere(gluNewQuadric(),0.01,4,4);
                                        glPopMatrix();
                                        glColor3f(255.0,255.0,255.0);
                                }

                        }

                }
        }

        vector deform(float u, float v, float w){
                vector ffValues[4];
                for(int d = 0; d < 4;d++){
                        vector fValues[4];

                        /*#################### Produce Quadratic Control Points ##################################### */
                        for(int c = 0; c < 4; c++)
                        {
                                vector tValues[4][4];
                                for(int a = 0; a < 4; a++) // Loop through each line of matrix
                                {
                                        for(int b = 0; b < 4-a;b++) // Loop through each value in line a of matrix
                                        {
                                                if(a == 0)
                                                        tValues[0][b] = ControlPoints[d][c][b]; // Copy Original Control Points into working matrix
                                                else
                                                        tValues[a][b] = lerp(tValues[a-1][b],tValues[a-1][b+1],u);      // Derive new control point from working matrix

                                        }
                                }

                                fValues[c] = tValues[3][0];     // Copy final control point out of working matrix
                        }



                        /*#################### Produce Cubic Control Points ##################################### */
                        vector tValues[4][4];
                        for(int a = 0; a < 4; a++) // Loop through each line of matrix
                        {
                                for(int b = 0; b < 4-a;b++) // Loop through each value in line a of matrix
                                {
                                        if(a == 0)
                                                tValues[0][b] = fValues[b]; // Copy Original Control Points into working matrix
                                        else
                                                tValues[a][b] = lerp(tValues[a-1][b],tValues[a-1][b+1],v);      // Derive new control point from working matrix

                                }
                        }

                        ffValues[d] = tValues[3][0];    // Copy final control point out of working matrix
                }


                /*#################### Produce Final Co-Ordinates ##################################### */
                vector tValues[4][4];
                for(int a = 0; a < 4; a++) // Loop through each line of matrix
                {
                        for(int b = 0; b < 4-a;b++) // Loop through each value in line a of matrix
                        {
                                if(a == 0)
                                        tValues[0][b] = ffValues[b]; // Copy Original Control Points into working matrix
                                else
                                        tValues[a][b] = lerp(tValues[a-1][b],tValues[a-1][b+1],w);  // Derive new control point from working matrix
                        }
                }
                return tValues[3][0];
        }
        // Manipulate Control Point Functions
};


#endif // ndef FFD_H
