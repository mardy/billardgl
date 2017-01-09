/****************************************************************************
**
**  Kamera.cpp   Stefan Disch, Tobias Nopper, Martina Welte 2001
**
*****************************************************************************/

#include <math.h>
#include <stdio.h> //2CHANGE wieder raus wenn kein printf mehr drin
#include "Kugel.h"
#include "Kamera.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

GLfloat BewegFaktor=.3;
GLfloat DrehFaktor=.3;
GLfloat Positionen[12][6]; // Array zum Abspeichern der Kamerapositionen

/* --------- Konstruktor ---------- */
Kamera::Kamera() {
  // Generieren der vordefinierten Kamerapositionen
  Alpha=60.0;Beta=60.0;
  Pos_x=-100.0;Pos_y=-50.0;Pos_z=50.0;
  FOV=38.6;
  speicherePosition(0);

  Alpha=0;Beta=0;
  Pos_x=0;Pos_y=0;Pos_z=400;
  FOV=30.7;
  speicherePosition(1); 

  Alpha=80;Beta=90;
  Pos_x=-170;Pos_y=0;Pos_z=30;
  FOV=38.6;
  speicherePosition(2); 

  Alpha=80;Beta=-90;
  Pos_x=170;Pos_y=0;Pos_z=30;
  FOV=38.6;
  speicherePosition(3); 

  Alpha=53;Beta=90;
  Pos_x=-220;Pos_y=0;Pos_z=120;
  FOV=38.6;
  speicherePosition(4); 

  Alpha=53;Beta=-90;
  Pos_x=220;Pos_y=0;Pos_z=120;
  FOV=38.6;
  speicherePosition(5); 

  Alpha=48;Beta=123.5;
  Pos_x=-229;Pos_y=121;Pos_z=176;
  FOV=38.6;
  speicherePosition(7); 

  Alpha=48;Beta=56.5;
  Pos_x=-229;Pos_y=-121;Pos_z=176;
  FOV=38.6;
  speicherePosition(6); 

  Soll_Pos_x=-60;
  Soll_Pos_y=-30;
  Rundflug(0);
  Alpha=Soll_Alpha;
  Beta=Soll_Beta;
  Pos_x=Soll_Pos_x;
  Pos_y=Soll_Pos_y;
  Pos_z=Soll_Pos_z;

  Aspekt=1.333333;

  Verfolgung=-1;
 
  Alpha=100;Beta=0;
  Pos_x=0;Pos_y=-200;Pos_z=20;
  FOV=38.6;

}


void Kamera::male() {
  glMatrixMode(GL_PROJECTION); // Kameraparameter!
  glLoadIdentity();            // zuruecksetzen
  gluPerspective(FOV,Aspekt,Nah,Fern);

  glMatrixMode(GL_MODELVIEW);  // Blickpunkt!
  glLoadIdentity();            // Kamera an den Ursprung setzen

  glRotatef(Alpha,-1,0,0);     // um Alpha nach oben und Beta nach Rechts drehen
  glRotatef(Beta,0,0,1);
                               // an die gewuenschte Position setzen
  glTranslatef(-Pos_x,-Pos_y,-Pos_z); 

  //glEnable(GL_LIGHTING);
}

//setzt die Kamera an eine neue Position
void Kamera::neuePosition(GLfloat Position[]) {
  Soll_Pos_x = Position[0];
  Soll_Pos_y = Position[1];
  Soll_Pos_z = Position[2];
  Soll_Alpha = Position[3];
  Soll_Beta  = Position[4];
  Soll_FOV   = Position[5];
  BlickTiefeNeuBestimmen();
  Verfolgung=-1;
}

//gibt die aktuelle Kameraposition zur"uck
//GLfloat* Kamera::Position() {
//  GLfloat temp[] ={Soll_Pos_x,Soll_Pos_y,Soll_Pos_z,Soll_Alpha,Soll_Beta,Soll_FOV};
//  return temp;
//}

GLfloat Kamera::Pos_xCM() {
  return Pos_x;
}

GLfloat Kamera::Pos_yCM() {
  return Pos_y;
}

GLfloat Kamera::Pos_zCM() {
  return Pos_z;
}

