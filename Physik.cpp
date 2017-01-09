/****************************************************************************
**
**  Physik.cpp   Stefan Disch, Tobias Nopper, Martina Welte 2001
**
**  Berechnet Stoss und schreibt Positionsdaten in die Bewegungstabelle
**
*****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "Kugel.h"
#include "Schiedsrichter.h"
#include "Physik.h"

GLfloat altePos[16][3]; // alte Pos. der Kugeln
GLfloat neuePos[16][3]; // neue Pos. der Kugeln

GLfloat KugelSpeed[16][2]; // Geschw. Kugeln
GLfloat FallFaktor = 25.0;
GLfloat VerlustTasche = 1.0;

// ---------------- Kugel versenken ----------------------------------------

void versenken(GLint nr){
  if (neuePos[nr][2] <= -2.0) { // Kugel ist unten und verschwindet
    neuePos[nr][0]=1500;
    neuePos[nr][1]=1500;
    neuePos[nr][2]=0; 
    KugelSpeed[nr][0] = 0.0;
    KugelSpeed[nr][1] = 0.0;
    
  }
 
  if ((neuePos[nr][2]==0)&&(neuePos[nr][0]!=1500)) { // Kugel beginnt zu fallen
    neuePos[nr][2] = -0.05;
    KugelSpeed[nr][0] = KugelSpeed[nr][0]*0.95; // abbremsen
    KugelSpeed[nr][1] = KugelSpeed[nr][1]*0.95;
  }
  else           // Kugel faellt bereits
    {

      if (neuePos[nr][0]>10){                            // rechts
	if (neuePos[nr][1]>0){                             // oben
	  KugelSpeed[nr][0] = 23.322-neuePos[nr][0]+KugelSpeed[nr][0]*0.5;
	  KugelSpeed[nr][1] = 12.211-neuePos[nr][1]+KugelSpeed[nr][1]*0.5;
	}
	else{                                              // unten
	  KugelSpeed[nr][0] = 23.322-neuePos[nr][0]+KugelSpeed[nr][0]*0.5;
	  KugelSpeed[nr][1] = -12.211-neuePos[nr][1]+KugelSpeed[nr][1]*0.5;	
	}
      }
      if (neuePos[nr][0]<-10){                            // links
	if (neuePos[nr][1]>0){                             // oben
	  KugelSpeed[nr][0] = -23.322-neuePos[nr][0]+KugelSpeed[nr][0]*0.5;
	  KugelSpeed[nr][1] = 12.211-neuePos[nr][1]+KugelSpeed[nr][1]*0.5;	
	}
	else{                                              // unten
	  KugelSpeed[nr][0] = -23.322-neuePos[nr][0]+KugelSpeed[nr][0]*0.5;
	  KugelSpeed[nr][1] = -12.211-neuePos[nr][1]+KugelSpeed[nr][1]*0.5;	
	}
      }	
      if ((neuePos[nr][0]>-2)&&(neuePos[nr][0]<2)){               // Mitte
	if (neuePos[nr][1]>0){                             // oben
	  KugelSpeed[nr][0] = 0-neuePos[nr][0]+KugelSpeed[nr][0]*0.5;
	  KugelSpeed[nr][1] = 12.5547-neuePos[nr][1]+KugelSpeed[nr][1]*0.5;	
	}
	else{                                              // unten
	  KugelSpeed[nr][0] = 0-neuePos[nr][0]+KugelSpeed[nr][0]*0.5;
	  KugelSpeed[nr][1] = -12.5547-neuePos[nr][1]+KugelSpeed[nr][1]*0.5;	
	} 
      }
    }

}


// ----------------------------- Kollisionsberechnung ---------------------------


void Kollision(GLfloat neu1[],GLfloat neu2[],GLint erste,GLint zweite){

  GLfloat verlust = KollisionsFaktor; 


  
  neuePos[erste][0] = neu1[0]; // neue Position wird festgelegt
  neuePos[erste][1] = neu1[1];
  neuePos[zweite][0] = neu2[0];
  neuePos[zweite][1] = neu2[1];
  
  GLfloat dx2 = neu2[0]-neu1[0];
  GLfloat dy2 = neu2[1]-neu1[1];
  GLfloat Abstand2=sqrt(dx2*dx2+dy2*dy2);
  GLfloat dx = dx2/Abstand2;
  GLfloat dy = dy2/Abstand2;


  GLfloat richtung = (KugelSpeed[zweite][0]-KugelSpeed[erste][0])*dx2 + (KugelSpeed[zweite][1]-KugelSpeed[erste][1])*dy2;

  if (richtung < 0){
 
    GLfloat skalarp = .9*(KugelSpeed[erste][0]*dx+KugelSpeed[erste][1]*dy)-
      (KugelSpeed[zweite][0]*dx+KugelSpeed[zweite][1]*dy);
    GLfloat Kraftx = dx * skalarp;
    GLfloat Krafty = dy * skalarp;
    KugelSpeed[erste][0] = (KugelSpeed[erste][0] - Kraftx) * verlust; // neuer Geschw.-Vektor
    KugelSpeed[erste][1] = (KugelSpeed[erste][1] - Krafty) * verlust;
    KugelSpeed[zweite][0] = (KugelSpeed[zweite][0] + Kraftx) * verlust;
    KugelSpeed[zweite][1] = (KugelSpeed[zweite][1] + Krafty) * verlust;
  }
}








void Physik(GLfloat Stoss_x,GLfloat Stoss_y) {
  
  //printf(" Berechne Stoss ...");
  fflush(stdout);
  // ------------------------ Variablen initialisieren ------------------------  

  GLint Aufloesung = PhysikFrequenz; // min. 100
  GLfloat Tischlaenge = 22.22; // x-Achse
  GLfloat Tischbreite = 11.11; // y-Achse

  GLfloat reibung =  ReibungsFaktor; // Geschw.-Abzug durch Reibung

  GLfloat bandenfaktor = BandenFaktor; // Verlust an Banden
  


  

 

  // --------------------------- Kugelpositionen auslesen und Speed setzen ----------

  for (GLint i=0;i<16;i++) {  // erster Tabelleneintrag enthaellt Startposition
    Bewegungstabelle[0][i][0]=Kugel[i].Pos_xD(); 
    Bewegungstabelle[0][i][1]=Kugel[i].Pos_yD();
    Bewegungstabelle[0][i][2]=0;
    altePos[i][0]=Kugel[i].Pos_xD();
    altePos[i][1]=Kugel[i].Pos_yD();
    altePos[i][2]=0;
    neuePos[i][2]=0; //Kugel liegt noch auf dem Tisch
    KugelSpeed[i][0]=0.0;
    KugelSpeed[i][1]=0.0;
  }
  KugelSpeed[0][0] = Stoss_x; // Startgeschw. der weissen Kugel
  KugelSpeed[0][1] = Stoss_y;
  


  // ------------------------------ Berechnung nach diskreten Zeitschritten ---------------------
  int beweg = 0;
  for (int zeit=0;zeit<(20*Aufloesung);zeit++){
    beweg = 0; // noch keine Bewegung

    // neue Position berechnen

    
    for (int nr=0;nr<16;nr++){
      if (altePos[nr][0] == 1500.0) {
	neuePos[nr][0] = 1500.0;
      }
      else {
	neuePos[nr][0] = altePos[nr][0]+KugelSpeed[nr][0]/Aufloesung;
	neuePos[nr][1] = altePos[nr][1]+KugelSpeed[nr][1]/Aufloesung;
	if (altePos[nr][2]<0){
	  neuePos[nr][2] = altePos[nr][2]*(1+FallFaktor/Aufloesung);   // Kugel faellt
	  //beweg = 1;                                                   // und bewegt sich damit
	}
	else
	  {
	    neuePos[nr][2] = (fabs(KugelSpeed[nr][0])+fabs(KugelSpeed[nr][1])>0)?0:1;
	  }
      }
    }
    

  



    // ------------------------ Kollision mit anderer Kugel? ----------------------------------
    
    {
      for (int i=0;i<15;i++){          //letzte Kugel wird nicht betrachtet
	if (neuePos[i][0] != 1500.0){
	  for (int i2=i+1;i2<16;i2++){   //nur verbleibende Kugeln beruecksichtigen
	    if (neuePos[i2][0] != 1500.0){
	      GLfloat dx = neuePos[i][0] - neuePos[i2][0];
	      GLfloat dy = neuePos[i][1] - neuePos[i2][1];
	      GLfloat dBetraghoch2 = dx*dx + dy*dy; // Quadratwurzel sparen
	      if (dBetraghoch2 <= 1){
		// Kollision
		
		Kollision(neuePos[i],neuePos[i2],i,i2);
		
		Schiedsrichter.KugelKugel(i,neuePos[i][0],i2,neuePos[i2][0]);
	      }
	    }
	  }
	}
      }
    }
    
    // ------------------ Kugel in Loch? --------------------------
    
    GLfloat Betrax,Betray;

    for (int i=0;i<16;i++){
      if (neuePos[i][0]!=1500){
	if (neuePos[i][2]<0){
	  versenken(i);
	} else {

	  GLfloat x=neuePos[i][0];
	  GLfloat y=neuePos[i][1];
	  if ((x-23.32)*(x-23.32)+(y-12.21)*(y-12.21)<2.808) {
	    Schiedsrichter.KugelLoch(i,33);
	  }
	  if ((x+23.32)*(x+23.32)+(y-12.21)*(y-12.21)<2.808) {
	    Schiedsrichter.KugelLoch(i,35);
	  }
	  if ((x-23.32)*(x-23.32)+(y+12.21)*(y+12.21)<2.808) {
	    Schiedsrichter.KugelLoch(i,32);
	  }
	  if ((x+23.32)*(x+23.32)+(y+12.21)*(y+12.21)<2.808) {
	    Schiedsrichter.KugelLoch(i,30);
	  }
	  if (x*x+(y-12.55)*(y-12.55)<1.617) {
	    Schiedsrichter.KugelLoch(i,34);
	  }
	  if (x*x+(y+12.55)*(y+12.55)<1.617) {
	    Schiedsrichter.KugelLoch(i,31);
	  }

	  Betrax=fabs(neuePos[i][0]);
	  Betray=fabs(neuePos[i][1]);
	  if ((Betrax-23.32)*(Betrax-23.32)+(Betray-12.21)*(Betray-12.21)<2.808) {     // Ecke
	    versenken(i);
	    //printf("\nKugel %i versenkt",i);
	  }
	  if ((Betrax)*(Betrax)+(Betray-12.55)*(Betray-12.55)<1.617){                  // Mitte
	    versenken(i);
	    //printf("\nKugel %i versenkt",i);
	  }
	}
      }
    }
    




    // ------------------- Kollision mit Bande? ---------------------

    // der Kuerzungsfaktor ist 1-bandenfaktor*cosinus Ausfallwinkel
    // somit stellt der bandenfaktor den max. moeglichen Faktor dar (bei senkrechter Reflexion)

    
    {
      for (int i=0;i<16;i++){
	if (neuePos[i][0] != 1500.0) {
	  GLfloat laenge = 1;
	  GLfloat faktor = 1;
	  
	  //unten

	  if (neuePos[i][1]<(-Tischbreite+0.5)) {
	    if (((neuePos[i][0]>-20.53)&&(neuePos[i][0]<-1.137))||((neuePos[i][0]<20.53)&&(neuePos[i][0]>1.137))){
	      Schiedsrichter.KugelBande(i,neuePos[i][0],21);
	      neuePos[i][1]=(-Tischbreite+0.5);
	      laenge=sqrt(KugelSpeed[i][0]*KugelSpeed[i][0]+KugelSpeed[i][1]*KugelSpeed[i][1]);
	      faktor = 1-bandenfaktor*(-KugelSpeed[i][1]/laenge);
	      KugelSpeed[i][1]=-KugelSpeed[i][1]* faktor;
	      KugelSpeed[i][0]=KugelSpeed[i][0]* faktor;
	    } else {
	      // rechts
	      if (neuePos[i][0]>=20.53){
		if (neuePos[i][1] <= -0.75355 * (neuePos[i][0]-20.53) + (-Tischbreite+0.62)){  
		  Schiedsrichter.KugelBande(i,neuePos[i][0],21);
		  //neuePos[i][1] = -0.75355 * (neuePos[i][0]-20.53) + (-Tischbreite+0.62);
		  GLfloat cos37 = 0.798636;
		  GLfloat sin37 = -0.601815;
		  GLfloat xstrich = KugelSpeed[i][0] * cos37 + KugelSpeed[i][1] * sin37;
		  GLfloat ystrich = -KugelSpeed[i][0] * sin37 + KugelSpeed[i][1] * cos37;
		  ystrich = -ystrich;
		  ystrich = ystrich*VerlustTasche;
		  xstrich = xstrich*VerlustTasche;
		  KugelSpeed[i][0] = (xstrich * cos37 - ystrich * sin37);
		  KugelSpeed[i][1] = (xstrich * sin37 + ystrich * cos37); 
		  neuePos[i][0]+=KugelSpeed[i][0]/Aufloesung;
		  neuePos[i][1]+=KugelSpeed[i][1]/Aufloesung;
		}
	      }
	      // links
	      if (neuePos[i][0]<=-20.53){
		if (neuePos[i][1] <= 0.75355 * (neuePos[i][0]+20.53) + (-Tischbreite+0.62)){  
		  Schiedsrichter.KugelBande(i,neuePos[i][0],21);
		  //neuePos[i][1] = 0.75355 * (neuePos[i][0]+20.53) + (-Tischbreite+0.62);
		  GLfloat cos37 = 0.798636;
		  GLfloat sin37 = 0.601815;
		  GLfloat xstrich = KugelSpeed[i][0] * cos37 + KugelSpeed[i][1] * sin37;
		  GLfloat ystrich = -KugelSpeed[i][0] * sin37 + KugelSpeed[i][1] * cos37;
		  ystrich = -ystrich;
		  ystrich = ystrich*VerlustTasche;
		  xstrich = xstrich*VerlustTasche;
		  KugelSpeed[i][0] = (xstrich * cos37 - ystrich * sin37);
		  KugelSpeed[i][1] = (xstrich * sin37 + ystrich * cos37); 
		  neuePos[i][0]+=KugelSpeed[i][0]/Aufloesung;
		  neuePos[i][1]+=KugelSpeed[i][1]/Aufloesung;
		}
	      }
	      // Mitte rechts
	      if ((neuePos[i][0]>0)&&(neuePos[i][0]<=1.137)){
		if (neuePos[i][1] <= 5.671 * (neuePos[i][0]-1.137) + (-Tischbreite+2.879)){ 
		  Schiedsrichter.KugelBande(i,neuePos[i][0],21);
		  //neuePos[i][1] = 5.671 * (neuePos[i][0]-1.137) + (-Tischbreite+2.879);
		  GLfloat cos80 = 0.173648;
		  GLfloat sin80 = 0.984808;
		  GLfloat xstrich = KugelSpeed[i][0] * cos80 + KugelSpeed[i][1] * sin80;
		  GLfloat ystrich = -KugelSpeed[i][0] * sin80 + KugelSpeed[i][1] * cos80;
		  ystrich = -ystrich;
		  ystrich = ystrich*VerlustTasche;
		  xstrich = xstrich*VerlustTasche;
		  KugelSpeed[i][0] = (xstrich * cos80 - ystrich * sin80);
		  KugelSpeed[i][1] = (xstrich * sin80 + ystrich * cos80); 
		  neuePos[i][0]+=KugelSpeed[i][0]/Aufloesung;
		  neuePos[i][1]+=KugelSpeed[i][1]/Aufloesung;
		}
	      }
	      // Mitte links
	      if ((neuePos[i][0]<=0)&&(neuePos[i][0]>=-1.137)){
		if (neuePos[i][1] <= -5.671 * (neuePos[i][0]+1.137) + (-Tischbreite+2.879)){ 
		  Schiedsrichter.KugelBande(i,neuePos[i][0],21);
		  //neuePos[i][1] = -5.671 * (neuePos[i][0]+1.137) + (-Tischbreite+2.879);
		  GLfloat cos80 = 0.173648;
		  GLfloat sin80 = -0.984808;
		  GLfloat xstrich = KugelSpeed[i][0] * cos80 + KugelSpeed[i][1] * sin80;
		  GLfloat ystrich = -KugelSpeed[i][0] * sin80 + KugelSpeed[i][1] * cos80;
		  ystrich = -ystrich;
		  ystrich = ystrich*VerlustTasche;
		  xstrich = xstrich*VerlustTasche;
		  KugelSpeed[i][0] = (xstrich * cos80 - ystrich * sin80);
		  KugelSpeed[i][1] = (xstrich * sin80 + ystrich * cos80); 
		  neuePos[i][0]+=KugelSpeed[i][0]/Aufloesung;
		  neuePos[i][1]+=KugelSpeed[i][1]/Aufloesung;
		}
	      }
	    }
	  }
	  
	  //oben

	  if (neuePos[i][1]>(Tischbreite-0.5)){
	    if (((neuePos[i][0]>-20.53)&&(neuePos[i][0]<-1.137))||((neuePos[i][0]<20.53)&&(neuePos[i][0]>1.137))){
	      Schiedsrichter.KugelBande(i,neuePos[i][0],23);
	      neuePos[i][1]=(Tischbreite-0.5);
	      laenge=sqrt(KugelSpeed[i][0]*KugelSpeed[i][0]+KugelSpeed[i][1]*KugelSpeed[i][1]);
	      faktor = 1-bandenfaktor*(KugelSpeed[i][1]/laenge);
	      KugelSpeed[i][1]=-KugelSpeed[i][1]*faktor;
	      KugelSpeed[i][0]=KugelSpeed[i][0]*faktor;
	    } else {
	      // rechts
	      if (neuePos[i][0]>=20.53){
		if (neuePos[i][1] >= 0.75355 * (neuePos[i][0]-20.53) + (Tischbreite-0.62)){
		  Schiedsrichter.KugelBande(i,neuePos[i][0],23);
		  //neuePos[i][1] = 0.75355 * (neuePos[i][0]-20.53) + (Tischbreite-0.62);
		  GLfloat cos37 = 0.798636;
		  GLfloat sin37 = 0.601815;
		  GLfloat xstrich = KugelSpeed[i][0] * cos37 + KugelSpeed[i][1] * sin37;
		  GLfloat ystrich = -KugelSpeed[i][0] * sin37 + KugelSpeed[i][1] * cos37;
		  ystrich = -ystrich;
		  ystrich = ystrich*VerlustTasche;
		  xstrich = xstrich*VerlustTasche;
		  KugelSpeed[i][0] = (xstrich * cos37 - ystrich * sin37);
		  KugelSpeed[i][1] = (xstrich * sin37 + ystrich * cos37); 
		  neuePos[i][0]+=KugelSpeed[i][0]/Aufloesung;
		  neuePos[i][1]+=KugelSpeed[i][1]/Aufloesung;
		}
	      }
	      // links
	      if (neuePos[i][0]<=-20.53){
		if (neuePos[i][1] >= -0.75355 * (neuePos[i][0]+20.53) + (Tischbreite-0.62)){ 
		  Schiedsrichter.KugelBande(i,neuePos[i][0],23);
		  //neuePos[i][1] = -0.75355 * (neuePos[i][0]+20.53) + (Tischbreite-0.62);
		  GLfloat cos37 = 0.798636;
		  GLfloat sin37 = -0.601815;
		  GLfloat xstrich = KugelSpeed[i][0] * cos37 + KugelSpeed[i][1] * sin37;
		  GLfloat ystrich = -KugelSpeed[i][0] * sin37 + KugelSpeed[i][1] * cos37;
		  ystrich = -ystrich;
		  ystrich = ystrich*VerlustTasche;
		  xstrich = xstrich*VerlustTasche;
		  KugelSpeed[i][0] = (xstrich * cos37 - ystrich * sin37);
		  KugelSpeed[i][1] = (xstrich * sin37 + ystrich * cos37); 
		  neuePos[i][0]+=KugelSpeed[i][0]/Aufloesung;
		  neuePos[i][1]+=KugelSpeed[i][1]/Aufloesung;		  
		}
	      }
	      // Mitte rechts
	      if ((neuePos[i][0]>0)&&(neuePos[i][0]<=1.137)){
		if (neuePos[i][1] >= -5.671 * (neuePos[i][0]-1.137) + (Tischbreite-2.879)){  
		  Schiedsrichter.KugelBande(i,neuePos[i][0],23);
		  //neuePos[i][1] = -5.671 * (neuePos[i][0]-1.137) + (Tischbreite-2.879);
		  GLfloat cos80 = 0.173648;
		  GLfloat sin80 = -0.984808;		   
		  GLfloat xstrich = KugelSpeed[i][0] * cos80 + KugelSpeed[i][1] * sin80;
		  GLfloat ystrich = -KugelSpeed[i][0] * sin80 + KugelSpeed[i][1] * cos80;
		  ystrich = -ystrich;
		  ystrich = ystrich*VerlustTasche;
		  xstrich = xstrich*VerlustTasche;
		  KugelSpeed[i][0] = (xstrich * cos80 - ystrich * sin80);
		  KugelSpeed[i][1] = (xstrich * sin80 + ystrich * cos80); 
		  neuePos[i][0]+=KugelSpeed[i][0]/Aufloesung;
		  neuePos[i][1]+=KugelSpeed[i][1]/Aufloesung;
		}
	      }
	      // Mitte links
	      if ((neuePos[i][0]<=0)&&(neuePos[i][0]>=-1.137)){
		if (neuePos[i][1] >=  5.671 * (neuePos[i][0]+1.137) + (Tischbreite-2.879)){
		  Schiedsrichter.KugelBande(i,neuePos[i][0],23);
		  //neuePos[i][1] =  5.671 * (neuePos[i][0]+1.137) + (Tischbreite-2.879);
		  GLfloat cos80 = 0.173648;
		  GLfloat sin80 = 0.984808;	
		  GLfloat xstrich = KugelSpeed[i][0] * cos80 + KugelSpeed[i][1] * sin80;
		  GLfloat ystrich = -KugelSpeed[i][0] * sin80 + KugelSpeed[i][1] * cos80;
		  ystrich = -ystrich;
		  ystrich = ystrich*VerlustTasche;
		  xstrich = xstrich*VerlustTasche;
		  KugelSpeed[i][0] = (xstrich * cos80 - ystrich * sin80);
		  KugelSpeed[i][1] = (xstrich * sin80 + ystrich * cos80); 
		  neuePos[i][0]+=KugelSpeed[i][0]/Aufloesung;
		  neuePos[i][1]+=KugelSpeed[i][1]/Aufloesung;
		}
	      }
	    }
	  }

	  //links

	  if (neuePos[i][0]<(-Tischlaenge+0.5)) {
	    if ((neuePos[i][1]>-9.37)&&(neuePos[i][1]<9.37)){
	      Schiedsrichter.KugelBande(i,neuePos[i][0],20);
	      neuePos[i][0]=(-Tischlaenge+0.5);
	      laenge=sqrt(KugelSpeed[i][0]*KugelSpeed[i][0]+KugelSpeed[i][1]*KugelSpeed[i][1]);
	      faktor = 1-bandenfaktor*(-KugelSpeed[i][0]/laenge);
	      KugelSpeed[i][0]=-KugelSpeed[i][0]*faktor;
	      KugelSpeed[i][1]=KugelSpeed[i][1]*faktor;
	    } else {
	      // oben
	      if (neuePos[i][1]>=9.37){
		if (neuePos[i][0] <= -0.75355 * (neuePos[i][1]-9.37) + (-Tischlaenge+0.62)){  
		  Schiedsrichter.KugelBande(i,neuePos[i][0],20);
		  //neuePos[i][0] = -0.75355 * (neuePos[i][1]-9.37) + (-Tischlaenge+0.62);
		  GLfloat cos37 = 0.798636;
		  GLfloat sin37 = 0.601815;
		  GLfloat xstrich = KugelSpeed[i][0] * cos37 + KugelSpeed[i][1] * sin37;
		  GLfloat ystrich = -KugelSpeed[i][0] * sin37 + KugelSpeed[i][1] * cos37;
		  xstrich = -xstrich;
		  ystrich = ystrich*VerlustTasche;
		  xstrich = xstrich*VerlustTasche;
		  KugelSpeed[i][0] = (xstrich * cos37 - ystrich * sin37);
		  KugelSpeed[i][1] = (xstrich * sin37 + ystrich * cos37); 
		  neuePos[i][0]+=KugelSpeed[i][0]/Aufloesung;
		  neuePos[i][1]+=KugelSpeed[i][1]/Aufloesung;
		}
	      }
	      // unten
	      if (neuePos[i][1]<=-9.37){
		if (neuePos[i][0] <= 0.75355 * (neuePos[i][1]+9.37) + (-Tischlaenge+0.62)){
		  Schiedsrichter.KugelBande(i,neuePos[i][0],20);
		  //neuePos[i][0] = 0.75355 * (neuePos[i][1]+9.37) + (-Tischlaenge+0.62);
		  GLfloat cos37 = 0.798636;
		  GLfloat sin37 = -0.601815;
		  GLfloat xstrich = KugelSpeed[i][0] * cos37 + KugelSpeed[i][1] * sin37;
		  GLfloat ystrich = -KugelSpeed[i][0] * sin37 + KugelSpeed[i][1] * cos37;
		  xstrich = -xstrich;
		  ystrich = ystrich*VerlustTasche;
		  xstrich = xstrich*VerlustTasche;
		  KugelSpeed[i][0] = (xstrich * cos37 - ystrich * sin37);
		  KugelSpeed[i][1] = (xstrich * sin37 + ystrich * cos37); 
		  neuePos[i][0]+=KugelSpeed[i][0]/Aufloesung;
		  neuePos[i][1]+=KugelSpeed[i][1]/Aufloesung;
		}
	      }
	    }
	  }

	  //rechts

	  if (neuePos[i][0]>(Tischlaenge-0.5)){
	    if ((neuePos[i][1]>-9.37)&&(neuePos[i][1]<9.37)){
	      Schiedsrichter.KugelBande(i,neuePos[i][0],22);
	      neuePos[i][0]=(Tischlaenge-0.5);
	      laenge=sqrt(KugelSpeed[i][0]*KugelSpeed[i][0]+KugelSpeed[i][1]*KugelSpeed[i][1]);
	      faktor = 1-bandenfaktor*(KugelSpeed[i][0]/laenge);
	      KugelSpeed[i][0]=-KugelSpeed[i][0]*faktor;
	      KugelSpeed[i][1]=KugelSpeed[i][1]*faktor;
	    } else {
	      // oben
	      if (neuePos[i][1]>=9.37){
		if (neuePos[i][0] >= 0.75355 * (neuePos[i][1]-9.37) + (Tischlaenge-0.62)){ 
		  Schiedsrichter.KugelBande(i,neuePos[i][0],22);
		  //neuePos[i][0] = 0.75355 * (neuePos[i][1]-9.37) + (Tischlaenge-0.62);
		  GLfloat cos37 = 0.798636;
		  GLfloat sin37 = -0.601815;
		  GLfloat xstrich = KugelSpeed[i][0] * cos37 + KugelSpeed[i][1] * sin37;
		  GLfloat ystrich = -KugelSpeed[i][0] * sin37 + KugelSpeed[i][1] * cos37;
		  xstrich = -xstrich;
		  ystrich = ystrich*VerlustTasche;
		  xstrich = xstrich*VerlustTasche;
		  KugelSpeed[i][0] = (xstrich * cos37 - ystrich * sin37);
		  KugelSpeed[i][1] = (xstrich * sin37 + ystrich * cos37); 
		  neuePos[i][0]+=KugelSpeed[i][0]/Aufloesung;
		  neuePos[i][1]+=KugelSpeed[i][1]/Aufloesung;
		}
	      }
	      // unten
	      if (neuePos[i][1]<=-9.37){
		if (neuePos[i][0] >= -0.75355 * (neuePos[i][1]+9.37) + (Tischlaenge-0.62)){  
		  Schiedsrichter.KugelBande(i,neuePos[i][0],22);
		  //neuePos[i][0] = -0.75355 * (neuePos[i][1]+9.37) + (Tischlaenge-0.62);
		  GLfloat cos37 = 0.798636;
		  GLfloat sin37 = 0.601815;
		  GLfloat xstrich = KugelSpeed[i][0] * cos37 + KugelSpeed[i][1] * sin37;
		  GLfloat ystrich = -KugelSpeed[i][0] * sin37 + KugelSpeed[i][1] * cos37;
		  xstrich = -xstrich;
		  ystrich = ystrich*VerlustTasche;
		  xstrich = xstrich*VerlustTasche;
		  KugelSpeed[i][0] = (xstrich * cos37 - ystrich * sin37);
		  KugelSpeed[i][1] = (xstrich * sin37 + ystrich * cos37); 
		  neuePos[i][0]+=KugelSpeed[i][0]/Aufloesung;
		  neuePos[i][1]+=KugelSpeed[i][1]/Aufloesung;
		}
	      }
	    }
	  }
	}
      }
    }
    



    // ------------------------------- Tabelle aktualisieren -------------------------------

    GLint zeitpunkt = zeit*100/Aufloesung; // aktuelle Zeit berechnen (fuer Tabelle)
    {
      for (int i=0;i<16;i++){
	Bewegungstabelle[zeitpunkt][i][0] = neuePos[i][0];
	Bewegungstabelle[zeitpunkt][i][1] = neuePos[i][1];
	Bewegungstabelle[zeitpunkt][i][2] = neuePos[i][2];
      }
    }



    // -------------------------- neue Geschwindigkeit berechnen ----------------------------
    
    {
      for (int i=0;i<16;i++){
	if (neuePos[i][0] != 1500.0){
	  GLfloat geschw = sqrt(KugelSpeed[i][0]* KugelSpeed[i][0] +  KugelSpeed[i][1]* KugelSpeed[i][1]);
	  GLfloat geschwneu = geschw - (reibung/Aufloesung);
	  if (neuePos[i][2]<0){beweg=1;} // Kugel faellt und bewegt sich damit
	  if (geschwneu <= 0.0) {  // Kugel bleibt stehen
	    KugelSpeed[i][0] = 0.0;
	    KugelSpeed[i][1] = 0.0;
	  }
	  else {
	    KugelSpeed[i][0] = (KugelSpeed[i][0] / geschw) * geschwneu; // neue Geschw. wird gesetzt
	    KugelSpeed[i][1] = (KugelSpeed[i][1] / geschw) * geschwneu;
	    beweg = 1; // Es bewegt sich noch was...
	  }
	}
      }
    }
    

    // ---------------------------------- Stossdauer setzen ------------------------------------

    if (beweg) {
      Stossdauer = (zeitpunkt<1999)?zeitpunkt+1:1999;
    }
    
    { //  Daten umschreiben
      for (int i=0;i<16;i++){
	altePos[i][0]=neuePos[i][0];
	altePos[i][1]=neuePos[i][1];
	altePos[i][2]=neuePos[i][2];
      }
    }
  } 
  
  //printf(" fertig!\n\n");

 
}


