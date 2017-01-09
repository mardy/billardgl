#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Textfeld.h"
#include "Schild.h"
#include "Tisch.h"
#include "Kamera.h"
#include "Kugel.h"
#include "Anzeige.h"
#include "Menu.h"
#include "Beleuchtung.h"
#include "Schiedsrichter.h"

#include "LA.h"
#include "bmp.h"

#include "createTexture.h"  

#include "SpielfeldAufbau.h"
#include "kugeltabellen.h"
#include "BillardGL.h"
#include "Benutzerschnittstelle.h"

#include "LadeScreen.h"



void LSupdateGL() {

  glEnable(GL_BLEND);
  glDisable(GL_LIGHTING);
  //glDisable(GL_DEPTH_TEST);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-4,4,-3,3);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glClear(GL_COLOR_BUFFER_BIT);

  glBindTexture(GL_TEXTURE_2D,dreizehntextur);
  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);
  glColor4f(1.0,1.0,1.0,1);
  glTexCoord2f(0,0);
  glVertex2f(-1,-1-.5);
  glTexCoord2f(1,0);
  glVertex2f( 1,-1-.5);
  glTexCoord2f(1,1);
  glVertex2f( 1, 1-.5);
  glTexCoord2f(0,1);
  glVertex2f(-1, 1-.5);
  glEnd();
  glDisable(GL_TEXTURE_2D);

  GLfloat Winkel=(1-(LadeFortschritt/29.0))*6.2832;

  glColor4f(0.0,0.0,0.0,0.2);
  glBegin(GL_TRIANGLE_FAN);
  glVertex2f( 0.0, 0.0-.5);
  glVertex2f(-2*sin(1.00*Winkel),2*cos(1.00*Winkel)-.5);
  glVertex2f(-2*sin(0.75*Winkel),2*cos(0.75*Winkel)-.5);
  glVertex2f(-2*sin(0.50*Winkel),2*cos(0.50*Winkel)-.5);
  glVertex2f(-2*sin(0.25*Winkel),2*cos(0.25*Winkel)-.5);
  glVertex2f( 0.0, 2.0-.5);
  glEnd();

  glBindTexture(GL_TEXTURE_2D,logotextur);
  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);
  glColor4f(1.0,1.0,1.0,.7);
  glTexCoord2f(0,0);
  glVertex2f(-2,0);
  glTexCoord2f(1,0);
  glVertex2f( 2,0);
  glTexCoord2f(1,1);
  glVertex2f( 2,1);
  glTexCoord2f(0,1);
  glVertex2f(-2,1);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glutSwapBuffers();

}

void LSidle() {

  switch (LadeFortschritt++) {
  case 0: {
    glEnable(GL_BLEND);
    glDisable(GL_LIGHTING);
    glClear(GL_COLOR_BUFFER_BIT);
    FMatrix r,g,b;
    loadBMP(r,g,b,"Texturen/1/dreizehn.bmp");
    glGenTextures(1,&dreizehntextur);
    glBindTexture(GL_TEXTURE_2D,dreizehntextur);
    createTexture(r,g,b);
    r.free_FMatrix();
    g.free_FMatrix();
    b.free_FMatrix();
    loadBMP(r,g,b,"Texturen/1/logo.bmp");
    glGenTextures(1,&logotextur);
    glBindTexture(GL_TEXTURE_2D,logotextur);
    createTextureAlpha(r,g,b);
    r.free_FMatrix();
    g.free_FMatrix();
    b.free_FMatrix();
  }break;
  case 1: initialisiereKugelTabellen(KugelAufloesung); break;
  case 2: Kugel[0].Initialisiere(0,Texturgroesse,KugelAufloesung,Schatten); break;
  case 3: Kugel[1].Initialisiere(1,Texturgroesse,KugelAufloesung,Schatten); break;
  case 4: Kugel[2].Initialisiere(2,Texturgroesse,KugelAufloesung,Schatten); break;
  case 5: Kugel[3].Initialisiere(3,Texturgroesse,KugelAufloesung,Schatten); break;
  case 6: Kugel[4].Initialisiere(4,Texturgroesse,KugelAufloesung,Schatten); break;
  case 7: Kugel[5].Initialisiere(5,Texturgroesse,KugelAufloesung,Schatten); break;
  case 8: Kugel[6].Initialisiere(6,Texturgroesse,KugelAufloesung,Schatten); break;
  case 9: Kugel[7].Initialisiere(7,Texturgroesse,KugelAufloesung,Schatten); break;
  case 10: Kugel[8].Initialisiere(8,Texturgroesse,KugelAufloesung,Schatten); break;
  case 11: Kugel[9].Initialisiere(9,Texturgroesse,KugelAufloesung,Schatten); break;
  case 12: Kugel[10].Initialisiere(10,Texturgroesse,KugelAufloesung,Schatten); break;
  case 13: Kugel[11].Initialisiere(11,Texturgroesse,KugelAufloesung,Schatten); break;
  case 14: Kugel[12].Initialisiere(12,Texturgroesse,KugelAufloesung,Schatten); break;
  case 15: Kugel[13].Initialisiere(13,Texturgroesse,KugelAufloesung,Schatten); break;
  case 16: Kugel[14].Initialisiere(14,Texturgroesse,KugelAufloesung,Schatten); break;
  case 17: Kugel[15].Initialisiere(15,Texturgroesse,KugelAufloesung,Schatten); break;
  case 18: Tisch.Initialisiere(TischTexturgroesse); break;
  case 19: Beleuchtung.Initialisiere(AmbientesLicht,TischLampen,GrueneLampe,Reflektionen); break;
  case 20: Anzeige.Initialisiere(); break;
  case 21: Menu.Initialisiere(AnzeigeTexturgroesse); break;
  case 22: Menu.ladeSprache(900); break;
  case 23: Menu.ladeSprache(901); break;
  case 24: Menu.ladeSprache(999); break;
  case 25: Menu.Initialisiere(AnzeigeTexturgroesse); break;
  case 26: SpielfeldAufbau(); break;
  case 27: Schiedsrichter.NeuesSpiel(Spiel); break;
  case 28: {
    
    glDeleteTextures(1,&dreizehntextur);

    DelayAusgleich=1;

    glutIgnoreKeyRepeat(1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_NORMALIZE);
    glEnable(GL_BLEND);
    glShadeModel(GL_SMOOTH);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    
    //Callbacks setzen: Reaktion auf Mausklicks und -bewegungen, Tastaturaktivitäten
    glutMouseFunc(Maus);
    glutMotionFunc(Bewegung);
    glutKeyboardFunc(Taste);
    glutKeyboardUpFunc(TasteLos);
    glutSpecialFunc(Sondertaste);
    glutSpecialUpFunc(SondertasteLos);
  
    glutVisibilityFunc(Sichtbar);        
    glutIdleFunc(timerEvent);
    glutDisplayFunc(updateGL);
  } break;
  }
  glutPostWindowRedisplay(AktuellesFenster);
}
