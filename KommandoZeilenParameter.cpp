#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Namen.h"
#include "KommandoZeilenParameter.h"

void SchreibeKonfiguration(){
  FILE *f;
#ifndef _WIN32
  char dateiname[40];
  sprintf(dateiname,"%s/.BillardGL.conf.v7",getenv("HOME"));
  f=fopen(dateiname,"w+");
#endif
#ifdef _WIN32
  f=fopen("BillardGL.conf.v7","wb+");
#endif
  if (f) {
    char Spieler1temp[10];
    char Spieler2temp[10];
    char NetzwerkSpielertemp[10];
    for (int i=0;i<10;i++) {
      if (Spieler1[i]==' ') {
	Spieler1temp[i]='%';
      } else {
	Spieler1temp[i]=Spieler1[i];
      }
      if (Spieler2[i]==' ') {
	Spieler2temp[i]='%';
      } else {
	Spieler2temp[i]=Spieler2[i];
      }
      if (NetzwerkSpieler[i]==' ') {
	NetzwerkSpielertemp[i]='%';
      } else {
	NetzwerkSpielertemp[i]=NetzwerkSpieler[i];
      }
    }
    fprintf(f,"%i\n",Texturgroesse);
    fprintf(f,"%i\n",AnzeigeTexturgroesse);
    fprintf(f,"%i\n",TischTexturgroesse);
    fprintf(f,"%i\n",KugelAufloesung);
    fprintf(f,"%f\n",MouseSpeed);
    fprintf(f,"%i\n",InvertX);
    fprintf(f,"%i\n",InvertY);
    fprintf(f,"%i\n",BildschirmAufloesung);
    fprintf(f,"%i\n",Farbtiefe);
    fprintf(f,"%i\n",Reflektionen);
    fprintf(f,"%i\n",Schatten);
    fprintf(f,"%i\n",TexMMM);
    fprintf(f,"%i\n",Sprache);
    fprintf(f,"%i\n",ZeigeFPS);
    fprintf(f,"%i\n",AmbientesLicht);
    fprintf(f,"%i\n",TischLampen);
    fprintf(f,"%i\n",GrueneLampe);
    fprintf(f,"%f\n",EffektLautstaerke);
    fprintf(f,"%f\n",MusikLautstaerke);
    fprintf(f,"%s\n",Spieler1temp);
    fprintf(f,"%s\n",Spieler2temp);
    fprintf(f,"%s\n",NetzwerkSpielertemp);
    fclose(f);
  }
}

void LeseKonfiguration(){
  FILE *f;
#ifndef _WIN32
  char dateiname[40];
  sprintf(dateiname,"%s/.BillardGL.conf.v7",getenv("HOME"));
  f=fopen(dateiname,"r");
#endif
#ifdef _WIN32
  f=fopen("BillardGL.conf.v7","rb");
#endif
  if (f) {
    char Spieler1temp[10];
    char Spieler2temp[10];
    char NetzwerkSpielertemp[10];
    fscanf(f,"%i",&Texturgroesse);
    fscanf(f,"%i",&AnzeigeTexturgroesse);
    fscanf(f,"%i",&TischTexturgroesse);
    fscanf(f,"%i",&KugelAufloesung);
    fscanf(f,"%f",&MouseSpeed);
    fscanf(f,"%i",&InvertX);
    fscanf(f,"%i",&InvertY);
    fscanf(f,"%i",&BildschirmAufloesung);
    fscanf(f,"%i",&Farbtiefe);
    fscanf(f,"%i",&Reflektionen);
    fscanf(f,"%i",&Schatten);
    fscanf(f,"%i",&TexMMM);
    fscanf(f,"%i",&Sprache);
    fscanf(f,"%i",&ZeigeFPS);
    fscanf(f,"%i",&AmbientesLicht);
    fscanf(f,"%i",&TischLampen);
    fscanf(f,"%i",&GrueneLampe);
    fscanf(f,"%f",&EffektLautstaerke);
    fscanf(f,"%f",&MusikLautstaerke);
    fscanf(f,"%s",Spieler1temp);
    fscanf(f,"%s",Spieler2temp);
    fscanf(f,"%s",NetzwerkSpielertemp);
    for (int i=0;i<10;i++) {
      if (Spieler1temp[i]=='%') {
	Spieler1[i]=' ';
      } else {
	Spieler1[i]=Spieler1temp[i];
      }
      if (Spieler2temp[i]=='%') {
	Spieler2[i]=' ';
      } else {
	Spieler2[i]=Spieler2temp[i];
      }
      if (NetzwerkSpieler[i]=='%') {
	NetzwerkSpieler[i]=' ';
      } else {
	NetzwerkSpieler[i]=NetzwerkSpielertemp[i];
      }
    }
  }
}

