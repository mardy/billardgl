#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "LA.h"
#include "bmp.h"
#include "createTexture.h"
#include "Textfeld.h"

GLint links[] = {
 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
 0,  9, 11,  9,  9,  8,  8,  7,  8,  7,  7,  7,  6,  8,  9,  7, 
 9,  7,  8,  7,  7,  7,  8,  7,  7,  7,  9,  6,  8,  7,  7,  7, 
 9,  7,  9,  8,  9,  9,  9,  8,  8,  8,  7,  8,  8,  7,  8,  7, 
 9,  8,  9,  7,  6,  8,  6,  7,  7,  6,  6, 10,  7,  7,  9,  5, 
 5,  8,  9,  8,  8,  8,  6,  7,  8,  8,  8,  8,  8,  7,  8,  7, 
 9,  8,  9,  8,  7,  8,  7,  7,  7,  7,  7,  7,  9,  6,  8,  0, 

 0,  0,  0,  8,  7, 10,  8,  8,  3,  7,  0,  9,  7,  0,  0,  0, 
 0,  7,  8,  8,  7, 10,  7,  8,  3,  9,  0, 10,  7,  0,  0,  0, 
 0,  9, 11,  8, 10,  8, 10,  9,  4,  8,  7,  9,  7,  0,  7,  0, 
 0,  8,  8,  8,  7,  8,  8,  9,  7,  7,  7,  9,  8,  8,  8,  7, 
 8,  7,  8,  7,  7,  7,  7,  8,  8,  8,  8,  8,  4,  7,  3,  4, 
 6,  9,  8,  8,  8,  8,  8,  0,  7,  8,  8,  8,  8,  6,  8,  8, 
 8,  8,  8,  8,  8,  8,  8,  7,  7,  7,  7,  7,  4,  6,  3,  3, 
 9,  9,  8,  8,  8,  8,  8,  0,  7,  8,  8,  8,  8,  6,  8,  6
};

GLint rechts[]={
 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
10, 15, 22, 28, 29, 33, 33, 15, 15, 14, 20, 29, 14, 21, 14, 23, 
31, 17, 26, 26, 30, 26, 27, 25, 27, 27, 15, 14, 28, 28, 28, 25, 
37, 32, 29, 30, 32, 24, 24, 34, 32, 14, 21, 30, 23, 39, 32, 34,
29, 36, 29, 27, 25, 32, 30, 43, 30, 28, 27, 19, 23, 16, 27, 26, 
15, 28, 29, 24, 28, 27, 20, 27, 27, 13, 13, 26, 13, 38, 26, 27, 
28, 28, 20, 23, 19, 27, 25, 37, 26, 26, 24, 19, 12, 19, 28,  0, 

 0,  0,  0, 28, 25, 43, 28, 28, 18, 47,  0, 17, 43,  0,  0,  0, 
 0, 16, 16, 25, 25, 23, 26, 22, 18, 44,  0, 17, 42,  0,  0,  0, 
 0, 15, 28, 31, 29, 30, 13, 28, 17, 37, 20, 27, 29,  0, 36,  0, 
 0, 30, 20, 20, 17, 27, 29, 15, 15, 13, 20, 27, 42, 41, 42, 24, 
32, 32, 32, 31, 31, 31, 40, 30, 24, 24, 24, 24, 15, 17, 18, 17, 
32, 33, 35, 35, 34, 35, 35,  0, 35, 32, 32, 32, 32, 27, 28, 27, 
28, 28, 28, 28, 28, 28, 43, 24, 27, 27, 27, 27, 14, 17, 18, 17, 
28, 27, 28, 28, 28, 28, 28,  0, 28, 26, 26, 26, 26, 25, 28, 25
};

Textfeld::Textfeld() {
  //
  x=y=Hoehe=Aspekt=Alpha = 0;
  alt_x=alt_y=alt_Hoehe=alt_Alpha = 0;
  soll_x=soll_y=soll_Hoehe=soll_Alpha = 0;
  Ausrichtung = 0;
  InAnimation = 0;
  Signal = 0;
  Zeit = 0; 
  DisplayListAnfang = 0;
  for (GLint i=0;i<512;i++)
	  TexturenAnfang[i] = 0;
  TextfeldIndex = 0;
  Horchen = 0;
  Zeilen=0;

  MaxBreite=0;

}

