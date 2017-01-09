/****************************************************************************
**
** Menu.h   Stefan Disch, Tobias Nopper, Martina Welte 2001
**
****************************************************************************/  

#include "sprache.h"

#define AUS 0
#define STARTBILDSCHIRM 1
#define HAUPTMENU 2
#define TRAINING 3
#define ZWEISPIELER 4
#define NETZWERKHAUPT 5
#define NETZWERKNEU 6
#define NETZWERKBEITRETEN 7
#define BEENDEN 8
#define AUSSPIEL 9
#define EINSTELLUNGEN 10
#define EINSTELLUNGENSTEUERUNG 11
#define EINSTELLUNGENGRAFIK 12
#define EINSTELLUNGENGRAFIKHINWEIS 13
#define EINSTELLUNGENAUDIO 14
#define SPRACHAUSWAHL 15
#define SPIEL 20

#define HILFE 30
#define HILFEREGELN1 31
#define HILFEREGELN2 32
#define HILFEREGELN3 33
#define HILFEREGELN4 34
#define HILFEREGELN5 35
#define HILFEREGELN6 36
#define HILFEREGELN7 37
#define HILFEREGELN8 38
#define HILFEEINFUEHRUNG1 41
#define HILFEEINFUEHRUNG2 42
#define HILFEEINFUEHRUNG3 43
#define HILFEEINFUEHRUNG4 44
#define HILFEEINFUEHRUNG5 45
#define HILFEEINFUEHRUNG6 46
#define HILFEEINFUEHRUNG7 47
#define HILFEEINFUEHRUNG8 48
#define HILFETASTENBELEGUNGEN 49

#define SPIELENDE 99

#define S_SB_LOGO 100
#define S_SB_NAMEN 101
#define S_LOGO 102

#define S_HM_TRAINING 110
#define S_HM_ZWEISPIELER 111
#define S_HM_NETZWERKSPIEL 112
#define S_HM_EINSTELLUNGEN 113
#define S_HM_BEENDEN 114
#define S_HM_COMPUTERGEGNER 115
#define S_HM_HILFE 116

#define S_TR_ACHTBALL 120
#define S_TR_NEUNBALL 121
#define S_TR_VIERZEHNPLUSEINS 122
#define S_TR_ZURUECK 123

#define S_ZW_ACHTBALL 130
#define S_ZW_NEUNBALL 131
#define S_ZW_VIERZEHNPLUSEINS 132
#define S_ZW_ZURUECK 133

#define S_NE_BEGINNEN 140
#define S_NE_TEILNEHMEN 141
#define S_NE_ZURUECK 142

#define S_NB_ACHTBALL 150
#define S_NB_NEUNBALL 151
#define S_NB_VIERZEHNPLUSEINS 152
#define S_NB_ZURUECK  153

#define S_NT_IPADRESSE 160
#define S_NT_VERBINDEN 161
#define S_NT_ZURUECK   162

#define S_EI_BALLTEXTUREN 170
#define S_EI_TISCHTEXTUREN 180
#define S_EI_ANZEIGETEXTUREN 190
#define S_EI_TEXTURINTERPOLATION 195
#define S_EI_BALLGEOMETRIE   201
#define S_EI_MOUSESPEED      202
#define S_EI_XINVERT   203
#define S_EI_YINVERT   204
#define S_EI_SPRACHE   205
#define S_EI_ZURUECK 220
#define S_EI_ZURUECK_AS 221
#define S_EI_UEBERNEHMEN 222
#define S_EI_STEUERUNG 223
#define S_EI_STEUERUNGZURUECK 224
#define S_EI_STEUERUNGUEBERNEHMEN 225
#define S_EI_AUDIO 226
#define S_EI_AUDIOZURUECK 227
#define S_EI_AUDIOUEBERNEHMEN 228
#define S_EI_GRAFIK 800
#define S_EI_GRAFIKZURUECK 801
#define S_EI_GRAFIKUEBERNEHMEN 802
#define S_EI_AUFLOESUNG 803
#define S_EI_FARBTIEFE 804
#define S_EI_REFLEKTIONEN 805
#define S_EI_QUALITAET 806
#define S_EI_SCHATTEN 807
#define S_EI_AMBIENTESLICHT 808
#define S_EI_TISCHLAMPEN 809
#define S_EI_GRUENELAMPE 810
#define S_EI_FPS 811

#define S_AS_WEITERSPIELEN 230
#define S_AS_HAUPTMENU 231
#define S_AS_EINSTELLUNGEN 232
#define S_AS_BEENDEN 233
#define S_AS_HILFE 234

