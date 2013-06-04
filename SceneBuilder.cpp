#include "SceneBuilder.h"
#include "tex.h"
#include "MilkshapeModel.h"
//#include "CustomObjects.h"
#include "GameManager.h"
camera cam1;
int WindowDump(void);
void _SceneBuilder::PreloadScene(){

        // Obtain Sky Box textures!
        CreateGLTexture("skybox/space_front5.tga", SkyBox[0]);
        CreateGLTexture("skybox/space_back6.tga", SkyBox[1]);
        CreateGLTexture("skybox/space_left2.tga", SkyBox[2]);
        CreateGLTexture("skybox/space_right1.tga", SkyBox[3]);
        CreateGLTexture("skybox/space_top3.tga", SkyBox[4]);
        CreateGLTexture("skybox/space_bottom4.tga", SkyBox[5]);


        // Load in the models for both floors of the building
        MDL_FLOOR1 = new MilkshapeModel();

        if ( MDL_FLOOR1->loadModelData( "marksman.ms3d" ) == false )
        {
                MessageBox( NULL, "Couldn't load the model data/model.ms3d", "Error", MB_OK | MB_ICONERROR );
        }
        MDL_FLOOR1->reloadTextures();



        // Setup the Lights
        Sun.Ambience[0] = 0.4f;
        Sun.Ambience[1] = 0.4f;
        Sun.Ambience[2] = 0.4f;
        Sun.Ambience[3] = 1.0f;
        Sun.Diffuse[0] = 1.2f;
        Sun.Diffuse[1] = 1.2f;
        Sun.Diffuse[2] = 1.2f;
        Sun.Diffuse[3] = 1.0f;
        Sun.Specular[0] = 1.2f;
        Sun.Specular[1] = 1.2f;
        Sun.Specular[2] = 1.2f;
        Sun.Specular[3] = 1.0f;
        Sun.Constant = GL_LIGHT2;


        // Set a transparent material for the window
        WindowMatter.SetAmbience(1/255.0,155/255.0,217/255.0);
        WindowMatter.SetDiffuse(37,193,241);


        cam1.SwitchMode(camera::Mode::FlyThrough);
        cam1.SetPosition(0.0,0.0,0.0);
        cam1.SetRotation(0,0,0);

                SetCursorPos(400,300);
}

vector _SceneBuilder::getPoint(float u, float v){
        vector Return;
        Return.x = ((1-u)*(1-u) * (1+v)) + 2u*(1-u)*(3-3*v)+(u*u) * (4-6*v);
        Return.y = ((1-u)*(1-u) * (1-2*v)) + 2u*(1-u)*(3*v-1)+(u*u) * (4-2*v);
        Return.z = ((1-u)*(1-u) * (3*v)) + 2u*(1-u)*(2-v)+(u*u);
        return Return;
}

vector _SceneBuilder::getNormal(float u, float v){
        vector du, dv;
        du.x = 2*u*(v-1) - 8*v + 4;
        du.y = u*(14-20*v) + 10*v - 4;
        du.z = 2*u*(5*v-3) - 8*v + 4;

        dv.x = u*u - 8 *u + 1;
        dv.y = -2 *(5*u*u-5*u+1);
        dv.z = 5*u*u - 8 *u + 3;
        return du*dv;
}