//schreibt die aktuelle Kameraposition in die Tabelle ab
void Kamera::speicherePosition(GLint Platz) {
  Positionen[Platz][0]=Pos_x;
  Positionen[Platz][1]=Pos_y;
  Positionen[Platz][2]=Pos_z;
  Positionen[Platz][3]=Alpha;
  Positionen[Platz][4]=Beta;
  Positionen[Platz][5]=FOV;
  //2DEL
  //printf("%i: %f %f %f %f %f %f \n",Platz,Pos_x,Pos_y,Pos_z,Alpha,Beta,FOV);
}

// l"adt eine Kameraposition aus der Tabelle
void Kamera::ladePosition(GLint Platz) {
  setzeSollPosition(Positionen[Platz]);
  Verfolgung=-1;
}

// Bewegt die Kamera in Blickrichtung
void Kamera::Beweg_Rein(GLfloat Faktor) {
  Soll_Pos_x+=2*BewegFaktor*Faktor*sin(Soll_Alpha/57.29578)*sin(Soll_Beta/57.29578);
  Soll_Pos_y+=2*BewegFaktor*Faktor*sin(Soll_Alpha/57.29578)*cos(Soll_Beta/57.29578);
  Soll_Pos_z-=2*BewegFaktor*Faktor*cos(Soll_Alpha/57.29578);
  //  if (Pos_z>400) {Pos_z=400;}
  if (Soll_Pos_z<2.8) {Soll_Pos_z=2.9;}
  BlickTiefeNeuBestimmen();
  Verfolgung=-1;
}

// Bewegt die Kamera gegen die Blickrichtung
void Kamera::Beweg_Raus(GLfloat Faktor) {
  Soll_Pos_x-=2*BewegFaktor*Faktor*sin(Soll_Alpha/57.29578)*sin(Soll_Beta/57.29578);
  Soll_Pos_y-=2*BewegFaktor*Faktor*sin(Soll_Alpha/57.29578)*cos(Soll_Beta/57.29578);
  Soll_Pos_z+=2*BewegFaktor*Faktor*cos(Soll_Alpha/57.29578);
  //  if (Pos_z>400) {Pos_z=400;}
  if (Soll_Pos_z<2.8) {Soll_Pos_z=2.8;}
  BlickTiefeNeuBestimmen();
  Verfolgung=-1;
}

// Bewegt die Kamera in Blickrichtung, aber unter Beibehaltung der H"ohe
void Kamera::Beweg_Vor(GLfloat Faktor) {
  Soll_Pos_x+=2*BewegFaktor*Faktor*sin(Soll_Beta/57.29578);
  Soll_Pos_y+=2*BewegFaktor*Faktor*cos(Soll_Beta/57.29578);
  BlickTiefeNeuBestimmen();
  Verfolgung=-1;
}

// Bewegt die Kamera gegen die Blickrichtung, aber unter Beibehaltung der H"ohe
void Kamera::Beweg_Zurueck(GLfloat Faktor) {
  Soll_Pos_x-=2*BewegFaktor*Faktor*sin(Soll_Beta/57.29578);
  Soll_Pos_y-=2*BewegFaktor*Faktor*cos(Soll_Beta/57.29578);  
  BlickTiefeNeuBestimmen();
  Verfolgung=-1;
}

// Bewegt die Kamera nach rechts
void Kamera::Beweg_Rechts(GLfloat Faktor) {
  Soll_Pos_x+=BewegFaktor*Faktor*cos(Soll_Beta/57.29578);
  Soll_Pos_y-=BewegFaktor*Faktor*sin(Soll_Beta/57.29578);
  BlickTiefeNeuBestimmen();
  Verfolgung=-1;
}

// Bewegt die Kamera nach links
void Kamera::Beweg_Links(GLfloat Faktor) {
  Soll_Pos_x-=BewegFaktor*Faktor*cos(Soll_Beta/57.29578);
  Soll_Pos_y+=BewegFaktor*Faktor*sin(Soll_Beta/57.29578);
  BlickTiefeNeuBestimmen();
  Verfolgung=-1;
}

// Bewegt die Kamera nach oben
void Kamera::Beweg_Hoch(GLfloat Faktor) {
  Soll_Pos_z+=BewegFaktor*Faktor;
  //  if (Pos_z>400) {Pos_z=400;}
  BlickTiefeNeuBestimmen();
  Verfolgung=-1;
}

