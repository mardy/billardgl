/****************************************************************************
**
** Kamera.h   Stefan Disch, Tobias Nopper, Martina Welte 2001
**
****************************************************************************/  

#include <GL/glut.h>

class Kamera {
 public:
  Kamera();
  void male();
  void neuePosition(GLfloat[5]);
  GLfloat* Position();
  void speicherePosition(GLint);
  void ladePosition(GLint);
  void Beweg_Vor(GLfloat);
  void Beweg_Zurueck(GLfloat);
  void Beweg_Rein(GLfloat);
  void Beweg_Raus(GLfloat);
  void Beweg_Rechts(GLfloat);
  void Beweg_Links(GLfloat);
  void Beweg_Hoch(GLfloat);
  void Beweg_Runter(GLfloat);
  void Zoom_Rein(GLfloat);
  void Zoom_Raus(GLfloat);
  void Vertigo_Rein(GLfloat);
  void Vertigo_Raus(GLfloat);
  void Dreh_Rechts(GLfloat);
  void Dreh_Links(GLfloat);
  void Dreh_Hoch(GLfloat);
  void Dreh_Runter(GLfloat);
  void Schwenk_Rechts(GLfloat,GLfloat,GLfloat);
  void Schwenk_Links(GLfloat,GLfloat,GLfloat);
  void Schwenk_Hoch(GLfloat,GLfloat,GLfloat);
  void Schwenk_Runter(GLfloat,GLfloat,GLfloat);
  void Verfolge(GLint                  );
  void BlickeAuf(GLfloat[2]);
  void BlickeAuf(GLfloat,GLfloat);
  void BlickeAuf2(GLfloat[2]);
  void BlickeAuf2(GLfloat,GLfloat);
  void BlickeAuf3(GLfloat[2]);
  void BlickeAuf3(GLfloat,GLfloat);
  void Fahrt(GLfloat);
  void Rundflug(GLint);
  void setzeSollPosition(GLfloat[6]);
  void setzeSollPosition(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);
  void BlickTiefeNeuBestimmen();
  GLfloat Pos_xCM();
  GLfloat Pos_yCM();
  GLfloat Pos_zCM();
  GLfloat Aspekt;
  GLint Verfolgung;
  GLfloat Pos_x,Pos_y,Pos_z,Alpha,Beta,FOV;
 private:
  GLfloat Soll_Pos_x,Soll_Pos_y,Soll_Pos_z,Soll_Alpha,Soll_Beta,Soll_FOV;
  GLfloat d_Pos_x,d_Pos_y,d_Pos_z,d_Alpha,d_Beta,d_FOV;
  GLfloat Nah,Fern;
  GLint KameraNummer;  
};

