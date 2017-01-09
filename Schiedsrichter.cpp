#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include "Einsetzen.h"
#include "Schiedsrichter.h"

Schiedsrichter::Schiedsrichter() {
  //
  Begruendung=0;
}

void Schiedsrichter::NeuesSpiel(GLint _Spiel){
  //printf(" Schiedsrichter: NeuesSpiel %i\n",_Spiel);

  Spiel=_Spiel;

  Eroeffnungsstoss=JA;
  AusKopffeld=JA;
  GruppenVerteilung=KEINE;
  FoulsHintereinanderSpieler1=0;
  FoulsHintereinanderSpieler2=0;

  AufnahmeWechsel=NEIN;
  Foul=NEIN;
  LageVerbesserungKopffeld=NEIN;
  LageVerbesserung=NEIN;
  NeuAufbauenOderWeiterspielen=NEIN;
  NeuAufbauenOderAchtEinsetzen=NEIN;
  Spieler1Gewonnen=NEIN;
  Spieler2Gewonnen=NEIN;

  SpielerAmStoss=((rand()/(RAND_MAX+0.0))>.5)?1:0;

  if (Spiel==ACHTBALL) {
    for (GLint i=0;i<16;i++) {
      KugelnImSpiel[i]=JA;
    }
  } 
  if (Spiel==NEUNBALL) {
    for (GLint i=0;i<10;i++) {
      KugelnImSpiel[i]=JA;
    }
    for (GLint i2=10;i2<16;i2++) {
      KugelnImSpiel[i2]=NEIN;
    }    
  } 
}

void Schiedsrichter::NeuerStoss(){
  //printf(" Schiedsrichter: NeuerStoss\n");

  SchiedsrichterEntscheidung=-1;

  ErsteBeruehrteKugel=0;
  ErsteBeruehrteBande=0;
  ErsteVersenkteKugel=0;
  ErsteBeruehrung=0;
  ErsteBeruehrteKugelImKopffeld=NEIN;
  ErsteBeruehrungImKopffeld=NEIN;

  Begruendung = 0;

  BandeAusserhalbKopffeldvorKugelBeruehrt = NEIN;

  for (GLint i=0;i<16;i++) {
    if (KugelnVersenkt[i]) {KugelnImSpiel[i]=NEIN;}
    KugelnVersenkt[i]=NEIN;
    KugelnAnBande[i]=NEIN;
  }

  if (AufnahmeWechsel) {
    SpielerAmStoss=1-SpielerAmStoss;
  }

  AufnahmeWechsel=NEIN;
  Foul=NEIN;
  LageVerbesserungKopffeld=NEIN;
  LageVerbesserung=NEIN;
  NeuAufbauenOderWeiterspielen=NEIN;
  NeuAufbauenOderAchtEinsetzen=NEIN;
  Verloren=NEIN;
  Gewonnen=NEIN;
  Spieler1Gewonnen=NEIN;
  Spieler2Gewonnen=NEIN;

  if (Spiel==NEUNBALL) {
    for (GLint i2=9;i2>0;i2--) {
      if (KugelnImSpiel[i2]) {
	NiedrigsteKugel=i2;
      }
    }
  }


  //printf(" Eroeffnungsstoss : %i\n",Eroeffnungsstoss);
  //printf(" SpielerAmStoss   : %i\n",SpielerAmStoss);
  //printf(" Spiel            : %i\n",Spiel);
  //printf(" GruppenVerteilung: %i\n",GruppenVerteilung);
  //printf(" NiedrigsteKugel  : %i\n",NiedrigsteKugel);

}

void Schiedsrichter::KugelKugel(GLint,GLfloat,
				GLint Kugel2,GLfloat Kugel2x){
  if (!ErsteBeruehrteKugel) {
    ErsteBeruehrteKugel=Kugel2;
    if (Kugel2x<-63.5) {
      ErsteBeruehrteKugelImKopffeld=JA;
    }
  }
}

