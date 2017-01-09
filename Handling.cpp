#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "Textfeld.h"
#include "Kamera.h"
#include "Kugel.h"
#include "Anzeige.h"
#include "Namen.h"
#include "Schild.h"
#include "Menu.h"
#include "Schiedsrichter.h"

#include "Einsetzen.h"
#include "Handling.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


void StartHandling() {
  Kamera.Rundflug(Faktor);
  //Menu.Update(Faktor);
}

void BetrachtenHandling() {
  //Menu.Update(Faktor);
  if (Taste_Pfeil_Oben)  {Kamera.Beweg_Vor(Faktor);}   
  if (Taste_Pfeil_Unten) {Kamera.Beweg_Zurueck(Faktor);}
  if (Taste_Pfeil_Rechts){Kamera.Beweg_Rechts(Faktor);}
  if (Taste_Pfeil_Links) {Kamera.Beweg_Links(Faktor);}
  if (Taste_Shift)       {Kamera.Beweg_Hoch(Faktor);}
  if (Taste_Strg)        {Kamera.Beweg_Runter(Faktor);}
  if (Taste_Bild_Auf)    {Kamera.Beweg_Rein(Faktor);}
  if (Taste_Bild_Ab)     {Kamera.Beweg_Raus(Faktor);}
  if (Taste_Pos1)        {Kamera.Zoom_Rein(Faktor);}
  if (Taste_Ende)        {Kamera.Zoom_Raus(Faktor);}
}

void ZielenHandling() {
  if (Taste_Pfeil_Oben)  {Kamera.Beweg_Rein(Faktor);}   
  if (Taste_Pfeil_Unten) {Kamera.Beweg_Raus(Faktor);}
  if (Taste_Pfeil_Rechts){Kamera.Schwenk_Rechts(2*Faktor,Kugel[0].Pos_xCM(),Kugel[0].Pos_yCM());}
  if (Taste_Pfeil_Links) {Kamera.Schwenk_Links(2*Faktor,Kugel[0].Pos_xCM(),Kugel[0].Pos_yCM());}
  if (Taste_Shift)       {Kamera.Schwenk_Runter(Faktor,Kugel[0].Pos_xCM(),Kugel[0].Pos_yCM());}
  if (Taste_Strg)        {Kamera.Schwenk_Hoch(Faktor,Kugel[0].Pos_xCM(),Kugel[0].Pos_yCM());}
  if (Taste_Bild_Auf)    {Kamera.Beweg_Rein(Faktor);}
  if (Taste_Bild_Ab)     {Kamera.Beweg_Raus(Faktor);}
  if (Taste_Pos1)        {Kamera.Vertigo_Rein(Faktor);}
  if (Taste_Ende)        {Kamera.Vertigo_Raus(Faktor);}
}

void AusholenHandling() {
  if (Taste_Pfeil_Oben)  {Kamera.Beweg_Rein(Faktor);}   
  if (Taste_Pfeil_Unten) {Kamera.Beweg_Raus(Faktor);}
  if (Taste_Pfeil_Rechts){Kamera.Schwenk_Rechts(2*Faktor,Kugel[0].Pos_xCM(),Kugel[0].Pos_yCM());}
  if (Taste_Pfeil_Links) {Kamera.Schwenk_Links(2*Faktor,Kugel[0].Pos_xCM(),Kugel[0].Pos_yCM());}
  if (Taste_Shift)       {Kamera.Schwenk_Runter(Faktor,Kugel[0].Pos_xCM(),Kugel[0].Pos_yCM());}
  if (Taste_Strg)        {Kamera.Schwenk_Hoch(Faktor,Kugel[0].Pos_xCM(),Kugel[0].Pos_yCM());}
  if (Taste_Bild_Auf)    {Kamera.Beweg_Rein(Faktor);}
  if (Taste_Bild_Ab)     {Kamera.Beweg_Raus(Faktor);}
  if (Taste_Pos1)        {Kamera.Zoom_Rein(Faktor);}
  if (Taste_Ende)        {Kamera.Zoom_Raus(Faktor);}

  AusholStaerke=MaxAusholStaerke*(1-exp((-FrameZeitpunkt+AusholStartzeit)/400.0));
  Anzeige.setzeStossStaerke(AusholStaerke/3.333);

}