GLint Textfeld::dummyInitialisiere(GLint TexGr){
  FMatrix tex;
  if (!DisplayListAnfang)
    DisplayListAnfang=glGenLists(512);
  
  if (!TexturenAnfang[0]) 
    glGenTextures(512,&TexturenAnfang[0]);

  char DateiName[80];
  sprintf(DateiName,"Texturen/%i/buchstaben.bmp",TexGr); 
  loadBMP(tex,tex,tex,DateiName);
  GLint Rastergroesse=(tex.nch+1)/16;

  for (GLint Buchstabe=0;Buchstabe<256;Buchstabe++) {
    GLint x = Buchstabe % 16;
    GLint y = Buchstabe / 16;

    if (rechts[Buchstabe] && Buchstabe!=32) {
      glBindTexture(GL_TEXTURE_2D,TexturenAnfang[Buchstabe]);
      createTextureText(tex,x,y,Rastergroesse);
	}

    glNewList(DisplayListAnfang+Buchstabe,GL_COMPILE_AND_EXECUTE);
    if (rechts[Buchstabe] && Buchstabe!=32) {
      glBindTexture(GL_TEXTURE_2D,TexturenAnfang[Buchstabe]);
      //glEnable(GL_TEXTURE_2D);
      //glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
      glBegin(GL_QUADS);
      //    printf ("%i %i %i\n",Buchstabe,x,y);
      glTexCoord2f(0.0,0.0);glVertex2f(0.0,0.0);
      glTexCoord2f(1.0,0.0);glVertex2f(1.0,0.0);
      glTexCoord2f(1.0,1.0);glVertex2f(1.0,1.0);
      glTexCoord2f(0.0,1.0);glVertex2f(0.0,1.0);
      glEnd();     
      //glDisable(GL_TEXTURE_2D);
    }
    glEndList();
  }

  sprintf(DateiName,"Texturen/%i/buchstabenalpha.bmp",TexGr); 
  loadBMP(tex,tex,tex,DateiName);
  Rastergroesse=(tex.nch+1)/16;

  for (GLint Buchstabe2=0;Buchstabe2<256;Buchstabe2++) {
    GLint x = Buchstabe2 % 16;
    GLint y = Buchstabe2 / 16;

    if (rechts[Buchstabe2] && Buchstabe2!=32) {
      glBindTexture(GL_TEXTURE_2D,TexturenAnfang[256+Buchstabe2]);
      createTextureText2(tex,x,y,Rastergroesse);
	}

    glNewList(DisplayListAnfang+256+Buchstabe2,GL_COMPILE_AND_EXECUTE);
    if (rechts[Buchstabe2] && Buchstabe2!=32) {
      glBindTexture(GL_TEXTURE_2D,TexturenAnfang[256+Buchstabe2]);
      //glEnable(GL_TEXTURE_2D);
      //glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
      glBegin(GL_QUADS);
      //    printf ("%i %i %i\n",Buchstabe,x,y);
      glTexCoord2f(0.0,0.0);glVertex2f(0.0,0.0);
      glTexCoord2f(1.0,0.0);glVertex2f(1.0,0.0);
      glTexCoord2f(1.0,1.0);glVertex2f(1.0,1.0);
      glTexCoord2f(0.0,1.0);glVertex2f(0.0,1.0);
      glEnd();     
      //glDisable(GL_TEXTURE_2D);
    }
    glEndList();
  }

  tex.free_FMatrix();

  x=y=Hoehe=Aspekt=Alpha=0.0;
  alt_x=alt_y=alt_Hoehe=alt_Alpha=0.0;
  soll_x=soll_y=soll_Hoehe=soll_Alpha=0.0;
  Ausrichtung=A_LINKS;
  InAnimation=0;
  Signal=0;
  Zeit=0;
  Zeichenkette[0]='\0';
  Horchen=0;
  return DisplayListAnfang;
}





