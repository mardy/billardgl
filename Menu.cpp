/****************************************************************************
**
**  Menu.cpp   Stefan Disch, Tobias Nopper, Martina Welte 2001
**
*****************************************************************************/

#include <math.h>
#include <stdlib.h>
#include <stdio.h> //2CHANGE wieder raus wenn kein printf mehr drin
#include <GL/glut.h>

#include "LA.h"                // Zum Handling von .bmp-Files bzw. Matrix-Bildern
#include "bmp.h"
#include "Kamera.h"
#include "Kugel.h"
#include "Tisch.h"
#include "Anzeige.h"
#include "Schiedsrichter.h"
#include "Schild.h"
#include "Textfeld.h"
#include "Beleuchtung.h"

#include "SpielfeldAufbau.h"
#include "KommandoZeilenParameter.h"
#include "Einsetzen.h"
#include "kugeltabellen.h"
#include "Benutzerschnittstelle.h"
#include "BillardGL.h"

#include "Menu.h"

#include "Namen.h"

//#include "createTexture.h"   // Funktion zum Generieren einer Textur aus einem 
                               // Matrix-Bild (aus "Ubungen)


/* --------- Konstruktor ---------- */
Menu::Menu() {
  //
  for (GLint TextfeldNr=0; TextfeldNr < 1000 ; TextfeldNr++ ) {
    TextfeldArray[TextfeldNr] = 0;
  }

  TDL=0;
}

void Menu::Update(GLint Faktor) {

  if (!InAnimation) {
    return;
  } else {
    
    Animationszeit+=Faktor;
    if (Animationszeit>=ANIMATIONSDAUER) {
      Animationszeit=ANIMATIONSDAUER;
      InAnimation=0;
    }
    
    for (GLint SchildNr=0;SchildNr<SchildAnzahl;SchildNr++) {
      SchildArray[SchildNr]->Animiere(Faktor);
    }
    
    for (GLint TextfeldNr=0;TextfeldNr<1000;TextfeldNr++) {
      if( TextfeldArray[TextfeldNr] )
	TextfeldArray[TextfeldNr]->Animiere(Faktor);
    }
    
  }
}

void Menu::male() {

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0,16.0,0.0,12.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  for (GLint SchildNr=0;SchildNr<SchildAnzahl;SchildNr++) {
    SchildArray[SchildNr]->male();
  }

  for (GLint TextfeldNr=0;TextfeldNr<1000;TextfeldNr++) {
    if( TextfeldArray[TextfeldNr] )
      TextfeldArray[TextfeldNr]->male();
  }
  
}

void Menu::ladeSprache(GLint Sprache) {
  char wort[2000];
  char temp[2000];
  int index;
 
  FILE *f;
  char dateiname[1000];
#ifndef _WIN32
  sprintf(dateiname,"lang/%s%i.lang",PFAD,Sprache);
  f=fopen(dateiname,"r");
#endif
#ifdef _WIN32
  sprintf(dateiname,"lang/%i.lang",Sprache);
  f=fopen(dateiname,"rb");
#endif
  if (f) {
    GLint nummer;
    while (!feof(f)) {
      for (int j=0 ; j<2000 ; j++ ) {
	temp[j]=0;
	wort[j]=0;
      }
      fgets(temp,2000,f);
      int i=0;
      while (temp[i]) i++;
      while ((temp[--i]==10 || temp[i]==13 || temp[i]==32) && i) temp[i]=0;
      if (sscanf(temp,"%d %n",&nummer,&index)<1) continue;

      //printf("."); fflush(stdout);

      i=0;
      while (temp[index+i]) {
	wort[i]=temp[index+i];
	i++;
      }
      wort[index+i]=0;
      
      if (temp[0]) {
        if (TextfeldArray[nummer]) {
	  TextfeldArray[nummer]->SetzeTextKDL(wort);
	} else {
	  TextfeldArray[nummer] = new Textfeld();
	  TextfeldArray[nummer]->InitialisiereKDL(TDL,wort);
	}
      }     
    }
    fclose(f);
  }
}

void Menu::Initialisiere(GLint Texturgroesse) {

  if (!TDL) { 
    TDL=dummyTextfeld.dummyInitialisiere(Texturgroesse);
    return;
  }

  //printf(" Loading languages\n");
  ladeSprache(900); //Deutsch zuerst
  ladeSprache(901); //drueber Englisch als default
  ladeSprache(999); //Sprachenuebersicht

  if (Sprache) ladeSprache(Sprache);

  //Tutorial-Texta auf Breite 31.2 
  for (GLint tf=640 ; tf < 700 ; tf++ ) {
    if (!TextfeldArray[tf]) continue;
    TextfeldArray[tf]->SetzeMaxBreite(31.2);
  }

  //Regeln-Text auf Breite 24
  for (GLint tf2=700 ; tf2 < 800 ; tf2++ ) {
    if (!TextfeldArray[tf2]) continue;
    TextfeldArray[tf2]->SetzeMaxBreite(26);
  }

  //printf("\n\n Generating Menu Display Lists\n");

  for (GLint dl=0 ; dl < 1000 ; dl++ ) {
    if (!TextfeldArray[dl]) continue;
    TextfeldArray[dl]->GeneriereDisplayList();
    //printf("."); fflush(stdout);
  }

  //printf("\n\n");

  TextfeldArray[T_SPIELER1NAME]->SetzeText(Spieler1);

  TextfeldArray[T_SPIELER2NAME]->SetzeText(Spieler2);

  if (TextfeldArray[T_FPS]) 
    TextfeldArray[T_FPS]->SetzeText("0 fps");
  else {
    TextfeldArray[T_FPS] = new Textfeld();
    TextfeldArray[T_FPS]->Initialisiere(TDL,"0 fps");
  }

  SchildAnzahl=0;

  menuhintergrund.Initialisiere();
  SchildArray[SchildAnzahl++]=&menuhintergrund;

  logo.InitialisiereLogo();
  SchildArray[SchildAnzahl++]=&logo;

  ball[0].Initialisiere(1,"a00","aalpha");
  SchildArray[SchildAnzahl++]=&ball[0];
  ball[1].Initialisiere(1,"a1","aalpha");
  SchildArray[SchildAnzahl++]=&ball[1];
  ball[2].Initialisiere(1,"a2","aalpha");
  SchildArray[SchildAnzahl++]=&ball[2];
  ball[3].Initialisiere(1,"a3","aalpha");
  SchildArray[SchildAnzahl++]=&ball[3];
  ball[4].Initialisiere(1,"a4","aalpha");
  SchildArray[SchildAnzahl++]=&ball[4];
  ball[5].Initialisiere(1,"a5","aalpha");
  SchildArray[SchildAnzahl++]=&ball[5];
  ball[6].Initialisiere(1,"a6","aalpha");
  SchildArray[SchildAnzahl++]=&ball[6];
  ball[7].Initialisiere(1,"a7","aalpha");
  SchildArray[SchildAnzahl++]=&ball[7];
  ball[8].Initialisiere(1,"a8","aalpha");
  SchildArray[SchildAnzahl++]=&ball[8];
  ball[9].Initialisiere(1,"a9","aalpha");
  SchildArray[SchildAnzahl++]=&ball[9];
  ball[10].Initialisiere(1,"a10","aalpha");
  SchildArray[SchildAnzahl++]=&ball[10];
  ball[11].Initialisiere(1,"a11","aalpha");
  SchildArray[SchildAnzahl++]=&ball[11];
  ball[12].Initialisiere(1,"a12","aalpha");
  SchildArray[SchildAnzahl++]=&ball[12];
  ball[13].Initialisiere(1,"a13","aalpha");
  SchildArray[SchildAnzahl++]=&ball[13];
  ball[14].Initialisiere(1,"a14","aalpha");
  SchildArray[SchildAnzahl++]=&ball[14];
  ball[15].Initialisiere(1,"a15","aalpha");
  SchildArray[SchildAnzahl++]=&ball[15];

  volle.Initialisiere(Texturgroesse,"volle","aalpha2");
  SchildArray[SchildAnzahl++]=&volle;
  halbe.Initialisiere(Texturgroesse,"halbe","aalpha2");
  SchildArray[SchildAnzahl++]=&halbe;

  //GameStar.Initialisiere(1,"gamestar",1); //Gamestar
  //SchildArray[SchildAnzahl++]=&GameStar;


  if (!MenuZustand) {MenuZustand=STARTBILDSCHIRM;}

  NeuerMenuZustand();
  StarteAnimation();
  
  MenuGesperrt=0;

}

GLint Menu::Maustaste(int Taste,int Richtung,int x,int y){

  StarteAnimation();

  GLint Signal=0;
  GLint SchildNr=0;
  GLint TextfeldNr=0;

  while (!Signal && SchildNr<SchildAnzahl) {
    Signal=SchildArray[SchildNr++]->Maustaste(Taste,Richtung,x,y);
  }

  for (TextfeldNr=0 ; TextfeldNr<1000; TextfeldNr++) {
    if (Signal) break;
    if (TextfeldArray[TextfeldNr]) 
      Signal=TextfeldArray[TextfeldNr]->Maustaste(Taste,Richtung,x,y);
  }

  if (Signal>0) {
    SignalAusfuehrung(Signal);
  }

  if (MenuZustand==STARTBILDSCHIRM &&
      Richtung==GLUT_UP) {
    if (Sprache) SetzeMenuZustand(HAUPTMENU);
    else SetzeMenuZustand(SPRACHAUSWAHL);
    return 1;
  }

  if (MenuGesperrt || 
      MenuZustand!=SPIEL) {
    return 1;
  }

  return Signal;
}

void Menu::StarteAnimation() {
  InAnimation=1;
  Animationszeit=0;
}

void Menu::SetzeMenuZustand(GLint NeuerZustand) {
  MenuZustand=NeuerZustand;
  NeuerMenuZustand();
}

