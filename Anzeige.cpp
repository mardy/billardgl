/****************************************************************************
**
**  Anzeige.cpp   Stefan Disch, Tobias Nopper, Martina Welte 2001
**
*****************************************************************************/

#include <math.h>
#include <stdlib.h>
#include <stdio.h> //2CHANGE wieder raus wenn kein printf mehr drin
#include <GL/glut.h>

#include "LA.h"                // Zum Handling von .bmp-Files bzw. Matrix-Bildern
#include "bmp.h"

#include "Anzeige.h"

#include "Namen.h"

#include "createTexture.h"   // Funktion zum Generieren einer Textur aus einem 
                               // Matrix-Bild (aus "Ubungen)

int KugelAnzeige[16];

/* --------- Konstruktor ---------- */
Anzeige::Anzeige() {
  StossStaerke=0;

  //for (int i=1;i<16;i++) {
  //  KugelAnzeige[i]=0;
  //}
}


void Anzeige::male() {

  if (StossStaerke>0.0) {

    glPushMatrix();
    glBegin(GL_QUADS);
    glColor4f(1.0,1.0,1.0,0.2-0.2/StossStaerke);
    glVertex2f(14.0,2.0);
    glVertex2f(15.0,2.0);
    glColor4f(1.0,1.0,1.0,.7*StossStaerke/45.0);
    glVertex2f(15.0,2.0+StossStaerke*.2666);
    glVertex2f(14.0,2.0+StossStaerke*.2666);
    glColor4f(1.0,1.0,1.0,0.1-0.1/StossStaerke);
    glVertex2f(15.0,10.0);
    glVertex2f(14.0,10.0);
    glColor4f(1.0,1.0,1.0,.1*StossStaerke/45.0);
    glVertex2f(14.0,2.0+StossStaerke*.2666);
    glVertex2f(15.0,2.0+StossStaerke*.2666);    
    glEnd();
    glPopMatrix();
  }
}

void Anzeige::Initialisiere() {
}

void Anzeige::setzeStossStaerke(GLfloat neuStossStaerke) {
  StossStaerke=neuStossStaerke;
}