void _SceneBuilder::DrawSkybox()
{
        //Sun.ApplyLight();

        glPushMatrix();
        {
                glShadeModel(GL_SMOOTH);
                WindowMatter.ApplyMaterial();
                glDisable(GL_LIGHTING);
                glDisable(GL_FOG);
                glDisable(GL_DEPTH_TEST);
                glScalef(1,1,1);
                glBindTexture(GL_TEXTURE_2D,SkyBox[0]);
                glBegin(GL_TRIANGLES);
                glNormal3f(0,0,1);
                glTexCoord2f(0,1);
                glVertex3f(-1.001,1.001,-1);
                glTexCoord2f(0,0);
                glVertex3f(-1.001,-1.001,-1);
                glTexCoord2f(1,1);
                glVertex3f(1.001,1.001,-1);
                glTexCoord2f(1,1);
                glVertex3f(1.001,1.001,-1);
                glTexCoord2f(0,0);
                glVertex3f(-1.001,-1.001,-1);
                glTexCoord2f(1,0);
                glVertex3f(1.001,-1.001,-1);
                glEnd();

                glBindTexture(GL_TEXTURE_2D,SkyBox[1]);
                glBegin(GL_TRIANGLES);
                glNormal3f(0,0,-1);
                glTexCoord2f(1,1);
                glVertex3f(-1.001,1.001,1);
                glTexCoord2f(1,0);
                glVertex3f(-1.001,-1.001,1);
                glTexCoord2f(0,1);
                glVertex3f(1.001,1.001,1);
                glTexCoord2f(0,1);
                glVertex3f(1.001,1.001,1);
                glTexCoord2f(1,0);
                glVertex3f(-1.001,-1.001,1);
                glTexCoord2f(0,0);
                glVertex3f(1.001,-1.001,1);
                glEnd();

                glBindTexture(GL_TEXTURE_2D,SkyBox[2]);
                glBegin(GL_TRIANGLES);
                glNormal3f(1,0,0);
                glTexCoord2f(0,1);
                glVertex3f(-1,1.001,1.001);
                glTexCoord2f(1,1);
                glVertex3f(-1,1.001,-1.001);
                glTexCoord2f(0,0);
                glVertex3f(-1,-1.001,1.001);
                glTexCoord2f(0,0);
                glVertex3f(-1,-1.001,1.001);
                glTexCoord2f(1,1);
                glVertex3f(-1,1.001,-1.001);
                glTexCoord2f(1,0);
                glVertex3f(-1,-1.001,-1.001);
                glEnd();

                glNormal3f(-1,0,0);
                glBindTexture(GL_TEXTURE_2D,SkyBox[3]);
                glBegin(GL_TRIANGLES);
                glTexCoord2f(0,1);
                glVertex3f(1,1.001,-1.001);
                glTexCoord2f(1,1);
                glVertex3f(1,1.001,1.001);
                glTexCoord2f(0,0);
                glVertex3f(1,-1.001,-1.001);
                glTexCoord2f(0,0);
                glVertex3f(1,-1.001,-1.001);
                glTexCoord2f(1,1);
                glVertex3f(1,1.001,1.001);
                glTexCoord2f(1,0);
                glVertex3f(1,-1.001,1.001);
                glEnd();

                glBindTexture(GL_TEXTURE_2D,SkyBox[4]);
                glBegin(GL_TRIANGLES);
                glNormal3f(0,-1,0);
                glTexCoord2f(1,0);
                glVertex3f(1.001,1,-1.001);
                glTexCoord2f(0,0);
                glVertex3f(-1.001,1,-1.001);
                glTexCoord2f(1,1);
                glVertex3f(1.001,1,1.001);
                glTexCoord2f(1,1);
                glVertex3f(1.001,1,1.001);
                glTexCoord2f(0,0);
                glVertex3f(-1.001,1,-1.001);
                glTexCoord2f(0,1);
                glVertex3f(-1.001,1,1.001);
                glEnd();

                glBindTexture(GL_TEXTURE_2D,SkyBox[5]);
                glBegin(GL_TRIANGLES);
                glNormal3f(0,-1,0);
                glTexCoord2f(1,0);
                glVertex3f(1.001,-1,1.001);
                glTexCoord2f(0,0);
                glVertex3f(-1.001,-1,1.001);
                glTexCoord2f(1,1);
                glVertex3f(1.001,-1,-1.001);
                glTexCoord2f(1,1);
                glVertex3f(1.001,-1,-1.001);
                glTexCoord2f(0,0);
                glVertex3f(-1.001,-1,1.001);
                glTexCoord2f(0,1);
                glVertex3f(-1.001,-1,-1.001);
                glEnd();

        }
        //glEnable(GL_FOG);
        glEnable(GL_LIGHTING);
        glEnable(GL_DEPTH_TEST);
        glPopMatrix();
}