void Schiedsrichter::KugelBande(GLint Kugel,GLfloat Kugelx,
				GLint Bande){
  KugelnAnBande[Kugel]=JA;
  
  if (!ErsteBeruehrteKugel && ((Bande==20) ||
			      (Bande==21) && (Kugelx<-63.5) ||
			      (Bande==23) && (Kugelx<-63.5))) {
      BandeAusserhalbKopffeldvorKugelBeruehrt = JA;
  }
}

void Schiedsrichter::KugelLoch(GLint Kugel,GLint){
  KugelnVersenkt[Kugel]=JA;

  if (!ErsteVersenkteKugel) {
    ErsteVersenkteKugel=Kugel;
  }
}


GLint Schiedsrichter::Entscheidung(){
  
  if (SchiedsrichterEntscheidung==-1) {

    if (Eroeffnungsstoss) {
      //printf("check %i %i\n",FarbigeKugelDabei(KugelnVersenkt),FarbigeKugelSumme(KugelnAnBande));
      if (!FarbigeKugelDabei(KugelnVersenkt) &&
	  FarbigeKugelSumme(KugelnAnBande)<4) {
	Foul = JA; 
	Begruendung=450;
	//printf("Foul kein gescheiter eroeff\n");
	NeuAufbauenOderWeiterspielen = JA;
	//printf("NeuAufbauenOderWeiterspielen kein gescheiter eroeff\n");
      }
      if ((FarbigeKugelDabei(KugelnVersenkt) ||
	   (FarbigeKugelSumme(KugelnAnBande)>=4)) &&
	  KugelnVersenkt[0]) {
	Foul = JA;
	if (!Begruendung) Begruendung=451;
	//printf("Foul weiss bei eroff versenkt\n");
	if (Spiel==ACHTBALL) {
	  LageVerbesserungKopffeld = JA;
	  //printf("LageVerbesserungKopffeld weiss bei eroff versenkt\n");
	}
      }
    }
    
    if (!ErsteBeruehrteKugel) {
      Foul=JA;
      if (!Begruendung) Begruendung=452;
    }
    
    if (!KorrekteKugelAngespielt(ErsteBeruehrteKugel)) {
      Foul = JA;
      if (!Begruendung) Begruendung=453;
      //printf("Foul keine korrekte kugel angespielt\n");
    }
    
    if (KorrekteKugelAngespielt(ErsteBeruehrteKugel) && 
	!KorrekteKugelVersenktDabei(KugelnVersenkt)) {
      AufnahmeWechsel = JA;
      //printf("AufnahmeWechsel nix gescheites versenkt\n");
      if (!Summe(KugelnAnBande)) {
	Foul = JA;
	if (!Begruendung) Begruendung=454;
	//printf("Foul nix gescheites versenkt, keine Bande\n");
      }
    } 
    
    if (AusKopffeld && 
	ErsteBeruehrteKugelImKopffeld &&
	!BandeAusserhalbKopffeldvorKugelBeruehrt) {
      Foul = JA;
      if (!Begruendung) Begruendung=455;
      //printf("Foul im kopff angespielt\n");
    }
    
    if (! Eroeffnungsstoss && KugelnVersenkt[0]) {
      Foul = JA;
      //printf("Foul weiss versenkt\n");
      if (!Begruendung) Begruendung=456;
      LageVerbesserung = JA;
      //printf("LageVerbesserung weiss bei eroeff1\n");
    }
    
    if (Foul) {
      AufnahmeWechsel = JA;
      if (!LageVerbesserungKopffeld) {
	LageVerbesserung = JA;
      }
      //printf("AufnahmeWechsel wegen Foul\n");
    }
    
    if (Spiel==ACHTBALL) {
      
      if (Eroeffnungsstoss && KugelnVersenkt[8]) {
	NeuAufbauenOderAchtEinsetzen = JA;
        KugelnVersenkt[8]=NEIN;
        KugelnImSpiel[8]=JA;
	//printf("NeuAufbauenOderAchtEinsetzen 8 bei eroeff vers\n");
      }	

      if (NeuAufbauenOderAchtEinsetzen) {
	NeuAufbauenOderWeiterspielen=NEIN;
      }

      if (KugelnVersenkt[8] && !KorrekteKugelVersenkt(8) && !Eroeffnungsstoss) {
	Verloren = JA;
	//printf("Verloren 8\n");
      }

      if (ErsteBeruehrteKugel==8 && !KorrekteKugelAngespielt(8)){
	LageVerbesserung = JA;
      }

      if (KugelnVersenkt[8] && KorrekteKugelVersenkt(8) && !Foul) {
	Gewonnen = JA;
	//printf("Gewonnen\n");
      }
      
      if (!Foul && //Gruppenbestimung
	  !GruppenVerteilung && 
	  !Eroeffnungsstoss && 
	  ErsteVersenkteKugel &&
	  ErsteBeruehrteKugel != 8 &&
	  ErsteVersenkteKugel != 8) {
	if ((SpielerAmStoss == SPIELER1) &&
	    (ErsteVersenkteKugel < 8) ||
	    (SpielerAmStoss == SPIELER2) &&
	    (ErsteVersenkteKugel > 8)) {
	  GruppenVerteilung = S1_GANZE_S2_HALBE;
	  //printf("Gruppenverteilung:  S1_GANZE_S2_HALBE\n");
	}
	if ((SpielerAmStoss == SPIELER1) &&
	    (ErsteVersenkteKugel > 8) ||
	    (SpielerAmStoss == SPIELER2) &&
	    (ErsteVersenkteKugel < 8)) {
	  GruppenVerteilung = S1_HALBE_S2_GANZE;
	  //printf("Gruppenverteilung:  S1_HALBE_S2_GANZE\n");
	}      
      }
    }
    
    if (Spiel==NEUNBALL) {
      if (Foul && KugelnVersenkt[9]) {
	NeunEinsetzen();
        KugelnVersenkt[9]=NEIN;
        KugelnImSpiel[9]=JA;
      }

      if (Foul) {
	if (SpielerAmStoss==SPIELER1) {
	  FoulsHintereinanderSpieler1+=1;
	} else {
	  FoulsHintereinanderSpieler2+=1;
	}
      } else {
	if (SpielerAmStoss==SPIELER1) {
	  FoulsHintereinanderSpieler1=0;
	} else {
	  FoulsHintereinanderSpieler2=0;
	}
      }

      if ((SpielerAmStoss==SPIELER1) &&
	  (FoulsHintereinanderSpieler1 == 3) ||
	  (SpielerAmStoss==SPIELER2) &&
	  (FoulsHintereinanderSpieler2 == 3)) {
	Verloren = JA;
	//printf("Verloren durch drei Fouls hintereinander\n");
      }

      if (KugelnVersenkt[9] && !Foul) {
	Gewonnen = JA;
	//printf("Gewonnen\n");
      }
    }
      
    Eroeffnungsstoss = NEIN;
    AusKopffeld = NEIN;

    if (Gewonnen) {
      if (SpielerAmStoss==SPIELER1) {
	Spieler1Gewonnen=JA;
      } else {
	Spieler2Gewonnen=JA;
      }
    } 
    if (Verloren){
      if (SpielerAmStoss==SPIELER1) {
	Spieler2Gewonnen=JA;
      } else {
	Spieler1Gewonnen=JA;
      }
    }

    SchiedsrichterEntscheidung=(AufnahmeWechsel |
				(Foul * 2) |
				(LageVerbesserungKopffeld * 4) |
				(LageVerbesserung * 8) |
				(NeuAufbauenOderWeiterspielen * 16) |
				(NeuAufbauenOderAchtEinsetzen * 32) |
				(Spieler1Gewonnen * 64) |
				(Spieler2Gewonnen * 128));

    //printf("SchiedsrichterEntscheidung   :%i\n",SchiedsrichterEntscheidung);
    //printf("AufnahmeWechsel              :%i\n",AufnahmeWechsel);
    //printf("Foul                         :%i\n",Foul);
    //printf("LageVerbesserungKopffeld     :%i\n",LageVerbesserungKopffeld);
    //printf("LageVerbesserung             :%i\n",LageVerbesserung);
    //printf("NeuAufbauenOderWeiterspielen :%i\n",NeuAufbauenOderWeiterspielen);
    //printf("NeuAufbauenOderAchtEinsetzen :%i\n",NeuAufbauenOderAchtEinsetzen);
    //printf("Verloren                     :%i\n",Verloren);
    //printf("Gewonnen                     :%i\n",Gewonnen);

  }

  return SchiedsrichterEntscheidung;

}

