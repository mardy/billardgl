#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include "SchattenKreis.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void SchattenKreis(GLint Unterteilungen, 
				   GLfloat Innenradius, 
				   GLfloat Aussenradius, 
				   GLfloat InnenAlpha,
				   GLfloat AussenAlpha) {
  
  GLfloat *vertices;
  GLfloat *colors;
  GLint *indices;
  
  vertices = (GLfloat*) malloc (3*2*Unterteilungen* sizeof(GLfloat));
  colors   = (GLfloat*) malloc (4*2*Unterteilungen* sizeof(GLfloat));
  indices = (GLint*) malloc (4*(3*(Unterteilungen/2)-1)* sizeof(GLint));
  
  GLint iv=0,ic=0,ii=0;

  for (GLint i=0;i<Unterteilungen;i++) {
    vertices[iv++]=Aussenradius*cos(2*i*M_PI/Unterteilungen);
    vertices[iv++]=Aussenradius*sin(2*i*M_PI/Unterteilungen);
    vertices[iv++]=0;
    colors[ic++]=1.0;
    colors[ic++]=1.0;
    colors[ic++]=1.0;
    colors[ic++]=AussenAlpha;
    vertices[iv++]=Innenradius*cos(2*i*M_PI/Unterteilungen);
    vertices[iv++]=Innenradius*sin(2*i*M_PI/Unterteilungen);
    vertices[iv++]=0;
    colors[ic++]=1.0;
    colors[ic++]=1.0;
    colors[ic++]=1.0;
    colors[ic++]=InnenAlpha;
  }
  
  for (GLint j=0;j<Unterteilungen-1;j++) {
    indices[ii++]=2*j;
    indices[ii++]=2*j+2;
    indices[ii++]=2*j+3;
    indices[ii++]=2*j+1;
  }

  indices[ii++]=2*Unterteilungen-2;
  indices[ii++]=0;
  indices[ii++]=1;
  indices[ii++]=2*Unterteilungen-1;
  
  for (GLint k=0;k<=(Unterteilungen/4)-1;k++) {
    indices[ii++]=2*k+1;
    indices[ii++]=2*k+3;
    indices[ii++]=2*((Unterteilungen/2)-k)-1;
    indices[ii++]=2*((Unterteilungen/2)-k)+1;
  }

  for (GLint l=Unterteilungen/2;l<=(3*Unterteilungen/4)-1;l++) {
    indices[ii++]=2*l+1;
    indices[ii++]=2*l+3;
    indices[ii++]=2*((3*Unterteilungen/2)-l)-1;
    indices[ii++]=(l==Unterteilungen/2)?1:2*((3*Unterteilungen/2)-l)+1;
  }

  


  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glColorPointer(4, GL_FLOAT, 0, colors);

  glDisable(GL_LIGHTING);

  glBlendFunc(GL_ZERO,GL_ONE_MINUS_SRC_ALPHA);

  glDrawElements(GL_QUADS,4*(3*(Unterteilungen/2)-1), GL_UNSIGNED_INT,indices);

  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_LIGHTING);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);

  free(vertices);
  free(colors);
  free(indices);
}
