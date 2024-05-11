/****************************************************************************
**
**  Benutzerschnittstelle.cpp   Stefan Disch, Tobias Nopper, Martina Welte 2001
**
*****************************************************************************/

#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "BillardGL.h"

#include "Kugel.h"
#include "Kamera.h"
#include "Anzeige.h"
#include "Schild.h"
#include "Textfeld.h"
#include "Menu.h"
#include "Schiedsrichter.h"

#include "Namen.h"
#include "Zeit.h"
#include "SpielfeldAufbau.h"
#include "Handling.h"
#include "Einsetzen.h"

#include "Benutzerschnittstelle.h"

GLint Maustaste=0;

//Callback Funktion: Reaktion auf Mausclicks
void Maus(int button, int state, int x, int y)
{

  if (Menu.Maustaste(button,state,x,y)!=0) {
    MausTasteAbgefangen=1;
    //printf("Abgefangen\n");
  } else {
    MausTasteAbgefangen=0;
    //printf("AbgefangenAus\n");
    MouseLookLast_x=x;
    MouseLookLast_y=y;
    
    //  Kamera.FahrtAus();

    /*
      if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
      switch (StateMaschin) {
      case START:        
      StateMaschin=BETRACHTEN;
      Menu.NeuerMenuZustand();
      break; 
      case BETRACHTEN: {
      if (LageVerbesserungKopffeld|LageVerbesserung) {
      StateMaschin=WEISSNEU;
      Menu.NeuerMenuZustand();
      }
      } break; 
      case ZIELEN:       
      StateMaschin=BETRACHTEN; 
      Menu.NeuerMenuZustand();
      break;
      case AUSHOLEN:        
      StateMaschin=ZIELEN; 
      Menu.NeuerMenuZustand();
      Anzeige.setzeStossStaerke(0);
      break;
      case STOSS: {
      if (xnor) {
      StateMaschin=BETRACHTEN; 
      Menu.NeuerMenuZustand();
      for (int i=1;i<16;i++) {
      if (KugelnImSpiel[i] && !KugelnVersenkt[i] && (Kugel[i].Pos_x()==3000)) {
      KugelnVersenkt[i]=1;
      }
      }
      Menu.NeuerMenuZustand();
      Anzeige.setzeStossStaerke(0);
      }
      } break;
      }
      }
    */

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) Maustaste=GLUT_LEFT_BUTTON;
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) Maustaste=GLUT_RIGHT_BUTTON;

    if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
      Maustaste=GLUT_LEFT_BUTTON;
      switch (StateMaschin) {
      case BETRACHTEN: {  
	StateMaschin=ZIELEN; 
	Menu.NeuerMenuZustand();
	Kamera.BlickeAuf(Kugel[0].Pos_xCM(),Kugel[0].Pos_yCM());
      } break;
      case ZIELEN: {
	AusholStartzeit=Zeit();
	StateMaschin=AUSHOLEN; 
	Menu.NeuerMenuZustand();
      } break;      
      case STOSS: {
	if (xnor) {
	  for (int Kugelnr=0;Kugelnr<16;Kugelnr++) { // Alle Kugeln ans Ziel
	    Kugel[Kugelnr].neuePositionD(Bewegungstabelle[Stossdauer][Kugelnr]);
	    if (KugelnImSpiel[Kugelnr] && !KugelnVersenkt[Kugelnr] && (Kugel[Kugelnr].Pos_x()==3000)) {
	      KugelnVersenkt[Kugelnr]=1;
	    }
	    Menu.NeuerMenuZustand();
	  }
	  if (Kugel[0].Pos_x()==3000) {
	    StateMaschin=WEISSNEU;
	    WeisseEinsetzen();
	  } else {
	    StateMaschin=BETRACHTEN;      
	    Menu.NeuerMenuZustand();
	  }
	  Anzeige.setzeStossStaerke(0);
	}
      } break;
      case WEISSNEU: {
	StateMaschin=BETRACHTEN; 
	Menu.NeuerMenuZustand();	
      } break;
      case SCHIEDSRICHTER: {
	if (LageVerbesserungKopffeld|LageVerbesserung) {
	  WeisseEinsetzen();
	  StateMaschin=WEISSNEU;
	  Menu.NeuerMenuZustand();
	} else {
	  StateMaschin=BETRACHTEN;
	  Menu.NeuerMenuZustand();
	}
      } break;
      }
    }
    
    if (button == GLUT_MIDDLE_BUTTON && state == GLUT_UP && StateMaschin==AUSHOLEN) {
      GLfloat dx=Kugel[0].Pos_xCM()-Kamera.Pos_xCM();
      GLfloat dy=Kugel[0].Pos_yCM()-Kamera.Pos_yCM();
      GLfloat Abstand=sqrt(dx*dx+dy*dy);
      Stoss(dx*AusholStaerke/Abstand,dy*AusholStaerke/Abstand);
      StateMaschin=STOSS; 
      Menu.NeuerMenuZustand();
      //Kamera.Verfolge(0);
      Kamera.BlickeAuf2(Kugel[0].Pos_xCM(),Kugel[0].Pos_yCM());
      //    Kamera.FahrtEin();
      DelayAusgleich=1;
    } 

  }
}
//Callback Funktion: Reaktion auf Mausbewegung
void Bewegung(int x, int y) {
  if (MausTasteAbgefangen) return;
  if (StateMaschin==START) return;
  if (Maustaste==GLUT_LEFT_BUTTON) {
    if ((StateMaschin==ZIELEN)||(StateMaschin==AUSHOLEN)) {
      if (InvertX) {
	Kamera.Schwenk_Rechts(MouseSpeed*(x-MouseLookLast_x),Kugel[0].Pos_xCM(),Kugel[0].Pos_yCM());
      } else {
	Kamera.Schwenk_Links(MouseSpeed*(x-MouseLookLast_x),Kugel[0].Pos_xCM(),Kugel[0].Pos_yCM());
      }
      if (InvertY) {
	Kamera.Schwenk_Hoch(MouseSpeed*(y-MouseLookLast_y),Kugel[0].Pos_xCM(),Kugel[0].Pos_yCM());
      } else {
	Kamera.Schwenk_Runter(MouseSpeed*(y-MouseLookLast_y),Kugel[0].Pos_xCM(),Kugel[0].Pos_yCM());
      }
    } else {
      if (InvertX) {
	Kamera.Dreh_Links(MouseSpeed*(x-MouseLookLast_x));
      } else {
	Kamera.Dreh_Rechts(MouseSpeed*(x-MouseLookLast_x));
      }
      if (InvertY) {
	Kamera.Dreh_Hoch(MouseSpeed*(y-MouseLookLast_y));
      } else {
	Kamera.Dreh_Runter(MouseSpeed*(y-MouseLookLast_y));
      }
    }
  } else if (Maustaste==GLUT_RIGHT_BUTTON) {
    if ((StateMaschin==ZIELEN)||(StateMaschin==AUSHOLEN)) {
      if (InvertX) {
	Kamera.Schwenk_Rechts(MouseSpeed*(x-MouseLookLast_x),Kugel[0].Pos_xCM(),Kugel[0].Pos_yCM());
      } else {
	Kamera.Schwenk_Links(MouseSpeed*(x-MouseLookLast_x),Kugel[0].Pos_xCM(),Kugel[0].Pos_yCM());
      }
      if (InvertY) {
	Kamera.Beweg_Rein(MouseSpeed*(y-MouseLookLast_y));
      } else {
	Kamera.Beweg_Raus(MouseSpeed*(y-MouseLookLast_y));
      }
    } else {
      if (InvertX) {
	Kamera.Beweg_Links(MouseSpeed*(x-MouseLookLast_x));
      } else {
	Kamera.Beweg_Rechts(MouseSpeed*(x-MouseLookLast_x));
      }
      if (InvertY) {
	Kamera.Beweg_Rein(MouseSpeed*(y-MouseLookLast_y));
      } else {
	Kamera.Beweg_Raus(MouseSpeed*(y-MouseLookLast_y));
      }
    }
  }
  
  MouseLookLast_x=x;
  MouseLookLast_y=y;
}