GLint Schiedsrichter::KorrekteKugelAngespielt(GLint Kugel){
  switch (Spiel) {
  case ACHTBALL: {
    if (GruppenVerteilung == KEINE && Kugel != 8 ) {
      return JA;
    }
    if (GruppenVerteilung == S1_GANZE_S2_HALBE) {
      if (SpielerAmStoss == SPIELER1) {
	if ((Kugel) < 8 ||
	    (!KugelnImSpiel[1] &&
	     !KugelnImSpiel[2] &&
	     !KugelnImSpiel[3] &&
	     !KugelnImSpiel[4] &&
	     !KugelnImSpiel[5] &&
	     !KugelnImSpiel[6] &&
	     !KugelnImSpiel[7] &&
	     Kugel == 8)) {
	  return JA;
	}
      }
       if (SpielerAmStoss == SPIELER2) {
	if (Kugel > 8 ||
	    (!KugelnImSpiel[9] &&
	     !KugelnImSpiel[10] &&
	     !KugelnImSpiel[11] &&
	     !KugelnImSpiel[12] &&
	     !KugelnImSpiel[13] &&
	     !KugelnImSpiel[14] &&
	     !KugelnImSpiel[15] &&
	     Kugel == 8)) {
	  return JA;
	}
      }
    }
    if (GruppenVerteilung == S1_HALBE_S2_GANZE) {
      if (SpielerAmStoss == SPIELER2) {
	if (Kugel < 8 ||
	    (!KugelnImSpiel[1] &&
	     !KugelnImSpiel[2] &&
	     !KugelnImSpiel[3] &&
	     !KugelnImSpiel[4] &&
	     !KugelnImSpiel[5] &&
	     !KugelnImSpiel[6] &&
	     !KugelnImSpiel[7] &&
	     Kugel == 8)) {
	  return JA;
	}
      }
       if (SpielerAmStoss == SPIELER1) {
	if (Kugel > 8 ||
	    (!KugelnImSpiel[9] &&
	     !KugelnImSpiel[10] &&
	     !KugelnImSpiel[11] &&
	     !KugelnImSpiel[12] &&
	     !KugelnImSpiel[13] &&
	     !KugelnImSpiel[14] &&
	     !KugelnImSpiel[15] &&
	     Kugel == 8)) {
	  return JA;
	}
      }
    } 
  } break;
  case NEUNBALL: {
    if (Kugel==NiedrigsteKugel) {
      return JA;
    }
  } break;
  }
  return NEIN;
}

