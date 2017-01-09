class Netzwerk {
 public:
  Netzwerk();
  void Initialisiere();

  GLint TypNeueNachricht(); // 0, wenn keine  Nachricht da, sonst Typ

  GLint NeueId(char Empfaenger[200]);  //liefert Empfaenger-Id zurueck
  void NachrichtPartnersuche(GLint EmpfaengerId, GLint Spiel, char Name[10]);
  void NachrichtPartnerschaft(GLint EmpfaengerId, char Name[10]);
  void NachrichtKeinePartnerschaft(GLint EmpfaengerId, GLint Zuschauen, GLint Gegner);
  void NachrichtAnfaenger(GLint EmpfaengerId, GLint Wer); //Wer?Ich:Du
  void NachrichtKameraPosition(GLint EmpfaengerId, GLfloat Pos[6]);
  void NachrichtStoss(GLint EmpfaengerId, GLfloat Vektor[2]);
  void NachrichtSpielAbbruch(GLint EmpfaengerId);
  void NachrichtZuschauen(GLint EmpfaengerId, char Name[10]);
  void NachrichtZuschauenAbbruch(GLint EmpfaengerId);
  void NachrichtKugelPositionen(GLint EmpfaengerId, GLfloat Pos[16][3]);

  GLint SenderId;
  GLint Spiel;
  char GegnerName[10];
  GLint Zuschauen;
  GLint ZuschauenGegnerId;
  GLint Anfaenger;
  GLfloat KameraPos[6];
  GLfloat Stoss[2];
  char ZuschauerName[10];
  GLfloat KugelPos[16][3];

 private:
};

#define NN_PARTNERSUCHE 1
#define NN_PARTNERSCHAFT 2
#define NN_KEINEPARTNERSCHAFT 3
#define NN_ANFAENGER 4
#define NN_KAMERAPOSITION 5
#define NN_STOSS 6
#define NN_SPIELABBRUCH 7
#define NN_ZUSCHAUEN 8
#define NN_ZUSCHAUENABBRUCH 9
#define NN_KUGELPOSITIONEN 10