void Textfeld::Initialisiere(GLint DLA){
  DisplayListAnfang=DLA;
  x=y=Hoehe=Aspekt=Alpha=0.0;
  alt_x=alt_y=alt_Hoehe=alt_Alpha=0.0;
  soll_x=soll_y=soll_Hoehe=soll_Alpha=0.0;
  Ausrichtung=A_LINKS;
  InAnimation=0;
  Signal=0;
  Zeit=0;
  Zeichenkette[0]='\0';
  Horchen=0;
}  

void Textfeld::Initialisiere(GLint DLA, const char *TextZ){
  Initialisiere(DLA);
  SetzeText(TextZ);
}

void Textfeld::InitialisiereKDL(GLint DLA, char TextZ[]){
  Initialisiere(DLA);
  SetzeTextKDL(TextZ);
}

void Textfeld::male(){  
	if (Alpha<.03) {return;}
    glPushMatrix();
    glTranslatef(x,y,0);
    glScalef(Hoehe,Hoehe,1);
    glColor4f(1.0,1.0,1.0,Alpha);
    glCallList(TextfeldIndex);
    glPopMatrix();
  
}

void Textfeld::PositioniereFix(GLfloat X,GLfloat Y,GLfloat H,GLint A){

  if (A) Ausrichtung=A;

  switch (Ausrichtung) {
  case A_LINKS: { soll_x = X; } break;
  case A_MITTE: { soll_x = X-.5*Aspekt*H; } break;
  case A_RECHTS:{ soll_x = X-Aspekt*H; } break;
  }

  soll_y     = Y;
  soll_Hoehe = H; 
  soll_Alpha = EINGEBLENDET;

  x=soll_x;
  y=soll_y;
  Hoehe=soll_Hoehe;
    
  Signal=0;
  
}

void Textfeld::Positioniere(GLfloat X,GLfloat Y,GLfloat H,GLint A){

  if (A) Ausrichtung=A;

  switch (Ausrichtung) {
  case A_LINKS: { soll_x = X; } break;
  case A_MITTE: { soll_x = X-.5*Aspekt*H; } break;
  case A_RECHTS:{ soll_x = X-Aspekt*H; } break;
  }

  soll_y     = Y;
  soll_Hoehe = H; 
  soll_Alpha = EINGEBLENDET;

  if (Alpha==AUSGEBLENDET) {
    
    x=((soll_x-8)/1.5)+8;
    y=((soll_y-6)/1.5)+6;
    Hoehe=soll_Hoehe/1.5;
    
    /*
      ax=((24.0*rand())/RAND_MAX)-4;
      ay=((14.0*rand())/RAND_MAX)-1;
      bx=ax+2*(bx_-ax_);
      by=ay+2*(by_-ay_);     
    */
  }
  
  Signal=0;
  
  StarteAnimation();
}


void Textfeld::SetzeText(const char *TextZ){
  int i=0;
  while (TextZ[i] && i<1999) {
    Zeichenkette[i]=TextZ[i];
    i++;
  }
  Zeichenkette[i]=0;
  GeneriereDisplayList();
}

void Textfeld::SetzeTextKDL(char TextZ[]){
  int i=0;
  while (TextZ[i] && i<1999) {
    Zeichenkette[i]=TextZ[i];
    i++;
  }
  Zeichenkette[i]=0;
}

GLint Textfeld::Zeichen(char Taste){
  if (Horchen) {
    if (Taste>=32 &&
	Taste!=8 && Taste!=127 &&
	Taste!=12 && Taste!=10 ) {//normale Zeichen
      GLint i;
      for (i=0;i<9 && Zeichenkette[i];i++) {}
      if (i<9) sprintf(Zeichenkette,"%s%c",Zeichenkette,Taste);
      GeneriereDisplayList();
      return 1;
    } else if (Taste==8 || Taste==127) { // loeschen
      for (GLint i=0;i<9;i++) 
	if (!Zeichenkette[i+1]) Zeichenkette[i]='\0';
      GeneriereDisplayList();
      return 1;
    } else if (Taste==13 || Taste==10) { // enter
      soll_Alpha=EINGEBLENDET;
      Horchen=0;
      if (soll_Alpha!=Alpha) StarteAnimation();
      //GeneriereDisplayList();
      return 1;
    }
  }
  return 0;
}

char* Textfeld::Text(){return Zeichenkette;}

