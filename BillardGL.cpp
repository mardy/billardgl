/****************************************************************************
**
** BillardGL.cpp   Stefan Disch, Tobias Nopper, Martina Welte 2001
**
****************************************************************************/  


#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <string.h>

#include "Textfeld.h"
#include "Schild.h"
#include "Tisch.h"
#include "Kamera.h"
#include "Kugel.h"
#include "Anzeige.h"
#include "Menu.h"
#include "Beleuchtung.h"

#include "Namen.h" 
#include "LA.h"
#include "bmp.h"
#include "Zeit.h"
#include "Physik.h" 
#include "SpielfeldAufbau.h"
#include "Benutzerschnittstelle.h"
#include "KommandoZeilenParameter.h"
#include "Handling.h"
#include "Schiedsrichter.h"
#include "kugeltabellen.h"
#include "LadeScreen.h"

#include "BillardGL.h"

#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

//Tabellen
GLfloat Bewegungstabelle[2000][16][3];
GLint   Soundtabelle[1000];

//Objekte
class Kugel   Kugel[16];
class Tisch   Tisch;
class Anzeige Anzeige;
class Kamera  Kamera;
class Menu Menu;
class Schiedsrichter Schiedsrichter;
class Beleuchtung Beleuchtung;

//Sonstige Variablen
GLint   MouseLookLast_x;
GLint   MouseLookLast_y;

GLint   Stossdauer=1999;
GLint   Startzeit;
GLint   Frames=0;
GLint   FrameZeitpunkt;
GLint   LetztesFrameZeitpunkt=-1;

GLint   AusholStartzeit;
GLfloat AusholStaerke=0;
GLfloat MaxAusholStaerke=100;

GLint   DelayAusgleich;
GLint   Faktor;

GLint   AllerersterStoss=1;

GLint   FullScreen;
GLint   Hintergrundfarbe=0;

GLint   KugelnVersenkt[16];
GLint   KugelnImSpiel[16];

GLint   xnor=0;
GLint   MausTasteAbgefangen=0;

//State-Maschin'
GLint   StateMaschin=START;
GLint   Spiel=ACHTBALL;
GLint   SpielModus=TRAININGSSPIEL;

// Schiedsrichter
GLint SchiedsrichterEntscheidung=0;
GLint AufnahmeWechsel=0;
//GLint SpielerAmStoss=0;
GLint Foul=0;
GLint LageVerbesserungKopffeld=1;
GLint LageVerbesserung=0;
GLint NeuAufbauenOderWeiterspielen=0;
GLint NeuAufbauenOderAchtEinsetzen=0;
GLint Spieler1Gewonnen=0;
GLint Spieler2Gewonnen=0;

//Tasten
GLint Taste_Pfeil_Oben=0;
GLint Taste_Pfeil_Unten=0;
GLint Taste_Pfeil_Rechts=0;
GLint Taste_Pfeil_Links=0;
GLint Taste_Shift=0;
GLint Taste_Strg=0;
GLint Taste_Bild_Auf=0;
GLint Taste_Bild_Ab=0;
GLint Taste_Pos1=0;
GLint Taste_Ende=0;


//GLint   KameraFahrt=0;


//Betrachtungsweise
GLint PolygonMode_mode=GL_FILL;
GLint PolygonMode_view=GL_FRONT;

int value;

GLint Texturgroesse,AnzeigeTexturgroesse,TischTexturgroesse;
GLint KugelAufloesung;
GLint InvertX,InvertY,Schatten,ZBufferLoeschen;
GLint TexMMM;
GLfloat MouseSpeed,Epsilon;
GLint PhysikFrequenz=400;
GLfloat ReibungsFaktor,BandenFaktor,KollisionsFaktor;
GLint Farbtiefe, Reflektionen;
GLint BildschirmAufloesung;
GLint Sprache;

GLint LadeFortschritt=0;
GLuint dreizehntextur;
GLuint logotextur;

char Spieler1[10];
char Spieler2[10];
char NetzwerkSpieler[10];
char NetzwerkGegner[10];

int OriginalFenster=0,AktuellesFenster=0;

GLint ZeigeFPS;
GLint AmbientesLicht;
GLint TischLampen;
GLint GrueneLampe;

GLfloat EffektLautstaerke=.5;
GLfloat MusikLautstaerke=.5;

//KugelTabellen

GLfloat *ball_vertices[30];
GLfloat *ball_texcoord[30];
GLint *ball_indices[30];

