#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include "viertelLoch.h"

void viertelLoch(GLfloat x, GLfloat y, GLint xd, GLint yd,
		 GLfloat z1, GLfloat z2, GLfloat r1, GLfloat r2) {

  /* x = Breite des Rechtecks
     y = Höhe des Rechtecks
     xd = Anzahl der Teile der x-Strecke
     yd = Anzahl der Teile der y-Stecke
     z1 = Tiefe äußerer Kreis
     z2 = Tiefe innerer Kreis
     r1 = innerer Radius
     r2 = äußerer Radius
  */

  GLfloat *vertices;
  GLfloat *normals;
  GLuint *indices;

  vertices = (GLfloat*) malloc (12*(xd+yd+1)* sizeof(GLfloat));
  normals = (GLfloat*) malloc (12*(xd+yd+1)* sizeof(GLfloat));
  indices = (GLuint*) malloc (12*(xd+yd)* sizeof(GLint));

  GLint iv=0; GLint ii=0; GLint in=0;

  for (int iy=0;iy<yd;iy++) {
    GLfloat yi=(iy*y)/yd;
    GLfloat laenge=sqrt(x*x+yi*yi);
    GLfloat xn=x/laenge;
    GLfloat yn=yi/laenge;

    vertices[iv++]=x;
    vertices[iv++]=yi;
    vertices[iv++]=0;

    normals[in++]=0;
    normals[in++]=0;
    normals[in++]=1;

    vertices[iv++]=r1*xn;
    vertices[iv++]=r1*yn;
    vertices[iv++]=0;

    normals[in++]=0;
    normals[in++]=0;
    normals[in++]=1;

    vertices[iv++]=r2*xn;
    vertices[iv++]=r2*yn;
    vertices[iv++]=-z1;

    normals[in++]=-xn;
    normals[in++]=-yn;
    normals[in++]=0;

    vertices[iv++]=r2*xn;
    vertices[iv++]=r2*yn;
    vertices[iv++]=-z2;

    normals[in++]=-xn;
    normals[in++]=-yn;
    normals[in++]=0;
  }

  for (int ix=xd;ix>=0;ix--) {
    GLfloat xi=(ix*x)/xd;
    GLfloat laenge=sqrt(xi*xi+y*y);
    GLfloat xn=xi/laenge;
    GLfloat yn=y/laenge;

    vertices[iv++]=xi;
    vertices[iv++]=y;
    vertices[iv++]=0;

    normals[in++]=0;
    normals[in++]=0;
    normals[in++]=1;

    vertices[iv++]=r1*xn;
    vertices[iv++]=r1*yn;
    vertices[iv++]=0;

    normals[in++]=0;
    normals[in++]=0;
    normals[in++]=1;

    vertices[iv++]=r2*xn;
    vertices[iv++]=r2*yn;
    vertices[iv++]=-z1;

    normals[in++]=-xn;
    normals[in++]=-yn;
    normals[in++]=0;

    vertices[iv++]=r2*xn;
    vertices[iv++]=r2*yn;
    vertices[iv++]=-z2;

    normals[in++]=-xn;
    normals[in++]=-yn;
    normals[in++]=0;
  }

  for (int b=0;b<xd+yd;b++) {
    for (int h=0;h<=2;h++) {
      indices[ii++]=4*b+h;
      indices[ii++]=4*(b+1)+h;
      indices[ii++]=4*(b+1)+h+1;
      indices[ii++]=4*b+h+1;
    }
  }

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);

  glNormalPointer(GL_FLOAT, 0, normals);
  glVertexPointer(3, GL_FLOAT, 0, vertices);

  glDrawElements(GL_QUADS,12*(xd+yd), GL_UNSIGNED_INT,indices);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);

  free(vertices);
  free(normals);
  free(indices);
}

