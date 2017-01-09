
class Schiedsrichter {
 public:
  Schiedsrichter();
  void KugelKugel(GLint,GLfloat,GLint,GLfloat);
  void KugelBande(GLint,GLfloat,GLint);
  void KugelLoch(GLint,GLint);
  void NeuesSpiel(GLint);
  void NeuerStoss();
  void SetzeSpielerAmStoss(GLint);
  void SetzeFouls(GLint,GLint);
  GLint Entscheidung();

  GLint KorrekteKugelAngespielt(GLint);
  GLint KorrekteKugelVersenkt(GLint);
  GLint KorrekteKugelVersenktDabei(GLint[16]);
  GLint FarbigeKugel(GLint);
  GLint FarbigeKugelDabei(GLint[16]);
  GLint FarbigeKugelSumme(GLint[16]);
  GLint Summe(GLint[16]);

  GLint FrageNachSpielerAmStoss();
  GLint FrageNachGruppenVerteilung();
  GLint FrageNachBegruendung();
  GLint FrageNachFouls(GLint);

 private:
  GLint BandeAusserhalbKopffeldvorKugelBeruehrt;
  GLint ErsteBeruehrteKugel;
  GLint ErsteBeruehrteBande;
  GLint ErsteVersenkteKugel;
  GLint ErsteBeruehrung;
  GLint ErsteBeruehrteKugelImKopffeld;
  GLint ErsteBeruehrungImKopffeld;
  GLint KugelnImSpiel[16];
  GLint KugelnVersenkt[16];
  GLint KugelnAnBande[16];

  GLint FoulsHintereinanderSpieler1;
  GLint FoulsHintereinanderSpieler2;

  GLint SchiedsrichterEntscheidung;

  GLint SpielerAmStoss;

  GLint Begruendung;

  GLint AufnahmeWechsel;
  GLint Foul;
  GLint LageVerbesserungKopffeld;
  GLint LageVerbesserung;
  GLint NeuAufbauenOderWeiterspielen;
  GLint NeuAufbauenOderAchtEinsetzen;
  GLint Verloren;
  GLint Gewonnen;
  GLint Spieler1Gewonnen;
  GLint Spieler2Gewonnen;


  GLint AusKopffeld;
  GLint Eroeffnungsstoss;
  GLint Spiel;
  GLint GruppenVerteilung;
  GLint NiedrigsteKugel;

};

#define JA   1
#define NEIN 0

#define SPIELER1 0
#define SPIELER2 1

#define KEINE 0
#define S1_GANZE_S2_HALBE 1
#define S1_HALBE_S2_GANZE 2

#define ACHTBALL 8
#define NEUNBALL 9
