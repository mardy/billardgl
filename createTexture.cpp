// wandelt drei Matrix-Bilder in ein TexImage um

#include <GL/glut.h>
#include <stdlib.h>
#include "LA.h"
#include "bmp.h"

#include "createTexture.h"

void createTexture(FMatrix &imr, 
				   FMatrix &img, 
				   FMatrix &imb) {
  int point_i,x,y;
  GLfloat *texels = NULL;
  texels=(GLfloat *) malloc (3*imr.width()*imr.height()*sizeof(GLfloat));

  point_i=0;
  for (y=imr.nrl;y<=imr.nrh;y++) {
    for (x=imr.ncl;x<=imr.nch;x++) {
      texels[point_i++] = (GLfloat) imr.m[y][x];
      texels[point_i++] = (GLfloat) img.m[y][x];
      texels[point_i++] = (GLfloat) imb.m[y][x];
    }
  }
  
  glPixelStorei(GL_UNPACK_ALIGNMENT,1);
  
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  if (TexMMM & 2) 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  else 
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  if (TexMMM & 1)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  else
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imr.width(), imr.height(), 0, GL_RGB, GL_FLOAT, texels);

  free(texels);
}


void createTextureAlpha(FMatrix &imr, 
						FMatrix &img, 
						FMatrix &imb) {
  int point_i,x,y;
  GLfloat *texels = NULL;
  texels=(GLfloat *) malloc (4*imr.width()*imr.height()*sizeof(GLfloat));

  point_i=0;
  for (y=imr.nrl;y<=imr.nrh;y++) {
    for (x=imr.ncl;x<=imr.nch;x++) {
      texels[point_i++] = (GLfloat) img.m[y][x];
      texels[point_i++] = (GLfloat) img.m[y][x];
      texels[point_i++] = (GLfloat) imb.m[y][x];
      texels[point_i++] = (GLfloat) imr.m[y][x];
    }
  }
  
  glPixelStorei(GL_UNPACK_ALIGNMENT,1);
  
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

  if (TexMMM & 2) 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  else 
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  if (TexMMM & 1)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  else
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imr.width(), imr.height(), 0, GL_RGBA, GL_FLOAT, texels);
  
  free(texels);
}

void createTextureText(FMatrix &img,
					   GLint x,
					   GLint y,
					   GLint Rastergroesse) {
  int point_i,ax,ay;
  GLfloat *texels = NULL;
  texels=(GLfloat *) malloc (2*Rastergroesse*Rastergroesse*sizeof(GLfloat));

  point_i=0;
  for ( ay = (15-y)*Rastergroesse ; ay < (16-y)*Rastergroesse ; ay++ ) {
    for ( ax = x*Rastergroesse ; ax < (x+1)*Rastergroesse ; ax++) {
      texels[point_i++] = (GLfloat) 1.0;
      texels[point_i++] = (GLfloat) img.m[ay][ax];
    }
  }
  
  glPixelStorei(GL_UNPACK_ALIGNMENT,1);
  
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

  if (TexMMM & 2) 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  else 
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  if (TexMMM & 1)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  else
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, Rastergroesse, Rastergroesse, 0, GL_LUMINANCE_ALPHA, GL_FLOAT, texels);

  free(texels);
}

void createTextureText2(FMatrix &img,
						GLint x,
						GLint y,
						GLint Rastergroesse) {
  int point_i,ax,ay;
  GLfloat *texels = NULL;
  texels=(GLfloat *) malloc (2*Rastergroesse*Rastergroesse*sizeof(GLfloat));

  point_i=0;
  for ( ay = (15-y)*Rastergroesse ; ay < (16-y)*Rastergroesse ; ay++ ) {
    for ( ax = x*Rastergroesse ; ax < (x+1)*Rastergroesse ; ax++) {
      texels[point_i++] = (GLfloat) 0.0;
      texels[point_i++] = (GLfloat) img.m[ay][ax];
      //printf ("%i,%i ",ax,ay);
    }
  }
  
  glPixelStorei(GL_UNPACK_ALIGNMENT,1);
  
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  
  if (TexMMM & 2) 
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  else 
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  
  if (TexMMM & 1)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  else
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, Rastergroesse, Rastergroesse, 0, GL_LUMINANCE_ALPHA, GL_FLOAT, texels);
  
  free(texels);
}

void createTextureAlpha2(FMatrix &imr, 
						 FMatrix &img, 
						 FMatrix &imb, 
						 FMatrix &ima) {
  int point_i,x,y;
  GLfloat *texels = NULL;
  texels=(GLfloat *) malloc (4*imr.width()*imr.height()*sizeof(GLfloat));

  point_i=0;
  for (y=imr.nrl;y<=imr.nrh;y++) {
    for (x=imr.ncl;x<=imr.nch;x++) {
      texels[point_i++] = (GLfloat) imr.m[y][x];
      texels[point_i++] = (GLfloat) img.m[y][x];
      texels[point_i++] = (GLfloat) imb.m[y][x];
      texels[point_i++] = (GLfloat) ima.m[y][x];
    }
  }
  
  glPixelStorei(GL_UNPACK_ALIGNMENT,1);
  
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  if (TexMMM & 2) 
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  else 
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  if (TexMMM & 1)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  else
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imr.width(), imr.height(), 0, GL_RGBA, GL_FLOAT, texels);
  
  free(texels);
}


void createTextureMipmap(FMatrix &imr, 
						 FMatrix &img, 
						 FMatrix &imb) {
  int point_i,x,y;
  GLfloat *texels = NULL;
  texels=(GLfloat *) malloc (3*imr.width()*imr.height()*sizeof(GLfloat));

  point_i=0;
  for (y=imr.nrl;y<=imr.nrh;y++) {
    for (x=imr.ncl;x<=imr.nch;x++) {
      texels[point_i++] = (GLfloat) imr.m[y][x];
      texels[point_i++] = (GLfloat) img.m[y][x];
      texels[point_i++] = (GLfloat) imb.m[y][x];
    }
  }
  
  glPixelStorei(GL_UNPACK_ALIGNMENT,1);
  
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  if (TexMMM & 2) {
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  } else {
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  }

  if (TexMMM & 1) {
	if (TexMMM & 4) {
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	} else {
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	}
  } else {
	if (TexMMM & 4) {
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	} else {
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	}
  }
	  
  gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGB,imr.width(),imr.height(),GL_RGB,GL_FLOAT,texels);

  free(texels);
}
