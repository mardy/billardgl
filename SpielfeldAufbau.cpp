#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include "Zeit.h"
#include "Namen.h"
#include "Kugel.h"
#include "Textfeld.h"
#include "Schild.h"
#include "Menu.h"
#include "SpielfeldAufbau.h"

GLfloat random(GLfloat Epsilon) {
  return (Epsilon*(((rand()*2.0)/RAND_MAX)-1));
}

void SpielfeldAufbau() {
  if (StateMaschin==BETRACHTEN||
      StateMaschin==START||
      StateMaschin==WEISSNEU||
      StateMaschin==SCHIEDSRICHTER) {

    //Anfangsstoss=1;
    //WeisseVersetzbar=1;

    LageVerbesserungKopffeld=1;

    GLfloat r=5.715;
    GLfloat a=r+3*Epsilon;
    GLfloat asw3=a*sqrt(3)/6;
    
    srand(Zeit());
    
    //Anzeige.AlleKugelnAusblenden();
    
    for (int i=0;i<16;i++) {
      KugelnImSpiel[i]=0;
      KugelnVersenkt[i]=0;
    }
    
    
    switch (Spiel) {        // Was f"ur ein Spiel?
      
    case 2: {               // Nur zwei Kugeln
      Kugel[0].neuePositionCM(0.0,0.0);
      Kugel[1].neuePositionCM(20.0,0.0);
      for (int i=0;i<2;i++) {
	KugelnImSpiel[i]=1;
      }
      for (int j=2;j<16;j++) {
	Kugel[j].ausblenden();
      }
      break;
    }
      
    case 8: {               // 8-Ball
      
      GLint plaziert[16];
      GLint nummer[16];
      
      do {
	{
	  for (GLint i=0;i<16;i++) {
	    nummer[i]=0;
	    plaziert[i]=0;
	  }
	}
	nummer[0]=0;
	plaziert[0]=1;
	nummer[8]=8;
	plaziert[8]=1;
	
	for (GLint pos=1; pos<16;pos++) {
	  while (!nummer[pos]) {
	    GLint kugel=(GLint) (rand()*16.0/RAND_MAX);
	    if (!plaziert[kugel]) {
	      nummer[pos]=kugel;
	      plaziert[kugel]=1;
	    }
	  }
	}
      } while ((nummer[1]<8)&&(nummer[15]<8)||(nummer[1]>8)&&(nummer[15]>8));
      
      Kugel[nummer[0]].neuePositionCM(-63.5,0.0);
      Kugel[nummer[1]].neuePositionCM(63.5+12*asw3+random(Epsilon),-2.0*a+random(Epsilon));
      Kugel[nummer[2]].neuePositionCM(63.5+9*asw3+random(Epsilon),-1.5*a+random(Epsilon));
      Kugel[nummer[3]].neuePositionCM(63.5+6*asw3+random(Epsilon),-1.0*a+random(Epsilon));
      Kugel[nummer[4]].neuePositionCM(63.5+3*asw3+random(Epsilon),-0.5*a+random(Epsilon));
      Kugel[nummer[5]].neuePositionCM(63.5+0*asw3+random(Epsilon),0.0+random(Epsilon));
      Kugel[nummer[6]].neuePositionCM(63.5+12*asw3+random(Epsilon),-1.0*a+random(Epsilon));
      Kugel[nummer[7]].neuePositionCM(63.5+9*asw3+random(Epsilon),-0.5*a+random(Epsilon));
      Kugel[nummer[8]].neuePositionCM(63.5+6*asw3+random(Epsilon),0.0+random(Epsilon));
      Kugel[nummer[9]].neuePositionCM(63.5+3*asw3+random(Epsilon),0.5*a+random(Epsilon));
      Kugel[nummer[10]].neuePositionCM(63.5+12*asw3+random(Epsilon),0.0+random(Epsilon));
      Kugel[nummer[11]].neuePositionCM(63.5+9*asw3+random(Epsilon),0.5*a+random(Epsilon));
      Kugel[nummer[12]].neuePositionCM(63.5+6*asw3+random(Epsilon),1.0*a+random(Epsilon));
      Kugel[nummer[13]].neuePositionCM(63.5+12*asw3+random(Epsilon),1.0*a+random(Epsilon));
      Kugel[nummer[14]].neuePositionCM(63.5+9*asw3+random(Epsilon),1.5*a+random(Epsilon));
      Kugel[nummer[15]].neuePositionCM(63.5+12*asw3+random(Epsilon),2.0*a+random(Epsilon));
      
      {
	for (int i=0;i<=15;i++) {
	  KugelnImSpiel[i]=1;
	}
      }
      
      break;
    }
      
    case 9: {               // 9-Ball
      
      GLint plaziert[10];
      GLint nummer[10];
      
      {
	for (int i=0;i<10;i++) {
	  KugelnImSpiel[i]=1;
	  nummer[i]=0;
	  plaziert[i]=0;
	}
      }
      nummer[0]=0;
      plaziert[0]=1;
      nummer[3]=1;
      plaziert[1]=1;
      nummer[9]=9;
      plaziert[9]=1;
      
      for (GLint pos=1; pos<10;pos++) {
	while (!nummer[pos]) {
	  GLint kugel=(GLint) (rand()*10.0/RAND_MAX);
	  if (!plaziert[kugel]) {
	    nummer[pos]=kugel;
	    plaziert[kugel]=1;
	  }
	}
      }
      
      Kugel[nummer[0]].neuePositionCM(-63.5,0.0);
      Kugel[nummer[1]].neuePositionCM(63.5+6*asw3+random(Epsilon),-1.0*a+random(Epsilon));
      Kugel[nummer[2]].neuePositionCM(63.5+3*asw3+random(Epsilon),-0.5*a+random(Epsilon));
      Kugel[nummer[3]].neuePositionCM(63.5+0*asw3+random(Epsilon),0.0+random(Epsilon));
      Kugel[nummer[4]].neuePositionCM(63.5+3*asw3+random(Epsilon),0.5*a+random(Epsilon));
      Kugel[nummer[5]].neuePositionCM(63.5+6*asw3+random(Epsilon),1.0*a+random(Epsilon));
      Kugel[nummer[6]].neuePositionCM(63.5+9*asw3+random(Epsilon),0.5*a+random(Epsilon));
      Kugel[nummer[7]].neuePositionCM(63.5+12*asw3+random(Epsilon),0.0+random(Epsilon));
      Kugel[nummer[8]].neuePositionCM(63.5+9*asw3+random(Epsilon),-0.5*a+random(Epsilon));
      Kugel[nummer[9]].neuePositionCM(63.5+6*asw3+random(Epsilon),0.0+random(Epsilon));
      
      {
	for (int i=10;i<16;i++) {
	  Kugel[i].ausblenden();
	}
      }
      break;
    }
      
    case 7: {               // Zufalls-Belegung
      {
	for (int i=0;i<=15;i++) {
	  KugelnImSpiel[i]=1;
	}
      }
      {
	for (int i=0;i<16;i++) {
	  GLfloat min,x,y;
	  do {
	    min=3000;
	    x=118*((((rand()+0.0)/RAND_MAX)*2)-1);
	    y= 59*((((rand()+0.0)/RAND_MAX)*2)-1);
	    for (int j=0;j<i;j++) {
	      GLfloat dx=x-Kugel[j].Pos_xCM();
	      GLfloat dy=y-Kugel[j].Pos_yCM();
	      GLfloat Abstand=sqrt(dx*dx+dy*dy);
	      if (Abstand<min) {min=Abstand;}
	    }
	  } while (min<7);
	  Kugel[i].neuePositionCM(x,y);
	}
	break;
      }
    }
      
    case 0: {               // Keine Kugeln
      {
	for (int i=0;i<16;i++) {
	  Kugel[i].ausblenden();
	}
      }
      break;
    }
      
    }
  }
  
  Menu.NeuerMenuZustand();

}