void Textfeld::Desaktiviere(){
  soll_Alpha=AUSGEBLENDET;
  
  soll_x=((x-8)*1.5)+8;
  soll_y=((y-6)*1.5)+6;
  soll_Hoehe=Hoehe*1.5;

  Horchen = 0;
  
  if (soll_Alpha!=Alpha) StarteAnimation();
}

void Textfeld::Weghoeren(){
  if (Alpha && soll_Alpha) Eingeblendet();
  Horchen = 0;
}

void Textfeld::Herhoeren(){
  VollSichtbar();
  Horchen = 1;
}

void Textfeld::Angewaehlt(){
  Alpha=ANGEWAEHLT;
  soll_Alpha=EINGEBLENDET;
  if (soll_Alpha!=Alpha) StarteAnimation();
}

void Textfeld::Eingeblendet(){
  soll_Alpha=EINGEBLENDET;
  if (soll_Alpha!=Alpha) StarteAnimation();
}

void Textfeld::VollSichtbar(){
  soll_Alpha=VOLLSICHTBAR;
  if (soll_Alpha!=Alpha) StarteAnimation();
}

GLint Textfeld::Animiere(GLint Faktor){
  if (!InAnimation) {return 0;}
  Zeit+=Faktor;
  if (Zeit>=ANIMATIONSDAUER) {
    x=soll_x;
    y=soll_y;
    Hoehe=soll_Hoehe;
    Alpha=soll_Alpha;
    InAnimation=0;
    return 1;
  } else {
    GLfloat Faktor=(.5-.5*cos(M_PI*Zeit/ANIMATIONSDAUER));
    x=(soll_x-alt_x)*Faktor+alt_x;
    y=(soll_y-alt_y)*Faktor+alt_y;
    Hoehe=(soll_Hoehe-alt_Hoehe)*Faktor+alt_Hoehe;
    Alpha=(soll_Alpha-alt_Alpha)*Faktor+alt_Alpha;
    //    printf("%i: %f\n",Zeit,Alpha);
    return 0;
  }
}

void Textfeld::SetzeSignal(GLint NeuesSignal){
  Signal=NeuesSignal;
}

void Textfeld::StarteAnimation(){
  InAnimation=1;
  Zeit=0;
  alt_x=x;
  alt_y=y;
  alt_Hoehe=Hoehe;
  alt_Alpha=Alpha;
}

