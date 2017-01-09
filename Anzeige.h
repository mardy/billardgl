/****************************************************************************
**
** Anzeige.h   Stefan Disch, Tobias Nopper, Martina Welte 2001
**
****************************************************************************/  

class Anzeige {
 public:
  Anzeige();
  void Initialisiere();
  void male();
  void setzeStossStaerke(GLfloat);
 private:
  //GLint AusschlagIndex;
  GLfloat StossStaerke;
};






