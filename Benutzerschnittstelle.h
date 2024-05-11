/****************************************************************************
**
** Benutzerschnittstelle.h   Stefan Disch, Tobias Nopper, Martina Welte 2001
**
****************************************************************************/  

void Maus(int,int,int,int);
void Bewegung(int,int);
void Joystick(unsigned int, int, int, int);
void Taste(unsigned char,int,int);
void TasteLos(unsigned char,int,int);
void Sondertaste(int,int,int);
void SondertasteLos(int,int,int);

extern class Kugel Kugel[16];
extern class Kamera Kamera;
extern class Anzeige Anzeige;
extern class Menu Menu;
extern class Schiedsrichter Schiedsrichter;

extern GLint DelayAusgleich;
extern GLint InvertX;
extern GLint InvertY;
extern GLfloat MouseSpeed,AusholStaerke;
extern GLint   Hintergrundfarbe;
extern GLint PolygonMode_mode;
extern GLint PolygonMode_view;
extern GLint Startzeit,AusholStartzeit,Stossdauer,Ausholstaerke;
extern GLint xnor;
extern int OriginalFenster,AktuellesFenster;
extern GLint Spiel,StateMaschin, FullScreen;
extern GLint Taste_Pfeil_Oben,Taste_Pfeil_Unten;
extern GLint Taste_Pfeil_Rechts,Taste_Pfeil_Links;
extern GLint Taste_Shift, Taste_Strg;
extern GLint Taste_Bild_Auf,Taste_Bild_Ab;
extern GLint Taste_Pos1,Taste_Ende;

extern GLint MouseLookLast_x,MouseLookLast_y;
extern GLfloat Bewegungstabelle[2000][16][3];
extern GLint MausTasteAbgefangen;

extern GLint LageVerbesserungKopffeld;
extern GLint LageVerbesserung;
extern GLint AllerersterStoss;