GLint Schiedsrichter::KorrekteKugelVersenkt(GLint Kugel){
  switch (Spiel) {
  case ACHTBALL: {
    if (GruppenVerteilung == KEINE && Kugel != 8 ) {
      return JA;
    }
    if (GruppenVerteilung == S1_GANZE_S2_HALBE) {
      if (SpielerAmStoss == SPIELER1) {
	if (Kugel < 8 ||
	    (!KugelnImSpiel[1] &&
	     !KugelnImSpiel[2] &&
	     !KugelnImSpiel[3] &&
	     !KugelnImSpiel[4] &&
	     !KugelnImSpiel[5] &&
	     !KugelnImSpiel[6] &&
	     !KugelnImSpiel[7] &&
	     Kugel == 8)) {
	  return JA;
	}
      }
       if (SpielerAmStoss == SPIELER2) {
	if (Kugel > 8 ||
	    (!KugelnImSpiel[9] &&
	     !KugelnImSpiel[10] &&
	     !KugelnImSpiel[11] &&
	     !KugelnImSpiel[12] &&
	     !KugelnImSpiel[13] &&
	     !KugelnImSpiel[14] &&
	     !KugelnImSpiel[15] &&
	     Kugel == 8)) {
	  return JA;
	}
      }
    }
    if (GruppenVerteilung == S1_HALBE_S2_GANZE) {
      if (SpielerAmStoss == SPIELER2) {
	if (Kugel < 8 || 
	    (!KugelnImSpiel[1] &&
	     !KugelnImSpiel[2] &&
	     !KugelnImSpiel[3] &&
	     !KugelnImSpiel[4] &&
	     !KugelnImSpiel[5] &&
	     !KugelnImSpiel[6] &&
	     !KugelnImSpiel[7] &&
	     Kugel == 8)) {
	  return JA;
	}
      }
       if (SpielerAmStoss == SPIELER1) {
	if (Kugel > 8 || 
	    (!KugelnImSpiel[9] &&
	     !KugelnImSpiel[10] &&
	     !KugelnImSpiel[11] &&
	     !KugelnImSpiel[12] &&
	     !KugelnImSpiel[13] &&
	     !KugelnImSpiel[14] &&
	     !KugelnImSpiel[15] &&
	     Kugel == 8)) {
	  return JA;
	}
      }
    } 
  } break;
  case NEUNBALL: {
    return JA;
  } break;
  }
  return NEIN;
}

