#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include "kugeltabellen.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

GLint calc_ind2(GLint b, GLint c, GLint Aufloesung) {
  return ((c*(2*Aufloesung+3-c))/2)+b;
}

void Dreieck(GLfloat ax, GLfloat ay, GLfloat az,
	     GLfloat bx, GLfloat by, GLfloat bz,
	     GLfloat cx, GLfloat cy, GLfloat cz,
	     GLint Aufloesung, GLint &iv, GLint &ii, GLint &it,
	     GLfloat *vertices,GLint *indices,GLfloat *texcoord) {
  
  GLint c=0,b=0;
  GLfloat orient=99;
  GLint ivstart=iv/3;

  for (c=0;c<=Aufloesung;c++) {
    for (b=0;b<=Aufloesung-c;b++) {
      GLfloat temp_x=ax+((b+0.0)/(Aufloesung+0.0))*(bx-ax)+((c+0.0)/(Aufloesung+0.0))*(cx-ax);
      GLfloat temp_y=ay+((b+0.0)/(Aufloesung+0.0))*(by-ay)+((c+0.0)/(Aufloesung+0.0))*(cy-ay);
      GLfloat temp_z=az+((b+0.0)/(Aufloesung+0.0))*(bz-az)+((c+0.0)/(Aufloesung+0.0))*(cz-az);
      GLfloat Abstand=sqrt(temp_x*temp_x+temp_y*temp_y+temp_z*temp_z);
      temp_x=temp_x/Abstand;
      temp_y=temp_y/Abstand;
      temp_z=temp_z/Abstand;
      vertices[iv++]=temp_x; 
      vertices[iv++]=temp_y; 
      vertices[iv++]=temp_z; 
      GLfloat winkel=atan(temp_x/temp_y)/M_PI;
      if (temp_x==0 && temp_y==0) winkel=orient;
      if (!winkel) winkel=0;
      if (temp_y<0) winkel+=1; 
      else if (temp_x<0) winkel+=2;
      if (orient!=99) {
	while (winkel<orient-.5) {winkel+=1;}
	while (winkel>orient+.5) {winkel-=1;}
      }
      orient=winkel;
      texcoord[it++]=winkel;
      texcoord[it++]=acos(temp_z)/M_PI-1;
    }
  }

  for (c=0;c<Aufloesung;c++) {
    for (b=0;b<Aufloesung-c;b++) {
      if (c!=0) {
	indices[ii++]=ivstart+calc_ind2(b,c,Aufloesung);
	indices[ii++]=ivstart+calc_ind2(b+1,c-1,Aufloesung);
	indices[ii++]=ivstart+calc_ind2(b+1,c,Aufloesung);
      }
      indices[ii++]=ivstart+calc_ind2(b,c,Aufloesung);
      indices[ii++]=ivstart+calc_ind2(b+1,c,Aufloesung);
      indices[ii++]=ivstart+calc_ind2(b,c+1,Aufloesung);
    }
  }
}

