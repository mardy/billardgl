/****************************************************************************
**
** Tisch.h   Stefan Disch, Tobias Nopper, Martina Welte 2001
**
****************************************************************************/  

#include <GL/glut.h>

class Tisch {
 public:
  Tisch();
  void Initialisiere(GLint);
  void maleFlaeche();
  void maleBanden();
  void maleLinien();
 private:
  GLint TischFlaecheIndex;
  GLint BandenIndex;
  GLint LinienIndex;
  GLuint TischFlaechenTextur;
  GLuint HolzBandenTextur;
};