void StossHandling() {
  
  AllerersterStoss=0;
  //WeisseVersetzbar=0;

  if (Taste_Pfeil_Oben)  {Kamera.Beweg_Vor(Faktor);}   
  if (Taste_Pfeil_Unten) {Kamera.Beweg_Zurueck(Faktor);}
  if (Taste_Pfeil_Rechts){Kamera.Beweg_Rechts(Faktor);}
  if (Taste_Pfeil_Links) {Kamera.Beweg_Links(Faktor);}
  if (Taste_Shift)       {Kamera.Beweg_Hoch(Faktor);}
  if (Taste_Strg)        {Kamera.Beweg_Runter(Faktor);}
  if (Taste_Bild_Auf)    {Kamera.Beweg_Rein(Faktor);}
  if (Taste_Bild_Ab)     {Kamera.Beweg_Raus(Faktor);}
  if (Taste_Pos1)        {Kamera.Zoom_Rein(Faktor);}
  if (Taste_Ende)        {Kamera.Zoom_Raus(Faktor);}

  //Frames++;                       // F"ur die Frames/sec-Anzeige
  
  // Zeit seit Stossbeginn
  GLint Zeit=FrameZeitpunkt-Startzeit;
  
  // Letzten Zustand noch zeichnen, wenn Stoss
  if (Zeit>Stossdauer) {Zeit=Stossdauer;} // eigentlich schon vorbei

  //printf("%i-%i=%i: ",FrameZeitpunkt,Startzeit,Zeit);
  
  for (int Kugelnr=0;Kugelnr<16;Kugelnr++) { // Alle Kugeln neu positionieren
    if (Bewegungstabelle[Zeit][Kugelnr][2]<=0) {
      //if (Kugelnr<8)
		//printf("%i,%i ",(GLint)Bewegungstabelle[Zeit][Kugelnr][0],(GLint)Bewegungstabelle[Zeit][Kugelnr][1]);
	  Kugel[Kugelnr].neuePositionD(Bewegungstabelle[Zeit][Kugelnr]);
    }
  }
  //printf("\n");

  //DelayAusgleich=1;
  
  Anzeige.setzeStossStaerke(AusholStaerke/3.333-Zeit/3.0);
  
  if (!(Zeit & 31)) {
    GLint neu=0;
    for (int i=0;i<16;i++) {
      if (KugelnImSpiel[i] && !KugelnVersenkt[i] && (Kugel[i].Pos_x()==3000)) {
	KugelnVersenkt[i]=1;
	neu=1;
      }
    }
    if (neu) {Menu.NeuerMenuZustand();}
  }
  
  
  if (Zeit==Stossdauer &&
      !(SpielModus == TUTORIAL && FrameZeitpunkt-Startzeit < 1900)) {
    // Animation schon fertig?

    //#ifndef _WIN32 
    //printf(" %f Frames/sec\n",(Frames*100.0)/(Stossdauer+1.0));
    //#endif    

    for (int i=0;i<16;i++) {
      if (KugelnImSpiel[i] && !KugelnVersenkt[i] && (Kugel[i].Pos_x()==3000)) {
	KugelnVersenkt[i]=1;
      }
    }

    if (SpielModus == TRAININGSSPIEL||SpielModus == TUTORIAL) {
      if (Kugel[0].Pos_x()==3000) {
	StateMaschin=WEISSNEU;
	Anzeige.setzeStossStaerke(0.0);
	LageVerbesserung=1;
	LageVerbesserungKopffeld=1;
	WeisseEinsetzen();
	Menu.NeuerMenuZustand();
      } else {
	StateMaschin=BETRACHTEN;
	Anzeige.setzeStossStaerke(0.0);
	Menu.NeuerMenuZustand();
      }
    } else if (Schiedsrichter.Entscheidung()) {
      StateMaschin=SCHIEDSRICHTER;
      Anzeige.setzeStossStaerke(0.0);
    } else {
      StateMaschin=BETRACHTEN;
      Anzeige.setzeStossStaerke(0.0);
      Menu.NeuerMenuZustand();
    }
  }
}