void initialisiereKugelTabellen(GLint Aufloesung) {
  if (Aufloesung<1) Aufloesung=1;
  if (Aufloesung>29) Aufloesung=29;

  /*
    GLfloat a=atan(1/1)/M_PI;
    GLfloat b=atan(-1/1)/M_PI;
    GLfloat c=atan(-1/-1)/M_PI;
    GLfloat d=atan(1/-1)/M_PI;
    printf("%f %f %f %f\n",a,b,c,d);
  */

  for (GLint A=1;A<=Aufloesung;A++) {
    if (!ball_vertices[A]&& (A%2)) {
      //printf("%i ",A);fflush(stdout);
      ball_vertices[A] = (GLfloat*) malloc (20*3*(A+1)*(A+2)*sizeof(GLfloat)/2);
      ball_indices[A] = (GLint*) malloc (20*3*A*A*sizeof(GLint));
      ball_texcoord[A] = (GLfloat*) malloc (20*(A+1)*(A+2)*sizeof(GLfloat));

      GLfloat a=sqrt(.8);       // 0.8944271
      GLfloat b=sqrt(.2);       // 0.4472136
      GLfloat c=a*sin(.4*M_PI); // 0.8506508
      GLfloat d=a*cos(.4*M_PI); // 0.2763932
      GLfloat e=a*sin(.8*M_PI); // 0.5257311
      GLfloat f=a*cos(.8*M_PI); // 0.7236068
      
      GLint iv=0,ii=0,it=0;
      
      Dreieck(a,0,b,d,c,b,0,0,1,A,iv,ii,it,ball_vertices[A],ball_indices[A],ball_texcoord[A]);//1
      Dreieck(d,c,b,f,e,b,0,0,1,A,iv,ii,it,ball_vertices[A],ball_indices[A],ball_texcoord[A]);//2
      Dreieck(f,e,b,f,-e,b,0,0,1,A,iv,ii,it,ball_vertices[A],ball_indices[A],ball_texcoord[A]);//3
      Dreieck(f,-e,b,d,-c,b,0,0,1,A,iv,ii,it,ball_vertices[A],ball_indices[A],ball_texcoord[A]);//4
      Dreieck(d,-c,b,a,0,b,0,0,1,A,iv,ii,it,ball_vertices[A],ball_indices[A],ball_texcoord[A]);//5
      
      Dreieck(-f,-e,-b,-f,e,-b,a,0,b,A,iv,ii,it,ball_vertices[A],ball_indices[A],ball_texcoord[A]);//6
      Dreieck(a,0,b,-f,e,-b,d,c,b,A,iv,ii,it,ball_vertices[A],ball_indices[A],ball_texcoord[A]);//7
      Dreieck(-f,e,-b,-d,c,-b,d,c,b,A,iv,ii,it,ball_vertices[A],ball_indices[A],ball_texcoord[A]);//8
      Dreieck(d,c,b,-d,c,-b,f,e,b,A,iv,ii,it,ball_vertices[A],ball_indices[A],ball_texcoord[A]);//9
      Dreieck(-d,c,-b,-a,0,-b,f,e,b,A,iv,ii,it,ball_vertices[A],ball_indices[A],ball_texcoord[A]);//10
      Dreieck(f,e,b,-a,0,-b,f,-e,b,A,iv,ii,it,ball_vertices[A],ball_indices[A],ball_texcoord[A]);//11
      Dreieck(-a,0,-b,-d,-c,-b,f,-e,b,A,iv,ii,it,ball_vertices[A],ball_indices[A],ball_texcoord[A]);//12
      Dreieck(f,-e,b,-d,-c,-b,d,-c,b,A,iv,ii,it,ball_vertices[A],ball_indices[A],ball_texcoord[A]);//13
      Dreieck(-d,-c,-b,-f,-e,-b,d,-c,b,A,iv,ii,it,ball_vertices[A],ball_indices[A],ball_texcoord[A]);//14
      Dreieck(d,-c,b,-f,-e,-b,a,0,b,A,iv,ii,it,ball_vertices[A],ball_indices[A],ball_texcoord[A]);//15
      
      Dreieck(-f,e,-b,0,0,-1,-d,c,-b,A,iv,ii,it,ball_vertices[A],ball_indices[A],ball_texcoord[A]);//16
      Dreieck(-d,c,-b,0,0,-1,-a,0,-b,A,iv,ii,it,ball_vertices[A],ball_indices[A],ball_texcoord[A]);//17
      Dreieck(-a,0,-b,0,0,-1,-d,-c,-b,A,iv,ii,it,ball_vertices[A],ball_indices[A],ball_texcoord[A]);//18
      Dreieck(-d,-c,-b,0,0,-1,-f,-e,-b,A,iv,ii,it,ball_vertices[A],ball_indices[A],ball_texcoord[A]);//19
      Dreieck(-f,-e,-b,0,0,-1,-f,e,-b,A,iv,ii,it,ball_vertices[A],ball_indices[A],ball_texcoord[A]);//20
      
      GLint gespart=0;
      
      for (GLint test=0;test<ii;test++) {
	for (GLint vergleich=0;vergleich<test;vergleich++) {
	  if (ball_vertices[A][3*ball_indices[A][test]+0]==ball_vertices[A][3*ball_indices[A][vergleich]+0] &&
	      ball_vertices[A][3*ball_indices[A][test]+1]==ball_vertices[A][3*ball_indices[A][vergleich]+1] &&
	      ball_vertices[A][3*ball_indices[A][test]+2]==ball_vertices[A][3*ball_indices[A][vergleich]+2]) {
	    if (ball_texcoord[A][2*ball_indices[A][test]+0]==ball_texcoord[A][2*ball_indices[A][vergleich]+0] &&
		ball_texcoord[A][2*ball_indices[A][test]+1]==ball_texcoord[A][2*ball_indices[A][vergleich]+1]) {
	      ball_indices[A][test]=ball_indices[A][vergleich];
	      gespart++;
	      break;
	    } else {
	      /*
	      printf("%f %f\n%f %f\n%f %f\n%f %f\n%f %f\n\n",
		     ball_vertices[A][3*ball_indices[A][test]+0],ball_vertices[A][3*ball_indices[A][vergleich]+0],
		     ball_vertices[A][3*ball_indices[A][test]+1],ball_vertices[A][3*ball_indices[A][vergleich]+1],
		     ball_vertices[A][3*ball_indices[A][test]+2],ball_vertices[A][3*ball_indices[A][vergleich]+2],
		     ball_texcoord[A][2*ball_indices[A][test]+0],ball_texcoord[A][2*ball_indices[A][vergleich]+0],
		     ball_texcoord[A][2*ball_indices[A][test]+1],ball_texcoord[A][2*ball_indices[A][vergleich]+1]);
	      */
	    }
	  }
	}
      }
      //printf("gespart: %i\n",gespart);
    }
  }
}