void Textfeld::GeneriereDisplayList(){
  if (!TextfeldIndex) {
    TextfeldIndex=glGenLists(1);
  }
  
 
  if (!MaxBreite) {
    glNewList(TextfeldIndex,GL_COMPILE_AND_EXECUTE);
	glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    Aspekt=0.0;
    Zeilen=1;
    GLint p=0;
    GLint c=0;
    while ((c=Zeichenkette[p++])) {
      if (c<0) c+=256;
      Aspekt+=(rechts[c]-links[c]+4)/64.0;
      glTranslatef(-links[c]/64.0,0,0);
      glCallList(DisplayListAnfang+c+256);
      glTranslatef((rechts[c]+4)/64.0,0,0);
    }
    glPopMatrix();
    glPushMatrix();
    Zeilen=1;
    p=0;
    while ((c=Zeichenkette[p++])) {
      if (c<0) c+=256;
      glTranslatef(-links[c]/64.0,0,0);
      glCallList(DisplayListAnfang+c);
      glTranslatef((rechts[c]+4)/64.0,0,0);
    }
    glPopMatrix();
	glDisable(GL_TEXTURE_2D);
    glEndList();
  }
 
 
  if (MaxBreite) {
    glNewList(TextfeldIndex,GL_COMPILE_AND_EXECUTE);
	glEnable(GL_TEXTURE_2D);
    Aspekt=0.0;
    Zeilen=1;
    
    GLint Anfang=0;
    GLint Zeichen=0;
    GLint Pos=0;
    GLint LeerzeichenAnzahl=0;
    GLint LetztesLeerzeichen=0;
    Zeilen=0;
    GLfloat ZeilenBreite=0.0;
    GLfloat ZeilenBreiteBisLetztesLeerzeichen=0.0;
    while (Zeichenkette[Pos]) {
      
      Anfang=Pos;
      LeerzeichenAnzahl=0;
      LetztesLeerzeichen=0;
      ZeilenBreite=0.0;
      
      while ((Zeichen=Zeichenkette[Pos]) && ZeilenBreite<MaxBreite*1.05) {
	if (Zeichen==32) {
	  ZeilenBreiteBisLetztesLeerzeichen=ZeilenBreite;
	  LetztesLeerzeichen=Pos;
	  LeerzeichenAnzahl++;
	}
	//printf("%c",Zeichen);fflush(stdout);
	if (Zeichen<0) Zeichen+=256;
	ZeilenBreite+=(rechts[Zeichen]-links[Zeichen]+4)/64.0;
	Pos++;
      }

      if (Zeichenkette[Pos]) { // noch nicht am Ende: Blocksatz
	GLfloat delta=(MaxBreite-ZeilenBreiteBisLetztesLeerzeichen)/(LeerzeichenAnzahl-1.0);
	//printf("%f\n",delta);
	glPushMatrix();
	glTranslatef(0,-Zeilen*.7,0);
	GLint c;
	Pos=Anfang;
	while ((c=Zeichenkette[Pos++])&& Pos<=LetztesLeerzeichen) {
	  if (c<0) c+=256;
	  glTranslatef(-links[c]/64.0,0,0);
	  glCallList(DisplayListAnfang+c+256);
	  glTranslatef((rechts[c]+4)/64.0,0,0);
	  if (c==32) glTranslatef(delta,0,0);
	}
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,-Zeilen*.7,0);
	Pos=Anfang;
	while ((c=Zeichenkette[Pos++])&& Pos<=LetztesLeerzeichen) {
	  if (c<0) c+=256;
	  glTranslatef(-links[c]/64.0,0,0);
	  glCallList(DisplayListAnfang+c);
	  glTranslatef((rechts[c]+4)/64.0,0,0);
	  if (c==32) glTranslatef(delta,0,0);
	}
	glPopMatrix();
	Zeilen++;      
      } else { // am Ende: Linksbuendig
	GLfloat delta=0;
	if (ZeilenBreite>MaxBreite) 
	  delta=(MaxBreite-ZeilenBreite)/(LeerzeichenAnzahl+0.0);
	glPushMatrix();
	glTranslatef(0,-Zeilen*.7,0);
	GLint c;
	Pos=Anfang;
	while ((c=Zeichenkette[Pos++])) {
	  if (c<0) c+=256;
	  glTranslatef(-links[c]/64.0,0,0);
	  glCallList(DisplayListAnfang+c+256);
	  glTranslatef((rechts[c]+4)/64.0,0,0);
	  if (c==32) glTranslatef(delta,0,0);
	}
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,-Zeilen*.7,0);
	Pos=Anfang;
	while ((c=Zeichenkette[Pos++])) {
	  if (c<0) c+=256;
	  glTranslatef(-links[c]/64.0,0,0);
	  glCallList(DisplayListAnfang+c);
	  glTranslatef((rechts[c]+4)/64.0,0,0);
	  if (c==32) glTranslatef(delta,0,0);
	}
	glPopMatrix();
	Zeilen++;      
	break;
      }
    }
    
    glDisable(GL_TEXTURE_2D);

    glEndList();

  }

}

GLint Textfeld::Maustaste(int Taste,int Richtung,int x_,int y_) {
  GLfloat xf=16.0*x_/glutGet(GLUT_WINDOW_WIDTH);
  GLfloat yf=12.0-12.0*y_/glutGet(GLUT_WINDOW_HEIGHT);
  if (soll_Alpha>0.0 &&
      Signal!=0 &&
      x<=xf && xf<=x+Hoehe*Aspekt && y<=yf && yf<=y+Hoehe) {
    if (Taste==GLUT_LEFT_BUTTON) {
      if (Richtung==GLUT_DOWN) {
	Angewaehlt();
	return -1;
      } else {
	return Signal;
      }
    } else {
      return -1;
    }
  } else {
    return 0;
  }
}

GLfloat Textfeld::TextfeldHoehe() {
  return .7*Zeilen;
}


void Textfeld::SetzeMaxBreite(GLfloat mb) {
  if (mb<0) mb=0;
  MaxBreite=mb;
}
