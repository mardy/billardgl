/****************************************************************************
**
**  Kugel.cpp   Stefan Disch, Tobias Nopper, Martina Welte 2001
**
*****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "LA.h"                // Zum Handling von .bmp-Files bzw. Matrix-Bildern
#include "bmp.h"

#include "Kugel.h"

#include "createTexture.h"   // Funktion zum Generieren einer Textur aus einem 
                               // Matrix-Bild (aus "Ubungen)

#include "SchattenKreis.h"   // zeichnet Schatten


// leerer Konstruktor (OpenGL macht hier dumm)...
Kugel::Kugel() {
  Position[0]=0;
  Position[1]=0;
  Position[2]=0;
  Nummer=-1;
  for (GLint i=0;i<30;i++) {
    sphereIndex[i]=0; 
    sphereIndexStatisch[i]=0; 
	StatischExistiert[i]=0;
  }
  schattenIndex=0;
  schattenIndexStatisch=0;
  Schatten=0;
  InAnimation=0;
  StatischExistiertSchatten=0;
  //GLfloat DrehMatrix[16];
  Schatten1_x=0;
  Schatten1_y=0;
  Schatten1_scale=0;
  Schatten1_winkel=0;
  Schatten2_x=0;
  Schatten2_y=0;
  Schatten2_scale=0;
  Schatten2_winkel=0;
  Schatten3_x=0;
  Schatten3_y=0;
  Schatten3_scale=0;
  Schatten3_winkel=0;
  AlteTexturgroesse=1;

	/* */
  Texturen[1]=0;
  Texturen[2]=0;
  Texturen[4]=0;
  Texturen[8]=0;
}

GLint exp2(GLint a) { //b=2^a
  return 1<<a;
}