#define S_BE_JABEENDEN       850
#define S_BE_ZURUECK         851
#define S_BE_ZURUECK_AS       852

#define S_SP_LOGO    500
#define S_SP_BALL    510
#define S_SP_WEITERSPIELEN 530
#define S_SP_ACHTEINSETZEN 531
#define S_SP_NEUAUFBAUEN 532
#define S_SP_HAUPTMENU 540
#define S_SP_NEUESSPIEL 541

#define S_SP_NEUEACHTBALLAUFSTELLUNG 550
#define S_SP_NEUENEUNBALLAUFSTELLUNG 551

#define S_SPIELER1HERHOEREN 601
#define S_SPIELER2HERHOEREN 602
#define S_NETZWERKSPIELERHERHOEREN 603

#define S_H_TASTENBELEGUNGEN 300
#define S_H_BILLARDREGELN 301
#define S_H_TUTORIAL 302
#define S_H_ZUHILFE 303
#define S_H_E1_N 304
#define S_H_E2_N 305
#define S_H_E2_L 306
#define S_H_E3_N 307
#define S_H_E3_L 308
#define S_H_E4_N 309
#define S_H_E4_L 310
#define S_H_E5_N 311
#define S_H_E5_L 312
#define S_H_E6_N 313
#define S_H_E6_L 314
#define S_H_R1_N 315
#define S_H_R2_N 316
#define S_H_R2_L 317
#define S_H_R3_N 318
#define S_H_R3_L 319
#define S_H_R4_N 320
#define S_H_R4_L 321
#define S_H_R5_N 322
#define S_H_R5_L 323
#define S_H_R6_N 324
#define S_H_R6_L 325


#define ANIMATIONSDAUER 100

class Menu {
 public:
  Menu();
  void Initialisiere(GLint);
  void male();
  void Update(GLint);

  GLint Maustaste(int,int,int,int);
  GLint KeyboardTaste (unsigned char,int,int);
  void NeuerMenuZustand();
  void SignalAusfuehrung(GLint);
  void SetzeMenuZustand(GLint); 
  void SetzeFPS(GLint);
  void ladeSprache(GLint);
 private:
  void StarteAnimation();
  GLint Animationszeit;
  GLint InAnimation;

  GLint MenuZustand;
  GLint AusSpiel;

  Schild menuhintergrund;

  Schild logo;
  Schild namen;

  Schild halbe;
  Schild volle;

  Schild ball[16];

  Schild GameStar;

  Schild* SchildArray[300];
  Textfeld* TextfeldArray[1000];

  Textfeld dummyTextfeld;

  GLint TDL;
  //GLint TTA;

  GLint SchildAnzahl;
  GLint TextfeldAnzahl;

  GLint E_Texturgroesse;
  GLint E_AnzeigeTexturgroesse;
  GLint E_TischTexturgroesse;
  GLint E_KugelAufloesung;
  GLfloat E_MouseSpeed;
  GLint E_InvertX;
  GLint E_InvertY;
  GLint MenuGesperrt;
  GLint E_Reflektionen;
  GLint E_Farbtiefe;
  GLint E_BildschirmAufloesung;
  GLint Qualitaet;
  GLint E_Schatten;

  GLint E_AmbientesLicht;
  GLint E_TischLampen;
  GLint E_GrueneLampe;
  GLint E_ZeigeFPS;

  GLint E_TexMMM;

};


extern GLint StateMaschin;
extern GLint Spiel;
extern class Kamera Kamera;

extern GLint Texturgroesse,
  AnzeigeTexturgroesse,
  TischTexturgroesse,
  KugelAufloesung,
  InvertX,
  InvertY,
  Schatten,
  SpielModus,
  SpielerAmStoss;

extern GLfloat MouseSpeed;
extern GLint   KugelnVersenkt[16];
extern GLint   KugelnImSpiel[16];

extern class Kugel Kugel[16];  
extern class Tisch Tisch;
extern class Anzeige Anzeige;
extern class Schiedsrichter Schiedsrichter;
extern class Beleuchtung Beleuchtung;

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

extern GLint ZeigeFPS,TischLampen,GrueneLampe;
extern GLfloat EffektLautstaerke,MusikLautstaerke;

extern GLint TexMMM;

extern GLint DelayAusgleich;

extern GLint xnor;

extern char Spieler1[10],Spieler2[10],NetzwerkSpieler[10],NetzwerkGegner[10];


