void viertelLoch(GLfloat x, GLfloat y, GLint xd, GLint yd,
                 GLfloat z1, GLfloat z2, GLfloat r1, GLfloat r2,
		 GLfloat xo,GLfloat yo,GLfloat m00,GLfloat m01,GLfloat m10,GLfloat m11) {

  /* x = Breite des Rechtecks
     y = Höhe des Rechtecks
     xd = Anzahl der Teile der x-Strecke
     yd = Anzahl der Teile der y-Stecke
     z1 = Tiefe äußerer Kreis
     z2 = Tiefe innerer Kreis
     r1 = innerer Radius
     r2 = äußerer Radius
  */

  GLfloat *vertices;
  GLfloat *normals;
  GLfloat *texcoord;
  GLuint *indices;

  vertices = (GLfloat*) malloc (12*(xd+yd+1)* sizeof(GLfloat));
  normals = (GLfloat*) malloc (12*(xd+yd+1)* sizeof(GLfloat));
  texcoord = (GLfloat*) malloc (8*(xd+yd+1)* sizeof(GLfloat));
  indices = (GLuint*) malloc (12*(xd+yd)* sizeof(GLint));

  GLint iv=0; GLint ii=0; GLint in=0; GLint it=0;

  for (int iy=0;iy<yd;iy++) {
    GLfloat yi=(iy*y)/yd;
    GLfloat laenge=sqrt(x*x+yi*yi);
    GLfloat xn=x/laenge;
    GLfloat yn=yi/laenge;

    vertices[iv++]=x;
    vertices[iv++]=yi;
    vertices[iv++]=0;
    normals[in++]=0;
    normals[in++]=0;
    normals[in++]=1;
    texcoord[it++]=(m00*x+m01*yi+xo)/8.5;
    texcoord[it++]=(m10*x+m11*yi+yo)/8.5;

    vertices[iv++]=r1*xn;
    vertices[iv++]=r1*yn;
    vertices[iv++]=0;
    normals[in++]=0;
    normals[in++]=0;
    normals[in++]=1;
    texcoord[it++]=(m00*r1*xn+m01*r1*yn+xo)/8.5;
    texcoord[it++]=(m10*r1*xn+m11*r1*yn+yo)/8.5;

    vertices[iv++]=r2*xn;
    vertices[iv++]=r2*yn;
    vertices[iv++]=-z1;
    normals[in++]=-xn;
    normals[in++]=-yn;
    normals[in++]=0;
    texcoord[it++]=(m00*r2*xn+m01*r2*yn+xo)/8.5;
    texcoord[it++]=(m10*r2*xn+m11*r2*yn+yo)/8.5;

    vertices[iv++]=r2*xn;
    vertices[iv++]=r2*yn;
    vertices[iv++]=-z2;
    normals[in++]=-xn;
    normals[in++]=-yn;
    normals[in++]=0;
    texcoord[it++]=(m00*r2*xn+m01*r2*yn+xo)/8.5;
    texcoord[it++]=(m10*r2*xn+m11*r2*yn+yo)/8.5;
  }

  for (int ix=xd;ix>=0;ix--) {
    GLfloat xi=(ix*x)/xd;
    GLfloat laenge=sqrt(xi*xi+y*y);
    GLfloat xn=xi/laenge;
    GLfloat yn=y/laenge;

    vertices[iv++]=xi;
    vertices[iv++]=y;
    vertices[iv++]=0;
    normals[in++]=0;
    normals[in++]=0;
    normals[in++]=1;
    texcoord[it++]=(m00*xi+m01*y+xo)/8.5;
    texcoord[it++]=(m10*xi+m11*y+yo)/8.5;

    vertices[iv++]=r1*xn;
    vertices[iv++]=r1*yn;
    vertices[iv++]=0;
    normals[in++]=0;
    normals[in++]=0;
    normals[in++]=1;
    texcoord[it++]=(m00*r1*xn+m01*r1*yn+xo)/8.5;
    texcoord[it++]=(m10*r1*xn+m11*r1*yn+yo)/8.5;

    vertices[iv++]=r2*xn;
    vertices[iv++]=r2*yn;
    vertices[iv++]=-z1;
    normals[in++]=-xn;
    normals[in++]=-yn;
    normals[in++]=0;
    texcoord[it++]=(m00*r2*xn+m01*r2*yn+xo)/8.5;
    texcoord[it++]=(m10*r2*xn+m11*r2*yn+yo)/8.5;

    vertices[iv++]=r2*xn;
    vertices[iv++]=r2*yn;
    vertices[iv++]=-z2;
    normals[in++]=-xn;
    normals[in++]=-yn;
    normals[in++]=0;
    texcoord[it++]=(m00*r2*xn+m01*r2*yn+xo)/8.5;
    texcoord[it++]=(m10*r2*xn+m11*r2*yn+yo)/8.5;
  }

  for (int b=0;b<xd+yd;b++) {
    for (int h=0;h<=2;h++) {
      indices[ii++]=4*b+h;
      indices[ii++]=4*(b+1)+h;
      indices[ii++]=4*(b+1)+h+1;
      indices[ii++]=4*b+h+1;
    }
  }

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  glNormalPointer(GL_FLOAT, 0, normals);
  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glTexCoordPointer(2, GL_FLOAT, 0, texcoord);

  glDrawElements(GL_QUADS,12*(xd+yd), GL_UNSIGNED_INT,indices);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);

  free(vertices);
  free(normals);
  free(indices);
  free(texcoord); 
}