void Menu::NeuerMenuZustand(){

  for (GLint SchildNr=0;SchildNr<SchildAnzahl;SchildNr++) {
    SchildArray[SchildNr]->Desaktiviere();
  }

  for (GLint TextfeldNr=0;TextfeldNr<1000;TextfeldNr++) {
    if( TextfeldArray[TextfeldNr] )
      TextfeldArray[TextfeldNr]->Desaktiviere();
  }

  if (ZeigeFPS) TextfeldArray[T_FPS]->Positioniere(0,11.7,.3,A_LINKS);

  switch (MenuZustand) {

  case STARTBILDSCHIRM: {

    //GameStar.Positioniere(6,5,10,6);
    //GameStar.Positioniere(6,5,10,6);
	  
    logo.PositioniereFix(4,6,12,8);
    //logo.Positioniere(4,6,12,8);

	//TextfeldArray[790]->Positioniere(3.8,5,1,A_RECHTS);
	//TextfeldArray[790]->Positioniere(3.8,5,1,A_RECHTS);
	//TextfeldArray[791]->Positioniere(10.2,5,1,A_LINKS);
	//TextfeldArray[791]->Positioniere(10.2,5,1,A_LINKS);

    TextfeldArray[T_NAMEN1]->Positioniere(8,1.4,.5,A_MITTE);
    TextfeldArray[T_NAMEN2]->Positioniere(8,1.0,.5,A_MITTE);
    TextfeldArray[T_NOWARRANTY]->Positioniere(8,0,.5,A_MITTE);
    TextfeldArray[T_HOMEPAGE]->Positioniere(15.9,0,.5,A_RECHTS);
    TextfeldArray[T_VERSION]->Positioniere(.1,0,.5,A_LINKS);

  } break;
    
  case SPRACHAUSWAHL: {

    menuhintergrund.Positioniere(2,2.5,14,8.5);
    logo.Positioniere(5,9,11,11);
    logo.VollSichtbar();

    TextfeldArray[T_SPRACHAUSWAHL]->Positioniere(8,8,1,A_MITTE);
    TextfeldArray[T_SPRACHAUSWAHL]->VollSichtbar();
    GLfloat Pos_y=7;
    for (GLint TextfeldNr=900;TextfeldNr<1000;TextfeldNr++) {
      if ( TextfeldArray[TextfeldNr] ) {
	TextfeldArray[TextfeldNr]->Positioniere(8,Pos_y,.71,A_MITTE);
	TextfeldArray[TextfeldNr]->SetzeSignal(TextfeldNr);
	Pos_y-=.5;
      }
    }

    if (Sprache) {
      TextfeldArray[T_ZURUECK]->Positioniere(8,1,1,A_MITTE);
      TextfeldArray[T_ZURUECK]->SetzeSignal(S_HM_EINSTELLUNGEN);
    }
    TextfeldArray[T_HOMEPAGE]->Positioniere(15.9,0,.5,A_RECHTS);
    TextfeldArray[T_VERSION]->Positioniere(.1,0,.5,A_LINKS);
  } break;

  case HAUPTMENU: {

    menuhintergrund.Positioniere(2,2.5,14,8.5);

    logo.Positioniere(5,9,11,11);
    logo.VollSichtbar();
    logo.SetzeSignal(S_LOGO);

    TextfeldArray[T_HAUPTMENU]->Positioniere(8,8,1,A_MITTE);
    TextfeldArray[T_HAUPTMENU]->VollSichtbar();

    TextfeldArray[T_TRAINING]->Positioniere(5.5,6,1,A_MITTE);
    TextfeldArray[T_TRAINING]->SetzeSignal(S_HM_TRAINING);

    TextfeldArray[T_ZWEISPIELER]->Positioniere(10.5,6,1,A_MITTE);
    TextfeldArray[T_ZWEISPIELER]->SetzeSignal(S_HM_ZWEISPIELER);

    TextfeldArray[T_HILFE]->Positioniere(5.5,4,1,A_MITTE);
    TextfeldArray[T_HILFE]->SetzeSignal(S_HM_HILFE);

    TextfeldArray[T_EINSTELLUNGEN]->Positioniere(10.5,4,1,A_MITTE);
    TextfeldArray[T_EINSTELLUNGEN]->SetzeSignal(S_HM_EINSTELLUNGEN);

    TextfeldArray[T_BEENDEN]->Positioniere(8,1,1,A_MITTE);
    TextfeldArray[T_BEENDEN]->SetzeSignal(S_HM_BEENDEN);

    TextfeldArray[T_HOMEPAGE]->Positioniere(15.9,0,.5,A_RECHTS);
    TextfeldArray[T_VERSION]->Positioniere(.1,0,.5,A_LINKS);
  } break;

  case TRAINING: {

    menuhintergrund.Positioniere(4,5,12,8.5);

    logo.Positioniere(4,9,12,11);
    logo.VollSichtbar();

    TextfeldArray[T_TRAINING]->Positioniere(8,8,1,A_MITTE);
    TextfeldArray[T_TRAINING]->VollSichtbar();

    TextfeldArray[T_ACHTBALL]->Positioniere(6.5,6,1,A_MITTE);
    TextfeldArray[T_ACHTBALL]->SetzeSignal(S_TR_ACHTBALL);
      
    TextfeldArray[T_NEUNBALL]->Positioniere(9.5,6,1,A_MITTE);
    TextfeldArray[T_NEUNBALL]->SetzeSignal(S_TR_NEUNBALL);

    TextfeldArray[T_ZURUECK]->Positioniere(8,1,1,A_MITTE);
    TextfeldArray[T_ZURUECK]->SetzeSignal(S_TR_ZURUECK);

    TextfeldArray[T_HOMEPAGE]->Positioniere(15.9,0,.5,A_RECHTS);
    TextfeldArray[T_VERSION]->Positioniere(.1,0,.5,A_LINKS);
  } break;

  case ZWEISPIELER: {
    menuhintergrund.Positioniere(3,2.5,13,8.5);
    logo.Positioniere(4,9,12,11);
    logo.VollSichtbar();
    TextfeldArray[T_ZWEISPIELER]->Positioniere(8,8,1,A_MITTE);
    TextfeldArray[T_ZWEISPIELER]->VollSichtbar();
    TextfeldArray[T_SPIELER1]->Positioniere(8,6,1,A_RECHTS);
    TextfeldArray[T_SPIELER1]->SetzeSignal(S_SPIELER1HERHOEREN);
    TextfeldArray[T_SPIELER1NAME]->Positioniere(8.2,6,1,A_LINKS);
    TextfeldArray[T_SPIELER1NAME]->SetzeSignal(S_SPIELER1HERHOEREN);
    TextfeldArray[T_SPIELER2]->Positioniere(8,5,1,A_RECHTS);
    TextfeldArray[T_SPIELER2]->SetzeSignal(S_SPIELER2HERHOEREN);
    TextfeldArray[T_SPIELER2NAME]->Positioniere(8.2,5,1,A_LINKS);
    TextfeldArray[T_SPIELER2NAME]->SetzeSignal(S_SPIELER2HERHOEREN);
    TextfeldArray[T_ACHTBALL]->Positioniere(5,3,1,A_MITTE);
    TextfeldArray[T_ACHTBALL]->SetzeSignal(S_ZW_ACHTBALL);
    TextfeldArray[T_NEUNBALL]->Positioniere(11,3,1,A_MITTE);
    TextfeldArray[T_NEUNBALL]->SetzeSignal(S_ZW_NEUNBALL);
    TextfeldArray[T_ZURUECK]->Positioniere(8,1,1,A_MITTE);
    TextfeldArray[T_ZURUECK]->SetzeSignal(S_ZW_ZURUECK);

    TextfeldArray[T_HOMEPAGE]->Positioniere(15.9,0,.5,A_RECHTS);
    TextfeldArray[T_VERSION]->Positioniere(.1,0,.5,A_LINKS);
  } break;

  case EINSTELLUNGEN: {
    menuhintergrund.Positioniere(4,2.5,12,8.5);
    logo.Positioniere(4,9,12,11);
    logo.VollSichtbar();
    TextfeldArray[T_EINSTELLUNGEN]->Positioniere(8,8,1,A_MITTE);
    TextfeldArray[T_EINSTELLUNGEN]->VollSichtbar();
    TextfeldArray[T_STEUERUNG]->Positioniere(8,6.5,1,A_MITTE);
    TextfeldArray[T_STEUERUNG]->SetzeSignal(S_EI_STEUERUNG);
    TextfeldArray[T_GRAFIK]->Positioniere(8,5.5,1,A_MITTE);
    TextfeldArray[T_GRAFIK]->SetzeSignal(S_EI_GRAFIK);
    TextfeldArray[T_AUDIO]->Positioniere(8,4.5,1,A_MITTE);
    TextfeldArray[T_SPRACHE]->Positioniere(8,3.5,1,A_MITTE);
    TextfeldArray[T_SPRACHE]->SetzeSignal(S_EI_SPRACHE);
    TextfeldArray[T_ZURUECK]->Positioniere(8,1,1,A_MITTE);
    if (AusSpiel) {
      TextfeldArray[T_ZURUECK]->SetzeSignal(S_EI_ZURUECK_AS);
    } else {
      TextfeldArray[T_ZURUECK]->SetzeSignal(S_EI_ZURUECK);
    }

    TextfeldArray[T_HOMEPAGE]->Positioniere(15.9,0,.5,A_RECHTS);
    TextfeldArray[T_VERSION]->Positioniere(.1,0,.5,A_LINKS);

  } break;

  case EINSTELLUNGENSTEUERUNG: {
    menuhintergrund.Positioniere(2,3.5,14,8.5);
    logo.Positioniere(4,9,12,11);
    logo.VollSichtbar();
    TextfeldArray[T_EINSTELLUNGEN]->Positioniere(4,8,1,A_LINKS);
    TextfeldArray[T_EINSTELLUNGEN]->VollSichtbar();
    TextfeldArray[T_STEUERUNG]->Positioniere(12,8,1,A_RECHTS);
    TextfeldArray[T_STEUERUNG]->VollSichtbar();

    TextfeldArray[T_MAUSGESCHWINDIGKEIT]->Positioniere(8,6,.71,A_RECHTS);
    TextfeldArray[T_MAUSGESCHWINDIGKEIT]->SetzeSignal(S_EI_MOUSESPEED);
    TextfeldArray[T_XACHSEINVERTIERT]->Positioniere(8,5.5,.71,A_RECHTS);
    TextfeldArray[T_XACHSEINVERTIERT]->SetzeSignal(S_EI_XINVERT);
    TextfeldArray[T_YACHSEINVERTIERT]->Positioniere(8,5,.71,A_RECHTS);
    TextfeldArray[T_YACHSEINVERTIERT]->SetzeSignal(S_EI_YINVERT);

    if (E_InvertX) {
      TextfeldArray[T_X_AN]->Positioniere(8.2,5.5,.71,A_LINKS);
      TextfeldArray[T_X_AN]->SetzeSignal(S_EI_XINVERT);
    } else {
      TextfeldArray[T_X_AUS]->Positioniere(8.2,5.5,.71,A_LINKS);
      TextfeldArray[T_X_AUS]->SetzeSignal(S_EI_XINVERT);
    }
    if (E_InvertY) {
      TextfeldArray[T_Y_AN]->Positioniere(8.2,5,.71,A_LINKS);
      TextfeldArray[T_Y_AN]->SetzeSignal(S_EI_YINVERT);
    } else {
      TextfeldArray[T_Y_AUS]->Positioniere(8.2,5,.71,A_LINKS);
      TextfeldArray[T_Y_AUS]->SetzeSignal(S_EI_YINVERT);
    }
    if (E_MouseSpeed<=.293) {
      TextfeldArray[T_MG_LANGSAM]->Positioniere(8.2,6,.71,A_LINKS);
      TextfeldArray[T_MG_LANGSAM]->SetzeSignal(S_EI_MOUSESPEED);
    } else if (E_MouseSpeed<=.41) {
      TextfeldArray[T_MG_NORMAL]->Positioniere(8.2,6,.71,A_LINKS);
      TextfeldArray[T_MG_NORMAL]->SetzeSignal(S_EI_MOUSESPEED);
    } else if (E_MouseSpeed<=.575) {
      TextfeldArray[T_MG_SCHNELL]->Positioniere(8.2,6,.71,A_LINKS);
      TextfeldArray[T_MG_SCHNELL]->SetzeSignal(S_EI_MOUSESPEED);
    } else {
      TextfeldArray[T_MG_SEHRSCHNELL]->Positioniere(8.2,6,.71,A_LINKS);
      TextfeldArray[T_MG_SEHRSCHNELL]->SetzeSignal(S_EI_MOUSESPEED);
    }
    if( E_MouseSpeed==MouseSpeed &&
	E_InvertX==InvertX &&
	E_InvertY==InvertY) {
      TextfeldArray[T_ZURUECK]->Positioniere(8,1,1,A_MITTE);
      TextfeldArray[T_ZURUECK]->SetzeSignal(S_EI_STEUERUNGZURUECK);
    } else {
      TextfeldArray[T_UEBERNEHMEN]->Positioniere(12,1,1,A_RECHTS);
      TextfeldArray[T_UEBERNEHMEN]->SetzeSignal(S_EI_STEUERUNGUEBERNEHMEN);
      TextfeldArray[T_ABBRECHEN]->Positioniere(4,1,1,A_LINKS);
      TextfeldArray[T_ABBRECHEN]->SetzeSignal(S_EI_STEUERUNGZURUECK);
    }

    TextfeldArray[T_HOMEPAGE]->Positioniere(15.9,0,.5,A_RECHTS);
    TextfeldArray[T_VERSION]->Positioniere(.1,0,.5,A_LINKS);
  } break;

  case EINSTELLUNGENGRAFIK: {
    if (E_KugelAufloesung==3 &&
	E_Texturgroesse==8 &&
	E_TischTexturgroesse==0 &&
	E_AnzeigeTexturgroesse==2 &&
	E_Reflektionen==0 &&
	E_BildschirmAufloesung==640 &&
	E_Farbtiefe==16 &&
	E_Schatten==0 &&
	E_TischLampen==1 &&
	E_TexMMM==0 &&
	E_GrueneLampe==0) {Qualitaet=1;}
    else if (E_KugelAufloesung==5 &&
	     E_Texturgroesse==4 &&
	     E_TischTexturgroesse==4 &&
	     E_AnzeigeTexturgroesse==2 &&
	     E_Reflektionen==0 &&
	     E_BildschirmAufloesung==640 &&
	     E_Farbtiefe==16 &&
	     E_Schatten==1 &&
	     E_TischLampen==1 &&
	     E_TexMMM==2 &&
	     E_GrueneLampe==0) {Qualitaet=2;}
    else if (E_KugelAufloesung==7 &&
	     E_Texturgroesse==2 &&
	     E_TischTexturgroesse==2 &&
	     E_AnzeigeTexturgroesse==1 &&
	     E_Reflektionen==0 &&
	     E_BildschirmAufloesung==800 &&
	     E_Farbtiefe==16 &&
	     E_Schatten==1 &&
	     E_TischLampen==2 &&
	     E_TexMMM==3 &&
	     E_GrueneLampe==0) {Qualitaet=3;}
    else if (E_KugelAufloesung==7 &&
	     E_Texturgroesse==2 &&
	     E_TischTexturgroesse==1 &&
	     E_AnzeigeTexturgroesse==1 &&
	     E_Reflektionen==1 &&
	     E_BildschirmAufloesung==1024 &&
	     E_Farbtiefe==16 &&
	     E_Schatten==1 &&
	     E_TischLampen==2 &&
	     E_TexMMM==7 &&
	     E_GrueneLampe==1) {Qualitaet=4;}
    else if (E_KugelAufloesung==11 &&
	     E_Texturgroesse==1 &&
	     E_TischTexturgroesse==1 &&
	     E_AnzeigeTexturgroesse==1 &&
	     E_Reflektionen==1 &&
	     E_BildschirmAufloesung==1024 &&
	     E_Farbtiefe==32 &&
	     E_Schatten==1 &&
	     E_TischLampen==3 &&
	     E_TexMMM==7 &&
	     E_GrueneLampe==1) {Qualitaet=5;}
    else Qualitaet=0;

    menuhintergrund.Positioniere(2,1.7,14,8.5);
    logo.Positioniere(4,9,12,11);
    logo.VollSichtbar();
    TextfeldArray[T_EINSTELLUNGEN]->Positioniere(4,8,1,A_LINKS);
    TextfeldArray[T_EINSTELLUNGEN]->VollSichtbar();
    TextfeldArray[T_GRAFIK]->Positioniere(12,8,1,A_RECHTS);
    TextfeldArray[T_GRAFIK]->VollSichtbar();

    TextfeldArray[T_QUALITAET]->Positioniere(8,7,1,A_RECHTS);
    TextfeldArray[T_QUALITAET]->SetzeSignal(S_EI_QUALITAET);

    TextfeldArray[T_BALLGEOMETRIE]->Positioniere(8,6.5,.6,A_RECHTS);
    TextfeldArray[T_BALLGEOMETRIE]->SetzeSignal(S_EI_BALLGEOMETRIE);
    TextfeldArray[T_BALLTEXTUREN]->Positioniere(8,6.1,.6,A_RECHTS);
    TextfeldArray[T_BALLTEXTUREN]->SetzeSignal(S_EI_BALLTEXTUREN);
    TextfeldArray[T_TISCHTEXTUREN]->Positioniere(8,5.7,.6,A_RECHTS);
    TextfeldArray[T_TISCHTEXTUREN]->SetzeSignal(S_EI_TISCHTEXTUREN);
    TextfeldArray[T_MENUTEXTUREN]->Positioniere(8,5.3,.6,A_RECHTS);
    TextfeldArray[T_MENUTEXTUREN]->SetzeSignal(S_EI_ANZEIGETEXTUREN);
    TextfeldArray[T_REFLEKTIONEN]->Positioniere(8,4.9,.6,A_RECHTS);
    TextfeldArray[T_REFLEKTIONEN]->SetzeSignal(S_EI_REFLEKTIONEN);
    TextfeldArray[T_AUFLOESUNG]->Positioniere(8,4.5,.6,A_RECHTS);
    TextfeldArray[T_AUFLOESUNG]->SetzeSignal(S_EI_AUFLOESUNG);
    TextfeldArray[T_FARBTIEFE]->Positioniere(8,4.1,.6,A_RECHTS);
    TextfeldArray[T_FARBTIEFE]->SetzeSignal(S_EI_FARBTIEFE);
    TextfeldArray[T_SCHATTEN]->Positioniere(8,3.7,.6,A_RECHTS);
    TextfeldArray[T_SCHATTEN]->SetzeSignal(S_EI_SCHATTEN);
    TextfeldArray[T_TEXTURINTERPOLATION]->Positioniere(8,3.3,.6,A_RECHTS);
    TextfeldArray[T_TEXTURINTERPOLATION]->SetzeSignal(S_EI_TEXTURINTERPOLATION);
    //TextfeldArray[T_AMBIENTESLICHT]->Positioniere(8,2.9,.6,A_RECHTS);
    //TextfeldArray[T_AMBIENTESLICHT]->SetzeSignal(S_EI_AMBIENTESLICHT);
    TextfeldArray[T_TISCHLAMPEN]->Positioniere(8,2.9,.6,A_RECHTS);
    TextfeldArray[T_TISCHLAMPEN]->SetzeSignal(S_EI_TISCHLAMPEN);
    TextfeldArray[T_TISCHCOLORBLEEDING]->Positioniere(8,2.5,.6,A_RECHTS);
    TextfeldArray[T_TISCHCOLORBLEEDING]->SetzeSignal(S_EI_GRUENELAMPE);
    TextfeldArray[T_FRAMERATE]->Positioniere(8,2.1,.6,A_RECHTS);
    TextfeldArray[T_FRAMERATE]->SetzeSignal(S_EI_FPS);

    //switch (E_AmbientesLicht) {
    //case 1: {
    //  TextfeldArray[T_AMBIENTESLICHTEIN]->Positioniere(8.2,2.9,.6,A_LINKS);
    //  TextfeldArray[T_AMBIENTESLICHTEIN]->SetzeSignal(S_EI_AMBIENTESLICHT);
    //} break;
    //case 0: {
    //  TextfeldArray[T_AMBIENTESLICHTAUS]->Positioniere(8.2,2.9,.6,A_LINKS);
    //  TextfeldArray[T_AMBIENTESLICHTAUS]->SetzeSignal(S_EI_AMBIENTESLICHT);
    //} break;
    //}

    switch (E_TischLampen) {
    case 1: {
      TextfeldArray[T_TISCHLAMPEN1]->Positioniere(8.2,2.9,.6,A_LINKS);
      TextfeldArray[T_TISCHLAMPEN1]->SetzeSignal(S_EI_TISCHLAMPEN);
    } break;
    case 2: {
      TextfeldArray[T_TISCHLAMPEN2]->Positioniere(8.2,2.9,.6,A_LINKS);
      TextfeldArray[T_TISCHLAMPEN2]->SetzeSignal(S_EI_TISCHLAMPEN);
    } break;
    case 3: {
      TextfeldArray[T_TISCHLAMPEN3]->Positioniere(8.2,2.9,.6,A_LINKS);
      TextfeldArray[T_TISCHLAMPEN3]->SetzeSignal(S_EI_TISCHLAMPEN);
    } break;
    }

    switch (E_GrueneLampe) {
    case 1: {
      TextfeldArray[T_TISCHCOLORBLEEDINGEIN]->Positioniere(8.2,2.5,.6,A_LINKS);
      TextfeldArray[T_TISCHCOLORBLEEDINGEIN]->SetzeSignal(S_EI_GRUENELAMPE);
    } break;
    case 0: {
      TextfeldArray[T_TISCHCOLORBLEEDINGAUS]->Positioniere(8.2,2.5,.6,A_LINKS);
      TextfeldArray[T_TISCHCOLORBLEEDINGAUS]->SetzeSignal(S_EI_GRUENELAMPE);
    } break;
    }

    switch (E_ZeigeFPS) {
    case 1: {
      TextfeldArray[T_FRAMERATEEIN]->Positioniere(8.2,2.1,.6,A_LINKS);
      TextfeldArray[T_FRAMERATEEIN]->SetzeSignal(S_EI_FPS);
    } break;
    case 0: {
      TextfeldArray[T_FRAMERATEAUS]->Positioniere(8.2,2.1,.6,A_LINKS);
      TextfeldArray[T_FRAMERATEAUS]->SetzeSignal(S_EI_FPS);
    } break;
    }

    switch (E_Schatten) {
    case 1: {
      TextfeldArray[T_S_EIN]->Positioniere(8.2,3.7,.6,A_LINKS);
      TextfeldArray[T_S_EIN]->SetzeSignal(S_EI_SCHATTEN);
    } break;
    case 0: {
      TextfeldArray[T_S_AUS]->Positioniere(8.2,3.7,.6,A_LINKS);
      TextfeldArray[T_S_AUS]->SetzeSignal(S_EI_SCHATTEN);
    } break;
    }
 
    
    switch (E_TexMMM) {
    case 0: {
      TextfeldArray[T_TI_AUS]->Positioniere(8.2,3.3,.6,A_LINKS);
      TextfeldArray[T_TI_AUS]->SetzeSignal(S_EI_TEXTURINTERPOLATION);
    } break;
    case 2: {
      TextfeldArray[T_TI_NIEDRIG]->Positioniere(8.2,3.3,.6,A_LINKS);
      TextfeldArray[T_TI_NIEDRIG]->SetzeSignal(S_EI_TEXTURINTERPOLATION);
    } break;
    case 7: {
      TextfeldArray[T_TI_HOCH]->Positioniere(8.2,3.3,.6,A_LINKS);
      TextfeldArray[T_TI_HOCH]->SetzeSignal(S_EI_TEXTURINTERPOLATION);
    } break;
    default: {
      TextfeldArray[T_TI_NORMAL]->Positioniere(8.2,3.3,.6,A_LINKS);
      TextfeldArray[T_TI_NORMAL]->SetzeSignal(S_EI_TEXTURINTERPOLATION);
    } break;
    }

    switch (Qualitaet) {
    case 1: {
      TextfeldArray[T_Q_SEHRSCHNELL]->Positioniere(8.2,7,1,A_LINKS);
      TextfeldArray[T_Q_SEHRSCHNELL]->SetzeSignal(S_EI_QUALITAET);
    }break;
    case 2: {
      TextfeldArray[T_Q_SCHNELL]->Positioniere(8.2,7,1,A_LINKS);
      TextfeldArray[T_Q_SCHNELL]->SetzeSignal(S_EI_QUALITAET);
    }break;
    case 3: {
      TextfeldArray[T_Q_NORMAL]->Positioniere(8.2,7,1,A_LINKS);
      TextfeldArray[T_Q_NORMAL]->SetzeSignal(S_EI_QUALITAET);
    }break;
    case 4: {
      TextfeldArray[T_Q_HOCH]->Positioniere(8.2,7,1,A_LINKS);
      TextfeldArray[T_Q_HOCH]->SetzeSignal(S_EI_QUALITAET);
    }break;
    case 5: {
      TextfeldArray[T_Q_SEHRHOCH]->Positioniere(8.2,7,1,A_LINKS);
      TextfeldArray[T_Q_SEHRHOCH]->SetzeSignal(S_EI_QUALITAET);
    }break;
    default: {
      TextfeldArray[T_Q_BENUTZER]->Positioniere(8.2,7,1,A_LINKS);
      TextfeldArray[T_Q_BENUTZER]->SetzeSignal(S_EI_QUALITAET);
    }break;
    }

    switch (E_BildschirmAufloesung) {
    case 640: {
      TextfeldArray[T_AUF_640x480]->Positioniere(8.2,4.5,.6,A_LINKS);
      TextfeldArray[T_AUF_640x480]->SetzeSignal(S_EI_AUFLOESUNG);
    }break;
    case 1024: {
      TextfeldArray[T_AUF_1024x768]->Positioniere(8.2,4.5,.6,A_LINKS);
      TextfeldArray[T_AUF_1024x768]->SetzeSignal(S_EI_AUFLOESUNG);
    }break;
    case 1280: {
      TextfeldArray[T_AUF_1280x960]->Positioniere(8.2,4.5,.6,A_LINKS);
      TextfeldArray[T_AUF_1280x960]->SetzeSignal(S_EI_AUFLOESUNG);
    }break;
    case 1600: {
      TextfeldArray[T_AUF_1600x1200]->Positioniere(8.2,4.5,.6,A_LINKS);
      TextfeldArray[T_AUF_1600x1200]->SetzeSignal(S_EI_AUFLOESUNG);
    }break;
     default: {
      TextfeldArray[T_AUF_800x600]->Positioniere(8.2,4.5,.6,A_LINKS);
      TextfeldArray[T_AUF_800x600]->SetzeSignal(S_EI_AUFLOESUNG);
    }break;
    }

    switch (E_Reflektionen) {
    case 1: {
      TextfeldArray[T_REF_EIN]->Positioniere(8.2,4.9,.6,A_LINKS);
      TextfeldArray[T_REF_EIN]->SetzeSignal(S_EI_REFLEKTIONEN);
    }break;
    default: {
      TextfeldArray[T_REF_AUS]->Positioniere(8.2,4.9,.6,A_LINKS);
      TextfeldArray[T_REF_AUS]->SetzeSignal(S_EI_REFLEKTIONEN);
    }break;
    }

    switch (E_Farbtiefe) {
    case 32: {
      TextfeldArray[T_FT_32]->Positioniere(8.2,4.1,.6,A_LINKS);
      TextfeldArray[T_FT_32]->SetzeSignal(S_EI_FARBTIEFE);
    }break;
    default: {
      TextfeldArray[T_FT_16]->Positioniere(8.2,4.1,.6,A_LINKS);
      TextfeldArray[T_FT_16]->SetzeSignal(S_EI_FARBTIEFE);
    }break;
    }
    switch (E_AnzeigeTexturgroesse) {
    case 1: {
      TextfeldArray[T_MT_NORMAL]->Positioniere(8.2,5.3,.6,A_LINKS);
      TextfeldArray[T_MT_NORMAL]->SetzeSignal(S_EI_ANZEIGETEXTUREN);
    }break;
    case 2: {
      TextfeldArray[T_MT_NIEDRIG]->Positioniere(8.2,5.3,.6,A_LINKS);
      TextfeldArray[T_MT_NIEDRIG]->SetzeSignal(S_EI_ANZEIGETEXTUREN);
    }break;
    }
    switch (E_Texturgroesse) {
    case 1: {
      TextfeldArray[T_BT_HOCH]->Positioniere(8.2,6.1,.6,A_LINKS);
      TextfeldArray[T_BT_HOCH]->SetzeSignal(S_EI_BALLTEXTUREN);
    }break;
    case 2: {
      TextfeldArray[T_BT_NORMAL]->Positioniere(8.2,6.1,.6,A_LINKS);
      TextfeldArray[T_BT_NORMAL]->SetzeSignal(S_EI_BALLTEXTUREN);
    }break;
    case 4: {
      TextfeldArray[T_BT_NIEDRIG]->Positioniere(8.2,6.1,.6,A_LINKS);
      TextfeldArray[T_BT_NIEDRIG]->SetzeSignal(S_EI_BALLTEXTUREN);
    }break;
    case 8: {
      TextfeldArray[T_BT_SEHRNIEDRIG]->Positioniere(8.2,6.1,.6,A_LINKS);
      TextfeldArray[T_BT_SEHRNIEDRIG]->SetzeSignal(S_EI_BALLTEXTUREN);
    }break;
    }
    switch (E_TischTexturgroesse) {
    case 1: {
      TextfeldArray[T_TT_HOCH]->Positioniere(8.2,5.7,.6,A_LINKS);
      TextfeldArray[T_TT_HOCH]->SetzeSignal(S_EI_TISCHTEXTUREN);
    }break;
    case 2: {
      TextfeldArray[T_TT_NORMAL]->Positioniere(8.2,5.7,.6,A_LINKS);
      TextfeldArray[T_TT_NORMAL]->SetzeSignal(S_EI_TISCHTEXTUREN);
    }break;
    case 4: {
      TextfeldArray[T_TT_NIEDRIG]->Positioniere(8.2,5.7,.6,A_LINKS);
      TextfeldArray[T_TT_NIEDRIG]->SetzeSignal(S_EI_TISCHTEXTUREN);
    }break;
    case 8: {
      TextfeldArray[T_TT_SEHRNIEDRIG]->Positioniere(8.2,5.7,.6,A_LINKS);
      TextfeldArray[T_TT_SEHRNIEDRIG]->SetzeSignal(S_EI_TISCHTEXTUREN);
    }break;
    case 0: {
      TextfeldArray[T_TT_AUS]->Positioniere(8.2,5.7,.6,A_LINKS);
      TextfeldArray[T_TT_AUS]->SetzeSignal(S_EI_TISCHTEXTUREN);
    }break;
    }

    switch (E_KugelAufloesung) {
    case 3: {
      TextfeldArray[T_BG_SEHRNIEDRIG]->Positioniere(8.2,6.5,.6,A_LINKS);
      TextfeldArray[T_BG_SEHRNIEDRIG]->SetzeSignal(S_EI_BALLGEOMETRIE);
    }break;
    case 5: {
      TextfeldArray[T_BG_NIEDRIG]->Positioniere(8.2,6.5,.6,A_LINKS);
      TextfeldArray[T_BG_NIEDRIG]->SetzeSignal(S_EI_BALLGEOMETRIE);
    }break;
    case 7: {
      TextfeldArray[T_BG_NORMAL]->Positioniere(8.2,6.5,.6,A_LINKS);
      TextfeldArray[T_BG_NORMAL]->SetzeSignal(S_EI_BALLGEOMETRIE);
    }break;
    case 11: {
      TextfeldArray[T_BG_HOCH]->Positioniere(8.2,6.5,.6,A_LINKS);
      TextfeldArray[T_BG_HOCH]->SetzeSignal(S_EI_BALLGEOMETRIE);
    }break;
    }

    if( E_Texturgroesse==Texturgroesse &&
	E_AnzeigeTexturgroesse==AnzeigeTexturgroesse &&
	E_TischTexturgroesse==TischTexturgroesse &&
	E_KugelAufloesung==KugelAufloesung &&
	E_BildschirmAufloesung==BildschirmAufloesung &&
	E_Farbtiefe==Farbtiefe &&
	E_Reflektionen==Reflektionen &&
	E_Schatten==Schatten &&
	E_AmbientesLicht==AmbientesLicht &&
	E_TischLampen==TischLampen &&
	E_TexMMM==TexMMM &&
	E_GrueneLampe==GrueneLampe) {
      TextfeldArray[T_ZURUECK]->Positioniere(8,.7,1,A_MITTE);
      TextfeldArray[T_ZURUECK]->SetzeSignal(S_EI_GRAFIKZURUECK);
    } else {
      TextfeldArray[T_UEBERNEHMEN]->Positioniere(4,0.7,1,A_LINKS);
      TextfeldArray[T_UEBERNEHMEN]->SetzeSignal(S_EI_GRAFIKUEBERNEHMEN);
      TextfeldArray[T_ABBRECHEN]->Positioniere(12,0.7,1,A_RECHTS);
      TextfeldArray[T_ABBRECHEN]->SetzeSignal(S_EI_GRAFIKZURUECK);
    }
    TextfeldArray[T_HOMEPAGE]->Positioniere(15.9,0,.5,A_RECHTS);
    TextfeldArray[T_VERSION]->Positioniere(.1,0,.5,A_LINKS);
  } break;

  case EINSTELLUNGENGRAFIKHINWEIS: {
    menuhintergrund.Positioniere(2,3.5,14,8.5);
    logo.Positioniere(4,9,12,11);
    logo.VollSichtbar();
    TextfeldArray[T_HINWEIS]->Positioniere(8,8,1,A_MITTE);
    TextfeldArray[T_HINWEIS]->VollSichtbar();
    
    TextfeldArray[T_HINWEIS1]->Positioniere(8,6,.7,A_MITTE);
    TextfeldArray[T_HINWEIS2]->Positioniere(8,5.5,.7,A_MITTE);

    TextfeldArray[T_OK]->Positioniere(8,1,1,A_MITTE);
    TextfeldArray[T_OK]->SetzeSignal(S_EI_GRAFIKUEBERNEHMEN);

    TextfeldArray[T_HOMEPAGE]->Positioniere(15.9,0,.5,A_RECHTS);
    TextfeldArray[T_VERSION]->Positioniere(.1,0,.5,A_LINKS);
  } break;

  case HILFE: {
    menuhintergrund.Positioniere(4.5,3.5,11.5,8.5);
    logo.Positioniere(4,9,12,11);
    logo.VollSichtbar();
    TextfeldArray[T_HILFE]->Positioniere(8,8,1,A_MITTE);
    TextfeldArray[T_HILFE]->VollSichtbar();
    
    TextfeldArray[T_H_TUTORIAL]->Positioniere(8,6.5,1,A_MITTE);
    TextfeldArray[T_H_TUTORIAL]->SetzeSignal(S_H_TUTORIAL);

    TextfeldArray[T_H_TASTENBELEGUNGEN]->Positioniere(8,5.5,1,A_MITTE);
    TextfeldArray[T_H_TASTENBELEGUNGEN]->SetzeSignal(S_H_TASTENBELEGUNGEN);

    TextfeldArray[T_H_BILLARDREGELN]->Positioniere(8,4.5,1,A_MITTE);
    TextfeldArray[T_H_BILLARDREGELN]->SetzeSignal(S_H_BILLARDREGELN);

    TextfeldArray[T_ZURUECK]->Positioniere(8,1,1,A_MITTE);
    if (AusSpiel) {
      TextfeldArray[T_ZURUECK]->SetzeSignal(S_BE_ZURUECK_AS);
    } else {
      TextfeldArray[T_ZURUECK]->SetzeSignal(S_BE_ZURUECK);
    }

    TextfeldArray[T_HOMEPAGE]->Positioniere(15.9,0,.5,A_RECHTS);
    TextfeldArray[T_VERSION]->Positioniere(.1,0,.5,A_LINKS);

  } break;

  case HILFETASTENBELEGUNGEN: {
    menuhintergrund.Positioniere(.5,1,15.5,10.5);
    logo.Positioniere(0,11,4,12);
    logo.VollSichtbar();
    TextfeldArray[T_HILFE]->Positioniere(4,11.4,.6,A_LINKS);
    TextfeldArray[T_HILFE]->VollSichtbar();
    TextfeldArray[T_H_TASTENBELEGUNGEN]->Positioniere(4,11,.6,A_LINKS);
    TextfeldArray[T_H_TASTENBELEGUNGEN]->VollSichtbar();

    TextfeldArray[600]->Positioniere(1.25,9.5,.7,A_LINKS);
    TextfeldArray[601]->Positioniere(1.5,9.166666,.5,A_LINKS);
    TextfeldArray[602]->Positioniere(1.25,8.5,.7,A_LINKS);
    TextfeldArray[603]->Positioniere(1.5,8.166666,.5,A_LINKS);
    TextfeldArray[604]->Positioniere(1.25,7.5,.7,A_LINKS);
    TextfeldArray[605]->Positioniere(1.5,7.166666,.5,A_LINKS);

    TextfeldArray[606]->Positioniere(1.25,5.5,.7,A_LINKS);
    TextfeldArray[607]->Positioniere(1.5,5.166666,.5,A_LINKS);
    TextfeldArray[608]->Positioniere(1.25,4.5,.7,A_LINKS);
    TextfeldArray[609]->Positioniere(1.5,4.166666,.5,A_LINKS);
    TextfeldArray[610]->Positioniere(1.25,3.5,.7,A_LINKS);
    TextfeldArray[611]->Positioniere(1.5,3.166666,.5,A_LINKS);
    TextfeldArray[612]->Positioniere(1.25,2.5,.7,A_LINKS);
    TextfeldArray[613]->Positioniere(1.5,2.166666,.5,A_LINKS);

    TextfeldArray[614]->Positioniere(8.25,5.5,.7,A_LINKS);
    TextfeldArray[615]->Positioniere(8.5,5.166666,.5,A_LINKS);
    TextfeldArray[616]->Positioniere(8.25,4.5,.7,A_LINKS);
    TextfeldArray[617]->Positioniere(8.5,4.166666,.5,A_LINKS);
    TextfeldArray[618]->Positioniere(8.25,3.5,.7,A_LINKS);
    TextfeldArray[619]->Positioniere(8.5,3.166666,.5,A_LINKS);
    TextfeldArray[620]->Positioniere(8.25,2.5,.7,A_LINKS);
    TextfeldArray[621]->Positioniere(8.5,2.166666,.5,A_LINKS);

    TextfeldArray[T_ZURUECK]->Positioniere(8,.1,1,A_MITTE);
    TextfeldArray[T_ZURUECK]->SetzeSignal(S_H_ZUHILFE);
  } break;

  case HILFEREGELN1: {
    menuhintergrund.Positioniere(.5,.7,15.5,11);
    logo.Positioniere(0,11,4,12);
    logo.VollSichtbar();
    TextfeldArray[T_HILFE]->Positioniere(4,11.4,.6,A_LINKS);
    TextfeldArray[T_HILFE]->VollSichtbar();
    TextfeldArray[T_H_BILLARDREGELN]->Positioniere(4,11,.6,A_LINKS);
    TextfeldArray[T_H_BILLARDREGELN]->VollSichtbar();

    TextfeldArray[710]->Positioniere(1,10,1,A_LINKS);

    TextfeldArray[711]->Positioniere(1.25,9.5,.7,A_LINKS);
    TextfeldArray[712]->Positioniere(1.5,9.166666,.5,A_LINKS);
    TextfeldArray[713]->Positioniere(1.25,8.5,.7,A_LINKS);
    TextfeldArray[714]->Positioniere(1.5,8.166666,.5,A_LINKS);
    TextfeldArray[715]->Positioniere(1.25,7.5,.7,A_LINKS);
    TextfeldArray[716]->Positioniere(1.5,7.166666,.5,A_LINKS);
    TextfeldArray[717]->Positioniere(1.25,6.5,.7,A_LINKS);
    TextfeldArray[718]->Positioniere(1.5,6.166666,.5,A_LINKS);
    TextfeldArray[719]->Positioniere(1.25,5.5,.7,A_LINKS);
    TextfeldArray[720]->Positioniere(1.5,5.166666,.5,A_LINKS);
    TextfeldArray[721]->Positioniere(1.25,4.5,.7,A_LINKS);
    TextfeldArray[722]->Positioniere(1.5,4.166666,.5,A_LINKS);
    TextfeldArray[723]->Positioniere(1.25,3.5,.7,A_LINKS);
    TextfeldArray[724]->Positioniere(1.5,3.166666,.5,A_LINKS);
    TextfeldArray[725]->Positioniere(1.25,2.5,.7,A_LINKS);
    TextfeldArray[726]->Positioniere(1.5,2.166666,.5,A_LINKS);
    TextfeldArray[727]->Positioniere(1.25,1.5,.7,A_LINKS);
    TextfeldArray[728]->Positioniere(1.5,1.166666,.5,A_LINKS);

    TextfeldArray[T_ZURUECK]->Positioniere(8,0,.7,A_MITTE);
    TextfeldArray[T_ZURUECK]->SetzeSignal(S_H_ZUHILFE);
    TextfeldArray[T_H_NAECHSTESEITE]->Positioniere(15.8,0,.7,A_RECHTS);
    TextfeldArray[T_H_NAECHSTESEITE]->SetzeSignal(S_H_R1_N);
    //TextfeldArray[T_H_LETZTESEITE]->Positioniere(.2,0,.7,A_LINKS);
    //TextfeldArray[T_H_LETZTESEITE]->SetzeSignal(S_H_R1_L);
  } break;

  case HILFEREGELN2: {
    menuhintergrund.Positioniere(.5,.7,15.5,11);
    logo.Positioniere(0,11,4,12);
    logo.VollSichtbar();
    TextfeldArray[T_HILFE]->Positioniere(4,11.4,.6,A_LINKS);
    TextfeldArray[T_HILFE]->VollSichtbar();
    TextfeldArray[T_H_BILLARDREGELN]->Positioniere(4,11,.6,A_LINKS);
    TextfeldArray[T_H_BILLARDREGELN]->VollSichtbar();

    GLfloat ypos=10;
    TextfeldArray[740]->Positioniere(1,ypos,1,A_LINKS);
    ypos-=.7*TextfeldArray[740]->TextfeldHoehe();
    TextfeldArray[741]->Positioniere(1.25,ypos,.7,A_LINKS);
    ypos-=.5*TextfeldArray[741]->TextfeldHoehe();
    TextfeldArray[742]->Positioniere(1.5,ypos,.5,A_LINKS);
    ypos-=.5*TextfeldArray[742]->TextfeldHoehe()+.5;
    TextfeldArray[743]->Positioniere(1.25,ypos,.7,A_LINKS);
    ypos-=.5*TextfeldArray[743]->TextfeldHoehe();
    TextfeldArray[744]->Positioniere(1.5,ypos,.5,A_LINKS);
    ypos-=.5*TextfeldArray[744]->TextfeldHoehe()+.5;
    TextfeldArray[745]->Positioniere(1.25,ypos,.7,A_LINKS);
    ypos-=.5*TextfeldArray[745]->TextfeldHoehe();
    TextfeldArray[746]->Positioniere(1.5,ypos,.5,A_LINKS);
    ypos-=.5*TextfeldArray[746]->TextfeldHoehe()+.5;

    TextfeldArray[T_ZURUECK]->Positioniere(8,0,.7,A_MITTE);
    TextfeldArray[T_ZURUECK]->SetzeSignal(S_H_ZUHILFE);
    TextfeldArray[T_H_NAECHSTESEITE]->Positioniere(15.8,0,.7,A_RECHTS);
    TextfeldArray[T_H_NAECHSTESEITE]->SetzeSignal(S_H_R2_N);
    TextfeldArray[T_H_LETZTESEITE]->Positioniere(.2,0,.7,A_LINKS);
    TextfeldArray[T_H_LETZTESEITE]->SetzeSignal(S_H_R2_L);
  } break;

  case HILFEREGELN3: {
    menuhintergrund.Positioniere(.5,.7,15.5,11);
    logo.Positioniere(0,11,4,12);
    logo.VollSichtbar();
    TextfeldArray[T_HILFE]->Positioniere(4,11.4,.6,A_LINKS);
    TextfeldArray[T_HILFE]->VollSichtbar();
    TextfeldArray[T_H_BILLARDREGELN]->Positioniere(4,11,.6,A_LINKS);
    TextfeldArray[T_H_BILLARDREGELN]->VollSichtbar();

    GLfloat ypos=10;
    TextfeldArray[747]->Positioniere(1,ypos,1,A_LINKS);
    ypos-=.7*TextfeldArray[747]->TextfeldHoehe();
    TextfeldArray[748]->Positioniere(1.25,ypos,.7,A_LINKS);
    ypos-=.5*TextfeldArray[748]->TextfeldHoehe();
    TextfeldArray[749]->Positioniere(1.5,ypos,.5,A_LINKS);
    ypos-=.5*TextfeldArray[749]->TextfeldHoehe()+.5;
    TextfeldArray[750]->Positioniere(1.25,ypos,.7,A_LINKS);
    ypos-=.5*TextfeldArray[750]->TextfeldHoehe();
    TextfeldArray[751]->Positioniere(1.5,ypos,.5,A_LINKS);
    ypos-=.5*TextfeldArray[751]->TextfeldHoehe()+.2;
    TextfeldArray[752]->Positioniere(1.5,ypos,.5,A_LINKS);
    ypos-=.5*TextfeldArray[752]->TextfeldHoehe()+.2;
    TextfeldArray[753]->Positioniere(1.5,ypos,.5,A_LINKS);
    ypos-=.5*TextfeldArray[753]->TextfeldHoehe()+.2;
    TextfeldArray[754]->Positioniere(1.5,ypos,.5,A_LINKS);
    ypos-=.5*TextfeldArray[754]->TextfeldHoehe()+.5;

    TextfeldArray[T_ZURUECK]->Positioniere(8,0,.7,A_MITTE);
    TextfeldArray[T_ZURUECK]->SetzeSignal(S_H_ZUHILFE);
    TextfeldArray[T_H_NAECHSTESEITE]->Positioniere(15.8,0,.7,A_RECHTS);
    TextfeldArray[T_H_NAECHSTESEITE]->SetzeSignal(S_H_R3_N);
    TextfeldArray[T_H_LETZTESEITE]->Positioniere(.2,0,.7,A_LINKS);
    TextfeldArray[T_H_LETZTESEITE]->SetzeSignal(S_H_R3_L);
  } break;

  case HILFEREGELN4: {
    menuhintergrund.Positioniere(.5,.7,15.5,11);
    logo.Positioniere(0,11,4,12);
    logo.VollSichtbar();
    TextfeldArray[T_HILFE]->Positioniere(4,11.4,.6,A_LINKS);
    TextfeldArray[T_HILFE]->VollSichtbar();
    TextfeldArray[T_H_BILLARDREGELN]->Positioniere(4,11,.6,A_LINKS);
    TextfeldArray[T_H_BILLARDREGELN]->VollSichtbar();

    GLfloat ypos=10;
    TextfeldArray[747]->Positioniere(1,ypos,1,A_LINKS);
    ypos-=.7*TextfeldArray[747]->TextfeldHoehe();
    TextfeldArray[755]->Positioniere(1.25,ypos,.7,A_LINKS);
    ypos-=.5*TextfeldArray[755]->TextfeldHoehe();
    TextfeldArray[756]->Positioniere(1.5,ypos,.5,A_LINKS);
    ypos-=.5*TextfeldArray[756]->TextfeldHoehe()+.5;
    TextfeldArray[757]->Positioniere(1.25,ypos,.7,A_LINKS);
    ypos-=.5*TextfeldArray[757]->TextfeldHoehe();
    TextfeldArray[758]->Positioniere(1.5,ypos,.5,A_LINKS);
    ypos-=.5*TextfeldArray[758]->TextfeldHoehe()+.5;
    TextfeldArray[759]->Positioniere(1.25,ypos,.7,A_LINKS);
    ypos-=.5*TextfeldArray[759]->TextfeldHoehe();
    TextfeldArray[760]->Positioniere(1.5,ypos,.5,A_LINKS);
    ypos-=.5*TextfeldArray[760]->TextfeldHoehe()+.5;
    TextfeldArray[761]->Positioniere(1.25,ypos,.7,A_LINKS);
    ypos-=.5*TextfeldArray[761]->TextfeldHoehe();
    TextfeldArray[762]->Positioniere(1.5,ypos,.5,A_LINKS);
    ypos-=.5*TextfeldArray[762]->TextfeldHoehe()+.5;

    TextfeldArray[T_ZURUECK]->Positioniere(8,0,.7,A_MITTE);
    TextfeldArray[T_ZURUECK]->SetzeSignal(S_H_ZUHILFE);
    TextfeldArray[T_H_NAECHSTESEITE]->Positioniere(15.8,0,.7,A_RECHTS);
    TextfeldArray[T_H_NAECHSTESEITE]->SetzeSignal(S_H_R4_N);
    TextfeldArray[T_H_LETZTESEITE]->Positioniere(.2,0,.7,A_LINKS);
    TextfeldArray[T_H_LETZTESEITE]->SetzeSignal(S_H_R4_L);
  } break;

  case HILFEREGELN5: {
    menuhintergrund.Positioniere(.5,.7,15.5,11);
    logo.Positioniere(0,11,4,12);
    logo.VollSichtbar();
    TextfeldArray[T_HILFE]->Positioniere(4,11.4,.6,A_LINKS);
    TextfeldArray[T_HILFE]->VollSichtbar();
    TextfeldArray[T_H_BILLARDREGELN]->Positioniere(4,11,.6,A_LINKS);
    TextfeldArray[T_H_BILLARDREGELN]->VollSichtbar();

    GLfloat ypos=10;
    TextfeldArray[770]->Positioniere(1,ypos,1,A_LINKS);
    ypos-=.7*TextfeldArray[770]->TextfeldHoehe();
    TextfeldArray[771]->Positioniere(1.25,ypos,.7,A_LINKS);
    ypos-=.5*TextfeldArray[771]->TextfeldHoehe();
    TextfeldArray[772]->Positioniere(1.5,ypos,.5,A_LINKS);
    ypos-=.5*TextfeldArray[772]->TextfeldHoehe()+.5;
    TextfeldArray[773]->Positioniere(1.25,ypos,.7,A_LINKS);
    ypos-=.5*TextfeldArray[773]->TextfeldHoehe();
    TextfeldArray[774]->Positioniere(1.5,ypos,.5,A_LINKS);
    ypos-=.5*TextfeldArray[774]->TextfeldHoehe()+.2;
    TextfeldArray[775]->Positioniere(1.5,ypos,.5,A_LINKS);
    ypos-=.5*TextfeldArray[775]->TextfeldHoehe();


    TextfeldArray[T_ZURUECK]->Positioniere(8,0,.7,A_MITTE);
    TextfeldArray[T_ZURUECK]->SetzeSignal(S_H_ZUHILFE);
    TextfeldArray[T_H_NAECHSTESEITE]->Positioniere(15.8,0,.7,A_RECHTS);
    TextfeldArray[T_H_NAECHSTESEITE]->SetzeSignal(S_H_R5_N);
    TextfeldArray[T_H_LETZTESEITE]->Positioniere(.2,0,.7,A_LINKS);
    TextfeldArray[T_H_LETZTESEITE]->SetzeSignal(S_H_R5_L);
  } break;

  case HILFEREGELN6: {
    menuhintergrund.Positioniere(.5,.7,15.5,11);
    logo.Positioniere(0,11,4,12);
    logo.VollSichtbar();
    TextfeldArray[T_HILFE]->Positioniere(4,11.4,.6,A_LINKS);
    TextfeldArray[T_HILFE]->VollSichtbar();
    TextfeldArray[T_H_BILLARDREGELN]->Positioniere(4,11,.6,A_LINKS);
    TextfeldArray[T_H_BILLARDREGELN]->VollSichtbar();

    GLfloat ypos=10;
    TextfeldArray[770]->Positioniere(1,ypos,1,A_LINKS);
    ypos-=.7*TextfeldArray[770]->TextfeldHoehe();
    TextfeldArray[776]->Positioniere(1.25,ypos,.7,A_LINKS);
    ypos-=.5*TextfeldArray[776]->TextfeldHoehe();
    TextfeldArray[777]->Positioniere(1.5,ypos,.5,A_LINKS);
    ypos-=.5*TextfeldArray[777]->TextfeldHoehe()+.5;
    TextfeldArray[778]->Positioniere(1.25,ypos,.7,A_LINKS);
    ypos-=.5*TextfeldArray[778]->TextfeldHoehe();
    TextfeldArray[779]->Positioniere(1.5,ypos,.5,A_LINKS);
    ypos-=.5*TextfeldArray[779]->TextfeldHoehe()+.5;
    TextfeldArray[780]->Positioniere(1.25,ypos,.7,A_LINKS);
    ypos-=.5*TextfeldArray[780]->TextfeldHoehe();
    TextfeldArray[781]->Positioniere(1.5,ypos,.5,A_LINKS);
    ypos-=.5*TextfeldArray[781]->TextfeldHoehe()+.5;
    TextfeldArray[782]->Positioniere(1.25,ypos,.7,A_LINKS);
    ypos-=.5*TextfeldArray[782]->TextfeldHoehe();
    TextfeldArray[783]->Positioniere(1.5,ypos,.5,A_LINKS);
    ypos-=.5*TextfeldArray[783]->TextfeldHoehe()+.5;

    TextfeldArray[T_ZURUECK]->Positioniere(8,0,.7,A_MITTE);
    TextfeldArray[T_ZURUECK]->SetzeSignal(S_H_ZUHILFE);
    //TextfeldArray[T_H_NAECHSTESEITE]->Positioniere(15.8,0,.7,A_RECHTS);
    //TextfeldArray[T_H_NAECHSTESEITE]->SetzeSignal(S_H_R5_N);
    TextfeldArray[T_H_LETZTESEITE]->Positioniere(.2,0,.7,A_LINKS);
    TextfeldArray[T_H_LETZTESEITE]->SetzeSignal(S_H_R6_L);
  } break;

  case BEENDEN: {
    menuhintergrund.Positioniere(4.5,4.5,11.5,8.5);
    logo.Positioniere(4,9,12,11);
    logo.VollSichtbar();
    TextfeldArray[T_BEENDEN]->Positioniere(8,8,1,A_MITTE);
    TextfeldArray[T_BEENDEN]->VollSichtbar();
    TextfeldArray[T_JABEENDEN]->Positioniere(8,6,1,A_MITTE);
    TextfeldArray[T_JABEENDEN]->SetzeSignal(S_BE_JABEENDEN);
    TextfeldArray[T_ZURUECK]->Positioniere(8,1,1,A_MITTE);
    if (AusSpiel) {
      TextfeldArray[T_ZURUECK]->SetzeSignal(S_BE_ZURUECK_AS);
    } else {
      TextfeldArray[T_ZURUECK]->SetzeSignal(S_BE_ZURUECK);
    }

    TextfeldArray[T_HOMEPAGE]->Positioniere(15.9,0,.5,A_RECHTS);
    TextfeldArray[T_VERSION]->Positioniere(.1,0,.5,A_LINKS);

  } break;

  case AUSSPIEL: {
    menuhintergrund.Positioniere(3.5,0.5,12.5,8.5);
    logo.Positioniere(4,9,12,11);
    logo.VollSichtbar();
    TextfeldArray[T_WEITERSPIELEN]->Positioniere(8,7,1,A_MITTE);
    TextfeldArray[T_WEITERSPIELEN]->SetzeSignal(S_AS_WEITERSPIELEN);
    TextfeldArray[T_HILFE]->Positioniere(8,5.5,1,A_MITTE);
    TextfeldArray[T_HILFE]->SetzeSignal(S_AS_HILFE);
    TextfeldArray[T_TISCHVERLASSEN]->Positioniere(8,4,1,A_MITTE);
    TextfeldArray[T_TISCHVERLASSEN]->SetzeSignal(S_AS_HAUPTMENU);
    TextfeldArray[T_EINSTELLUNGEN]->Positioniere(8,2.5,1,A_MITTE);
    TextfeldArray[T_EINSTELLUNGEN]->SetzeSignal(S_AS_EINSTELLUNGEN);
    TextfeldArray[T_BEENDEN]->Positioniere(8,1,1,A_MITTE);
    TextfeldArray[T_BEENDEN]->SetzeSignal(S_AS_BEENDEN);

    TextfeldArray[T_HOMEPAGE]->Positioniere(15.9,0,.5,A_RECHTS);
    TextfeldArray[T_VERSION]->Positioniere(.1,0,.5,A_LINKS);

  } break;
  
  case SPIEL: {
    //    menuhintergrund.Positioniere(0,11,16,12);
    
    if (SpielModus==TRAININGSSPIEL) {
      logo.Positioniere(0,11,4,12);
    } else if (SpielModus==TUTORIAL) {
      logo.Positioniere(12,0,16,1);
    } else {
      logo.Positioniere(6,11,10,12);
    }
    logo.SetzeSignal(S_SP_LOGO);

    switch (SpielModus) {
    case TUTORIAL: {
      GLfloat posy=11.5;
      GLint Bereich=0;
      //TextfeldArray[T_H_TUTORIAL]->Positioniere(15.75,0,1,A_RECHTS);//
      switch (StateMaschin) {
      case BETRACHTEN: {
	if (AllerersterStoss)
	  Bereich=640;
	else 
	  Bereich=690;
      } break;
      case ZIELEN: {
	Bereich=650;
      } break;
      case AUSHOLEN: {
	Bereich=660;
      } break;
      case STOSS: {
	Bereich=670;
      } break;
      case WEISSNEU: {
	Bereich=680;
      } break;
      }
      for (GLint i=Bereich;i<Bereich+10;i++) {
	if (TextfeldArray[i]) {
	  TextfeldArray[i]->Positioniere(0.2,posy,.5,A_LINKS);
	  TextfeldArray[i]->VollSichtbar();
	  posy-=.5*TextfeldArray[i]->TextfeldHoehe()+.2;
	}
      }
    menuhintergrund.Positioniere(0,posy+.5,16,12);
    } break;

    case TRAININGSSPIEL: {
      TextfeldArray[T_TRAINING]->Positioniere(15.75,0,1,A_RECHTS);//
      TextfeldArray[T_NEUEACHTBALLAUFSTELLUNG]->Positioniere(15.75,11.5,.5,A_RECHTS);
      TextfeldArray[T_NEUEACHTBALLAUFSTELLUNG]->SetzeSignal(S_SP_NEUEACHTBALLAUFSTELLUNG);
      TextfeldArray[T_NEUENEUNBALLAUFSTELLUNG]->Positioniere(15.75,11.2,.5,A_RECHTS);
      TextfeldArray[T_NEUENEUNBALLAUFSTELLUNG]->SetzeSignal(S_SP_NEUENEUNBALLAUFSTELLUNG);
    } break;
    case ZWEISPIELERSPIEL: {
      TextfeldArray[T_ZWEISPIELER]->Positioniere(15.75,0,1,A_RECHTS);//12,11,16,12);
      if (Schiedsrichter.FrageNachSpielerAmStoss()==0) {
	TextfeldArray[T_SPIELER1NAME]->Positioniere(0.2,11,1,A_LINKS);
	TextfeldArray[T_SPIELER2NAME]->Positioniere(15.9,11.5,.5,A_RECHTS);
	if (Spiel==ACHTBALL) {
	  if (Schiedsrichter.FrageNachGruppenVerteilung()==1) {
	    volle.Positioniere(0.2,10,1.2,11);
	    halbe.Positioniere(15.4,11,15.9,11.5);
	  }
	  if (Schiedsrichter.FrageNachGruppenVerteilung()==2) {
	    halbe.Positioniere(0.2,10,1.2,11);
	    volle.Positioniere(15.4,11,15.9,11.5);
	  }
	}
 	if (Spiel==NEUNBALL) {
	  if (Schiedsrichter.FrageNachFouls(0)==1) {
	    TextfeldArray[T_ZUSATZTEXTLINKS]->SetzeText("1 Foul");
	    TextfeldArray[T_ZUSATZTEXTLINKS]->Positioniere(.2,10,1,A_LINKS);
	  }
	  if (Schiedsrichter.FrageNachFouls(0)==2) {
 	    TextfeldArray[T_ZUSATZTEXTLINKS]->SetzeText("2 Fouls");
	    TextfeldArray[T_ZUSATZTEXTLINKS]->Positioniere(.2,10,1,A_LINKS);
	  }
	  if (Schiedsrichter.FrageNachFouls(0)==3) {
 	    TextfeldArray[T_ZUSATZTEXTLINKS]->SetzeText("3 Fouls");
	    TextfeldArray[T_ZUSATZTEXTLINKS]->Positioniere(.2,10,1,A_LINKS);
	  }
	  if (Schiedsrichter.FrageNachFouls(1)==1) {
 	    TextfeldArray[T_ZUSATZTEXTRECHTS]->SetzeText("1 Foul");
	    TextfeldArray[T_ZUSATZTEXTRECHTS]->Positioniere(15.9,11,.5,A_RECHTS);
	  }
 	  if (Schiedsrichter.FrageNachFouls(1)==2) {
 	    TextfeldArray[T_ZUSATZTEXTRECHTS]->SetzeText("2 Fouls");
	    TextfeldArray[T_ZUSATZTEXTRECHTS]->Positioniere(15.9,11,.5,A_RECHTS);
	  }
 	  if (Schiedsrichter.FrageNachFouls(1)==3) {
 	    TextfeldArray[T_ZUSATZTEXTRECHTS]->SetzeText("3 Fouls");
	    TextfeldArray[T_ZUSATZTEXTRECHTS]->Positioniere(15.9,11,.5,A_RECHTS);
 	  }
	}
      } else {
	TextfeldArray[T_SPIELER1NAME]->Positioniere(0.1,11.5,.5,A_LINKS);
	TextfeldArray[T_SPIELER2NAME]->Positioniere(15.8,11,1,A_RECHTS);
	if (Spiel==ACHTBALL) {
	  if (Schiedsrichter.FrageNachGruppenVerteilung()==1) {
	    volle.Positioniere(0.1,11,.5,11.5);
	    halbe.Positioniere(14.8,10,15.8,11);
	  }
	  if (Schiedsrichter.FrageNachGruppenVerteilung()==2) {
	    halbe.Positioniere(0.1,11,.5,11.5);
	    volle.Positioniere(14.8,10,15.8,11);
	  }
	}
 	if (Spiel==NEUNBALL) {
	  if (Schiedsrichter.FrageNachFouls(0)==1) {
	    TextfeldArray[T_ZUSATZTEXTLINKS]->SetzeText("1 Foul");
	    TextfeldArray[T_ZUSATZTEXTLINKS]->Positioniere(.1,11,.5,A_LINKS);
	  }
	  if (Schiedsrichter.FrageNachFouls(0)==2) {
	    TextfeldArray[T_ZUSATZTEXTLINKS]->SetzeText("2 Fouls");
	    TextfeldArray[T_ZUSATZTEXTLINKS]->Positioniere(.1,11,.5,A_LINKS);
	  }
	  if (Schiedsrichter.FrageNachFouls(0)==3) {
	    TextfeldArray[T_ZUSATZTEXTLINKS]->SetzeText("3 Fouls");
	    TextfeldArray[T_ZUSATZTEXTLINKS]->Positioniere(.1,11,.5,A_LINKS);
	  }
	  if (Schiedsrichter.FrageNachFouls(1)==1) {
	    TextfeldArray[T_ZUSATZTEXTRECHTS]->SetzeText("1 Foul");
	    TextfeldArray[T_ZUSATZTEXTRECHTS]->Positioniere(15.8,10,1,A_RECHTS);
	  }
 	  if (Schiedsrichter.FrageNachFouls(1)==2) {
	    TextfeldArray[T_ZUSATZTEXTRECHTS]->SetzeText("2 Fouls");
	    TextfeldArray[T_ZUSATZTEXTRECHTS]->Positioniere(15.8,10,1,A_RECHTS);
	  }
 	  if (Schiedsrichter.FrageNachFouls(1)==3) {
	    TextfeldArray[T_ZUSATZTEXTRECHTS]->SetzeText("3 Fouls");
	    TextfeldArray[T_ZUSATZTEXTRECHTS]->Positioniere(15.8,10,1,A_RECHTS);
 	  }
	}
      }
    } break;
    
    /*
      case NETZWERKSPIEL: {
      netzwerkspiel.Positioniere(12,0,16,1);//12,11,16,12);
      if (Schiedsrichter.FrageNachSpielerAmStoss()==0) {
      spieler1.Positioniere(0,11,4,12);
      spieler2.Positioniere(14,11.25,16,11.75);
      } else {
      spieler1.Positioniere(0,11.25,2,11.75);
      spieler2.Positioniere(12,11,16,12);
      }
      } break;
    */
    }


    switch (StateMaschin) {
    case BETRACHTEN: {
      TextfeldArray[T_BETRACHTEN]->Positioniere(0.25,0,1,A_LINKS);
    } break;
    case ZIELEN: {
      TextfeldArray[T_ZIELEN]->Positioniere(0.25,0,1,A_LINKS);
    } break;
    case AUSHOLEN: {
      TextfeldArray[T_AUSHOLEN]->Positioniere(0.25,0,1,A_LINKS);
    } break;
    case STOSS: {
      TextfeldArray[T_STOSS]->Positioniere(0.25,0,1,A_LINKS);
    } break;
    case WEISSNEU: {
      TextfeldArray[T_WEISSENEUSETZEN]->Positioniere(0.25,0,1,A_LINKS);
    } break;
    case SCHIEDSRICHTER: {
      TextfeldArray[T_STOSS]->Positioniere(0.25,0,1,A_LINKS);
      if (Foul) {
	TextfeldArray[T_FOUL]->Positioniere(8,9,1.5,A_MITTE); 
	if (Schiedsrichter.FrageNachBegruendung())
	  TextfeldArray[Schiedsrichter.FrageNachBegruendung()]->Positioniere(8,8.5,.75,A_MITTE);
      }
      if (!Spieler1Gewonnen && !Spieler2Gewonnen) {
	TextfeldArray[T_ISTAMTISCH]->Positioniere(8,5,1,A_MITTE);      
	if (Schiedsrichter.FrageNachSpielerAmStoss()==0) {
	  TextfeldArray[T_SPIELER1NAME]->Positioniere(8,6,1.5,A_MITTE);
	  TextfeldArray[T_SPIELER1NAME]->VollSichtbar();
	} else {
	  TextfeldArray[T_SPIELER2NAME]->Positioniere(8,6,1.5,A_MITTE);
	  TextfeldArray[T_SPIELER2NAME]->VollSichtbar();
	}
	if (!NeuAufbauenOderWeiterspielen &&
	    !NeuAufbauenOderAchtEinsetzen) {
	  if (LageVerbesserungKopffeld) {
	    TextfeldArray[T_IMKOPFFELD]->Positioniere(8,3,1,A_MITTE);  
	  }
	  if (LageVerbesserung|LageVerbesserungKopffeld) {
	    TextfeldArray[T_UNDHATLAGEVERBESSERUNG]->Positioniere(8,4,1,A_MITTE);  
	  }
	} else if (NeuAufbauenOderAchtEinsetzen) {
	  MenuGesperrt=1;
	  if (Foul) {
	    TextfeldArray[T_FOUL]->Positioniere(8,9,1.5,A_MITTE);      
	    if (Schiedsrichter.FrageNachBegruendung())
	      TextfeldArray[Schiedsrichter.FrageNachBegruendung()]->Positioniere(8,8.5,.75,A_MITTE);
	  }
	  TextfeldArray[T_ISTAMTISCH]->Positioniere(8,6,1,A_MITTE);  
	  if (Schiedsrichter.FrageNachSpielerAmStoss()==0) {
	    TextfeldArray[T_SPIELER1NAME]->Positioniere(8,7,1.5,A_MITTE);
	    TextfeldArray[T_SPIELER1NAME]->VollSichtbar();
	  } else {
	    TextfeldArray[T_SPIELER2NAME]->Positioniere(8,7,1.5,A_MITTE);
	    TextfeldArray[T_SPIELER2NAME]->VollSichtbar();
	  }
	  TextfeldArray[T_WOLLENSIE]->Positioniere(8,4,1,A_MITTE);
	  TextfeldArray[T_NEUAUFBAUEN]->Positioniere(5.5,2.5,1,A_MITTE);
	  TextfeldArray[T_NEUAUFBAUEN]->SetzeSignal(S_SP_NEUAUFBAUEN);
	  TextfeldArray[T_DIEACHTEINSETZEN]->Positioniere(10.5,2.5,1,A_MITTE);
	  TextfeldArray[T_DIEACHTEINSETZEN]->SetzeSignal(S_SP_ACHTEINSETZEN);
	} else if (NeuAufbauenOderWeiterspielen) {
	  MenuGesperrt=1;
	  if (Foul) {
	    TextfeldArray[T_FOUL]->Positioniere(8,9,1.5,A_MITTE);      
	    if (Schiedsrichter.FrageNachBegruendung())
	      TextfeldArray[Schiedsrichter.FrageNachBegruendung()]->Positioniere(8,8.5,.75,A_MITTE);
	  }
	  TextfeldArray[T_ISTAMTISCH]->Positioniere(8,6,1,A_MITTE);  
	  if (Schiedsrichter.FrageNachSpielerAmStoss()==0) {
	    TextfeldArray[T_SPIELER1NAME]->Positioniere(8,7,1.5,A_MITTE);
	    TextfeldArray[T_SPIELER1NAME]->VollSichtbar();
	  } else {
	    TextfeldArray[T_SPIELER2NAME]->Positioniere(8,7,1.5,A_MITTE);
	    TextfeldArray[T_SPIELER2NAME]->VollSichtbar();
	  }
	  TextfeldArray[T_WOLLENSIE]->Positioniere(8,4,1,A_MITTE);
	  TextfeldArray[T_NEUAUFBAUEN]->Positioniere(5.5,2.5,1,A_MITTE);
	  TextfeldArray[T_NEUAUFBAUEN]->SetzeSignal(S_SP_NEUAUFBAUEN);
	  TextfeldArray[T_WEITERSPIELEN]->Positioniere(10.5,2.5,1,A_MITTE);
	  TextfeldArray[T_WEITERSPIELEN]->SetzeSignal(S_SP_WEITERSPIELEN);
	}
      }
      if (Spieler1Gewonnen||Spieler2Gewonnen) {
	MenuGesperrt=1;
	TextfeldArray[T_HATGEWONNEN]->Positioniere(8,5,1,A_MITTE);
	
	TextfeldArray[T_NEUESSPIEL]->Positioniere(5.5,3,1,A_MITTE);
	TextfeldArray[T_NEUESSPIEL]->SetzeSignal(S_SP_NEUESSPIEL);
	TextfeldArray[T_TISCHVERLASSEN]->Positioniere(10.5,3,1,A_MITTE);
	TextfeldArray[T_TISCHVERLASSEN]->SetzeSignal(S_SP_HAUPTMENU);

	if (Spieler1Gewonnen) {
	    TextfeldArray[T_SPIELER1NAME]->Positioniere(8,6,1.5,A_MITTE);
	    TextfeldArray[T_SPIELER1NAME]->VollSichtbar();
	}
	if (Spieler2Gewonnen) {
	    TextfeldArray[T_SPIELER2NAME]->Positioniere(8,6,1.5,A_MITTE);
	    TextfeldArray[T_SPIELER2NAME]->VollSichtbar();
	}
      }
    } break;
    }

    GLint i;
    if (Spiel==ACHTBALL) {
      for (i=0;i<8;i++) {
	if (!KugelnVersenkt[i]&&KugelnImSpiel[i]) {
	  ball[i].Positioniere(6+.5*i,.5,6+.5*(i+1),1);
	  ball[i].SetzeSignal(S_SP_BALL+i);
	}
      }
      for (i=8;i<16;i++) {
	if (!KugelnVersenkt[i]&&KugelnImSpiel[i]) {
	  ball[i].Positioniere(6+.5*(i-8),0,6+.5*(i-7),.5);
	  ball[i].SetzeSignal(S_SP_BALL+i);
	}
      } 
    } else {
      for (i=0;i<5;i++) {
	if (!KugelnVersenkt[i]&&KugelnImSpiel[i]) {
	  ball[i].Positioniere(6.75+.5*i,.5,6.75+.5*(i+1),1);
	  ball[i].SetzeSignal(S_SP_BALL+i);
	}
      }
      for (i=5;i<10;i++) {
	if (!KugelnVersenkt[i]&&KugelnImSpiel[i]) {
	  ball[i].Positioniere(6.75+.5*(i-5),0,6.75+.5*(i-4),.5);
	  ball[i].SetzeSignal(S_SP_BALL+i);
	}
      }
    }
  } break;

  }
  StarteAnimation();
}

