/****************************************************************************
**
** Kugel.h   Stefan Disch, Tobias Nopper, Martina Welte 2001
**
****************************************************************************/  

#include <GL/glut.h>

class Kugel {
 public:
  Kugel();
  void male(GLint);
  void maleSchatten();
  void neuePosition(GLfloat[]);  
  void neuePosition(GLfloat,GLfloat);  
  void neuePosition(GLfloat,GLfloat,GLfloat);  
  void neuePositionCM(GLfloat[]);
  void neuePositionCM(GLfloat,GLfloat);
  void neuePositionCM(GLfloat,GLfloat,GLfloat);
  void neuePositionD(GLfloat[]);
  void neuePositionD(GLfloat,GLfloat);
  void neuePositionD(GLfloat,GLfloat,GLfloat);
  void neuePositionINCH(GLfloat[]);
  void neuePositionINCH(GLfloat,GLfloat);
  void neuePositionINCH(GLfloat,GLfloat,GLfloat);
  void ausblenden();
  void Initialisiere(GLint,GLint,GLint,GLint);
  GLfloat Pos_x();
  GLfloat Pos_y();
  GLfloat Pos_xD();
  GLfloat Pos_yD();
  GLfloat Pos_xCM();
  GLfloat Pos_yCM();
 private:
  GLfloat Position[3];
  GLint Nummer;
  GLint sphereIndex[30]; 
  GLint sphereIndexStatisch[30]; 
  GLint schattenIndex;
  GLint schattenIndexStatisch;
  GLint schatten2Index;
  GLint Schatten;
  GLint InAnimation;
  GLint StatischExistiert[30];
  GLint StatischExistiertSchatten;
  GLfloat DrehMatrix[16];
  GLfloat Schatten1_x,Schatten1_y,Schatten1_scale,Schatten1_winkel;
  GLfloat Schatten2_x,Schatten2_y,Schatten2_scale,Schatten2_winkel;
  GLfloat Schatten3_x,Schatten3_y,Schatten3_scale,Schatten3_winkel;
  GLfloat AlteTexturgroesse;

  GLuint Texturen[9];
};

extern class Kugel Kugel[16];
extern GLfloat *ball_vertices[30];
extern GLfloat *ball_texcoord[30];
extern GLint *ball_indices[30];