// ... stattdessen kommt hier alles in Initialisiere
void Kugel::Initialisiere(GLint Nr, GLint Texturgroesse, GLint MaxAufloesung, GLint Schatten_) {

  Schatten=Schatten_;

  FMatrix tex_r,tex_g,tex_b;     // Matrix-Bilder, in die die Textur kommt

  char Name[40];                  // Wie hei"st die zu ladene .bmp-Datei?
  sprintf(Name,"Texturen/%i/%i.bmp",Texturgroesse,Nr); 

  if (!sphereIndex[3]) {
    Position[0]=Position[1]=3000.0; // Kugel nicht sichtbar

    glPushMatrix();                 // Drehmatrix auf die Einheitsmatrix setzen;
    glLoadIdentity();
    glGetFloatv(GL_MODELVIEW_MATRIX,DrehMatrix);
    glPopMatrix();
  }
  
  Nummer=Nr;                      // KugelNummer setzen
  
  for (int Aufloesung=3; Aufloesung<=MaxAufloesung;Aufloesung+=2) {
    
    if (!sphereIndex[Aufloesung]||
			 (AlteTexturgroesse!=Texturgroesse)) {

      //printf(".");fflush(stdout);

      sphereIndex[Aufloesung]=glGenLists(1); 
      sphereIndexStatisch[Aufloesung]=glGenLists(1); 
      
      if ((Texturgroesse==0)||(Nummer==0)) { // Keine Textur?
	
	glNewList(sphereIndex[Aufloesung],GL_COMPILE_AND_EXECUTE);
        GLfloat mat_diffuse[]={1.0,1.0,1.0,1.0};
        GLfloat mat_specular[]={0.5,0.5,0.5,1.0};
        //GLfloat mat_specular[]={0.0,0.0,0.0,0.0};
        GLfloat mat_shininess = 80.0;
	
        glMaterialfv(GL_FRONT, GL_AMBIENT,mat_diffuse);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR,mat_specular);
        glMaterialf(GL_FRONT, GL_SHININESS,mat_shininess);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, ball_vertices[Aufloesung]);
	glVertexPointer(3, GL_FLOAT, 0, ball_vertices[Aufloesung]);
	glDrawElements(GL_TRIANGLES,20*3*Aufloesung*Aufloesung, GL_UNSIGNED_INT,ball_indices[Aufloesung]);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glEndList();
	
      } else {                        // sonst
	
	GLint TG=exp2((7-Aufloesung)/2);
	if (TG<Texturgroesse) TG=Texturgroesse;
	if (TG>8) TG=1;
	if (!Texturen[TG]) 
	  glGenTextures(1,&Texturen[TG]);
        glBindTexture(GL_TEXTURE_2D,Texturen[TG]);
	sprintf(Name,"Texturen/%i/%i.bmp",TG,Nr); 
	loadBMP(tex_r,tex_g,tex_b,Name);
	GLfloat *texcoord;
	if (tex_r.nrh!=tex_r.nch) {
	  GLfloat Aspekt=(tex_r.nch+1.0)/(tex_r.nrh+1.0);
	  texcoord = (GLfloat*) malloc (20*(Aufloesung+1)*(Aufloesung+2)*sizeof(GLfloat));
	  for (GLint a=0;a<20*(Aufloesung+1)*(Aufloesung+2);a+=2) {
	    texcoord[a]=ball_texcoord[Aufloesung][a]/Aspekt;
	    texcoord[a+1]=ball_texcoord[Aufloesung][a+1];
	  }
	} 
	createTexture(tex_r,tex_g,tex_b);
	
	glNewList(sphereIndex[Aufloesung],GL_COMPILE_AND_EXECUTE);
	GLfloat mat_diffuse[]={1.0,1.0,1.0,1.0};
	GLfloat mat_specular[]={0.5,0.5,0.5,1.0};
	//GLfloat mat_specular[]={0.0,0.0,0.0,0.0};
	GLfloat mat_shininess = 80.0;
	
	glMaterialfv(GL_FRONT, GL_AMBIENT,mat_diffuse);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR,mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS,mat_shininess);
	//createTexture(tex_r,tex_g,tex_b,Nearest,0);
	glBindTexture(GL_TEXTURE_2D,Texturen[TG]);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glNormalPointer(GL_FLOAT, 0, ball_vertices[Aufloesung]);
	glVertexPointer(3, GL_FLOAT, 0, ball_vertices[Aufloesung]);
	if (tex_r.nrh!=tex_r.nch) {
	  glTexCoordPointer(2, GL_FLOAT, 0, texcoord);
	} else {
	  glTexCoordPointer(2, GL_FLOAT, 0, ball_texcoord[Aufloesung]);
	}
	glDrawElements(GL_TRIANGLES,20*3*Aufloesung*Aufloesung, GL_UNSIGNED_INT,ball_indices[Aufloesung]);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glEndList();
	tex_r.free_FMatrix();
	tex_g.free_FMatrix();
	tex_b.free_FMatrix();
	if (tex_r.nrh!=tex_r.nch) {
	  free(texcoord);
	}
	
      }
      
      StatischExistiert[Aufloesung]=0;
      StatischExistiertSchatten=0;
      InAnimation=1;
    }
  }
  
  if (!schattenIndex) {
    schattenIndex=glGenLists(1);
    schattenIndexStatisch=glGenLists(1);

    glNewList(schattenIndex,GL_COMPILE_AND_EXECUTE);
    SchattenKreis(18, .7, 1.2, 0.2, 0.0);
    glEndList();
    
    Schatten=Schatten_;
    
    Schatten1_x=0;
    Schatten1_y=0;
    Schatten1_scale=1;
    Schatten1_winkel=0;
    Schatten2_x=0;
    Schatten2_y=0;
    Schatten2_scale=1;
    Schatten2_winkel=0;
    Schatten3_x=0;
    Schatten3_y=0;
    Schatten3_scale=1;
    Schatten3_winkel=0;
  }

  if (!schatten2Index) {
    schatten2Index=glGenLists(1);

    glNewList(schatten2Index,GL_COMPILE_AND_EXECUTE);
    SchattenKreis(14, 0.1, 0.5, 0.5, 0.0);
    glEndList();
  }

  AlteTexturgroesse=Texturgroesse;

}


// Zeichnet die Kugel mit Hilfe der Display List
void Kugel::male(GLint Aufloesung) {
  if (Position[0]!=3000) {

    if (InAnimation) {

      glPushMatrix();                // Matrix auf Stack
      
      glScalef(2.8575,2.8575,2.8575);// Skalieren auf Zentimetersystem;
      
                                     // Kugel auf die Position verschieben
      glTranslatef(Position[0],Position[1],Position[2]);
      
      glMultMatrixf(DrehMatrix);     // Kugel mit der Drehmatrix drehen
      
      glCallList(sphereIndex[Aufloesung]);       // Kugel zeichnen
      
      glPopMatrix();                 // Matrix wiederherstellen
      
      InAnimation=0;

      for (int i=0;i<30;i++) {
	StatischExistiert[i]=0;
      }
      
    } else if (StatischExistiert[Aufloesung]) {

	  /*
	    glPushMatrix();
	    glTranslatef(0,0,-5.715);
        glScalef(1,1,-1);
        glFrontFace(GL_CW);
        glDisable(GL_DEPTH_TEST);
	    glCallList(sphereIndexStatisch[Aufloesung]);
        glEnable(GL_DEPTH_TEST);
	    glFrontFace(GL_CCW);
        glPopMatrix();
      */

      glCallList(sphereIndexStatisch[Aufloesung]);

	} else {

      glNewList(sphereIndexStatisch[Aufloesung],GL_COMPILE_AND_EXECUTE);

      glPushMatrix();                // Matrix auf Stack
      
      glScalef(2.8575,2.8575,2.8575);// Skalieren auf Zentimetersystem;
      
                                     // Kugel auf die Position verschieben
      glTranslatef(Position[0],Position[1],Position[2]);
      
      glMultMatrixf(DrehMatrix);     // Kugel mit der Drehmatrix drehen
      
      glCallList(sphereIndex[Aufloesung]);       // Kugel zeichnen
      
      glPopMatrix();                 // Matrix wiederherstellen

      glEndList();

      StatischExistiert[Aufloesung]=1;
    }
  }
}