void updateGL()
{
  if (ZBufferLoeschen) {glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);}

  Kamera.male();                        // Kamera-Postion und -Parameter setzen

  Beleuchtung.male();

  Tisch.maleFlaeche();                  // Tischflaeche zeichen
 
  glDisable(GL_DEPTH_TEST);

  Tisch.maleLinien();

  for (int Kugelnr=0;Kugelnr<16;Kugelnr++) {
    Kugel[Kugelnr].maleSchatten();      // Schatten zeichen 
  }

  glEnable(GL_DEPTH_TEST);

  Tisch.maleBanden();

  GLfloat Abstand=0;
  GLint Aufloesung=1;

  for (int Kugelnr2=0;Kugelnr2<16;Kugelnr2++) {
    GLfloat x=Kugel[Kugelnr2].Pos_xCM()-Kamera.Pos_x;
    GLfloat y=Kugel[Kugelnr2].Pos_yCM()-Kamera.Pos_y;
    GLfloat z=Kamera.Pos_z;
    Abstand=sqrt(x*x+y*y+z*z);
    Aufloesung=(GLint(400/Abstand));//300
    if (Aufloesung<3) Aufloesung=3;
    Aufloesung=(Aufloesung/2)*2+1;
    if (Aufloesung>KugelAufloesung) Aufloesung=KugelAufloesung;
    Kugel[Kugelnr2].male(Aufloesung);              // Kugeln zeichen 
  }

  glDisable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  glDisable(GL_LIGHTING);

  Menu.male();

  if (StateMaschin!=START) {
    Anzeige.male();                       // Anzeige zeichnen
  }
  glEnable(GL_DEPTH_TEST);

  glutSwapBuffers();
}

/* -------------------- timerEvent -------------------- */
void timerEvent() {

  //egal+=egal;

  //glutTimerFunc(20,timerEvent,0);
  
  FrameZeitpunkt=Zeit();              // Framezeit bestimmen

                                            // Faktor= Zeit seit letztem Frame
  Faktor=FrameZeitpunkt-LetztesFrameZeitpunkt; 


  if (DelayAusgleich) {
    Faktor=1;
    DelayAusgleich=0;
  }
 
  if (Faktor) {

    if (ZeigeFPS) {
      if ((FrameZeitpunkt%200)<(LetztesFrameZeitpunkt%200)) {
	Menu.SetzeFPS(Frames/2);
	Frames=0;
      } else Frames++;
    } 

    Menu.Update(Faktor);

    switch (StateMaschin) {

    case START: StartHandling();break;
      
    case BETRACHTEN: BetrachtenHandling();break;
      
    case ZIELEN: ZielenHandling();break;
      
    case AUSHOLEN: AusholenHandling();break;
      
    case STOSS: StossHandling();break;
      
    case WEISSNEU: WeissneuHandling();break;
      
    case SCHIEDSRICHTER: SchiedsrichterHandling();break;

    }

    Kamera.Fahrt(Faktor);
    
    LetztesFrameZeitpunkt=FrameZeitpunkt; 

    glutPostWindowRedisplay(AktuellesFenster);
  }  
} 


int main(int argc, char **argv)
{ 
  //char string[10];  

  glutInit(&argc, argv);

  KommandoZeilenParameter(argc,argv);
  
  for (int i=0;i<16;i++) {
    KugelnImSpiel[i]=1;
    KugelnVersenkt[i]=0;
  }
  KugelnImSpiel[0]=0;

  //GLUT initialisieren, Fenster setzen
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  if (FullScreen) {
    char temp[20];
    sprintf(temp,"%ix%i:%i",BildschirmAufloesung,(BildschirmAufloesung*3)/4,Farbtiefe);
    glutGameModeString(temp);
    if (!glutGameModeGet(GLUT_GAME_MODE_POSSIBLE))
      printf ("  No Game Mode possible!\n\n");
    glutEnterGameMode();
    glutFullScreen();
  } else {
    glutInitWindowSize (BildschirmAufloesung,(BildschirmAufloesung*3)/4);
    glutInitWindowPosition (0, 0);
    glutCreateWindow ("BillardGL 1.7");
  }

  glClearColor(0,0,0,0);


  glutIdleFunc(LSidle);

  //Callback zum Zeichnen der GL-Funktion
  glutDisplayFunc(LSupdateGL);

  AktuellesFenster=glutGetWindow();

  //  CreateMenu();

  //  timerEvent(0);

  glutMainLoop();
	
  return EXIT_SUCCESS;
}

/* -------------------- Stoss -------------------- */
void Stoss(GLfloat Stoss_x, GLfloat Stoss_y) {

  Schiedsrichter.NeuerStoss();
  SchiedsrichterEntscheidung=-1;

  Physik(Stoss_x, Stoss_y);               // Physik-Simulation

  Startzeit=Zeit();                       // Startzeit bestimmen

}

void Sichtbar (int vis) {
  if (vis == GLUT_VISIBLE) {
    glutIdleFunc(timerEvent);
  }
}