// Bewegt die Kamera nach unten
void Kamera::Beweg_Runter(GLfloat Faktor) {
  Soll_Pos_z-=BewegFaktor*Faktor;
  if (Soll_Pos_z<2.8) {Soll_Pos_z=2.8;}
  BlickTiefeNeuBestimmen();
  Verfolgung=-1;
}

// Vergr"o"sert den Zoom
void Kamera::Zoom_Rein(GLfloat Faktor) {
  Soll_FOV-=BewegFaktor*Faktor;
  if (Soll_FOV<1) {Soll_FOV=1;}
  Verfolgung=-1;
}

// Verkleinert den Zoom
void Kamera::Zoom_Raus(GLfloat Faktor) {
  Soll_FOV+=BewegFaktor*Faktor;
  Verfolgung=-1;
}

// Vergr"o"sert den Vertigo
void Kamera::Vertigo_Rein(GLfloat Faktor) {
  Soll_Pos_x-=2*BewegFaktor*Faktor*sin(Soll_Alpha/57.29578)*sin(Soll_Beta/57.29578);
  Soll_Pos_y-=2*BewegFaktor*Faktor*sin(Soll_Alpha/57.29578)*cos(Soll_Beta/57.29578);
  Soll_Pos_z+=2*BewegFaktor*Faktor*cos(Soll_Alpha/57.29578);
  Soll_FOV=2077*cos(Soll_Alpha/57.29578)/Soll_Pos_z;
  if (Soll_FOV<1) {Soll_FOV=1;}
  Verfolgung=-1;
}

// Verkleinert den Vertigo
void Kamera::Vertigo_Raus(GLfloat Faktor) {
  Soll_Pos_x+=2*BewegFaktor*Faktor*sin(Soll_Alpha/57.29578)*sin(Soll_Beta/57.29578);
  Soll_Pos_y+=2*BewegFaktor*Faktor*sin(Soll_Alpha/57.29578)*cos(Soll_Beta/57.29578);
  Soll_Pos_z-=2*BewegFaktor*Faktor*cos(Soll_Alpha/57.29578);
  Soll_FOV=2077*cos(Soll_Alpha/57.29578)/Soll_Pos_z;
  Verfolgung=-1;
}

// Dreht die Kamera nach rechts
void Kamera::Dreh_Rechts(GLfloat Faktor) {
  Soll_Beta+=Faktor*DrehFaktor;
  Verfolgung=-1;
}

// Dreht die Kamera nach links
void Kamera::Dreh_Links(GLfloat Faktor) {
  Soll_Beta-=Faktor*DrehFaktor;
  Verfolgung=-1;
}

// Dreht die Kamera nach oben
void Kamera::Dreh_Hoch(GLfloat Faktor) {
  Soll_Alpha+=Faktor*DrehFaktor;
  if (Soll_Alpha>90) {Soll_Alpha=90;}
  if (Soll_Alpha<0) {Soll_Alpha=0;}
  Verfolgung=-1;
}

// Dreht die Kamera nach unten
void Kamera::Dreh_Runter(GLfloat Faktor) {
  Soll_Alpha-=Faktor*DrehFaktor; 
  if (Soll_Alpha>90) {Soll_Alpha=90;}
  if (Soll_Alpha<0) {Soll_Alpha=0;}
  Verfolgung=-1;
}

void Kamera::Schwenk_Links(GLfloat Faktor, GLfloat Mitte_x, GLfloat Mitte_y) {
  GLfloat Abstand=sqrt((Mitte_x-Soll_Pos_x)*(Mitte_x-Soll_Pos_x)+(Mitte_y-Soll_Pos_y)*(Mitte_y-Soll_Pos_y));
  if (Abstand<5) Abstand=5;
  Soll_Beta+=Faktor*DrehFaktor*7.338/sqrt(Abstand);
  Soll_Pos_x=Mitte_x-Abstand*sin(Soll_Beta/57.29578);
  Soll_Pos_y=Mitte_y-Abstand*cos(Soll_Beta/57.29578);
  BlickTiefeNeuBestimmen();
  Verfolgung=-1;
}

