/*
        Model.cpp

                Abstract base class for a model. The specific extended class wil
l render the given model.

        Author: Brett Porter
        Email: brettporter@yahoo.com
        Website: http://www.geocities.com/brettporter/
        Copyright (C)2000, Brett Porter. All Rights Reserved.

        This file may be used only as long as this copyright notice remains intact.
*/

#include <windows.h>            // Header File For Windows
#include <gl\gl.h>                      // Header File For The OpenGL32 Library

#include "Model.h"
#include "tex.h"
#include "vector.h"
Model::Model()
{
        m_numMeshes = 0;
        m_pMeshes = NULL;
        m_numMaterials = 0;
        m_pMaterials = NULL;
        m_numTriangles = 0;
        m_pTriangles = NULL;
        m_numVertices = 0;
        m_pVertices = NULL;
        deformDevice.setControlPoints();
}

Model::~Model()
{
        int i;
        for ( i = 0; i < m_numMeshes; i++ )
                delete[] m_pMeshes[i].m_pTriangleIndices;
        for ( i = 0; i < m_numMaterials; i++ )
                delete[] m_pMaterials[i].m_pTextureFilename;

        m_numMeshes = 0;
        if ( m_pMeshes != NULL )
        {
                delete[] m_pMeshes;
                m_pMeshes = NULL;
        }

        m_numMaterials = 0;
        if ( m_pMaterials != NULL )
        {
                delete[] m_pMaterials;
                m_pMaterials = NULL;
        }

        m_numTriangles = 0;
        if ( m_pTriangles != NULL )
        {
                delete[] m_pTriangles;
                m_pTriangles = NULL;
        }

        m_numVertices = 0;
        if ( m_pVertices != NULL )
        {
                delete[] m_pVertices;
                m_pVertices = NULL;
        }
}

void Model::draw()
{
        GLboolean texEnabled = glIsEnabled( GL_TEXTURE_2D );

        // Draw by group
        for ( int i = 0; i < m_numMeshes; i++ )
        {
                int materialIndex = m_pMeshes[i].m_materialIndex;
                if ( materialIndex >= 0 )
                {
                        glMaterialfv( GL_FRONT, GL_AMBIENT, m_pMaterials[materialIndex].m_ambient );
                        glMaterialfv( GL_FRONT, GL_DIFFUSE, m_pMaterials[materialIndex].m_diffuse );
                        glMaterialfv( GL_FRONT, GL_SPECULAR, m_pMaterials[materialIndex].m_specular );
                        glMaterialfv( GL_FRONT, GL_EMISSION, m_pMaterials[materialIndex].m_emissive );
                        glMaterialf( GL_FRONT, GL_SHININESS, m_pMaterials[materialIndex].m_shininess );

                        if ( m_pMaterials[materialIndex].m_texture > 0 )
                        {
                                glBindTexture( GL_TEXTURE_2D, m_pMaterials[materialIndex].m_texture );
                                glEnable( GL_TEXTURE_2D );
                        }
                        else
                                glDisable( GL_TEXTURE_2D );
                }
                else
                {
                        // Material properties?
                        glDisable( GL_TEXTURE_2D );
                }

                glBegin( GL_TRIANGLES );
                {
                        for ( int j = 0; j < m_pMeshes[i].m_numTriangles; j++ )
                        {
                                int triangleIndex = m_pMeshes[i].m_pTriangleIndices[j];
                                const Triangle* pTri = &m_pTriangles[triangleIndex];

                                for ( int k = 0; k < 3; k++ )
                                {
                                        int index = pTri->m_vertexIndices[k];
                                        vector i,o;
                                        i.x = (m_pVertices[index].m_location[0]-scaleOff.x)/scale.x;
                                        i.y = (m_pVertices[index].m_location[1]-scaleOff.y)/scale.y;
                                        i.z = (m_pVertices[index].m_location[2]-scaleOff.z)/scale.z;
                                        try{
                                        if(i.x > 1.0)
                                                throw 1;
                                        if(i.y > 1.0)
                                                throw 2;
                                        if(i.z > 1.0)
                                                throw 3;
                                        }
                                        catch(int e){
                                                MessageBox(NULL,"ERROR: input out of scale","User Error",0);

                                        }
                                        o = deformDevice.deform(i.x,i.y,i.z);
#define deform
#ifdef deform
                                        float vertex[] = {o.z,o.x,o.y};
#else
                                        float vertex[] = {m_pVertices[index].m_location[0],m_pVertices[index].m_location[1],m_pVertices[index].m_location[2]};
#endif
                                        glNormal3fv( pTri->m_vertexNormals[k] );

                                        glTexCoord2f( pTri->m_s[k], pTri->m_t[k]
 );
                                        glVertex3fv(vertex );
                                }
                        }
                }
                glEnd();
        }

        if ( texEnabled )
                glEnable( GL_TEXTURE_2D );
        else
                glDisable( GL_TEXTURE_2D );
}

void Model::reloadTextures()
{
        GLuint temp;
        for ( int i = 0; i < m_numMaterials; i++ )
                if ( strlen( m_pMaterials[i].m_pTextureFilename ) > 0 )
                {
                        CreateGLTexture(m_pMaterials[i].m_pTextureFilename, temp );
                        m_pMaterials[i].m_texture = temp;
                }
                else
                        m_pMaterials[i].m_texture = 0;
        getScale();

}


void Model::getScale(){
        vector max;
        vector min;
        for ( int i = 0; i < m_numMeshes; i++ )
        {

                        for ( int j = 0; j < m_pMeshes[i].m_numTriangles; j++ )
                        {
                                int triangleIndex = m_pMeshes[i].m_pTriangleIndices[j];
                                const Triangle* pTri = &m_pTriangles[triangleIndex];

                                for ( int k = 0; k < 3; k++ )
                                {
                                        int index = pTri->m_vertexIndices[k];


                                         if(m_pVertices[index].m_location[0]>max.x)
                                                 max.x = m_pVertices[index].m_location[0];
                                         else if(m_pVertices[index].m_location[0]<min.x)
                                                 min.x = m_pVertices[index].m_location[0];
                                         if(m_pVertices[index].m_location[1]>max.y)
                                                 max.y = m_pVertices[index].m_location[1];
                                         else if(m_pVertices[index].m_location[1]<min.y)
                                                 min.y = m_pVertices[index].m_location[1];
                                         if(m_pVertices[index].m_location[2]>max.z)
                                                 max.z = m_pVertices[index].m_location[2];
                                         else if(m_pVertices[index].m_location[2]<min.z)
                                                 min.z = m_pVertices[index].m_location[2];
                                }
                        }
        }
        scale = max-min;
        scaleOff = min;
}