void WeissneuHandling() {

  if (SpielModus==TRAININGSSPIEL) {
    LageVerbesserungKopffeld=0;
    LageVerbesserung=1;
  }

  GLfloat x=Kugel[0].Pos_xCM();
  GLfloat y=Kugel[0].Pos_yCM();

  GLfloat Faktor2=sqrt((Kugel[0].Pos_xCM()-Kamera.Pos_xCM())*
		       (Kugel[0].Pos_xCM()-Kamera.Pos_xCM())+
		       (Kugel[0].Pos_yCM()-Kamera.Pos_yCM())*
		       (Kugel[0].Pos_yCM()-Kamera.Pos_yCM())+
		       Kamera.Pos_zCM()*Kamera.Pos_zCM());

  Faktor2*=.005;

  if (Taste_Pfeil_Oben) {
    x+=.3*Faktor*Faktor2*sin(Kamera.Beta*M_PI/180.0);
    y+=.3*Faktor*Faktor2*cos(Kamera.Beta*M_PI/180.0);
  }
  if (Taste_Pfeil_Unten) {
    x-=.3*Faktor*Faktor2*sin(Kamera.Beta*M_PI/180.0);
    y-=.3*Faktor*Faktor2*cos(Kamera.Beta*M_PI/180.0);
  }
  if (Taste_Pfeil_Links) {
    x-=.3*Faktor*Faktor2*cos(Kamera.Beta*M_PI/180.0);
    y+=.3*Faktor*Faktor2*sin(Kamera.Beta*M_PI/180.0);
  }
  if (Taste_Pfeil_Rechts) {
    x+=.3*Faktor*Faktor2*cos(Kamera.Beta*M_PI/180.0);
    y-=.3*Faktor*Faktor2*sin(Kamera.Beta*M_PI/180.0);
  }

  GLint ungueltig=0;

  if (x<-124 || x>124 || (x>-63.5 && LageVerbesserungKopffeld)) {
    x=Kugel[0].Pos_xCM();
  }
  if (y<-60.5||y>60.5) {
    y=Kugel[0].Pos_yCM();
  }
  
  for (int nr=1;nr<16;nr++) {
    if ((Kugel[nr].Pos_xCM()-x)*(Kugel[nr].Pos_xCM()-x)+
	(Kugel[nr].Pos_yCM()-y)*(Kugel[nr].Pos_yCM()-y)<32.7) {
      ungueltig=1;
    }
  }

  if (!ungueltig) {
    Kugel[0].neuePositionCM(x,y);
  }

  if (Taste_Shift)       {Kamera.Beweg_Hoch(Faktor);}
  if (Taste_Strg)        {Kamera.Beweg_Runter(Faktor);}
  if (Taste_Bild_Auf)    {Kamera.Beweg_Rein(Faktor);}
  if (Taste_Bild_Ab)     {Kamera.Beweg_Raus(Faktor);}
  if (Taste_Pos1)        {Kamera.Zoom_Rein(Faktor);}
  if (Taste_Ende)        {Kamera.Zoom_Raus(Faktor);}
}

void SchiedsrichterHandling() {
  if (SchiedsrichterEntscheidung == -1) {
    SchiedsrichterEntscheidung = Schiedsrichter.Entscheidung();

    AufnahmeWechsel = SchiedsrichterEntscheidung & 1;
    Foul = SchiedsrichterEntscheidung & 2;
    LageVerbesserungKopffeld = SchiedsrichterEntscheidung & 4;
    LageVerbesserung = SchiedsrichterEntscheidung & 8;
    NeuAufbauenOderWeiterspielen = SchiedsrichterEntscheidung & 16;
    NeuAufbauenOderAchtEinsetzen = SchiedsrichterEntscheidung & 32;
    Spieler1Gewonnen = SchiedsrichterEntscheidung & 64;
    Spieler2Gewonnen = SchiedsrichterEntscheidung & 128;
    
    Menu.NeuerMenuZustand();
    
  }
}