void Kamera::Schwenk_Rechts(GLfloat Faktor, GLfloat Mitte_x, GLfloat Mitte_y) {
  GLfloat Abstand=sqrt((Mitte_x-Soll_Pos_x)*(Mitte_x-Soll_Pos_x)+(Mitte_y-Soll_Pos_y)*(Mitte_y-Soll_Pos_y));
  if (Abstand<5) Abstand=5;
  Soll_Beta-=Faktor*DrehFaktor*7.338/sqrt(Abstand);
  Soll_Pos_x=Mitte_x-Abstand*sin(Soll_Beta/57.29578);
  Soll_Pos_y=Mitte_y-Abstand*cos(Soll_Beta/57.29578);
  BlickTiefeNeuBestimmen();
  Verfolgung=-1;
}

void Kamera::Schwenk_Hoch(GLfloat Faktor, GLfloat Mitte_x, GLfloat Mitte_y) {
  GLfloat Abstand=sqrt((Mitte_x-Soll_Pos_x)*(Mitte_x-Soll_Pos_x)+(Mitte_y-Soll_Pos_y)*(Mitte_y-Soll_Pos_y)+(Soll_Pos_z-2.8)*(Soll_Pos_z-2.8));
  if (Abstand==0) {
    Soll_Alpha=0;
  } else {
    Soll_Alpha+=Faktor*DrehFaktor*7.338/sqrt(Abstand);
    if (Soll_Alpha<0) {Soll_Alpha=0;}
    if (Soll_Alpha>90) {Soll_Alpha=90;}
  }
  Soll_Pos_x=Mitte_x-Abstand*sin(Soll_Beta/57.29578)*sin(Soll_Alpha/57.29578);
  Soll_Pos_y=Mitte_y-Abstand*cos(Soll_Beta/57.29578)*sin(Soll_Alpha/57.29578);
  Soll_Pos_z=2.8+Abstand*cos(Soll_Alpha/57.29578);
  //  if (Pos_z>400) {Pos_z=400;}
  if (Soll_Pos_z<2.8) {Soll_Pos_z=2.8;}
  BlickTiefeNeuBestimmen();
  Verfolgung=-1;
}

void Kamera::Schwenk_Runter(GLfloat Faktor, GLfloat Mitte_x, GLfloat Mitte_y) {
  GLfloat Abstand=sqrt((Mitte_x-Soll_Pos_x)*(Mitte_x-Soll_Pos_x)+(Mitte_y-Soll_Pos_y)*(Mitte_y-Soll_Pos_y)+(Soll_Pos_z-2.8)*(Soll_Pos_z-2.8));
  if (Abstand==0) {
    Soll_Alpha=0;
  } else {
    Soll_Alpha-=Faktor*DrehFaktor*7.338/sqrt(Abstand);
  if (Soll_Alpha<0) {Soll_Alpha=0;}
  if (Soll_Alpha>90) {Soll_Alpha=90;}
  }
  Soll_Pos_x=Mitte_x-Abstand*sin(Soll_Beta/57.29578)*sin(Soll_Alpha/57.29578);
  Soll_Pos_y=Mitte_y-Abstand*cos(Soll_Beta/57.29578)*sin(Soll_Alpha/57.29578);
  Soll_Pos_z=2.8+Abstand*cos(Soll_Alpha/57.29578);
  //  if (Pos_z>400) {Pos_z=400;}
  if (Soll_Pos_z<2.8) {Soll_Pos_z=2.8;}
  BlickTiefeNeuBestimmen();
  Verfolgung=-1;
}

void Kamera::setzeSollPosition(GLfloat Soll_Pos[6]) {
  Soll_Pos_x = Soll_Pos[0];
  Soll_Pos_y = Soll_Pos[1];
  Soll_Pos_z = Soll_Pos[2];
  Soll_Alpha = Soll_Pos[3];
  Soll_Beta  = Soll_Pos[4];
  Soll_FOV   = Soll_Pos[5];

  Beta=fmod(Beta,360);
  Soll_Beta=fmod(Soll_Beta,360);

  if (Soll_Beta>Beta+180) {Soll_Beta-=360;}
  if (Soll_Beta<Beta-180) {Soll_Beta+=360;}
  BlickTiefeNeuBestimmen();
  Verfolgung=-1;
}