void Kugel::maleSchatten() {
  if (Schatten&&(Position[0]!=3000)&&(Position[2]>=0)) {
    if (InAnimation) {
      glPushMatrix();
      glScalef(2.8575,2.8575,2.8575);// Skalieren auf Zentimetersystem;
      glTranslatef(Position[0],Position[1],Position[2]-1);
      
	  glCallList(schatten2Index); //TEST
      
	  glPushMatrix();
      glTranslatef(Schatten1_x,Schatten1_y,0);
      glRotatef(Schatten1_winkel,0,0,1);
      glScalef(Schatten1_scale,1,1);
      glCallList(schattenIndex);
      glPopMatrix();
    
      glPushMatrix();
      glTranslatef(Schatten2_x,Schatten2_y,0);
      glRotatef(Schatten2_winkel,0,0,1);
      glScalef(Schatten2_scale,1,1);
      glCallList(schattenIndex);
      glPopMatrix();
      
      glPushMatrix();
      glTranslatef(Schatten3_x,Schatten3_y,0);
      glRotatef(Schatten3_winkel,0,0,1);
      glScalef(Schatten3_scale,1,1);
      glCallList(schattenIndex);
      glPopMatrix();
      glPopMatrix();

      StatischExistiertSchatten=0;

    } else if (StatischExistiertSchatten) {

      glCallList(schattenIndexStatisch);

    } else {

      glNewList(schattenIndexStatisch,GL_COMPILE_AND_EXECUTE);
      glPushMatrix();
      glScalef(2.8575,2.8575,2.8575);// Skalieren auf Zentimetersystem;
      glTranslatef(Position[0],Position[1],Position[2]-1);

      glCallList(schatten2Index); //TEST

      glPushMatrix();
      glTranslatef(Schatten1_x,Schatten1_y,0);
      glRotatef(Schatten1_winkel,0,0,1);
      glScalef(Schatten1_scale,1,1);
      glCallList(schattenIndex);
      glPopMatrix();
    
      glPushMatrix();
      glTranslatef(Schatten2_x,Schatten2_y,0);
      glRotatef(Schatten2_winkel,0,0,1);
      glScalef(Schatten2_scale,1,1);
      glCallList(schattenIndex);
      glPopMatrix();
      
      glPushMatrix();
      glTranslatef(Schatten3_x,Schatten3_y,0);
      glRotatef(Schatten3_winkel,0,0,1);
      glScalef(Schatten3_scale,1,1);
      glCallList(schattenIndex);
      glPopMatrix();
      glPopMatrix();
      glEndList();

      StatischExistiertSchatten=1;
    }
  }
}


void Kugel::neuePosition(GLfloat neuPos[]) {

  GLfloat dx=neuPos[0]-Position[0]; // Differenzvektor bestimmen
  GLfloat dy=neuPos[1]-Position[1];

  //printf("%i %f %f\n",Nummer,Position[0],Position[1]);

  if (dx || dy) {
    
    glPushMatrix();                   // Matrix auf Stack

    glLoadIdentity();                 // Einheitsmatrix laden

    // um die L"ange des Diff.vektors (umgerechnet in Gradma"s) um die
    // Achse senkrecht zum Differenzvektor rotieren
    glRotatef(sqrt(dx*dx+dy*dy)*20.051016*2,-dy,dx,0.0);
    
    glMultMatrixf(DrehMatrix);        // Die alte Drehmatrix dazumultiplizieren

                                    // Die neue Drehmatrix abspeichern
    glGetFloatv(GL_MODELVIEW_MATRIX,DrehMatrix);
    
    glPopMatrix();                    // Matrix wiederherstellen
    
    Position[0]=neuPos[0];            // neue Position setzen
    Position[1]=neuPos[1];
    Position[2]=(neuPos[2]>0)?0:neuPos[2];
    
    if (Schatten) {
      Schatten1_x=neuPos[0]/34;
      Schatten1_x=(Schatten1_x)?Schatten1_x:.0001;
      Schatten1_y=neuPos[1]/34;
      Schatten1_scale=sqrt(Schatten1_x*Schatten1_x+Schatten1_y*Schatten1_y+1);
      Schatten1_winkel=57.3*atan(Schatten1_y/Schatten1_x);
      
      Schatten2_x=(neuPos[0]-22.22)/34;
      Schatten2_x=(Schatten2_x)?Schatten2_x:.0001;
      Schatten2_y=Schatten1_y;
      Schatten2_scale=sqrt(Schatten2_x*Schatten2_x+Schatten2_y*Schatten2_y+1);
      Schatten2_winkel=57.3*atan(Schatten2_y/Schatten2_x);
      
      Schatten3_x=(neuPos[0]+22.22)/34;
      Schatten3_x=(Schatten3_x)?Schatten3_x:.0001;
      Schatten3_y=Schatten1_y;
      Schatten3_scale=sqrt(Schatten3_x*Schatten3_x+Schatten3_y*Schatten3_y+1);
      Schatten3_winkel=57.3*atan(Schatten3_y/Schatten3_x);
    }
  }
  InAnimation=1;
}