void KommandoZeilenParameter(int argc,char **argv) {

  // Titeltext
  //#ifndef _WIN32
  printf("\n BillardGL (C) 2001, 2002 Tobias Nopper, Stefan Disch, Martina Welte\n\n");
  //#endif

  //Defaultwerte
  Texturgroesse        = 2;
  AnzeigeTexturgroesse = 1;
  TischTexturgroesse   = 2;
  KugelAufloesung      = 7;
  InvertX              = 0;
  InvertY              = 0;
  Spiel                = ACHTBALL;
  Schatten             = 1;

  TexMMM               = 3;

  Epsilon              = 0.05;
  MouseSpeed           = 0.4;
  PhysikFrequenz       = 400;
  ReibungsFaktor       = 1.2;
  BandenFaktor         = 0.4;
  KollisionsFaktor     = 0.95;
  ZBufferLoeschen      = 1;
  BildschirmAufloesung = 800;
  Farbtiefe            = 16;
  Reflektionen         = 0;
  Sprache              = 0;

  ZeigeFPS             = 0;
  AmbientesLicht       = 1;
  TischLampen          = 2;
  GrueneLampe          = 0;

  FullScreen           = 1;

  EffektLautstaerke    = .5;
  MusikLautstaerke     = .5;

  sprintf(Spieler1,"Name 1");
  sprintf(Spieler2,"Name 2");
  sprintf(NetzwerkSpieler,"Name");

  LeseKonfiguration();

  // Einlesen der Kommandozeilenparameter
  int i=1;
  while (i<argc) {
    if (!strcmp(argv[i],"-y")||!strcmp(argv[i],"-inverty")) {
      InvertY = 1; 
    } else if (!strcmp(argv[i],"-x")||!strcmp(argv[i],"-invertx")) {
      InvertX = 1; 
    } else if (!strcmp(argv[i],"-z")||!strcmp(argv[i],"-zbuffer")) {
      ZBufferLoeschen = 0; 
    } else if (!strcmp(argv[i],"-f")||!strcmp(argv[i],"-fullscreen")) {
      FullScreen = 1; 
    } else if (!strcmp(argv[i],"-w")||!strcmp(argv[i],"-windowed")) {
      FullScreen = 0; 
    } else if (!strcmp(argv[i],"-hq")||!strcmp(argv[i],"-highquality")) {
      Texturgroesse=2;
      AnzeigeTexturgroesse = 2;
      TischTexturgroesse   = 1;
      KugelAufloesung      = 9;
      BildschirmAufloesung = 1024;
      Farbtiefe            = 32;
      Reflektionen = 1;
    } else if (!strcmp(argv[i],"-t")||!strcmp(argv[i],"-texturen")) {
      i++;
      if (!strcmp(argv[i],"1")||!strcmp(argv[i],"voll")) {
	Texturgroesse=1;
      } else if (!strcmp(argv[i],"2")||!strcmp(argv[i],"halb")) {
	Texturgroesse=2;
      } else if (!strcmp(argv[i],"4")||!strcmp(argv[i],"viertel")) {
	Texturgroesse=4;
      } else if (!strcmp(argv[i],"8")||!strcmp(argv[i],"achtel")) {
	Texturgroesse=8;
      } else if (!strcmp(argv[i],"0")||!strcmp(argv[i],"aus")) {
	Texturgroesse=0;
      } 
    } else if (!strcmp(argv[i],"-at")||!strcmp(argv[i],"-atexturen")) {
      i++;
      if (!strcmp(argv[i],"1")||!strcmp(argv[i],"voll")) {
	AnzeigeTexturgroesse=1;
      } else if (!strcmp(argv[i],"2")||!strcmp(argv[i],"halb")) {
	AnzeigeTexturgroesse=2;
      } else if (!strcmp(argv[i],"4")||!strcmp(argv[i],"viertel")) {
	AnzeigeTexturgroesse=4;
      } else if (!strcmp(argv[i],"8")||!strcmp(argv[i],"achtel")) {
	AnzeigeTexturgroesse=8;
      } else if (!strcmp(argv[i],"0")||!strcmp(argv[i],"aus")) {
	AnzeigeTexturgroesse=0;
      } 
    } else if (!strcmp(argv[i],"-tt")||!strcmp(argv[i],"-ttexturen")) {
      i++;
      if (!strcmp(argv[i],"1")||!strcmp(argv[i],"voll")) {
	TischTexturgroesse=1;
      } else if (!strcmp(argv[i],"2")||!strcmp(argv[i],"halb")) {
	TischTexturgroesse=2;
      } else if (!strcmp(argv[i],"4")||!strcmp(argv[i],"viertel")) {
	TischTexturgroesse=4;
      } else if (!strcmp(argv[i],"8")||!strcmp(argv[i],"achtel")) {
	TischTexturgroesse=8;
      } else if (!strcmp(argv[i],"0")||!strcmp(argv[i],"aus")) {
	TischTexturgroesse=0;
      } 
    } else if (!strcmp(argv[i],"-a")||!strcmp(argv[i],"-aufstellung")) {
      i++;
      if (!strcmp(argv[i],"2")||!strcmp(argv[i],"s")||!strcmp(argv[i],"simpel")||!strcmp(argv[i],"zweibaelle")) {
	Spiel=ZWEIBAELLE;
      } else if (!strcmp(argv[i],"8")||!strcmp(argv[i],"a")||!strcmp(argv[i],"achtball")||!strcmp(argv[i],"8ball")||!strcmp(argv[i],"8-ball")) {
	Spiel=ACHTBALL;
      } else if (!strcmp(argv[i],"9")||!strcmp(argv[i],"n")||!strcmp(argv[i],"neunball")||!strcmp(argv[i],"9ball")||!strcmp(argv[i],"9-ball")) {
	Spiel=NEUNBALL;
      } else if (!strcmp(argv[i],"0")||!strcmp(argv[i],"l")||!strcmp(argv[i],"leer")) {
	Spiel=LEER;
      } else if (!strcmp(argv[i],"z")||!strcmp(argv[i],"zufall")) {
	Spiel=ZUFALL;
      }
    } else if (!strcmp(argv[i],"-s")||!strcmp(argv[i],"-schatten")) {
	Schatten=0;
    } else if (!strcmp(argv[i],"-g")||!strcmp(argv[i],"-geometrie")) {
      i++;
      KugelAufloesung=atoi(argv[i]);
    } else if (!strcmp(argv[i],"-ep")||!strcmp(argv[i],"-epsilon")) {
      i++;
      Epsilon=atof(argv[i]);
    } else if (!strcmp(argv[i],"-m")||!strcmp(argv[i],"-mousespeed")) {
      i++;
      MouseSpeed=atof(argv[i]);
    } else if (!strcmp(argv[i],"-p")||!strcmp(argv[i],"-physik")) {
      i++;
      PhysikFrequenz=atoi(argv[i]);
    } else if (!strcmp(argv[i],"-r")||!strcmp(argv[i],"-reibung")) {
      i++;
      ReibungsFaktor=atof(argv[i]);
    } else if (!strcmp(argv[i],"-k")||!strcmp(argv[i],"-kollision")) {
      i++;
      KollisionsFaktor=atof(argv[i]);
    } else if (!strcmp(argv[i],"-b")||!strcmp(argv[i],"-banden")) {
      i++;
      BandenFaktor=atof(argv[i]);
    } 

    i++;
  }

  SchreibeKonfiguration();
  
  
  //#ifndef _WIN32
  
  //Ausgabe der Parameter
  /*
    printf("  Ball textures : ");
    switch (Texturgroesse) {
    case 1: printf("High");break;
    case 2: printf("Normal");break;
    case 4: printf("Low");break;
    case 8: printf("Very low");break;
    case 0: printf("Off");break;
    }
    
    printf("\n  Menu textures : ");
    switch (AnzeigeTexturgroesse) {
    case 1: printf("Normal");break;
    case 2: printf("Low");break;
    case 4: printf("Groesse 4 - Viertel");break;
    case 8: printf("Groesse 8 - Achtel");break;
    case 0: printf("Aus");break;
    }
    
    printf("\n  Table texture : ");
    switch (TischTexturgroesse) {
    case 1: printf("High");break;
    case 2: printf("Normal");break;
    case 4: printf("Low");break;
    case 8: printf("Very Low");break;
    case 0: printf("Off");break;
    }
    
    printf("\n");
    
    if (ZBufferLoeschen) {
    printf("  ZBufferLoesch.: Ein\n");
    } else {
    printf("  ZBufferLoesch.: Aus\n");
    AnzeigeTexturgroesse=0;
    Schatten=0;
    }
    
    printf("  Ball Res.     : %i\n",KugelAufloesung);
    
    printf("  Shadows       : ");
    switch (Schatten) {
    case 1: printf("On");break;
    case 0: printf("Off");break;
    }
    //  printf("  Epsilon       : %f\n",Epsilon);
    
    printf("\n  Mousespeed    : %f\n",MouseSpeed);
    
    if (InvertX) {
    printf("  InvertX       : On\n");
    } else {
    printf("  InvertX       : Off\n");
    }
    
    if (InvertY) {
    printf("  InvertY       : On\n");
    } else {
    printf("  InvertY       : Off\n");
    }
    
    printf("  Spiel         : ");
    switch (Spiel) {
    case ZWEIBAELLE: printf("Zwei Kugeln");break;
    case ACHTBALL: printf("8-Ball");break;
    case NEUNBALL: printf("9-Ball");break;
    case ZUFALL: printf("Zufall");break;
    case LEER: printf("Aus");break;
    }
    
    //printf("\n  Physikfrequenz: %i\n",PhysikFrequenz);
    //printf("  Reibungsfaktor: %f\n",ReibungsFaktor);
    //printf("  Bandenfaktor  : %f\n",BandenFaktor);
    //printf("  Koll.faktor   : %f\n",KollisionsFaktor);
    //printf("  Bildschirmaufl: %i\n",BildschirmAufloesung);
    
    
    printf("\n");
    
    //#endif
    */
}