void Kamera::setzeSollPosition(GLfloat SollPosx,
			       GLfloat SollPosy,
			       GLfloat SollPosz,
			       GLfloat SollAlpha,
			       GLfloat SollBeta,
			       GLfloat SollFOV) {
  Soll_Pos_x = SollPosx;
  Soll_Pos_y = SollPosy;
  Soll_Pos_z = SollPosz;
  Soll_Alpha = SollAlpha;
  Soll_Beta  = SollBeta;
  Soll_FOV   = SollFOV;

  Beta=fmod(Beta,360);
  Soll_Beta=fmod(Soll_Beta,360);

  if (Soll_Beta>Beta+180) {Soll_Beta-=360;}
  if (Soll_Beta<Beta-180) {Soll_Beta+=360;}
  Verfolgung=-1;
}

void Kamera::BlickeAuf(GLfloat Blickpunkt[2]) {
  BlickeAuf(Blickpunkt[0],Blickpunkt[1]);
}

void Kamera::BlickeAuf(GLfloat Blickpunkt_x,GLfloat Blickpunkt_y) {
  GLfloat SollPosx=50*(Pos_x-Blickpunkt_x)/
    sqrt((Blickpunkt_x-Pos_x)*(Blickpunkt_x-Pos_x)+
	 (Blickpunkt_y-Pos_y)*(Blickpunkt_y-Pos_y))+
    Blickpunkt_x;
  GLfloat SollPosy=50*(Pos_y-Blickpunkt_y)/
    sqrt((Blickpunkt_x-Pos_x)*(Blickpunkt_x-Pos_x)+
	 (Blickpunkt_y-Pos_y)*(Blickpunkt_y-Pos_y))+
    Blickpunkt_y;
  GLfloat SollPosz=20;
  GLfloat SollAlpha=71.0167;
  GLfloat SollBeta=atan((Blickpunkt_x-SollPosx)/(Blickpunkt_y-SollPosy))*180/M_PI;
  if (SollPosy>Blickpunkt_y) {SollBeta-=180;}
  GLfloat SollFOV=38.6;

  setzeSollPosition(SollPosx,SollPosy,SollPosz,SollAlpha,SollBeta,SollFOV);
  Verfolgung=-1;
}

void Kamera::BlickeAuf2(GLfloat Blickpunkt[2]) {
  BlickeAuf2(Blickpunkt[0],Blickpunkt[1]);
}

void Kamera::BlickeAuf2(GLfloat Blickpunkt_x,GLfloat Blickpunkt_y) {
  GLfloat SollPosx=80*(Pos_x-Blickpunkt_x)/
    sqrt((Blickpunkt_x-Pos_x)*(Blickpunkt_x-Pos_x)+
	 (Blickpunkt_y-Pos_y)*(Blickpunkt_y-Pos_y))+
    Blickpunkt_x;
  GLfloat SollPosy=80*(Pos_y-Blickpunkt_y)/
    sqrt((Blickpunkt_x-Pos_x)*(Blickpunkt_x-Pos_x)+
	 (Blickpunkt_y-Pos_y)*(Blickpunkt_y-Pos_y))+
    Blickpunkt_y;
  GLfloat SollPosz=50;
  GLfloat SollAlpha=72;
  GLfloat SollBeta=atan((Blickpunkt_x-SollPosx)/(Blickpunkt_y-SollPosy))*180/M_PI;
  if (SollPosy>Blickpunkt_y) {SollBeta-=180;}
  GLfloat SollFOV=38.6;

  setzeSollPosition(SollPosx,SollPosy,SollPosz,SollAlpha,SollBeta,SollFOV);
  Verfolgung=-1;
}

void Kamera::BlickeAuf3(GLfloat Blickpunkt[2]) {
  BlickeAuf3(Blickpunkt[0],Blickpunkt[1]);
}