void Joystick(unsigned int buttons, int x, int y, int z)
{
    static unsigned int buttons_old = 0;
    unsigned int changed = buttons ^ buttons_old;
    unsigned int pressed = changed & buttons;
    unsigned int released = changed & ~buttons;
    buttons_old = buttons;
    unsigned char key = 0;

    if (changed & 1) {
        key = ' ';
    }

    Taste_Pfeil_Rechts = Taste_Pfeil_Links = Taste_Pfeil_Oben = Taste_Pfeil_Unten = 0;
    if (x > 10) {
      Taste_Pfeil_Rechts = 1;
    } else if (x < -10) {
      Taste_Pfeil_Links = 1;
    }

    if (y > 10) {
      Taste_Pfeil_Oben = 1;
    } else if (y < -10) {
      Taste_Pfeil_Unten = 1;
    }

    if (key) {
        if (pressed) Taste(key, 0, 0);
        else TasteLos(key, 0, 0);
    }
}

//Callback Funktion: Reaktion auf Tastendruck
void Taste( unsigned char keyPressed, int x, int y )
{
  //printf("%c: %i\n",keyPressed,keyPressed);

  if (!Menu.KeyboardTaste(keyPressed,x,y)) {
    switch( keyPressed ) {
    case 'h': {
      if (xnor==4) {
	Hintergrundfarbe=1-Hintergrundfarbe;
	glClearColor(Hintergrundfarbe,Hintergrundfarbe,Hintergrundfarbe,0);
      }
    } break;                           //h: Hintergrundfarbe invertieren
    case 'v': {
      if (xnor==4) {
	switch (PolygonMode_view) {      //v: Vorne/Hinten/Beides
	case GL_FRONT: 
	  PolygonMode_view=GL_BACK;
	  break;
	case GL_BACK: 
	  PolygonMode_view=GL_FRONT_AND_BACK;
	  break;
	case GL_FRONT_AND_BACK: 
	  PolygonMode_view=GL_FRONT;
	  break;
	} 
	glPolygonMode(PolygonMode_view,PolygonMode_mode);
      }
    } break;
    case 'w': {
      if (xnor==4) {
	switch (PolygonMode_mode) {     //w: Punkte/Linien/Fl"achen
	case GL_FILL: PolygonMode_mode=GL_POINT;break;
	case GL_POINT: PolygonMode_mode=GL_LINE;break;
	case GL_LINE: PolygonMode_mode=GL_FILL;break;
	} 
	glPolygonMode(PolygonMode_view,PolygonMode_mode);
      }
    } break;
      
    case '1': Kamera.speicherePosition(0);break; //1
    case '2': Kamera.speicherePosition(1);break; //2
    case '3': Kamera.speicherePosition(2);break; //3
    case '4': Kamera.speicherePosition(3);break; //4
    case '5': Kamera.speicherePosition(4);break; //5
    case '6': Kamera.speicherePosition(5);break; //6
    case '7': Kamera.speicherePosition(6);break; //7
    case '8': Kamera.speicherePosition(7);break; //8
      
    case '\b': {
      switch (StateMaschin) {
      case START:        
	StateMaschin=BETRACHTEN;
	Menu.NeuerMenuZustand();
	break; 
      case BETRACHTEN: {
	if (LageVerbesserungKopffeld|LageVerbesserung) {
	  StateMaschin=WEISSNEU;
	  Menu.NeuerMenuZustand();
	}
      } break; 
      case ZIELEN:       
	StateMaschin=BETRACHTEN; 
	Menu.NeuerMenuZustand();
	break;
      case AUSHOLEN:        
	StateMaschin=ZIELEN; 
	Menu.NeuerMenuZustand();
	Anzeige.setzeStossStaerke(0);
	break;
      case STOSS: {
	if (xnor) {
	  StateMaschin=BETRACHTEN; 
	  Menu.NeuerMenuZustand();
	  for (int i=1;i<16;i++) {
	    if (KugelnImSpiel[i] && !KugelnVersenkt[i] && (Kugel[i].Pos_x()==3000)) {
	      KugelnVersenkt[i]=1;
	    }
	  }
	  Menu.NeuerMenuZustand();
	  Anzeige.setzeStossStaerke(0);
	}
      } break;
      }
    } break;
    
    case 'r': {
      if (xnor==3) {
	xnor=4;
      } else if (!AllerersterStoss) {
	Startzeit=Zeit();
	//Frames=0;
	StateMaschin=STOSS;
	Menu.NeuerMenuZustand();
	for (int Kugelnr=0;Kugelnr<16;Kugelnr++) {
	  Kugel[Kugelnr].neuePositionD(Bewegungstabelle[0][Kugelnr]);
	}
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
      }
    } break;           //r
      
      
    case 'c': {
      if (xnor==4) {
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	}
    } break; //c
      
    case 27 : {
      Menu.SetzeMenuZustand(AUSSPIEL);
    } break;
      
    case 'q': {
      if (xnor==4) {
	StateMaschin=START;
	Menu.SetzeMenuZustand(STARTBILDSCHIRM);
      }
    } break; 
      
    case 'f': {
      /*
	(FullScreen=1-FullScreen);
	if (FullScreen) {
	glutFullScreen();
	} else {
	glutReshapeWindow(800, 600);
	}
      */
    } break;
    /*
    //      if (xnor==4) {
    (FullScreen=1-FullScreen);
    if (FullScreen) {
    glutFullScreen();
    //glutGameModeString("640x480:16@60");
    //glutEnterGameMode();
    //AktuellesFenster=glutGetWindow();
    //glutIgnoreKeyRepeat(1);
    //glutMouseFunc(Maus);
    //glutMotionFunc(Bewegung);
    //glutKeyboardFunc(Taste);
    //glutKeyboardUpFunc(TasteLos);
    //glutSpecialFunc(Sondertaste);
    //glutSpecialUpFunc(SondertasteLos);
    //glutIdleFunc(timerEvent);
    //glutDisplayFunc(updateGL);
    //glutVisibilityFunc(Sichtbar);        
    //      CreateMenu();
    } else {
    glutReshapeWindow(800, 600);
    if (OriginalFenster != 0 && AktuellesFenster != OriginalFenster) {
    glutLeaveGameMode();
    AktuellesFenster=OriginalFenster;
    }
    }  
    }
    } break;
    */
    case 127: {
      Taste_Strg=1;
    } break;
    case 'x': {
      if (xnor==0) {
	xnor=1;
      }
    } break;
    case 'o': {
      if (xnor==2) {
	xnor=3;
      }
    } break;
    case 'z': {
      if (xnor==4) {
	Spiel=ZUFALL;  
	SpielfeldAufbau();
      }
    } break;//z
    case 'a': {
      if (xnor==4) {
	Spiel=ACHTBALL;
	SpielfeldAufbau();
	Schiedsrichter.NeuesSpiel(Spiel);
      }
    } break;//a
    case 'n': {
      if (xnor==1) {
	xnor=2;
      }
      if (xnor==4) {
	Spiel=NEUNBALL;
	SpielfeldAufbau();
	Schiedsrichter.NeuesSpiel(Spiel);
      } 
    } break;//n
    case '9': {
      if (xnor==4) {
	Spiel=NEUNBALL;
	SpielfeldAufbau();
	Schiedsrichter.NeuesSpiel(Spiel);
      }
    } break;//9
    case 's': {
      if (xnor==4) {
	Spiel=ZWEIBAELLE;
	SpielfeldAufbau();
      }
    } break;//s
    case 'l': {
      if (xnor==4) {
	Spiel=LEER;
	SpielfeldAufbau();
      }
    } break;//l
    case 'd': {    
      if (xnor==4) {
	GLfloat dx=Kugel[0].Pos_xCM()-Kamera.Pos_xCM();
	GLfloat dy=Kugel[0].Pos_yCM()-Kamera.Pos_yCM();
	GLfloat Abstand=sqrt(dx*dx+dy*dy);
	Stoss(dx*80.0/Abstand,dy*80.0/Abstand);
      }
    } break;//d
    case 'e': {    
      if (xnor==4) {
	GLfloat dx=Kugel[0].Pos_xCM()-Kamera.Pos_xCM();
	GLfloat dy=Kugel[0].Pos_yCM()-Kamera.Pos_yCM();
	GLfloat Abstand=sqrt(dx*dx+dy*dy);
	Stoss(dx*80.0/Abstand,dy*80.0/Abstand);
	StateMaschin=STOSS; 
	Menu.NeuerMenuZustand();
	Kamera.BlickeAuf2(Kugel[0].Pos_xCM(),Kugel[0].Pos_yCM());
	//Kamera.Verfolge(0);
	DelayAusgleich=1;
      }
    } break;//e
    case ' ': {  
      switch (StateMaschin) {
      case BETRACHTEN:   
	StateMaschin=ZIELEN; 
	Menu.NeuerMenuZustand();
	Kamera.BlickeAuf(Kugel[0].Pos_xCM(),Kugel[0].Pos_yCM());
	break;
      case ZIELEN:       
	AusholStartzeit=Zeit();
	StateMaschin=AUSHOLEN; 
	Menu.NeuerMenuZustand();
	break;      
      case STOSS: {
	if (xnor) {
	  for (int Kugelnr=0;Kugelnr<16;Kugelnr++) { // Alle Kugeln ans Ziel
	    Kugel[Kugelnr].neuePositionD(Bewegungstabelle[Stossdauer][Kugelnr]);
	  }
	  if (Kugel[0].Pos_x()==3000) {
	    StateMaschin=WEISSNEU;
	    WeisseEinsetzen();
	    Menu.NeuerMenuZustand();
	  } else {
	    StateMaschin=BETRACHTEN;      
	    Menu.NeuerMenuZustand();
	  } 
	}
      } break;
      case WEISSNEU: {    
	StateMaschin=BETRACHTEN; 
	Menu.NeuerMenuZustand();
      } break;
      case SCHIEDSRICHTER: {
	if (LageVerbesserungKopffeld|LageVerbesserung) {
	  WeisseEinsetzen();
	  StateMaschin=WEISSNEU;
	  Menu.NeuerMenuZustand();
	} else {
	  StateMaschin=BETRACHTEN;
	  Menu.NeuerMenuZustand();
	}
      } break;
      }
    } 
    }
  }
}