void Menu::SignalAusfuehrung(GLint Signal) {
  DelayAusgleich=1;
  switch (Signal) {
  case S_LOGO: {
    SetzeMenuZustand(STARTBILDSCHIRM);
  } break;
  case S_HM_TRAINING: {
    SetzeMenuZustand(TRAINING);
  } break;
  case S_HM_ZWEISPIELER: {
    SetzeMenuZustand(ZWEISPIELER);
  } break;
  case S_HM_NETZWERKSPIEL: {
    SetzeMenuZustand(NETZWERKHAUPT);
  } break;
  case S_HM_EINSTELLUNGEN: {
    AusSpiel=0;
    SetzeMenuZustand(EINSTELLUNGEN);
  } break;
  case S_HM_HILFE: {
    AusSpiel=0;
    SetzeMenuZustand(HILFE);
  } break;
  case S_HM_BEENDEN: {
    AusSpiel=0;
    SetzeMenuZustand(BEENDEN);
  } break;
  case S_TR_ACHTBALL: {
    Foul=0;
    LageVerbesserungKopffeld=1;
    LageVerbesserung=0;
    NeuAufbauenOderWeiterspielen=0;
    NeuAufbauenOderAchtEinsetzen=0;
    Spieler1Gewonnen=0;
    Spieler2Gewonnen=0;
    MenuGesperrt=0;
    SpielModus=TRAININGSSPIEL;
    StateMaschin=WEISSNEU;
    Spiel=ACHTBALL;
    SpielfeldAufbau();
    Schiedsrichter.NeuesSpiel(Spiel);
    SchiedsrichterEntscheidung=0;
    Kamera.ladePosition(4);
    SetzeMenuZustand(SPIEL);
  } break;
  case S_TR_NEUNBALL: {
    Foul=0;
    LageVerbesserungKopffeld=1;
    LageVerbesserung=0;
    NeuAufbauenOderWeiterspielen=0;
    NeuAufbauenOderAchtEinsetzen=0;
    Spieler1Gewonnen=0;
    Spieler2Gewonnen=0;
    MenuGesperrt=0;
    SpielModus=TRAININGSSPIEL;
    StateMaschin=WEISSNEU;
    Spiel=NEUNBALL;
    SpielfeldAufbau();
    Schiedsrichter.NeuesSpiel(Spiel);
    SchiedsrichterEntscheidung=0;
    Kamera.ladePosition(4);
    SetzeMenuZustand(SPIEL);
  } break;
  case S_TR_VIERZEHNPLUSEINS: {
  } break;
  case S_TR_ZURUECK: {
    SetzeMenuZustand(HAUPTMENU);
  } break;
  case S_ZW_ACHTBALL: {
    sprintf(Spieler1,"%s",TextfeldArray[T_SPIELER1NAME]->Text());
    sprintf(Spieler2,"%s",TextfeldArray[T_SPIELER2NAME]->Text());
    SchreibeKonfiguration();
    Foul=0;
    LageVerbesserungKopffeld=1;
    LageVerbesserung=0;
    NeuAufbauenOderWeiterspielen=0;
    NeuAufbauenOderAchtEinsetzen=0;
    Spieler1Gewonnen=0;
    Spieler2Gewonnen=0;
    MenuGesperrt=0;
    SpielModus=ZWEISPIELERSPIEL;
    StateMaschin=SCHIEDSRICHTER;
    Spiel=ACHTBALL;
    SpielfeldAufbau();
    Schiedsrichter.NeuesSpiel(Spiel);
    SchiedsrichterEntscheidung=0;
    Kamera.ladePosition(4);
    SetzeMenuZustand(SPIEL);
  } break;
  case S_ZW_NEUNBALL: {
    sprintf(Spieler1,"%s",TextfeldArray[T_SPIELER1NAME]->Text());
    sprintf(Spieler2,"%s",TextfeldArray[T_SPIELER2NAME]->Text());
    SchreibeKonfiguration();
    Foul=0;
    LageVerbesserungKopffeld=1;
    LageVerbesserung=0;
    NeuAufbauenOderWeiterspielen=0;
    NeuAufbauenOderAchtEinsetzen=0;
    Spieler1Gewonnen=0;
    Spieler2Gewonnen=0;
    MenuGesperrt=0;
    SpielModus=ZWEISPIELERSPIEL;
    StateMaschin=SCHIEDSRICHTER;
    Spiel=NEUNBALL;
    SpielfeldAufbau();
    Schiedsrichter.NeuesSpiel(Spiel);
    SchiedsrichterEntscheidung=0;
    Kamera.ladePosition(4);
    SetzeMenuZustand(SPIEL);
  } break;
  case S_ZW_VIERZEHNPLUSEINS: {
  } break;
  case S_ZW_ZURUECK: {
    SetzeMenuZustand(HAUPTMENU);
  } break;
  case S_NE_BEGINNEN: {
    SetzeMenuZustand(NETZWERKNEU);
  } break;
  case S_NE_TEILNEHMEN: {
    SetzeMenuZustand(NETZWERKBEITRETEN);
  } break;
  case S_NE_ZURUECK: {
    SetzeMenuZustand(HAUPTMENU);
  } break;
  case S_NB_ACHTBALL: {
  } break;
  case S_NB_NEUNBALL: {
  } break;
  case S_NB_VIERZEHNPLUSEINS: {
  } break;
  case S_NB_ZURUECK: {
  } break;
  case S_NT_IPADRESSE: {
  } break;
  case S_NT_VERBINDEN: {
  } break;
  case S_NT_ZURUECK: {
  } break;
  case S_EI_STEUERUNG: {
    E_MouseSpeed=MouseSpeed;
    E_InvertX=InvertX;
    E_InvertY=InvertY;
    SetzeMenuZustand(EINSTELLUNGENSTEUERUNG);
  } break;
  case S_EI_SPRACHE: {
    SetzeMenuZustand(SPRACHAUSWAHL);
  } break;
  case S_EI_GRAFIK: {
    E_Texturgroesse=Texturgroesse;
    E_AnzeigeTexturgroesse=AnzeigeTexturgroesse;
    E_TischTexturgroesse=TischTexturgroesse;
    E_KugelAufloesung=KugelAufloesung;
    E_BildschirmAufloesung=BildschirmAufloesung;
    E_Farbtiefe=Farbtiefe;
    E_Reflektionen=Reflektionen;
    E_Schatten=Schatten;
    E_AmbientesLicht=AmbientesLicht;
    E_TischLampen=TischLampen;
    E_GrueneLampe=GrueneLampe;
    E_ZeigeFPS=ZeigeFPS;
    E_TexMMM=TexMMM;
    SetzeMenuZustand(EINSTELLUNGENGRAFIK);
  } break;
  case S_EI_BALLTEXTUREN: {
    switch (E_Texturgroesse) {
    case 1: E_Texturgroesse=2; break;
    case 2: E_Texturgroesse=4; break;
    case 4: E_Texturgroesse=8; break;
    case 8: E_Texturgroesse=1; break;
    }  
    SetzeMenuZustand(EINSTELLUNGENGRAFIK);
  } break;
  case S_EI_TISCHTEXTUREN: {
    switch (E_TischTexturgroesse) {
    case 1: E_TischTexturgroesse=2; break;
    case 2: E_TischTexturgroesse=4; break;
    case 4: E_TischTexturgroesse=8; break;
    case 8: E_TischTexturgroesse=0; break;
    case 0: E_TischTexturgroesse=1; break;
    default: E_TischTexturgroesse=4; break;
    }
    SetzeMenuZustand(EINSTELLUNGENGRAFIK);
  } break;
  case S_EI_ANZEIGETEXTUREN: {
    switch (E_AnzeigeTexturgroesse) {
    case 1: E_AnzeigeTexturgroesse=2; break;
    case 2: E_AnzeigeTexturgroesse=1; break;
    default: E_AnzeigeTexturgroesse=1; break;
    }
    SetzeMenuZustand(EINSTELLUNGENGRAFIK);
  } break;
  case S_EI_AUFLOESUNG: {
    switch (E_BildschirmAufloesung) {
    case 640: E_BildschirmAufloesung=1600; break;
    case 800: E_BildschirmAufloesung=640; break;
    case 1024: E_BildschirmAufloesung=800; break;
    case 1280: E_BildschirmAufloesung=1024; break;
    case 1600: E_BildschirmAufloesung=1280; break;
    default: E_BildschirmAufloesung=800; break;
    }
    SetzeMenuZustand(EINSTELLUNGENGRAFIK);
  } break;
  case S_EI_FARBTIEFE: {
    switch (E_Farbtiefe) {
    case 16: E_Farbtiefe=32; break;
    default: E_Farbtiefe=16; break;
    }
    SetzeMenuZustand(EINSTELLUNGENGRAFIK);
  } break;
  case S_EI_REFLEKTIONEN: {
    switch (E_Reflektionen) {
    case 0: E_Reflektionen=1; break;
    default:  E_Reflektionen=0; break;    
    }
    SetzeMenuZustand(EINSTELLUNGENGRAFIK);
  } break;
  case S_EI_SCHATTEN: {
    switch (E_Schatten) {
    case 0: E_Schatten=1; break;
    default:  E_Schatten=0; break;    
    }
    SetzeMenuZustand(EINSTELLUNGENGRAFIK);
  } break;
  case S_EI_TEXTURINTERPOLATION: {
    switch (E_TexMMM) {
    case 0: E_TexMMM=7; break;
    case 2: E_TexMMM=0; break;
    case 3: E_TexMMM=2; break;
    default:  E_TexMMM=3; break;    
    }
    SetzeMenuZustand(EINSTELLUNGENGRAFIK);
    } break;
  case S_EI_AMBIENTESLICHT: {
    switch (E_AmbientesLicht) {
    case 1: E_AmbientesLicht=0; break;
    default:  E_AmbientesLicht=1; break;    
    }
    SetzeMenuZustand(EINSTELLUNGENGRAFIK);
  } break;
  case S_EI_TISCHLAMPEN: {
    switch (E_TischLampen) {
    case 1: E_TischLampen=2; break;
    case 2: E_TischLampen=3; break;
    case 3: E_TischLampen=1; break;
    default:  E_TischLampen=1; break;    
    }
    SetzeMenuZustand(EINSTELLUNGENGRAFIK);
  } break;
  case S_EI_GRUENELAMPE: {
    switch (E_GrueneLampe) {
    case 1: E_GrueneLampe=0; break;
    default:  E_GrueneLampe=1; break;    
    }
    SetzeMenuZustand(EINSTELLUNGENGRAFIK);
  } break;
  case S_EI_FPS: {
    switch (E_ZeigeFPS) {
    case 1: ZeigeFPS=E_ZeigeFPS=0; break;
    default: ZeigeFPS=E_ZeigeFPS=1; break;    
    }
    SetzeMenuZustand(EINSTELLUNGENGRAFIK);
  } break;
  case S_EI_BALLGEOMETRIE: {
    switch (E_KugelAufloesung) {
    case 1: {
      E_KugelAufloesung=7;
    } break;
    case 2: {
      E_KugelAufloesung=7;
    } break;
    case 3: {
      E_KugelAufloesung=11;
    } break;
    case 5: {
      E_KugelAufloesung=3;
    } break;
    case 7: {
      E_KugelAufloesung=5;
    } break;
    case 9: {
      E_KugelAufloesung=7;
    } break;
    case 11: {
      E_KugelAufloesung=7;
    } break;
    default: {
      E_KugelAufloesung=7;
    } break;
    }
    SetzeMenuZustand(EINSTELLUNGENGRAFIK);
  } break;
  case S_EI_MOUSESPEED: {
    if (E_MouseSpeed<=.21) {
      E_MouseSpeed=.8;
    } else if (E_MouseSpeed<=.29) {
      E_MouseSpeed=.8;
    } else if (E_MouseSpeed<=.41) {
      E_MouseSpeed=.28;
    } else if (E_MouseSpeed<=.575) {
      E_MouseSpeed=.4;
    } else {
      E_MouseSpeed=.565;
    }
    SetzeMenuZustand(EINSTELLUNGENSTEUERUNG);
  } break;
  case S_EI_XINVERT: {
    if (E_InvertX) {
      E_InvertX=0;
    } else {
      E_InvertX=1;
    }
    SetzeMenuZustand(EINSTELLUNGENSTEUERUNG);
  } break;
  case S_EI_YINVERT: {
    if (E_InvertY) {
      E_InvertY=0;
    } else {
      E_InvertY=1;
    }
    SetzeMenuZustand(EINSTELLUNGENSTEUERUNG);
  } break;


  case S_EI_QUALITAET: {
    switch(Qualitaet) {
    case 1: {
      E_KugelAufloesung=11;
      E_Texturgroesse=1;
      E_TischTexturgroesse=1;
      E_AnzeigeTexturgroesse=1;
      E_Reflektionen=1;
      E_BildschirmAufloesung=1024;
      E_Farbtiefe=32;
      E_Schatten=1;
      E_TischLampen=3;
      E_GrueneLampe=1;
      E_TexMMM=7;
    } break;
    case 2: {
      E_KugelAufloesung=3;
      E_Texturgroesse=8;
      E_TischTexturgroesse=0;
      E_AnzeigeTexturgroesse=2;
      E_Reflektionen=0;
      E_BildschirmAufloesung=640;
      E_Farbtiefe=16;
      E_Schatten=0;
      E_TischLampen=1;
      E_GrueneLampe=0;
      E_TexMMM=0;
    } break;
    case 3: {
      E_KugelAufloesung=5;
      E_Texturgroesse=4;
      E_TischTexturgroesse=4;
      E_AnzeigeTexturgroesse=2;
      E_Reflektionen=0;
      E_BildschirmAufloesung=640;
      E_Farbtiefe=16;
      E_Schatten=1;
      E_TischLampen=1;
      E_GrueneLampe=0;
      E_TexMMM=2;
    } break;
    case 4: {
      E_KugelAufloesung=7;
      E_Texturgroesse=2;
      E_TischTexturgroesse=2;
      E_AnzeigeTexturgroesse=1;
      E_Reflektionen=0;
      E_BildschirmAufloesung=800;
      E_Farbtiefe=16;
      E_Schatten=1;
      E_TischLampen=2;
      E_GrueneLampe=0;
      E_TexMMM=3;
    } break;
    case 5: {
      E_KugelAufloesung=7;
      E_Texturgroesse=2;
      E_TischTexturgroesse=1;
      E_AnzeigeTexturgroesse=1;
      E_Reflektionen=1;
      E_BildschirmAufloesung=1024;
      E_Farbtiefe=16;
      E_Schatten=1;
      E_TischLampen=2;
      E_GrueneLampe=1;
      E_TexMMM=7;
    } break;
    default: {
      E_KugelAufloesung=7;
      E_Texturgroesse=2;
      E_TischTexturgroesse=2;
      E_AnzeigeTexturgroesse=1;
      E_Reflektionen=0;
      E_BildschirmAufloesung=800;
      E_Farbtiefe=16;
      E_Schatten=1;
      E_TischLampen=2;
      E_GrueneLampe=0;
      E_TexMMM=3;
    } break;
    }
    SetzeMenuZustand(EINSTELLUNGENGRAFIK);
  } break;

  case S_EI_GRAFIKUEBERNEHMEN: {

    GLint TexMMMgeaendert=0;

    if (TexMMM!=E_TexMMM) {
      TexMMMgeaendert=1;
      TexMMM=E_TexMMM;
    }
      
    if (Texturgroesse!=E_Texturgroesse ||
	KugelAufloesung!=E_KugelAufloesung ||
	TexMMMgeaendert ||
	Schatten!=E_Schatten) {
      
      initialisiereKugelTabellen(E_KugelAufloesung);
      
      for (GLint j=0;j<16;j++) {  // Initialisierung der Baelle + Laden der Texturen
	Kugel[j].Initialisiere(j,E_Texturgroesse,E_KugelAufloesung,E_Schatten);
      }
    }

    if (TischTexturgroesse!=E_TischTexturgroesse ||
	TexMMMgeaendert){
      Tisch.Initialisiere(E_TischTexturgroesse);
    }

    if (Reflektionen!=E_Reflektionen ||
	AmbientesLicht!=E_AmbientesLicht ||
	TischLampen!=E_TischLampen ||
	GrueneLampe!=E_GrueneLampe) {
      Beleuchtung.Initialisiere(E_AmbientesLicht,E_TischLampen,E_GrueneLampe,E_Reflektionen);
    }

    if (AnzeigeTexturgroesse!=E_AnzeigeTexturgroesse||
	TexMMMgeaendert){
      Initialisiere(E_AnzeigeTexturgroesse);
    }

    GLint NeueAufloesung=0;
    if (Farbtiefe!=E_Farbtiefe || BildschirmAufloesung!=E_BildschirmAufloesung)
      NeueAufloesung=1;

    KugelAufloesung=E_KugelAufloesung;
    Texturgroesse=E_Texturgroesse;
    AnzeigeTexturgroesse=E_AnzeigeTexturgroesse;
    TischTexturgroesse=E_TischTexturgroesse;
    Reflektionen=E_Reflektionen;
    BildschirmAufloesung=E_BildschirmAufloesung;
    Farbtiefe=E_Farbtiefe;
    Schatten=E_Schatten;
    TischTexturgroesse=E_TischTexturgroesse;
    AmbientesLicht=E_AmbientesLicht;
    TischLampen=E_TischLampen;
    GrueneLampe=E_GrueneLampe;
    ZeigeFPS=E_ZeigeFPS;

    SchreibeKonfiguration();

    if (NeueAufloesung)
      SetzeMenuZustand(EINSTELLUNGENGRAFIKHINWEIS);
    else 
      SetzeMenuZustand(EINSTELLUNGENGRAFIK);

  } break;
  case S_EI_GRAFIKZURUECK: {
    SetzeMenuZustand(EINSTELLUNGEN);
  } break;
  case S_EI_STEUERUNGUEBERNEHMEN: {
    InvertX=E_InvertX;
    InvertY=E_InvertY;
    MouseSpeed=E_MouseSpeed;
    SchreibeKonfiguration();
    SetzeMenuZustand(EINSTELLUNGEN);
  } break;
  case S_EI_STEUERUNGZURUECK: {
    SetzeMenuZustand(EINSTELLUNGEN);
  } break;
  case S_EI_ZURUECK: {
    SetzeMenuZustand(HAUPTMENU);
  } break;
  case S_EI_ZURUECK_AS: {
    SetzeMenuZustand(AUSSPIEL);
  } break;
  case S_BE_JABEENDEN: {
    exit(0);
  } break;
  case S_BE_ZURUECK: {
    SetzeMenuZustand(HAUPTMENU);
  } break;
  case S_BE_ZURUECK_AS: {
    SetzeMenuZustand(AUSSPIEL);
  } break;
  case S_AS_WEITERSPIELEN: {
    SetzeMenuZustand(SPIEL);
  } break;
  case S_AS_HAUPTMENU: {
    AusSpiel=0;
    StateMaschin=START;
    SetzeMenuZustand(HAUPTMENU);
  } break;
  case S_AS_HILFE: {
    AusSpiel=1;
    SetzeMenuZustand(HILFE);
  } break;
  case S_AS_EINSTELLUNGEN: {
    AusSpiel=1;
    SetzeMenuZustand(EINSTELLUNGEN);
  } break;
  case S_AS_BEENDEN: {
    AusSpiel=1;
    SetzeMenuZustand(BEENDEN);
  } break;
  case S_SP_LOGO: {
    AusSpiel=1;
    SetzeMenuZustand(AUSSPIEL);
  } break;
  case S_SP_BALL+0: {
    if (StateMaschin==BETRACHTEN ||
	StateMaschin==WEISSNEU) {
      Kamera.BlickeAuf3(Kugel[0].Pos_xCM(),Kugel[0].Pos_yCM());
    } else if (StateMaschin==STOSS) {
      Kamera.Verfolge(0);
    }
  } break;
  case S_SP_BALL+1: {
    if (StateMaschin==BETRACHTEN ||
	StateMaschin==WEISSNEU) {
      Kamera.BlickeAuf3(Kugel[1].Pos_xCM(),Kugel[1].Pos_yCM());
    } else if (StateMaschin==STOSS) {
      Kamera.Verfolge(1);
    }
  } break;
  case S_SP_BALL+2: {
    if (StateMaschin==BETRACHTEN ||
	StateMaschin==WEISSNEU) {
      Kamera.BlickeAuf3(Kugel[2].Pos_xCM(),Kugel[2].Pos_yCM());
    } else if (StateMaschin==STOSS) {
      Kamera.Verfolge(2);
    }
  } break;
  case S_SP_BALL+3: {
    if (StateMaschin==BETRACHTEN ||
	StateMaschin==WEISSNEU) {
      Kamera.BlickeAuf3(Kugel[3].Pos_xCM(),Kugel[3].Pos_yCM());
    } else if (StateMaschin==STOSS) {
      Kamera.Verfolge(3);
    }
  } break;
  case S_SP_BALL+4: {
    if (StateMaschin==BETRACHTEN ||
	StateMaschin==WEISSNEU) {
      Kamera.BlickeAuf3(Kugel[4].Pos_xCM(),Kugel[4].Pos_yCM());
    } else if (StateMaschin==STOSS) {
      Kamera.Verfolge(4);
    }
  } break;
  case S_SP_BALL+5: {
    if (StateMaschin==BETRACHTEN ||
	StateMaschin==WEISSNEU) {
      Kamera.BlickeAuf3(Kugel[5].Pos_xCM(),Kugel[5].Pos_yCM());
    } else if (StateMaschin==STOSS) {
      Kamera.Verfolge(5);
    }
  } break;
  case S_SP_BALL+6: {
    if (StateMaschin==BETRACHTEN ||
	StateMaschin==WEISSNEU) {
      Kamera.BlickeAuf3(Kugel[6].Pos_xCM(),Kugel[6].Pos_yCM());
    } else if (StateMaschin==STOSS) {
      Kamera.Verfolge(6);
    }
  } break;
  case S_SP_BALL+7: {
    if (StateMaschin==BETRACHTEN ||
	StateMaschin==WEISSNEU) {
      Kamera.BlickeAuf3(Kugel[7].Pos_xCM(),Kugel[7].Pos_yCM());
    } else if (StateMaschin==STOSS) {
      Kamera.Verfolge(7);
    }
  } break;
  case S_SP_BALL+8: {
    if (StateMaschin==BETRACHTEN ||
	StateMaschin==WEISSNEU) {
      Kamera.BlickeAuf3(Kugel[8].Pos_xCM(),Kugel[8].Pos_yCM());
    } else if (StateMaschin==STOSS) {
      Kamera.Verfolge(8);
    }
  } break;
  case S_SP_BALL+9: {
    if (StateMaschin==BETRACHTEN ||
	StateMaschin==WEISSNEU) {
      Kamera.BlickeAuf3(Kugel[9].Pos_xCM(),Kugel[9].Pos_yCM());
    } else if (StateMaschin==STOSS) {
      Kamera.Verfolge(9);
    }
  } break;
  case S_SP_BALL+10: {
    if (StateMaschin==BETRACHTEN ||
	StateMaschin==WEISSNEU) {
      Kamera.BlickeAuf3(Kugel[10].Pos_xCM(),Kugel[10].Pos_yCM());
    } else if (StateMaschin==STOSS) {
      Kamera.Verfolge(10);
    }
  } break;
  case S_SP_BALL+11: {
    if (StateMaschin==BETRACHTEN ||
	StateMaschin==WEISSNEU) {
      Kamera.BlickeAuf3(Kugel[11].Pos_xCM(),Kugel[11].Pos_yCM());
    } else if (StateMaschin==STOSS) {
      Kamera.Verfolge(11);
    }
  } break;
  case S_SP_BALL+12: {
    if (StateMaschin==BETRACHTEN ||
	StateMaschin==WEISSNEU) {
      Kamera.BlickeAuf3(Kugel[12].Pos_xCM(),Kugel[12].Pos_yCM());
    } else if (StateMaschin==STOSS) {
      Kamera.Verfolge(12);
    }
  } break;
  case S_SP_BALL+13: {
    if (StateMaschin==BETRACHTEN ||
	StateMaschin==WEISSNEU) {
      Kamera.BlickeAuf3(Kugel[13].Pos_xCM(),Kugel[13].Pos_yCM());
    } else if (StateMaschin==STOSS) {
      Kamera.Verfolge(13);
    }
  } break;
  case S_SP_BALL+14: {
    if (StateMaschin==BETRACHTEN ||
	StateMaschin==WEISSNEU) {
      Kamera.BlickeAuf3(Kugel[14].Pos_xCM(),Kugel[14].Pos_yCM());
    } else if (StateMaschin==STOSS) {
      Kamera.Verfolge(14);
    }
  } break;
  case S_SP_BALL+15: {
    if (StateMaschin==BETRACHTEN ||
	StateMaschin==WEISSNEU) {
      Kamera.BlickeAuf3(Kugel[15].Pos_xCM(),Kugel[15].Pos_yCM());
    } else if (StateMaschin==STOSS) {
      Kamera.Verfolge(15);
    }
  } break;
  case S_SP_WEITERSPIELEN: {
    NeuAufbauenOderWeiterspielen=0;
    NeuAufbauenOderAchtEinsetzen=0;
    MenuGesperrt=0;
    NeuerMenuZustand();
  } break;
  case S_SP_ACHTEINSETZEN: {
    NeuAufbauenOderWeiterspielen=0;
    NeuAufbauenOderAchtEinsetzen=0;
    MenuGesperrt=0;
    AchtEinsetzen();
    NeuerMenuZustand();
  } break;
  case S_SP_NEUAUFBAUEN: {
    Foul=0;
    LageVerbesserungKopffeld=1;
    LageVerbesserung=0;
    NeuAufbauenOderWeiterspielen=0;
    NeuAufbauenOderAchtEinsetzen=0;
    Spieler1Gewonnen=0;
    Spieler2Gewonnen=0;
    MenuGesperrt=0;
    StateMaschin=SCHIEDSRICHTER;
    GLint Spieler=Schiedsrichter.FrageNachSpielerAmStoss();
    GLint Fouls0=Schiedsrichter.FrageNachFouls(0);
    GLint Fouls1=Schiedsrichter.FrageNachFouls(1);
    Schiedsrichter.NeuesSpiel(Spiel);
    //SchiedsrichterEntscheidung=0; nur nicht!
    Schiedsrichter.SetzeSpielerAmStoss(Spieler);
    Schiedsrichter.SetzeFouls(0,Fouls0);
    Schiedsrichter.SetzeFouls(1,Fouls1);    
    SpielfeldAufbau();
    Kamera.ladePosition(4);
    NeuerMenuZustand();
  } break;
  case S_SP_HAUPTMENU:{
    AusSpiel=0;
    StateMaschin=START;
    SetzeMenuZustand(HAUPTMENU);
  } break;
  case S_SP_NEUESSPIEL:{
    Foul=0;
    LageVerbesserungKopffeld=1;
    LageVerbesserung=0;
    NeuAufbauenOderWeiterspielen=0;
    NeuAufbauenOderAchtEinsetzen=0;
    Spieler1Gewonnen=0;
    Spieler2Gewonnen=0;
    NeuAufbauenOderWeiterspielen=0;
    NeuAufbauenOderAchtEinsetzen=0;
    MenuGesperrt=0;
    StateMaschin=SCHIEDSRICHTER;
    GLint Spieler=Schiedsrichter.FrageNachSpielerAmStoss();
    Schiedsrichter.NeuesSpiel(Spiel);
    SchiedsrichterEntscheidung=0;
    Schiedsrichter.SetzeSpielerAmStoss(1-Spieler);
    SpielfeldAufbau();
    Kamera.ladePosition(4);
    NeuerMenuZustand();
  } break;
  case S_SP_NEUEACHTBALLAUFSTELLUNG:{
   if (StateMaschin==BETRACHTEN||
       StateMaschin==WEISSNEU) {
     Spiel=ACHTBALL;
     SpielfeldAufbau();
   }
  } break;
  case S_SP_NEUENEUNBALLAUFSTELLUNG:{
   if (StateMaschin==BETRACHTEN||
       StateMaschin==WEISSNEU) {
     Spiel=NEUNBALL;
     SpielfeldAufbau();
   }
  } break;
  case S_SPIELER1HERHOEREN:{
    for (GLint TextfeldNr=0;TextfeldNr<1000;TextfeldNr++) {
      if (TextfeldArray[TextfeldNr]) 
	TextfeldArray[TextfeldNr]->Weghoeren();
    }
    TextfeldArray[T_SPIELER1NAME]->Herhoeren();
  } break;
  case S_SPIELER2HERHOEREN:{
    for (GLint TextfeldNr=0;TextfeldNr<1000;TextfeldNr++) {
      if (TextfeldArray[TextfeldNr]) 
	TextfeldArray[TextfeldNr]->Weghoeren();
    }
    TextfeldArray[T_SPIELER2NAME]->Herhoeren();
  } break;
  case S_NETZWERKSPIELERHERHOEREN:{
    //for (GLint TextfeldNr=0;TextfeldNr<TextfeldAnzahl;TextfeldNr++) {
    //  TextfeldArray[TextfeldNr]->Weghoeren();
    //}
    //T_NetzwerkSpielerName.Herhoeren();
  } break;
  case S_H_TASTENBELEGUNGEN: {
    SetzeMenuZustand(HILFETASTENBELEGUNGEN);
  } break;
  case S_H_BILLARDREGELN: {
    SetzeMenuZustand(HILFEREGELN1);
  } break;
  case S_H_TUTORIAL: {
    Foul=0;
    LageVerbesserungKopffeld=0;
    LageVerbesserung=0;
    NeuAufbauenOderWeiterspielen=0;
    NeuAufbauenOderAchtEinsetzen=0;
    Spieler1Gewonnen=0;
    Spieler2Gewonnen=0;
    MenuGesperrt=0;
    SpielModus=TUTORIAL;
    StateMaschin=BETRACHTEN;
    Spiel=ACHTBALL;
    SpielfeldAufbau();
    Schiedsrichter.NeuesSpiel(Spiel);
    SchiedsrichterEntscheidung=0;
    Kamera.ladePosition(4);
    SetzeMenuZustand(SPIEL);
  } break;
  case S_H_ZUHILFE: {
    SetzeMenuZustand(HILFE);
  } break;
  case S_H_E1_N: {
    SetzeMenuZustand(HILFEEINFUEHRUNG2);
  } break;
  case S_H_E2_N: {
    SetzeMenuZustand(HILFEEINFUEHRUNG3);
  } break;
  case S_H_E2_L: {
    SetzeMenuZustand(HILFEEINFUEHRUNG1);
  } break;
  case S_H_E3_N: {
    SetzeMenuZustand(HILFEEINFUEHRUNG4);
  } break;
  case S_H_E3_L: {
    SetzeMenuZustand(HILFEEINFUEHRUNG2);
  } break;
  case S_H_E4_N: {
    SetzeMenuZustand(HILFEEINFUEHRUNG5);
  } break;
  case S_H_E4_L: {
    SetzeMenuZustand(HILFEEINFUEHRUNG3);
  } break;
  case S_H_E5_N: {
    SetzeMenuZustand(HILFEEINFUEHRUNG6);
  } break;
  case S_H_E5_L: {
    SetzeMenuZustand(HILFEEINFUEHRUNG4);
  } break;
  case S_H_E6_N: {
    SetzeMenuZustand(HILFEEINFUEHRUNG7);
  } break;
  case S_H_E6_L: {
    SetzeMenuZustand(HILFEEINFUEHRUNG5);
  } break;
  case S_H_R1_N: {
    SetzeMenuZustand(HILFEREGELN2);
  } break;
  case S_H_R2_N: {
    SetzeMenuZustand(HILFEREGELN3);
  } break;
  case S_H_R2_L: {
    SetzeMenuZustand(HILFEREGELN1);
  } break;
  case S_H_R3_N: {
    SetzeMenuZustand(HILFEREGELN4);
  } break;
  case S_H_R3_L: {
    SetzeMenuZustand(HILFEREGELN2);
  } break;
  case S_H_R4_N: {
    SetzeMenuZustand(HILFEREGELN5);
  } break;
  case S_H_R4_L: {
    SetzeMenuZustand(HILFEREGELN3);
  } break;
  case S_H_R5_N: {
    SetzeMenuZustand(HILFEREGELN6);
  } break;
  case S_H_R5_L: {
    SetzeMenuZustand(HILFEREGELN4);
  } break;
  case S_H_R6_N: {
    SetzeMenuZustand(HILFEREGELN7);
  } break;
  case S_H_R6_L: {
    SetzeMenuZustand(HILFEREGELN5);
  } break;

  default:{
    if (Signal>=900 && Signal<990) {
      ladeSprache(Signal);
      for (GLint dl=0 ; dl < 1000 ; dl++ ) {
	if (!TextfeldArray[dl]) continue;
	TextfeldArray[dl]->GeneriereDisplayList();
	printf("."); fflush(stdout);
      }
      if (Sprache) SetzeMenuZustand(EINSTELLUNGEN);
      else SignalAusfuehrung(S_H_TUTORIAL);
	//SetzeMenuZustand(HAUPTMENU);
      Sprache=Signal;
      SchreibeKonfiguration();
    }
  } break;
  }
}

