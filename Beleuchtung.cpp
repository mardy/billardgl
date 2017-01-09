#include <GL/glut.h>
#include "Beleuchtung.h"

Beleuchtung::Beleuchtung() {
  BeleuchtungIndex=0;
  /* */
}


void Beleuchtung::Initialisiere(GLint AmbientesLicht, GLint Tischlampen, GLint GrueneLampe, GLint Reflektionen) {
  
  if (!BeleuchtungIndex) {
    BeleuchtungIndex=glGenLists(2);      // Display List erzeugen
  }
  glNewList(BeleuchtungIndex,GL_COMPILE_AND_EXECUTE);

  glEnable(GL_LIGHTING);

  if (AmbientesLicht) {
    GLfloat ambient_light []={.15,.15,.15,1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient_light);
  }

  GLfloat Helligkeit=1.0/Tischlampen;

  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHT1);
  glDisable(GL_LIGHT2);
  glDisable(GL_LIGHT3);


  if (Tischlampen>=2) {
    //LampeMitte:  
    GLfloat light_position1 [] = {63.5,0.0,100.0,1.0};
    GLfloat white_light1[] = {Helligkeit,Helligkeit,Helligkeit,1};
    glLightfv(GL_LIGHT1,GL_POSITION, light_position1);
    glLightfv(GL_LIGHT1,GL_DIFFUSE,white_light1);
    glLightfv(GL_LIGHT1,GL_SPECULAR,white_light1);
    glEnable(GL_LIGHT1);
  }

  if (Tischlampen==1 || Tischlampen==3) {
    //LampeRechts:
    GLfloat light_position0 [] = {0.0,0.0,100.0,1.0};  
    GLfloat white_light0[] = {Helligkeit,Helligkeit,Helligkeit,1};
    glLightfv(GL_LIGHT0,GL_POSITION, light_position0);
    glLightfv(GL_LIGHT0,GL_DIFFUSE, white_light0);
    glLightfv(GL_LIGHT0,GL_SPECULAR, white_light0);
    glEnable(GL_LIGHT0);
  }

  if (Tischlampen>=2) {
    //LampeLinks:
    GLfloat light_position2 [] = {-63.5,0.0,100.0,1.0};
    GLfloat white_light2[] = {Helligkeit,Helligkeit,Helligkeit,1};
    glLightfv(GL_LIGHT2,GL_POSITION, light_position2);
    glLightfv(GL_LIGHT2,GL_DIFFUSE, white_light2);
    glLightfv(GL_LIGHT2,GL_SPECULAR, white_light2);
    glEnable(GL_LIGHT2);
  }
  
  if (GrueneLampe) {
    //LampeUnten:
    GLfloat light_position3 [] = {0,0,-1,0};
    GLfloat white_light3[] = {.05,.225,.1,1};
    GLfloat specular[]={0,0,0,1};
    glLightfv(GL_LIGHT3,GL_POSITION, light_position3);
    glLightfv(GL_LIGHT3,GL_DIFFUSE, white_light3);
    glLightfv(GL_LIGHT3,GL_SPECULAR, specular);
    glEnable(GL_LIGHT3);
  }

  glEndList();

  if (Reflektionen) 
    glLightModelf(33272,33274);


}

void Beleuchtung::male() {
  glCallList(BeleuchtungIndex);
}

