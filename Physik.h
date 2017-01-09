/****************************************************************************
**
** Physik.h   Stefan Disch, Tobias Nopper, Martina Welte 2001
**
****************************************************************************/  

void Physik(GLfloat,GLfloat);
void Kollision(GLfloat[],GLfloat[],GLint,GLint);

extern GLfloat KollisionsFaktor,ReibungsFaktor,BandenFaktor;
extern GLint PhysikFrequenz, Stossdauer;

extern class Kugel Kugel[16];
extern class Schiedsrichter Schiedsrichter;

extern GLfloat Bewegungstabelle[2000][16][3];
