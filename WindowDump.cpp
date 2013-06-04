/*
   Write the current view to a file
   The multiple fputc()s can be replaced with
      fwrite(image,width*height*3,1,fptr);
   If the memory pixel order is the same as the destination file format.
*/
#include <windows.h>            // Header File For Windows
#include <gl\gl.h>                      // Header File For The OpenGL32 Library
#include <iostream>                     // Input/Output Stream FunctionsBYTE
#define stereo false
#define width 800
#define height 600
typedef struct _BITMAPINFOHEADER2 {
  BYTE idLength;
  BYTE ClrMapType;
  BYTE imgType;
  WORD fClrMapHeader;
  WORD fClrMapCount;
  BYTE fClrMapBitCount;

  WORD llX;
  WORD llY;
  WORD imgwidth;
  WORD imgheight;
  BYTE Bpp;
  BYTE flags;
} BITMAPINFOHEADER2;
int WindowDump(void)
{
        BITMAPINFOHEADER2 header;
        header.idLength =0;
        header.ClrMapType = 0;
        header.imgType = 2;
        header.fClrMapHeader = sizeof(BITMAPINFOHEADER2)/8;
        header.fClrMapCount = 0;
        header.fClrMapBitCount = 0;
        header.llX = 0;
        header.llY = 0;
        header.imgwidth = 800;
        header.imgheight = 600;
        header.Bpp = 3;
        header.flags = 0;

   int i,j;
   FILE *fptr;
   static int counter = 0; /* This supports animation sequences */
   char fname[32];
   unsigned int *image;

   /* Allocate our buffer for the image */
   if ((image = (unsigned int*)malloc(4*width*height*sizeof(int))) == NULL) {
      fprintf(stderr,"Failed to allocate memory for image\n");
      return(FALSE);
   }

   glPixelStorei(GL_PACK_ALIGNMENT,4);
   glPixelStorei(GL_UNPACK_ALIGNMENT,4);

   /* Open the file */
   if (stereo)
      sprintf(fname,"L_%04d.raw",0);
   else
      sprintf(fname,"C_%04d.raw",0);
   if ((fptr = fopen(fname,"w")) == NULL) {
      fprintf(stderr,"Failed to open file for window dump\n");
      return(FALSE);
   }

   /* Copy the image into our buffer */
   glReadBuffer(GL_BACK_LEFT);
   glReadPixels(0,0,width,height,GL_RGBA,GL_UNSIGNED_INT,image);

   /* Write the raw file */
   /* fprintf(fptr,"P6\n%d %d\n255\n",width,height); for ppm */
   for (j=height-1;j>=0;j--) {
      for (i=0;i<width;i++) {
         fputc(image[4*j*width+4*i+0],fptr);
         fputc(image[4*j*width+4*i+1],fptr);
         fputc(image[4*j*width+4*i+2],fptr);
      }
   }
   fclose(fptr);

   if (stereo) {
      /* Open the file */
      sprintf(fname,"R_%04d.raw",counter);
      if ((fptr = fopen(fname,"w")) == NULL) {
         fprintf(stderr,"Failed to open file for window dump\n");
         return(FALSE);
      }

      /* Copy the image into our buffer */
      glReadBuffer(GL_BACK_RIGHT);
      glReadPixels(0,0,width,height,GL_RGB,GL_UNSIGNED_BYTE,image);

      /* Write the raw file */
      /* fprintf(fptr,"P6\n%d %d\n255\n",width,height); for ppm */
      for (j=height-1;j>=0;j--) {
         for (i=0;i<width;i++) {
            fputc(image[3*j*width+3*i+0],fptr);
            fputc(image[3*j*width+3*i+1],fptr);
            fputc(image[3*j*width+3*i+2],fptr);
         }
      }
      fclose(fptr);
   }

   /* Clean up */
   counter++;
   free(image);
   return(TRUE);
}