void _SceneBuilder::RenderWindow(){
        glPushMatrix();
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA,  GL_ONE_MINUS_SRC_ALPHA);
        glDisable(GL_TEXTURE_2D);
        WindowMatter.ApplyMaterial();
        glBegin(GL_TRIANGLES);
        glNormal3f(0,0,1);
        glVertex3f(-1,1,-1);
        glVertex3f(-1,-1,-1);
        glVertex3f(1,1,-1);
        glVertex3f(1,1,-1);
        glVertex3f(-1,-1,-1);
        glVertex3f(1,-1,-1);
        glEnd();
        glEnable(GL_TEXTURE_2D);
        glDisable(GL_BLEND);
        glPopMatrix();
}
void _SceneBuilder::RenderScene()
{
        glPushMatrix();
        //glDisable(GL_LIGHTING);
                int xDrag, yDrag;
                POINT mouse;
                GetCursorPos(&mouse);   // Get mouse drag
                xDrag = mouse.x - 400;
                yDrag = mouse.y - 300;
                SetCursorPos(400,300);

                        cam1.IncreaseYaw(xDrag/2.0);
                        cam1.IncreasePitch(-yDrag/4.0);

                        // W, A, S & D control movement
                if(GetAsyncKeyState('W'))
                        cam1.MoveForward(0.3);
                else if(GetAsyncKeyState('S'))
                        cam1.MoveForward(-0.3);
                if(GetAsyncKeyState('A'))
                        cam1.MoveRight(-0.3);
                else if(GetAsyncKeyState('D'))
                        cam1.MoveRight(0.3);
                cam1.Update();
cam1.Switch();

Sun.ApplyLight();

        if(GetAsyncKeyState('Z'))
                MDL_FLOOR1->deformDevice.explodeCP();
        if(GetAsyncKeyState('X'))
                MDL_FLOOR1->deformDevice.bezierShips();
        if(GetAsyncKeyState('C'))
                MDL_FLOOR1->deformDevice.pushWings();
        if(GetAsyncKeyState('R'))
                MDL_FLOOR1->deformDevice.setControlPoints();



glPushMatrix();
        vector SkyboxPos = cam1.Vector_Position;
        glTranslatef(SkyboxPos.x,SkyboxPos.y,SkyboxPos.z);      // Move the skybox to it
        DrawSkybox();   // And render it...
        glPopMatrix();



        /*glPushMatrix();

         glBegin(GL_TRIANGLE_STRIP);
         float u,v;
         //glColor3f(0.0,25.0,255.0);
         int verts = 0;
         float inc = 0.05;
for( v = 0; v<=1.01;v += inc){
        glBegin(GL_TRIANGLE_STRIP);
        for( u = 0; u <= 1.01; u += inc){
                vector nPoint = getPoint(u,v);
                vector normPoint = getNormal(u,v);
                glNormal3f(normPoint.x,normPoint.y, normPoint.z);
                 glVertex3f( nPoint.x, nPoint.y, nPoint.z );
                 verts++;
                 nPoint = getPoint(u,v+inc);
                 normPoint = getNormal(u,v+inc);
                glNormal3f(normPoint.x,normPoint.y, normPoint.z);
                 glVertex3f( nPoint.x, nPoint.y, nPoint.z );
                 verts++;
        }
        glEnd();
}

        glPopMatrix();

*/
        glPushMatrix(); // Drawing ground floor
        {
                glTranslatef(-0.5,-0.7,-1.05);
                glRotatef(90,0,1,0);
                MDL_FLOOR1->draw();
                glDisable(GL_LIGHTING);
                MDL_FLOOR1->deformDevice.drawCP();
                glEnable(GL_LIGHTING);
        } glPopMatrix();

        glPopMatrix();

}

void _SceneBuilder::ApprovePosition(vector& position){


}