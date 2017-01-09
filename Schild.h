
class Schild {
 public:
  Schild();
  void Initialisiere();
  void InitialisiereLogo();
  void Initialisiere(GLint,char[]);
  void InitialisiereBuchstabe(GLint,char[]);
  void Initialisiere(GLint,char[],char);
  void Initialisiere(GLint,char[],char[]);
  void male();
  void Positioniere(GLfloat,GLfloat,GLfloat,GLfloat);
  void PositioniereFix(GLfloat,GLfloat,GLfloat,GLfloat);
  void Desaktiviere();
  void Angewaehlt();
  void Eingeblendet();
  void VollSichtbar();
  void StarteAnimation();
  GLint Animiere(GLint);
  GLint Maustaste(int,int,int,int);
  void SetzeZielZustand(GLint);
  void SetzeSignal(GLint);
  void KopieVon(Schild);
  GLint SchildIndex;
  GLint SchildTyp;
  GLfloat Aspekt;
 private:
  GLfloat ax,ay,bx,by;
  GLfloat Alpha;
  GLfloat soll_ax,soll_ay,soll_bx,soll_by;
  GLfloat soll_Alpha;
  GLfloat alt_ax,alt_ay,alt_bx,alt_by;
  GLfloat alt_Alpha;
  GLint InAnimation;
  GLint Signal;
  GLint Zeit;
  GLuint Textur;
};

#define AUSGEBLENDET 0.0
#define TRANSPARENT  0.2
#define EINGEBLENDET 0.6
#define ANGEWAEHLT   0.8
#define VOLLSICHTBAR 1.0

#define ANIMATIONSDAUER 100

extern GLuint logotextur;