GLint Schiedsrichter::KorrekteKugelVersenktDabei(GLint Kugel[16]){
  GLint Dabei=NEIN;
  for (GLint i=0;i<16;i++) {
    if (Kugel[i]) {
      Dabei|=KorrekteKugelVersenkt(i);
    }
  }
  return Dabei;
}

GLint Schiedsrichter::FarbigeKugel(GLint Kugel){
  if (Spiel==ACHTBALL) {
    if (0<Kugel && Kugel<8 || 8<Kugel && Kugel<16) {
      return JA;
    }
   }
  if (Spiel==NEUNBALL) {
    if (0<Kugel && Kugel<10){
      return JA;
    }
  }
  return NEIN;
}

GLint Schiedsrichter::FarbigeKugelDabei(GLint Kugel[16]){
  GLint Dabei=NEIN;
  for (GLint i=0;i<16;i++) {
    if (Kugel[i]) {
      Dabei|=FarbigeKugel(i);
    }
  }
  return Dabei;
}

GLint Schiedsrichter::FarbigeKugelSumme(GLint Kugel[16]){
  GLint S=NEIN;
  for (GLint i=0;i<16;i++) {
    if (Kugel[i]) {
      S+=FarbigeKugel(i);
    }
  }
  return S;
}

GLint Schiedsrichter::Summe(GLint Kugel[16]){
  GLint S=0;
  for (GLint i=0;i<16;i++) {
    S+=Kugel[i];
  }
  return S;
}

GLint Schiedsrichter::FrageNachSpielerAmStoss(){
  if (AufnahmeWechsel) {
    return 1-SpielerAmStoss;
  }
  return SpielerAmStoss;
}

GLint Schiedsrichter::FrageNachGruppenVerteilung(){
  return GruppenVerteilung;
}

GLint Schiedsrichter::FrageNachBegruendung(){
  return Begruendung;
}

GLint Schiedsrichter::FrageNachFouls(GLint Spieler){
  if (Spieler==SPIELER1) {
    return FoulsHintereinanderSpieler1;
  }
  if (Spieler==SPIELER2) {
    return FoulsHintereinanderSpieler2;
  }
  return 0;
}

void Schiedsrichter::SetzeSpielerAmStoss(GLint Spieler) {
  SpielerAmStoss=Spieler;
}

void Schiedsrichter::SetzeFouls(GLint Spieler,GLint Fouls) {
  if (Spieler==SPIELER1) {
    FoulsHintereinanderSpieler1=Fouls;
  } else {
    FoulsHintereinanderSpieler2=Fouls;
  }
}