GLint Menu::KeyboardTaste (unsigned char Taste,int,int){

  GLint Reaktion=0;
  GLint TextfeldNr=0;

  while (!Reaktion && TextfeldNr<1000) {
    if( TextfeldArray[TextfeldNr] ) 
      Reaktion = TextfeldArray[TextfeldNr]->Zeichen(Taste);
    
    //if (Reaktion) {
    //  printf("\nReaktion von %i\n",TextfeldNr);
    //  printf("%s",TextfeldArray[TextfeldNr]->Text());
    //}

    TextfeldNr++;
  }

  if (Reaktion) return 1;

  if (MenuGesperrt || 
      MenuZustand!=SPIEL) {
    return 1;
  }

  //Esc-Sequenzen ;)

  switch (MenuZustand) {
    
  case STARTBILDSCHIRM: {
    switch (Taste) {
    case 27: {
      MenuZustand=HAUPTMENU;
      NeuerMenuZustand();
      return 1;
    } break;
    }
  } break;
    
  case HAUPTMENU:{
    switch (Taste) {
    case 27: {
      MenuZustand=BEENDEN;
      NeuerMenuZustand();
      return 1;
    } break;
    }
  } break;

  case TRAINING:{
    switch (Taste) {
    case 27: {
      MenuZustand=HAUPTMENU;
      NeuerMenuZustand();
      return 1;
    } break;
    }
  } break;

  case ZWEISPIELER:{
    switch (Taste) {
    case 27: {
      MenuZustand=HAUPTMENU;
      NeuerMenuZustand();
      return 1;
    } break;
    }
  } break;

  case NETZWERKHAUPT:{
    switch (Taste) {
    case 27: {
      MenuZustand=HAUPTMENU;
      NeuerMenuZustand();
      return 1;
    } break;
    }
  } break;

  case NETZWERKNEU:{
    switch (Taste) {
    case 27: {
      MenuZustand=NETZWERKHAUPT;
      NeuerMenuZustand();
      return 1;
    } break;
    }
  } break;

  case NETZWERKBEITRETEN:{
    switch (Taste) {
    case 27: {
      MenuZustand=NETZWERKHAUPT;
      NeuerMenuZustand();
      return 1;
    } break;
    }
  } break;

  case BEENDEN:{
    switch (Taste) {
    case 27: {
      MenuZustand=HAUPTMENU;
      NeuerMenuZustand();
      return 1;
    } break;
    }
  } break;

  case AUSSPIEL:{
  } break;

  case EINSTELLUNGEN:{
  } break;

  }

  return 0;
}

void Menu::SetzeFPS(GLint fps) {
  char temp[]={0,0,0,0,0,0,0,0,0,0};
  sprintf(temp,"%i fps",fps);
  TextfeldArray[T_FPS]->SetzeText(temp);
}
