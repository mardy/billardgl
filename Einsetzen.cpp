#include <GL/glut.h>
#include <stdlib.h>
#include "Kugel.h"
#include "Kamera.h"
#include "Einsetzen.h"

void WeisseEinsetzen() {
  if (LageVerbesserungKopffeld) {
    GLfloat x=-63.2,y=0.0;
    GLfloat mabs=100,abs;
    for (int nr=1;nr<16;nr++) {
      abs=(Kugel[nr].Pos_xCM()-x)*(Kugel[nr].Pos_xCM()-x)+
	(Kugel[nr].Pos_yCM()-y)*(Kugel[nr].Pos_yCM()-y);
      if (abs<mabs) {mabs=abs;}
    }
    if (mabs<=32.7) {
      while (mabs<32.7) {
	mabs=100;
	x=(rand()*60.5/RAND_MAX)-124;
	y=(rand()*121.0/RAND_MAX)-60.5;
	for (int nr=1;nr<16;nr++) {
	  abs=(Kugel[nr].Pos_xCM()-x)*(Kugel[nr].Pos_xCM()-x)+
	    (Kugel[nr].Pos_yCM()-y)*(Kugel[nr].Pos_yCM()-y);
	  if (abs<mabs) {mabs=abs;}
	}
      }
    }
    Kugel[0].neuePositionCM(x,y);	 
    KugelnVersenkt[0]=0;
    Kamera.BlickeAuf2(Kugel[0].Pos_xCM(),Kugel[0].Pos_yCM());
  } else {
    GLfloat x=0.0,y=0.0;
    GLfloat mabs=100,abs;
    for (int nr=1;nr<16;nr++) {
      abs=(Kugel[nr].Pos_xCM()-x)*(Kugel[nr].Pos_xCM()-x)+
	(Kugel[nr].Pos_yCM()-y)*(Kugel[nr].Pos_yCM()-y);
      if (abs<mabs) {mabs=abs;}
    }
    if (mabs<=32.7) {
      while (mabs<32.7) {
	mabs=100;
	x=(rand()*248/RAND_MAX)-124;
	y=(rand()*121.0/RAND_MAX)-60.5;
	for (int nr=1;nr<16;nr++) {
	  abs=(Kugel[nr].Pos_xCM()-x)*(Kugel[nr].Pos_xCM()-x)+
	    (Kugel[nr].Pos_yCM()-y)*(Kugel[nr].Pos_yCM()-y);
	  if (abs<mabs) {mabs=abs;}
	}
      }
    }
    Kugel[0].neuePositionCM(x,y);	 
    KugelnVersenkt[0]=0;
    Kamera.BlickeAuf2(Kugel[0].Pos_xCM(),Kugel[0].Pos_yCM());
  }
}

void AchtEinsetzen() {
  Kugel[8].neuePositionCM(3000,3000);	 
  GLfloat x=63.5,y=0.0;
  GLfloat mabs=100,abs;  
  
  for (int nr=1;nr<16;nr++) {
    abs=(Kugel[nr].Pos_xCM()-x)*(Kugel[nr].Pos_xCM()-x)+
      (Kugel[nr].Pos_yCM()-y)*(Kugel[nr].Pos_yCM()-y);
    if (abs<mabs) {mabs=abs;}
  }
  if (mabs<=32.7) {
    while (mabs<32.7) {
      mabs=100;
      x+=.1;
      for (int nr=0;nr<16;nr++) {
	abs=(Kugel[nr].Pos_xCM()-x)*(Kugel[nr].Pos_xCM()-x)+
	  (Kugel[nr].Pos_yCM()-y)*(Kugel[nr].Pos_yCM()-y);
	if (abs<mabs) {mabs=abs;}
      }
    }
  }
  Kugel[8].neuePositionCM(x,y);	 
  KugelnVersenkt[8]=0;
}

void NeunEinsetzen() {
  Kugel[9].neuePositionCM(3000,3000);	 
  GLfloat x=63.5,y=0.0;
  GLfloat mabs=100,abs;  
  
  for (int nr=1;nr<16;nr++) {
    abs=(Kugel[nr].Pos_xCM()-x)*(Kugel[nr].Pos_xCM()-x)+
      (Kugel[nr].Pos_yCM()-y)*(Kugel[nr].Pos_yCM()-y);
    if (abs<mabs) {mabs=abs;}
  }
  if (mabs<=32.7) {
    while (mabs<32.7) {
      mabs=100;
      x+=.1;
      for (int nr=0;nr<16;nr++) {
	abs=(Kugel[nr].Pos_xCM()-x)*(Kugel[nr].Pos_xCM()-x)+
	  (Kugel[nr].Pos_yCM()-y)*(Kugel[nr].Pos_yCM()-y);
	if (abs<mabs) {mabs=abs;}
      }
    }
  }
  Kugel[9].neuePositionCM(x,y);	 
  KugelnVersenkt[9]=0;
}