void TasteLos( unsigned char keyPressed, int,int) {

  if ((keyPressed==' ')&&
      (StateMaschin==AUSHOLEN)) {
    GLfloat dx=Kugel[0].Pos_xCM()-Kamera.Pos_xCM();
    GLfloat dy=Kugel[0].Pos_yCM()-Kamera.Pos_yCM();
    GLfloat Abstand=sqrt(dx*dx+dy*dy);
    Stoss(dx*AusholStaerke/Abstand,dy*AusholStaerke/Abstand);
    StateMaschin=STOSS; 
    Menu.NeuerMenuZustand();
    Kamera.BlickeAuf2(Kugel[0].Pos_xCM(),Kugel[0].Pos_yCM());
    //Kamera.Verfolge(0);
    DelayAusgleich=1;
  } 
  if (keyPressed==127) {
    Taste_Strg=0;
  }

}


void Sondertaste(int Taste,int x, int y) {

  x=y;

  //printf("%i\n",Taste);

  //  Kamera.FahrtAus();

  if (StateMaschin!=START) {

    switch (Taste) {
    case GLUT_KEY_F1:    
      if (StateMaschin!=AUSHOLEN) {
	if (StateMaschin!=STOSS && StateMaschin!=WEISSNEU && StateMaschin!=SCHIEDSRICHTER) {
	  StateMaschin=BETRACHTEN;
	  Menu.NeuerMenuZustand();
	}
	Kamera.ladePosition(0);
      }
      break;
    case GLUT_KEY_F2:    
      if (StateMaschin!=AUSHOLEN) {
	if (StateMaschin!=STOSS && StateMaschin!=WEISSNEU && StateMaschin!=SCHIEDSRICHTER) {
	  StateMaschin=BETRACHTEN;
	  Menu.NeuerMenuZustand();
	}
	Kamera.ladePosition(1);
      }
      break;
    case GLUT_KEY_F3:    
      if (StateMaschin!=AUSHOLEN) {
	if (StateMaschin!=STOSS && StateMaschin!=WEISSNEU && StateMaschin!=SCHIEDSRICHTER) {
	  StateMaschin=BETRACHTEN;
	  Menu.NeuerMenuZustand();
	}
	Kamera.ladePosition(2);
      }
      break;
    case GLUT_KEY_F4:    
      if (StateMaschin!=AUSHOLEN) {
	if (StateMaschin!=STOSS && StateMaschin!=WEISSNEU && StateMaschin!=SCHIEDSRICHTER) {
	  StateMaschin=BETRACHTEN;
	  Menu.NeuerMenuZustand();
	}
	Kamera.ladePosition(3);
      }
      break;
    case GLUT_KEY_F5:    
      if (StateMaschin!=AUSHOLEN) {
	if (StateMaschin!=STOSS && StateMaschin!=WEISSNEU && StateMaschin!=SCHIEDSRICHTER) {
	  StateMaschin=BETRACHTEN;
	  Menu.NeuerMenuZustand();
	}
	Kamera.ladePosition(4);
      }
      break;
    case GLUT_KEY_F6:    
      if (StateMaschin!=AUSHOLEN) {
	if (StateMaschin!=STOSS && StateMaschin!=WEISSNEU && StateMaschin!=SCHIEDSRICHTER) {
	  StateMaschin=BETRACHTEN;
	  Menu.NeuerMenuZustand();
	}
	Kamera.ladePosition(5);
      }
      break;
    case GLUT_KEY_F7:    
      if (StateMaschin!=AUSHOLEN) {
	if (StateMaschin!=STOSS && StateMaschin!=WEISSNEU && StateMaschin!=SCHIEDSRICHTER) {
	  StateMaschin=BETRACHTEN;
	  Menu.NeuerMenuZustand();
	}
	Kamera.ladePosition(6);
      }
      break;
    case GLUT_KEY_F8:    
      if (StateMaschin!=AUSHOLEN) {
	if (StateMaschin!=STOSS && StateMaschin!=WEISSNEU && StateMaschin!=SCHIEDSRICHTER) {
	  StateMaschin=BETRACHTEN;
	  Menu.NeuerMenuZustand();
	}
	Kamera.ladePosition(7);
      }
      break;

    case 108: {
      Taste_Shift=1;
    } break;
    case GLUT_KEY_UP: 
      Taste_Pfeil_Oben=1; 
      break;
    case GLUT_KEY_DOWN: 
      Taste_Pfeil_Unten=1; 
      break;
    case GLUT_KEY_RIGHT:
      Taste_Pfeil_Rechts=1; 
      break;
    case GLUT_KEY_LEFT: 
      Taste_Pfeil_Links=1; 
      break;
    case GLUT_KEY_PAGE_UP:
      Taste_Bild_Auf=1; 
      break;
    case GLUT_KEY_PAGE_DOWN:
      Taste_Bild_Ab=1; 
      break;
    case GLUT_KEY_HOME: 
      if (xnor) Taste_Pos1=1; 
      break;
    case GLUT_KEY_END: 
      if (xnor) Taste_Ende=1; 
      break;
    }
  }
}


void SondertasteLos(int Taste,int x, int y) {

  x=y;

  if (StateMaschin!=START) {

    switch (Taste) {
    case 108: {
      Taste_Shift=0;
    } break;
    case GLUT_KEY_UP: 
      Taste_Pfeil_Oben=0; 
      break;
    case GLUT_KEY_DOWN: 
      Taste_Pfeil_Unten=0; 
      break;
    case GLUT_KEY_RIGHT:
      Taste_Pfeil_Rechts=0; 
      break;
    case GLUT_KEY_LEFT: 
      Taste_Pfeil_Links=0; 
      break;
    case GLUT_KEY_PAGE_UP:
      Taste_Bild_Auf=0; 
      break;
    case GLUT_KEY_PAGE_DOWN:
      Taste_Bild_Ab=0; 
      break;
    case GLUT_KEY_HOME: 
      Taste_Pos1=0; 
      break;
    case GLUT_KEY_END: 
      Taste_Ende=0; 
      break;
    }
  }
}
