void StartHandling();
void BetrachtenHandling();
void ZielenHandling();
void AusholenHandling();
void StossHandling();
void WeissneuHandling();
void MenuHandling();
void SchiedsrichterHandling();

extern GLint Taste_Pfeil_Oben,Taste_Pfeil_Unten,
  Taste_Pfeil_Rechts,Taste_Pfeil_Links,Taste_Shift,
  Taste_Strg,Taste_Bild_Auf,Taste_Bild_Ab,Taste_Pos1,
  Taste_Ende,Faktor,AusholStartzeit,Startzeit,
  Stossdauer,StateMaschin,FrameZeitpunkt,Anfangsstoss,
  WeisseVersetzbar;
extern GLfloat MaxAusholStaerke,AusholStaerke;
extern GLint   KugelnVersenkt[16];
extern GLint   KugelnImSpiel[16];
extern GLfloat Bewegungstabelle[2000][16][3];

extern class Kamera Kamera;
extern class Kugel Kugel[16];
extern class Anzeige Anzeige;
extern class Menu Menu;
extern class Schiedsrichter Schiedsrichter;

extern GLint SchiedsrichterEntscheidung;
extern GLint SpielerAmStoss;
extern GLint AufnahmeWechsel;
extern GLint Foul;
extern GLint LageVerbesserungKopffeld;
extern GLint LageVerbesserung;
extern GLint NeuAufbauenOderWeiterspielen;
extern GLint NeuAufbauenOderAchtEinsetzen;
extern GLint Spieler1Gewonnen;
extern GLint Spieler2Gewonnen;
extern GLint AllerersterStoss;