/* Das gleiche noch viele hundert Mal (in verschiedenen Masseinheiten etc.)*/
void Kugel::neuePosition(GLfloat neuPos_x,GLfloat neuPos_y,GLfloat neuPos_z) {
  GLfloat Pos[]={neuPos_x,neuPos_y,neuPos_z};
  neuePosition(Pos);
}

void Kugel::neuePosition(GLfloat neuPos_x,GLfloat neuPos_y) {
  GLfloat Pos[]={neuPos_x,neuPos_y,0.0};
  neuePosition(Pos);
}

void Kugel::neuePositionCM(GLfloat neuPos[]) {
  GLfloat Pos[]={neuPos[0]/2.8575,neuPos[1]/2.8575,neuPos[2]/2.8575};
  neuePosition(Pos);
}

void Kugel::neuePositionCM(GLfloat neuPos_x,GLfloat neuPos_y,GLfloat neuPos_z) {
  GLfloat Pos[]={neuPos_x/2.8575,neuPos_y/2.8575,neuPos_z/2.8575};
  neuePosition(Pos);
}

void Kugel::neuePositionCM(GLfloat neuPos_x,GLfloat neuPos_y) {
  GLfloat Pos[]={neuPos_x/2.8575,neuPos_y/2.8575,0.0};
  neuePosition(Pos);
}

void Kugel::neuePositionD(GLfloat neuPos[]) {
  GLfloat Pos[]={neuPos[0]*2,neuPos[1]*2,neuPos[2]*2};
  neuePosition(Pos);
}

void Kugel::neuePositionD(GLfloat neuPos_x,GLfloat neuPos_y,GLfloat neuPos_z) {
  GLfloat Pos[]={neuPos_x*2,neuPos_y*2,neuPos_z*2};
  neuePosition(Pos);
}

void Kugel::neuePositionD(GLfloat neuPos_x,GLfloat neuPos_y) {
  GLfloat Pos[]={neuPos_x*2,neuPos_y*2,0.0};
  neuePosition(Pos);
}

void Kugel::neuePositionINCH(GLfloat neuPos[]) {
  GLfloat Pos[]={neuPos[0]/1.125,neuPos[1]/1.125,neuPos[2]/1.125};
  neuePosition(Pos);
}

void Kugel::neuePositionINCH(GLfloat neuPos_x,GLfloat neuPos_y,GLfloat neuPos_z) {
  GLfloat Pos[]={neuPos_x/1.125,neuPos_y/1.125,neuPos_z/1.125};
  neuePosition(Pos);
}

void Kugel::neuePositionINCH(GLfloat neuPos_x,GLfloat neuPos_y) {
  GLfloat Pos[]={neuPos_x/1.125,neuPos_y/1.125,0.0};
  neuePosition(Pos);
}

// l"a"st die Kugel verschwinden
void Kugel::ausblenden() {
  GLfloat Pos[]={3000.0,3000.0,0.0};
  neuePosition(Pos);
}

// Liefert die Kugelposition in verschiedenen Ma"seinheiten zur"uck
GLfloat Kugel::Pos_x() {
  return Position[0];
}

GLfloat Kugel::Pos_y() {
  return Position[1];
}

GLfloat Kugel::Pos_xD() {
  return Position[0]*.5;
}

GLfloat Kugel::Pos_yD() {
  return Position[1]*.5;
}

GLfloat Kugel::Pos_xCM() {
  return Position[0]*2.8575;
}

GLfloat Kugel::Pos_yCM() {
  return Position[1]*2.8575;
}
