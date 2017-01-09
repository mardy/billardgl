/***************************************************************************
**
**  Tisch.cpp   Stefan Disch, Tobias Nopper, Martina Welte 2001
**
*****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

#include "LA.h"
#include "bmp.h"

#include "createTexture.h"  

#include "Tisch.h"

#include "Beleuchtung.h"
#include "Tischfunktionen.h"
#include "viertelLoch.h"

FMatrix woodtex_r,woodtex_g,woodtex_b;     // Matrix-Bilder, in die die Textur kommt


Tisch::Tisch() {
TischFlaechenTextur=0;
HolzBandenTextur=0;

	/* */
}

/* ----------------------
   Tisch initialisieren
   ---------------------- */

void Tisch::Initialisiere(GLint Texturgroesse) {
  if (!LinienIndex) {
    LinienIndex=glGenLists(1);      // Display List erzeugen
  }
  glNewList(LinienIndex,GL_COMPILE_AND_EXECUTE);
  glDisable(GL_LIGHTING);
  glBegin(GL_QUADS);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(-64.2,68.5,-2.8575);
  glVertex3f(-64.2,0.7,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(-63.5,0.0,-2.8575);
  glVertex3f(-63.5,68.5,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(-64.2,0.7,-2.8575);
  glVertex3f(-65.2,0.7,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(-64.5,0.0,-2.8575);
  glVertex3f(-63.5,0.0,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(-65.2,0.7,-2.8575);
  glVertex3f(-65.2,-0.7,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(-64.5,0.0,-2.8575);
  glVertex3f(-64.5,0.0,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(-65.2,-0.7,-2.8575);
  glVertex3f(-64.2,-0.7,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(-63.5,0.0,-2.8575);
  glVertex3f(-64.5,0.0,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(-64.2,-0.7,-2.8575);
  glVertex3f(-64.2,-68.5,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(-63.5,-68.5,-2.8575);
  glVertex3f(-63.5,0.0,-2.8575);

  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(-63.5,68.5,-2.8575);
  glVertex3f(-63.5,0,-2.8575);
  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(-62.8,0,-2.8575);
  glVertex3f(-62.8,68.5,-2.8575);

  glColor4f(1.0,1.0,1.0,0.2);
  glVertex3f(-63.5,0,-2.8575);
  glVertex3f(-63.5,-68.5,-2.8575);
  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(-62.8,-68.5,-2.8575);
  glVertex3f(-62.8,0,-2.8575);

  // Kreuz in der Mitte

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(-.5,0.5,-2.8575);
  glVertex3f(-1.5,0.5,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(-1,0.0,-2.8575);
  glVertex3f(0,0.0,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(-1.5,0.5,-2.8575);
  glVertex3f(-1.5,-0.5,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(-1,0.0,-2.8575);
  glVertex3f(-1,0.0,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(-1.5,-0.5,-2.8575);
  glVertex3f(-.5,-0.5,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(0,0.0,-2.8575);
  glVertex3f(-1,0.0,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(-.5,-0.5,-2.8575);
  glVertex3f(-.5,-1.5,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(0,-1,-2.8575);
  glVertex3f(0,0.0,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(-.5,-1.5,-2.8575);
  glVertex3f(.5,-1.5,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(0,-1,-2.8575);
  glVertex3f(0,-1,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(.5,-1.5,-2.8575);
  glVertex3f(.5,-0.5,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(0,0.0,-2.8575);
  glVertex3f(0,-1,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(.5,-0.5,-2.8575);
  glVertex3f(1.5,-0.5,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(1,0.0,-2.8575);
  glVertex3f(0,0.0,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(1.5,-0.5,-2.8575);
  glVertex3f(1.5,0.5,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(1,0.0,-2.8575);
  glVertex3f(1,0.0,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(1.5,0.5,-2.8575);
  glVertex3f(.5,0.5,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(0,0.0,-2.8575);
  glVertex3f(1,0.0,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(.5,0.5,-2.8575);
  glVertex3f(.5,1.5,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(0,1,-2.8575);
  glVertex3f(0,0.0,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(.5,1.5,-2.8575);
  glVertex3f(-.5,1.5,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(0,1,-2.8575);
  glVertex3f(0,1,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(-.5,1.5,-2.8575);
  glVertex3f(-.5,0.5,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(0,0.0,-2.8575);
  glVertex3f(0,1,-2.8575);
  
  //Dreieck
  glEnd();

  glPushMatrix();
  glTranslatef(63.5,0.0,0.0);
  glScalef(1.35,1.35,1);

  glBegin(GL_QUADS);
  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(-2.91,1.68,-2.8575);
  glVertex3f(-3.36,0,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(-2.86,0,-2.8575);
  glVertex3f(-2.47,1.43,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(-1.68,2.91,-2.8575);
  glVertex3f(-2.91,1.68,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(-2.47,1.43,-2.8575);
  glVertex3f(-1.43,2.47,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(13.17,11.48,-2.8575);
  glVertex3f(-1.68,2.91,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(-1.43,2.47,-2.8575);
  glVertex3f(13.42,11.05,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(14.85,11.93,-2.8575);
  glVertex3f(13.17,11.48,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(13.42,11.05,-2.8575);
  glVertex3f(14.85,11.43,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(16.53,11.48,-2.8575);
  glVertex3f(14.85,11.93,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(14.85,11.43,-2.8575);
  glVertex3f(16.28,11.05,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(17.76,10.25,-2.8575);
  glVertex3f(16.53,11.48,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(16.28,11.05,-2.8575);
  glVertex3f(17.32,10.00,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(18.21,8.57,-2.8575);
  glVertex3f(17.76,10.25,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(17.32,10.00,-2.8575);
  glVertex3f(17.71,8.57,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(18.21,0.5,-2.8575);
  glVertex3f(18.21,8.57,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(17.71,8.57,-2.8575);
  glVertex3f(17.71,0.0,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(53,0.5,-2.8575);
  glVertex3f(18.21,0.5,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(17.71,0.0,-2.8575);
  glVertex3f(53,0.0,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(18.21,-0.5,-2.8575);
  glVertex3f(53,-0.5,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(53,0.0,-2.8575);
  glVertex3f(17.71,0.0,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(18.21,-8.57,-2.8575);
  glVertex3f(18.21,-0.5,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(17.71,0.0,-2.8575);
  glVertex3f(17.71,-8.57,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(17.76,-10.25,-2.8575);
  glVertex3f(18.21,-8.57,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(17.71,-8.57,-2.8575);
  glVertex3f(17.32,-10.0,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(16.53,-11.48,-2.8575);
  glVertex3f(17.76,-10.25,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(17.32,-10.0,-2.8575);
  glVertex3f(16.28,-11.05,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(14.85,-11.93,-2.8575);
  glVertex3f(16.53,-11.48,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(16.28,-11.05,-2.8575);
  glVertex3f(14.85,-11.43,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(13.17,-11.48,-2.8575);
  glVertex3f(14.85,-11.93,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(14.85,-11.43,-2.8575);
  glVertex3f(13.42,-11.05,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(-1.68,-2.91,-2.8575);
  glVertex3f(13.17,-11.48,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(13.42,-11.05,-2.8575);
  glVertex3f(-1.43,-2.47,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(-2.91,-1.68,-2.8575);
  glVertex3f(-1.68,-2.91,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(-1.43,-2.47,-2.8575);
  glVertex3f(-2.47,-1.43,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(-3.36,0.0,-2.8575);
  glVertex3f(-2.91,-1.68,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(-2.47,-1.43,-2.8575);
  glVertex3f(-2.86,0.0,-2.8575);

  //innen
  
  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(-2.36,0.0,-2.8575);
  glVertex3f(-2.04,1.18,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(-2.47,1.43,-2.8575);
  glVertex3f(-2.86,0.0,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(-2.04,1.18,-2.8575);
  glVertex3f(-1.18,2.04,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(-1.43,2.47,-2.8575);
  glVertex3f(-2.47,1.43,-2.8575);
 
  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(-1.18,2.04,-2.8575);
  glVertex3f(13.67,10.61,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(13.42,11.05,-2.8575);
  glVertex3f(-1.43,2.47,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(13.67,10.61,-2.8575);
  glVertex3f(14.85,10.93,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(14.85,11.43,-2.8575);
  glVertex3f(13.42,11.05,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(14.85,10.93,-2.8575);
  glVertex3f(16.03,10.61,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(16.28,11.05,-2.8575);
  glVertex3f(14.85,11.43,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(16.03,10.61,-2.8575);
  glVertex3f(16.89,9.75,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(17.32,10.0,-2.8575);
  glVertex3f(16.28,11.05,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(16.89,9.75,-2.8575);
  glVertex3f(17.21,8.57,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(17.71,8.57,-2.8575);
  glVertex3f(17.32,10.0,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(17.21,8.57,-2.8575);
  glVertex3f(17.21,0.5,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(17.71,0.0,-2.8575);
  glVertex3f(17.71,8.57,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(17.21,0.5,-2.8575);
  glVertex3f(0.5,0.5,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(0.0,0.0,-2.8575);
  glVertex3f(17.71,0.0,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(0.5,0.5,-2.8575);
  glVertex3f(0.5,1.5,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(0.0,1.0,-2.8575);
  glVertex3f(0.0,0.0,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(0.5,1.5,-2.8575);
  glVertex3f(-0.5,1.5,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(0.0,1.0,-2.8575);
  glVertex3f(0.0,1.0,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(-0.5,1.5,-2.8575);
  glVertex3f(-0.5,-1.5,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(0.0,-1.0,-2.8575);
  glVertex3f(0.0,1.0,-2.8575);
  
  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(-0.5,-1.5,-2.8575);
  glVertex3f(0.5,-1.5,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(0.0,-1.0,-2.8575);
  glVertex3f(0.0,-1.0,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(0.5,-1.5,-2.8575);
  glVertex3f(0.5,-0.5,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(0.0,0.0,-2.8575);
  glVertex3f(0.0,-1.0,-2.8575);
  
  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(0.5,-0.5,-2.8575);
  glVertex3f(17.21,-0.5,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(17.71,0.0,-2.8575);
  glVertex3f(0.0,0.0,-2.8575);

  ////
  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(-2.04,-1.18,-2.8575);
  glVertex3f(-2.36,0.0,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(-2.86,0.0,-2.8575);
  glVertex3f(-2.47,-1.43,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(-1.18,-2.04,-2.8575);
  glVertex3f(-2.04,-1.18,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(-2.47,-1.43,-2.8575);
  glVertex3f(-1.43,-2.47,-2.8575);
 
  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(13.67,-10.61,-2.8575);
  glVertex3f(-1.18,-2.04,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(-1.43,-2.47,-2.8575);
  glVertex3f(13.42,-11.05,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(14.85,-10.93,-2.8575);
  glVertex3f(13.67,-10.61,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(13.42,-11.05,-2.8575);
  glVertex3f(14.85,-11.43,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(16.03,-10.61,-2.8575);
  glVertex3f(14.85,-10.93,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(14.85,-11.43,-2.8575);
  glVertex3f(16.28,-11.05,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(16.89,-9.75,-2.8575);
  glVertex3f(16.03,-10.61,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(16.28,-11.05,-2.8575);
  glVertex3f(17.32,-10.0,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(17.21,-8.57,-2.8575);
  glVertex3f(16.89,-9.75,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(17.32,-10.0,-2.8575);
  glVertex3f(17.71,-8.57,-2.8575);

  glColor4f(1.0,1.0,1.0,0);
  glVertex3f(17.21,-0.5,-2.8575);
  glVertex3f(17.21,-8.57,-2.8575);
  glColor4f(1.0,1.0,1.0,.2);
  glVertex3f(17.71,-8.57,-2.8575);
  glVertex3f(17.71,-0.0,-2.8575);

  glEnd();
  glPopMatrix();

  glBegin(GL_QUADS);

  //Schattenränder unter den Banden...
  /*
  glColor4f(0.0,0.0,0.0,0.0);
  glVertex3f(7.38,63.5,-2.8575);
  glVertex3f(117.16,63.5,-2.8575);
  glColor4f(0.0,0.0,0.0,.4);
  glVertex3f(128.3,68.5,-2.8575);
  glVertex3f(6.5,68.5,-2.8575);
  */
  glColor4f(0.0,0.0,0.0,0.0);
  glVertex3f(-139,65,-2.8575);
  glVertex3f(139,65,-2.8575);
  glColor4f(0.0,0.0,0.0,.6);
  glVertex3f(139,68.5,-2.8575);
  glVertex3f(-139,68.5,-2.8575);

  glColor4f(0.0,0.0,0.0,0.0);
  glVertex3f(139,-65,-2.8575);
  glVertex3f(-139,-65,-2.8575);
  glColor4f(0.0,0.0,0.0,.6);
  glVertex3f(-139,-68.5,-2.8575);
  glVertex3f(139,-68.5,-2.8575);

  glColor4f(0.0,0.0,0.0,0.0);
  glVertex3f(128.5,65,-2.8575);
  glVertex3f(128.5,-65,-2.8575);
  glColor4f(0.0,0.0,0.0,.6);
  glVertex3f(132,-65,-2.8575);
  glVertex3f(132,65,-2.8575);

  glColor4f(0.0,0.0,0.0,0.0);
  glVertex3f(-128.5,-65,-2.8575);
  glVertex3f(-128.5,65,-2.8575);
  glColor4f(0.0,0.0,0.0,.6);
  glVertex3f(-132,65,-2.8575);
  glVertex3f(-132,-65,-2.8575);

  glEnd();


  glEnable(GL_LIGHTING);
  glEndList();

  if (!TischFlaechenTextur) 
	glGenTextures(1,&TischFlaechenTextur);
  
  if (Texturgroesse && Texturgroesse<8) {
    GLint T=Texturgroesse;
    if (T==4) T=2;
    char Name[40];
    sprintf(Name,"Texturen/%i/filzkachel.bmp",T); 
    loadBMP(woodtex_r,woodtex_g,woodtex_b,Name);
    glBindTexture(GL_TEXTURE_2D,TischFlaechenTextur);
    createTextureMipmap(woodtex_r,woodtex_g,woodtex_b);
  }
  
  
  if (!TischFlaecheIndex) {
    TischFlaecheIndex=glGenLists(1);      // Display List erzeugen
  }
  glNewList(TischFlaecheIndex,GL_COMPILE_AND_EXECUTE);
  glPushMatrix();
  
  glTranslatef(0,0,-2.8575);     // Tisch um Kugelradius nach unten schieben
 
  //Licht an:
  //Beleuchtung(0,0,1,0,0,Reflektionen);

  //GLfloat mat_ambient[]={0.1,0.45,0.2,1.0};
  //GLfloat mat_diffuse[]={0.1,0.45,0.2,1.0};
  //GLfloat mat_specular[]={0,0,0,1.0};
  //GLfloat mat_shininess = 0.0;
  //glMaterialfv(GL_FRONT, GL_AMBIENT,mat_ambient);
  //glMaterialfv(GL_FRONT, GL_DIFFUSE,mat_diffuse);
  //glMaterialfv(GL_FRONT, GL_SPECULAR,mat_specular);
  //glMaterialf(GL_FRONT, GL_SHININESS,mat_shininess);


  // Maße der Spielfläche (in cm):
  // 254 x 127
  GLint xteile=16;     // Anzahl muss gerade sein
  GLint yteile=8;     // Anzahl muss gerade sein; 
  GLfloat widthx=264.0/xteile;
  GLfloat widthy=137.0/yteile;

/* -------------------------
   Flaeche berechnen  
   ------------------------- */  

  if (Texturgroesse && Texturgroesse<8) {

    GLfloat mat_ambient[]={1.0,1.0,1.0,1.0};
    GLfloat mat_diffuse[]={1.0,1.0,1.0,1.0};
    GLfloat mat_specular[]={0,0,0,1.0};
    GLfloat mat_shininess = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT,mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS,mat_shininess);
    glBindTexture(GL_TEXTURE_2D,TischFlaechenTextur);
    glEnable(GL_TEXTURE_2D);
    TischflaechemitTextur();
    /* -------------
       Löcher machen
       ------------- */
    
    // unten links
    glPushMatrix();
    glTranslatef(-133.29,-69.79,0);
    viertelLoch(widthx+1.3,widthy+1.3,4,4,.63,10,9.84,9.21,-133.29,-69.79,1,0,0,1); 
    glPopMatrix();
    
    // unten Mitte 
    glPushMatrix();
    glTranslatef(0,-71.75,0);
    viertelLoch(widthx+0.01,widthy+3.26,4,4,.63,10,7.62,6.99,0,-71.75,1,0,0,1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0,-71.75,0);
    glRotatef(90,0,0,1);
    viertelLoch(widthy+3.26,widthx+0.01,4,4,.63,10.2,7.62,6.99,0,-71.75,0,-1,1,0);
    glPopMatrix();
    
    //unten rechts   
    glPushMatrix();
    glTranslatef(133.29,-69.79,0); 
    glRotatef(90,0,0,1);
    viertelLoch(widthy+1.3,widthx+1.3,4,4,.63,10,9.84,9.21,133.29,-69.79,0,-1,-1,0); 
    glPopMatrix();
    
    //oben rechts
    glPushMatrix();
    glTranslatef(133.29,69.79,0);
    glRotatef(180,0,0,1);
    viertelLoch(widthx+1.3,widthy+1.3,4,4,.63,10,9.84,9.21,133.29,69.79,-1,0,0,-1); 
    glPopMatrix();
    
    //oben Mitte
    glPushMatrix();
    glTranslatef(0,71.75,0);
    glRotatef(180,0,0,1);
    viertelLoch(widthx+0.1,widthy+3.26,4,4,.63,10,7.62,6.99,0,71.75,-1,0,0,-1); 
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0,71.75,0);
    glRotatef(-90,0,0,1);
    viertelLoch(widthy+3.26,widthx+0.1,4,4,.63,10,7.62,6.99,0,71.75,0,1,-1,0);
    glPopMatrix();
    
    //oben links
    glPushMatrix();
    glTranslatef(-133.29,69.79,0); 
    glRotatef(-90,0,0,1);
    viertelLoch(widthy+1.3,widthx+1.3,4,4,.63,10,9.84,9.21,-133.29,69.79,0,1,-1,0); 
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    
  } else {
    
    GLfloat mat_ambient[]={0.1,0.45,0.2,1.0};
    GLfloat mat_diffuse[]={0.1,0.45,0.2,1.0};
    GLfloat mat_specular[]={0,0,0,1.0};
    GLfloat mat_shininess = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT,mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS,mat_shininess);
    

    Tischflaeche();
    
    /* -------------
       Löcher machen
       ------------- */
    
    // unten links
    glPushMatrix();
    glTranslatef(-133.29,-69.79,0);
    viertelLoch(widthx+1.3,widthy+1.3,4,4,.63,10,9.84,9.21); 
    glPopMatrix();
    
    // unten Mitte 
    glPushMatrix();
    glTranslatef(0,-71.75,0);
    viertelLoch(widthx+0.01,widthy+3.26,4,4,.63,10,7.62,6.99);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0,-71.75,0);
    glRotatef(90,0,0,1);
    viertelLoch(widthy+3.26,widthx+0.01,4,4,.63,10.2,7.62,6.99);
    glPopMatrix();
    
    //unten rechts   
    glPushMatrix();
    glTranslatef(133.29,-69.79,0); 
    glRotatef(90,0,0,1);
    viertelLoch(widthy+1.3,widthx+1.3,4,4,.63,10,9.84,9.21); 
    glPopMatrix();
    
    //oben rechts
    glPushMatrix();
    glTranslatef(133.29,69.79,0);
    glRotatef(180,0,0,1);
    viertelLoch(widthx+1.3,widthy+1.3,4,4,.63,10,9.84,9.21); 
    glPopMatrix();
    
    //oben Mitte
    glPushMatrix();
    glTranslatef(0,71.75,0);
    glRotatef(180,0,0,1);
    viertelLoch(widthx+0.1,widthy+3.26,4,4,.63,10,7.62,6.99); 
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0,71.75,0);
    glRotatef(-90,0,0,1);
    viertelLoch(widthy+3.26,widthx+0.1,4,4,.63,10,7.62,6.99);
    glPopMatrix();
    
    //oben links
    glPushMatrix();
    glTranslatef(-133.29,69.79,0); 
    glRotatef(-90,0,0,1);
    viertelLoch(widthy+1.3,widthx+1.3,4,4,.63,10,9.84,9.21); 
    glPopMatrix();

  }

  glPopMatrix();
  glEndList();




/* --------------------
   Banden berechnen 
   -------------------- */

  if (!HolzBandenTextur) 
	glGenTextures(1,&HolzBandenTextur);

  if (Texturgroesse) {
    char Name[40];
    sprintf(Name,"Texturen/%i/holz.bmp",Texturgroesse); 
      
    loadBMP(woodtex_r,woodtex_g,woodtex_b,Name);
    glBindTexture(GL_TEXTURE_2D,HolzBandenTextur);
    //createTextureMipmap(woodtex_r,woodtex_g,woodtex_b);
    createTexture(woodtex_r,woodtex_g,woodtex_b);
  }

  if (!BandenIndex) {
    BandenIndex=glGenLists(1);      // Display List erzeugen
  }
  glNewList(BandenIndex,GL_COMPILE_AND_EXECUTE);
  {
    GLfloat mat_ambient[]={0.1,0.45,0.2,1.0};
    GLfloat mat_diffuse[]={0.1,0.45,0.2,1.0};
    GLfloat mat_specular[]={0,0,0,1.0};
    GLfloat mat_shininess = 127.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT,mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS,mat_shininess);

    glPushMatrix();
    
    glTranslatef(0,0,-2.8575);     // Tisch um Kugelradius nach unten schieben
    
    // Bande links 
    glPushMatrix();
    Banden(0,1);
    glPopMatrix();
    
    // Bande rechts 
    glPushMatrix();
    glRotatef(180,0,0,1);
    Banden(0,1);
    glPopMatrix();
    
    // Bande oben links
    glPushMatrix();
    Banden(1,1);
    glPopMatrix();    
    
    // Bande oben rechts
    glPushMatrix();
    Banden(1,-1);
    glPopMatrix();
    
    // Bande unten links
    glPushMatrix();
    glRotatef(180,0,0,1);
    Banden(1,-1);
    glPopMatrix();
    
    // Bande unten rechts
    glPushMatrix();
    glRotatef(180,0,0,1);
    Banden(1,1);
    glPopMatrix();
    
    //Verkleidungen (;)
    glPushMatrix();
    MittelLochVerkleidung();
    MittelLochInnenverkleidung();
    MittelLochRand();
    glRotatef(180,0,0,1);
    MittelLochVerkleidung();
    MittelLochInnenverkleidung();
    MittelLochRand();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(132,68.5,0);
    EckLochVerkleidung();
    EckLochInnenverkleidung();
    EckLochRand();
    glPopMatrix();
    
    glPushMatrix();
    glRotatef(180,0,0,1);
    glTranslatef(132,68.5,0);
    EckLochVerkleidung();
    EckLochInnenverkleidung();
    EckLochRand();
    glPopMatrix();
    
    glPushMatrix();
    glRotatef(90,0,0,1);
    glTranslatef(68.5,132,0);
    EckLochVerkleidung();
    EckLochInnenverkleidung();
    EckLochRand();
    glPopMatrix();
    
    glPushMatrix();
    glRotatef(-90,0,0,1);
    glTranslatef(68.5,132,0);
    EckLochVerkleidung();
    EckLochInnenverkleidung();
    EckLochRand();
    glPopMatrix();
    
    {
      GLfloat mat_diffuse[]={0.8,0.8,1.0,1.0};
      GLfloat mat_specular[]={1.0,0.8,0.8,1.0};
      GLfloat mat_shininess = 127.0;
      
      glMaterialfv(GL_FRONT, GL_AMBIENT,mat_diffuse);
      glMaterialfv(GL_FRONT, GL_DIFFUSE,mat_diffuse);
      glMaterialfv(GL_FRONT, GL_SPECULAR,mat_specular);
      glMaterialf(GL_FRONT, GL_SHININESS,mat_shininess);
    }

    Diamant(31.75,72.5,4.9);
    Diamant(63.5,72.5,4.9);
    Diamant(95.25,72.5,4.9);
    Diamant(-31.75,72.5,4.9);
    Diamant(-63.5,72.5,4.9);
    Diamant(-95.25,72.5,4.9);
    Diamant(31.75,-72.5,4.9);
    Diamant(63.5,-72.5,4.9);
    Diamant(95.25,-72.5,4.9);
    Diamant(-31.75,-72.5,4.9);
    Diamant(-63.5,-72.5,4.9);
    Diamant(-95.25,-72.5,4.9);

    Diamant(136.5,31.75,4.9);
    Diamant(136.5,0,4.9);
    Diamant(136.5,-31.75,4.9);
    Diamant(-136.5,31.75,4.9);
    Diamant(-136.5,0,4.9);
    Diamant(-136.5,-31.75,4.9);

    
    //Holzbanden
    if (Texturgroesse) {
      //char Name[40];
      //sprintf(Name,"Texturen/%i/holz.bmp",Texturgroesse); 
      
      //loadBMP(woodtex_r,woodtex_g,woodtex_b,Name);
      //createWoodTexture(woodtex_r,woodtex_g,woodtex_b,Nearest);
      glBindTexture(GL_TEXTURE_2D,HolzBandenTextur);
      glEnable(GL_TEXTURE_2D);
      glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
      
      glPushMatrix();
      glTranslatef(7.5,68.5,0);
      Holzbande(115.5,8,1,1);
      glPopMatrix();
      
      glPushMatrix();
      glRotatef(180,0,0,1);
      glTranslatef(7.5,68.5,0);
      Holzbande(115.5,8,1,1);
      glPopMatrix();
      
      glPushMatrix();
      glTranslatef(-123,68.5,0);
      Holzbande(115.5,8,1,1);
      glPopMatrix();
      
      glPushMatrix();
      glRotatef(180,0,0,1);
      glTranslatef(-123,68.5,0);
      Holzbande(115.5,8,1,1);
      glPopMatrix();
      
      glPushMatrix();
      glTranslatef(-132,-59.5,0);
      glRotatef(90,0,0,1);
      Holzbande(119,8,1,1);
      glPopMatrix();
      
      glPushMatrix();
      glTranslatef(132,59.5,0);
      glRotatef(-90,0,0,1);
      Holzbande(119,8,1,1);
      glPopMatrix();
      
      glDisable(GL_TEXTURE_2D);
      
    } else {
      glPushMatrix();
      glTranslatef(7.5,68.5,0);
      HolzbandeOT(115.5,8);
      glPopMatrix();
      
      glPushMatrix();
      glRotatef(180,0,0,1);
      glTranslatef(7.5,68.5,0);
      HolzbandeOT(115.5,8);
      glPopMatrix();
      
      glPushMatrix();
      glTranslatef(-123,68.5,0);
      HolzbandeOT(115.5,8);
      glPopMatrix();
      
      glPushMatrix();
      glRotatef(180,0,0,1);
      glTranslatef(-123,68.5,0);
      HolzbandeOT(115.5,8);
      glPopMatrix();
      
      glPushMatrix();
      glTranslatef(-132,-59.5,0);
      glRotatef(90,0,0,1);
      HolzbandeOT(119,8);
      glPopMatrix();
      
      glPushMatrix();
      glTranslatef(132,59.5,0);
      glRotatef(-90,0,0,1);
      HolzbandeOT(119,8);
      glPopMatrix();
      
      GLfloat mat_diffuse[]={1.0,1.0,1.0,1.0};
      GLfloat mat_specular[]={1.0,1.0,1.0,1.0};
      GLfloat mat_shininess = 0.0;

      glMaterialfv(GL_FRONT, GL_AMBIENT,mat_diffuse);
      glMaterialfv(GL_FRONT, GL_DIFFUSE,mat_diffuse);
      glMaterialfv(GL_FRONT, GL_SPECULAR,mat_specular);
      glMaterialf(GL_FRONT, GL_SHININESS,mat_shininess);

    }
    
    glPopMatrix();
  
  }

  glEndList();
  
  if (Texturgroesse) {
    woodtex_r.free_FMatrix();
    woodtex_g.free_FMatrix();
    woodtex_b.free_FMatrix();
  }
  
}


/* -----------------
   Tisch malen
   ----------------- */

void Tisch::maleFlaeche() { 
  glCallList(TischFlaecheIndex);       // Tischflaeche zeichnen
}

void Tisch::maleBanden() { 
  glCallList(BandenIndex);       // Banden zeichnen
}

void Tisch::maleLinien() {
  glCallList(LinienIndex);
}