void Kamera::BlickeAuf3(GLfloat Blickpunkt_x,GLfloat Blickpunkt_y) {
  GLfloat SollPosx=80*(Pos_x-Blickpunkt_x)/
    sqrt((Blickpunkt_x-Pos_x)*(Blickpunkt_x-Pos_x)+
	 (Blickpunkt_y-Pos_y)*(Blickpunkt_y-Pos_y))+
    Blickpunkt_x;
  GLfloat SollPosy=80*(Pos_y-Blickpunkt_y)/
    sqrt((Blickpunkt_x-Pos_x)*(Blickpunkt_x-Pos_x)+
	 (Blickpunkt_y-Pos_y)*(Blickpunkt_y-Pos_y))+
    Blickpunkt_y;
  GLfloat SollPosz=50;
  GLfloat SollAlpha=58;
  GLfloat SollBeta=atan((Blickpunkt_x-SollPosx)/(Blickpunkt_y-SollPosy))*180/M_PI;
  if (SollPosy>Blickpunkt_y) {SollBeta-=180;}
  GLfloat SollFOV=38.6;

  setzeSollPosition(SollPosx,SollPosy,SollPosz,SollAlpha,SollBeta,SollFOV);
  Verfolgung=-1;
}

void Kamera::Fahrt(GLfloat Faktor) {
  if (Verfolgung!=-1) {
    if (Kugel[Verfolgung].Pos_x()==3000.0) {
      Verfolgung=-1;
    } else {
      GLint Verfolgung2=Verfolgung;
      BlickeAuf3(Kugel[Verfolgung].Pos_xCM(),Kugel[Verfolgung].Pos_yCM());
      Verfolgung=Verfolgung2;
    }
  }

  for (int i=0;i<Faktor;i++) {
    
    if (Soll_Beta-Beta<-180){Beta-=360;}
    if (Soll_Beta-Beta> 180){Beta+=360;}
      
    d_Pos_x = d_Pos_x * 0.9 + 0.003 * (Soll_Pos_x-Pos_x);
    d_Pos_y = d_Pos_y * 0.9 + 0.003 * (Soll_Pos_y-Pos_y);
    d_Pos_z = d_Pos_z * 0.9 + 0.003 * (Soll_Pos_z-Pos_z);
    d_Alpha = d_Alpha * 0.9 + 0.003 * (Soll_Alpha-Alpha);
    d_Beta  = d_Beta  * 0.9 + 0.003 * (Soll_Beta-Beta);
    d_FOV   = d_FOV   * 0.9 + 0.003 * (Soll_FOV-FOV);
    
    Pos_x += d_Pos_x;
    Pos_y += d_Pos_y;
    Pos_z += d_Pos_z;
    Alpha += d_Alpha;
    Beta  += d_Beta;
    FOV   += d_FOV;

    BlickTiefeNeuBestimmen();

  }
}

void Kamera::Verfolge(GLint Kugel) {
  Verfolgung=Kugel;
}

void Kamera::BlickTiefeNeuBestimmen() {
  GLfloat ax=fabs(Pos_x),ay=fabs(Pos_y),az=Pos_z;

  if (ax<150) {
    if (ay<80) {
      Nah=az-5; 
    } else {
      Nah=sqrt((ay-80)*(ay-80)+(az-5)*(az-5));
    }
  } else {
    if (ay<80) {
      Nah=sqrt((ax-150)*(ax-150)+(az-5)*(az-5)); 
    } else {
      Nah=sqrt((ax-150)*(ax-150)+(ay-80)*(ay-80)+(az-5)*(az-5));
    }
  }    

  Nah*=.8;

  if (Nah<1) {Nah=1;}

  Fern=sqrt((ax+150)*(ax+150)+(ay+80)*(ay+80)+az*az);
  // printf ("Nah:  %f\nFern: %f\n\n",Nah,Fern); 2DEL

}

void Kamera::Rundflug(GLint Faktor){
  if (Soll_Pos_y==0) {Soll_Pos_y=.00001;}
  //Soll_Beta=Faktor*.1+atan(Soll_Pos_x/Soll_Pos_y)*180/M_PI;
  //if (Soll_Pos_y>0) {Soll_Beta-=180;}
  Soll_Beta+=.1*Faktor;
  Soll_Pos_x=(-30*sin(Soll_Beta*M_PI/180)-280)*sin(Soll_Beta*M_PI/180);
  Soll_Pos_y=(-30*sin(Soll_Beta*M_PI/180)-280)*cos(Soll_Beta*M_PI/180);
  Soll_Pos_z=100-50*sin(Soll_Beta*M_PI/180);
  Soll_FOV=36.8;
  Soll_Alpha=atan(sqrt(Soll_Pos_x*Soll_Pos_x+
		       Soll_Pos_y*Soll_Pos_y)/
		  Soll_Pos_z)*180/M_PI;
}
