#include <GL/glut.h>
#include <stdlib.h>
#include "Tischfunktionen.h"

void Tischflaeche() {
  GLint xteile=16;     // Anzahl muss gerade sein
  GLint yteile=8;     // Anzahl muss gerade sein; 
 
  GLfloat *vertices;
  GLfloat *normals;
  GLuint *indices;
 
  vertices = (GLfloat*) malloc (3*(xteile+1)*(yteile+1)* sizeof(GLfloat));
  normals = (GLfloat*) malloc (3*(xteile+1)*(yteile+1)* sizeof(GLfloat));
  indices = (GLuint*) malloc (4*xteile*yteile* sizeof(GLuint));

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);

  GLfloat widthx=264.0/xteile;
  GLfloat widthy=137.0/yteile;

  GLint iv=0, in=0;
  for (float x=0;x<=xteile;x++) {
    for (float y=0;y<=yteile;y++) {
      vertices[iv++]=-132+x*widthx;
      vertices[iv++]=-68.5+y*widthy;
      vertices[iv++]=0;
	  normals[in++]=0;
      normals[in++]=0;
      normals[in++]=1; 
     }
  }
 
  GLint ii=0;
  for (int xi=0;xi<xteile;xi++) {
    for (int yi=0;yi<yteile;yi++) {
      if (((yi==0)&&
	   ((xi==0)||(xi==(xteile/2)-1)||(xi==xteile/2)||(xi==xteile-1)))||
	  ((yi==yteile-1)&&
	   ((xi==0)||(xi==(xteile/2)-1)||(xi==xteile/2)||(xi==xteile-1))))
	   {continue;}
      indices[ii++]=(yteile+1)*xi+yi;
      indices[ii++]=(yteile+1)*(xi+1)+yi;
      indices[ii++]=(yteile+1)*(xi+1)+yi+1;
      indices[ii++]=(yteile+1)*xi+yi+1;
    }
  }
 
  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glNormalPointer(GL_FLOAT, 0, normals);

  glDrawElements(GL_QUADS,4*xteile*yteile-8*4 , GL_UNSIGNED_INT,indices);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);

  free(vertices);
  free(normals);
  free(indices);
 }

void TischflaechemitTextur() {
  GLint xteile=16;     // Anzahl muss gerade sein
  GLint yteile=8;     // Anzahl muss gerade sein; 
 
  GLfloat *vertices;
  GLfloat *normals;
  GLfloat *texcoord;
  GLuint *indices;
 
  vertices = (GLfloat*) malloc (3*(xteile+1)*(yteile+1)* sizeof(GLfloat));
  normals = (GLfloat*) malloc (3*(xteile+1)*(yteile+1)* sizeof(GLfloat));
  texcoord = (GLfloat*) malloc (2*(xteile+1)*(yteile+1)* sizeof(GLfloat));
  indices = (GLuint*) malloc (4*xteile*yteile* sizeof(GLuint));

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  GLfloat widthx=264.0/xteile;
  GLfloat widthy=137.0/yteile;

  GLint iv=0, in=0, it=0;
  for (float x=0;x<=xteile;x++) {
    for (float y=0;y<=yteile;y++) {
      vertices[iv++]=-132+x*widthx;
      vertices[iv++]=-68.5+y*widthy;
      vertices[iv++]=0;
	  texcoord[it++]=(-132+x*widthx)/8.5;
	  texcoord[it++]=(-68.5+y*widthy)/8.5;
      normals[in++]=0;
      normals[in++]=0;
      normals[in++]=1; 
     }
  }
 
  GLint ii=0;
  for (int xi=0;xi<xteile;xi++) {
    for (int yi=0;yi<yteile;yi++) {
      if (((yi==0)&&
	   ((xi==0)||(xi==(xteile/2)-1)||(xi==xteile/2)||(xi==xteile-1)))||
	  ((yi==yteile-1)&&
	   ((xi==0)||(xi==(xteile/2)-1)||(xi==xteile/2)||(xi==xteile-1))))
	   {continue;}
      indices[ii++]=(yteile+1)*xi+yi;
      indices[ii++]=(yteile+1)*(xi+1)+yi;
      indices[ii++]=(yteile+1)*(xi+1)+yi+1;
      indices[ii++]=(yteile+1)*xi+yi+1;
    }
  }
 
  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glNormalPointer(GL_FLOAT, 0, normals);
  glTexCoordPointer(2, GL_FLOAT, 0, texcoord);

  glDrawElements(GL_QUADS,4*xteile*yteile-8*4 , GL_UNSIGNED_INT,indices);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);

  free(vertices);
  free(normals);
  free(indices);
  free(texcoord); 
 }


void MittelLochVerkleidung() {
  GLfloat mat_ambient[]={0,0,0,1};
  GLfloat mat_diffuse[]={.6,.45,0,1};
  GLfloat mat_specular[]={2,2,2,2};
  GLfloat mat_shininess = 127.0;
  glMaterialfv(GL_FRONT, GL_AMBIENT,mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,mat_specular);
  glMaterialf(GL_FRONT, GL_SHININESS,mat_shininess);




  GLfloat *vertices;
  GLfloat *normals;
  //  GLuint *indices;
 
  vertices = (GLfloat*) malloc (3*38*sizeof(GLfloat));
  normals = (GLfloat*) malloc (3*38*sizeof(GLfloat));
  //indices = (GLuint*) malloc (4*22*sizeof(GLint));

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);

  GLint iv=0;
  GLint in=0;

  //0
  vertices[iv++]=7.5;
  vertices[iv++]=68.5;
  vertices[iv++]=5;
  normals[in++]=0;
  normals[in++]=0;
  normals[in++]=1; 

  //1
  vertices[iv++]=7.5;
  vertices[iv++]=72.7;
  vertices[iv++]=3.3+1.5;
  normals[in++]=0;
  normals[in++]=0.1;
  normals[in++]=1; 

  //2
  vertices[iv++]=7.5;
  vertices[iv++]=76.5;
  vertices[iv++]=2.9+1.5;
  normals[in++]=0;
  normals[in++]=0.25;
  normals[in++]=.97; 

  //3
  vertices[iv++]=7.5;
  vertices[iv++]=80;
  vertices[iv++]=2.1+1.5;
  normals[in++]=0;
  normals[in++]=.4;
  normals[in++]=.91; 

  //4
  vertices[iv++]=3.75;
  vertices[iv++]=80;
  vertices[iv++]=2.1+1.5;
  normals[in++]=0;
  normals[in++]=.4;
  normals[in++]=.91; 

  //5
  vertices[iv++]=0;
  vertices[iv++]=80;
  vertices[iv++]=2.1+1.5;
  normals[in++]=0;
  normals[in++]=.4;
  normals[in++]=.91; 

  //6
  vertices[iv++]=-3.75;
  vertices[iv++]=80;
  vertices[iv++]=2.1+1.5;
  normals[in++]=0;
  normals[in++]=.4;
  normals[in++]=.91; 

  //7
  vertices[iv++]=-7.5;
  vertices[iv++]=80;
  vertices[iv++]=2.1+1.5;
  normals[in++]=0;
  normals[in++]=.4;
  normals[in++]=.91; 

  //8
  vertices[iv++]=-7.5;
  vertices[iv++]=76.5;
  vertices[iv++]=2.9+1.5;
  normals[in++]=0;
  normals[in++]=0.25;
  normals[in++]=.97; 

  //9
  vertices[iv++]=-7.5;
  vertices[iv++]=72.7;
  vertices[iv++]=3.3+1.5;
  normals[in++]=0;
  normals[in++]=0.1;
  normals[in++]=1; 

  //10
  vertices[iv++]=-7.5;
  vertices[iv++]=68.5;
  vertices[iv++]=5;
  normals[in++]=0;
  normals[in++]=0;
  normals[in++]=1; 

  //11
  vertices[iv++]=6.5;
  vertices[iv++]=68.5;
  vertices[iv++]=5;
  normals[in++]=0;
  normals[in++]=0;
  normals[in++]=1; 

  //12
  vertices[iv++]=5.6;
  vertices[iv++]=72.7;
  vertices[iv++]=3.3+1.5;
  normals[in++]=0;
  normals[in++]=.1;
  normals[in++]=1; 

  //13
  vertices[iv++]=5;
  vertices[iv++]=74.6;
  vertices[iv++]=3.15+1.5;
  normals[in++]=0;
  normals[in++]=0.2;
  normals[in++]=.97; 

  //14
  vertices[iv++]=3.75;
  vertices[iv++]=76.25;
  vertices[iv++]=2.9+1.5;
  normals[in++]=0;
  normals[in++]=0.25;
  normals[in++]=.97; 

  //15
  vertices[iv++]=2.05;
  vertices[iv++]=77.2;
  vertices[iv++]=2.7+1.5;
  normals[in++]=0;
  normals[in++]=.3;
  normals[in++]=.95; 

  //16
  vertices[iv++]=0;
  vertices[iv++]=77.6;
  vertices[iv++]=2.65+1.5;
  normals[in++]=0;
  normals[in++]=0.3;
  normals[in++]=.95; 

  //17
  vertices[iv++]=-2.05;
  vertices[iv++]=77.2;
  vertices[iv++]=2.7+1.5;
  normals[in++]=0;
  normals[in++]=0.3;
  normals[in++]=.95; 

  //18
  vertices[iv++]=-3.75;
  vertices[iv++]=76.25;
  vertices[iv++]=2.9+1.5;
  normals[in++]=0;
  normals[in++]=.25;
  normals[in++]=.97; 

  //19
  vertices[iv++]=-5;
  vertices[iv++]=74.6;
  vertices[iv++]=3.15+1.5;
  normals[in++]=0;
  normals[in++]=0.25;
  normals[in++]=.97; 

  //20
  vertices[iv++]=-5.6;
  vertices[iv++]=72.7;
  vertices[iv++]=3.3+1.5;
  normals[in++]=0;
  normals[in++]=0.1;
  normals[in++]=1; 

  //21
  vertices[iv++]=-6.5;
  vertices[iv++]=68.5;
  vertices[iv++]=5;
  normals[in++]=0;
  normals[in++]=0;
  normals[in++]=1; 

  //22
  vertices[iv++]=7.5;
  vertices[iv++]=81.8;
  vertices[iv++]=1.1+1.5;
  normals[in++]=0;
  normals[in++]=0.71;
  normals[in++]=0.71; 

  //23
  vertices[iv++]=3.75;
  vertices[iv++]=81.8;
  vertices[iv++]=1.1+1.5;
  normals[in++]=0;
  normals[in++]=.71;
  normals[in++]=.71; 

  //24
  vertices[iv++]=0;
  vertices[iv++]=81.8;
  vertices[iv++]=1.1+1.5;
  normals[in++]=0;
  normals[in++]=.71;
  normals[in++]=.71; 

  //25
  vertices[iv++]=-3.75;
  vertices[iv++]=81.8;
  vertices[iv++]=1.1+1.5;
  normals[in++]=0;
  normals[in++]=.71;
  normals[in++]=.71; 

  //26
  vertices[iv++]=-7.5;
  vertices[iv++]=81.8;
  vertices[iv++]=1.1+1.5;
  normals[in++]=0;
  normals[in++]=.71;
  normals[in++]=.71; 

  //27
  vertices[iv++]=7.5;
  vertices[iv++]=82.5;
  vertices[iv++]=0.0+1.5;
  normals[in++]=0;
  normals[in++]=1;
  normals[in++]=0; 

  //28
  vertices[iv++]=3.75;
  vertices[iv++]=82.5;
  vertices[iv++]=0.0+1.5;
  normals[in++]=0;
  normals[in++]=1;
  normals[in++]=0; 

  //29
  vertices[iv++]=0;
  vertices[iv++]=82.5;
  vertices[iv++]=0.0+1.5;
  normals[in++]=0;
  normals[in++]=1;
  normals[in++]=0; 

  //30
  vertices[iv++]=-3.75;
  vertices[iv++]=82.5;
  vertices[iv++]=0+1.5;
  normals[in++]=0;
  normals[in++]=1;
  normals[in++]=0; 

  //31
  vertices[iv++]=-7.5;
  vertices[iv++]=82.5;
  vertices[iv++]=0+1.5;
  normals[in++]=0;
  normals[in++]=1;
  normals[in++]=0; 

  //32
  vertices[iv++]=7.5;
  vertices[iv++]=82.5;
  vertices[iv++]=-10;
  normals[in++]=0;
  normals[in++]=1;
  normals[in++]=0; 

  //33
  vertices[iv++]=3.75;
  vertices[iv++]=82.5;
  vertices[iv++]=-10;
  normals[in++]=0;
  normals[in++]=1;
  normals[in++]=0; 

  //34
  vertices[iv++]=0;
  vertices[iv++]=82.5;
  vertices[iv++]=-10;
  normals[in++]=0;
  normals[in++]=1;
  normals[in++]=0; 

  //35
  vertices[iv++]=-3.75;
  vertices[iv++]=82.5;
  vertices[iv++]=-10;
  normals[in++]=0;
  normals[in++]=1;
  normals[in++]=0; 

  //36
  vertices[iv++]=-7.5;
  vertices[iv++]=82.5;
  vertices[iv++]=-10;
  normals[in++]=0;
  normals[in++]=1;
  normals[in++]=0; 

  GLuint indices[]={0,1,12,11,
	   1,2,13,12,
	   2,3,14,13,
	   3,4,15,14,
	   4,5,16,15,
	   5,6,17,16,
	   6,7,18,17,
	   7,8,19,18,
	   8,9,20,19,
	   9,10,21,20,
	   3,22,23,4,
	   4,23,24,5,
	   5,24,25,6,
	   6,25,26,7,
	   22,27,28,23,
	   23,28,29,24,
	   24,29,30,25,
	   25,30,31,26,
	   27,32,33,28,
	   28,33,34,29,
	   29,34,35,30,
	   30,35,36,31};

  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glNormalPointer(GL_FLOAT, 0, normals);

  glDrawElements(GL_QUADS,22*4 , GL_UNSIGNED_INT,indices);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);

  free(vertices);
  free(normals);
  //free(indices);

}

void EckLochVerkleidung() {
  
  GLfloat vertices[]={0,-9,5,
		      4.2,-9,4.8,
		      0,-8.2,5,
		      4.6,-3.2,4.8,
		      5.6,0,4.8,
		      5.2,2.1,4.8,
		      4,4,4.8,
		      2.1,5.2,4.8,
		      0,5.6,4.8,
		      -3.2,4.6,4.8,
		      -8.2,0,5,
		      -9,0,5,
		      -9,4.2,4.8,
		      8,-9,4.4,
		      8,-4.5,4.4,
		      8,0,4.4,
		      7.4,3,4.4,
		      5.7,5.7,4.4,
		      3,7.4,4.4,
		      0,8,4.4,
		      -4.5,8,4.4,
		      -9,8,4.4,
		      11.5,-9,3.6,
		      11.5,-4.5,3.6,
		      11.5,0,3.6,
		      10.6,4.4,3.6,
		      8.1,8.1,3.6,
		      4.4,10.6,3.6,
		      0,11.5,3.6,
		      -4.5,11.5,3.6,
		      -9,11.5,3.6,
		      13.3,-9,2.6,
		      13.3,-4.5,2.6,
		      13.3,0,2.6,
		      12.2,5.1,2.6,
		      9.4,9.4,2.6,
		      5.1,12.2,2.6,
		      0,13.3,2.6,
		      -4.5,13.3,2.6,
		      -9,13.3,2.6,
		      14,-9,1.5,
		      14,-4.5,1.5,
		      14,0,1.5,
		      12.9,5.3,1.5,
		      9.9,9.9,1.5,
		      5.3,12.9,1.5,
		      0,14,1.5,
		      -4.5,14,1.5,
		      -9,14,1.5,
		      14,-9,-10,
		      14,-4.5,-10,
		      14,0,-10,
		      12.9,5.3,-10,
		      9.9,9.9,-10,
		      5.3,12.9,-10,
		      0,14,-10,
		      -4.5,14,-10,
		      -9,14,-10};

  GLfloat normals[]={0,0,1,
		     0.1,0,1,
		     0,0,1,
		     0.1,0,1,
		     0.1,0,1,
		     0.08,0.01,1,
		     0.07,0.07,1,
		     0.01,0.08,1,
		     0,0.1,1,
		     0,0.1,1,
		     0,0,1,
		     0,0,1,
		     0,0.1,1,
		     .25,0,.97,
		     .25,0,.97,
		     .25,0,.97,
		     .23,.1,.97,
		     .17,.17,.97,
		     .1,.23,.97,
		     0,.25,.97,
		     0,.25,.97,
		     0,.25,.97,
		     .4,0,.91,
		     .4,0,.91,
		     .4,0,.91,
		     .37,.15,.91,
		     .28,.28,.91,
		     .15,.37,.91,
		     0,.4,.91,
		     0,.4,.91,
		     0,.4,.91,
		     .71,0,.71,
		     .71,0,.71,
		     .71,0,.71,
		     .66,.27,.71,
		     .5,.5,.71,
		     .27,.66,.71,
		     0,.71,.71,
		     0,.71,.71,
		     0,.71,.71,
		     1,0,0,
		     1,0,0,
		     1,0,0,
		     .92,.38,0,
		     .71,.71,0,
		     0.38,.92,0,
		     0,1,0,
		     0,1,0,
		     0,1,0,
		     1,0,0,
		     1,0,0,
		     1,0,0,
		     .92,.38,0,
		     .71,.71,0,
		     0.38,.92,0,
		     0,1,0,
		     0,1,0,
		     0,1,0};

  GLuint indices[]={0,1,3,2,
		    1,13,14,3,
		    3,14,15,4,
		    4,15,16,5,
		    5,16,17,6,
		    6,17,18,7,
		    7,18,19,8,
		    8,19,20,9,
		    9,20,21,12,
		    9,12,11,10,
		    13,22,23,14,
		    14,23,24,15,
		    15,24,25,16,
		    16,25,26,17,
		    17,26,27,18,
		    18,27,28,19,
		    19,28,29,20,
		    20,29,30,21,
		    22,31,32,23,
		    23,32,33,24,
		    24,33,34,25,
		    25,34,35,26,
		    26,35,36,27,
		    27,36,37,28,
		    28,37,38,29,
		    29,38,39,30,
		    31,40,41,32,
		    32,41,42,33,
		    33,42,43,34,
		    34,43,44,35,
		    35,44,45,36,
		    36,45,46,37,
		    37,46,47,38,
		    38,47,48,39,
                    40,49,50,41,
		    41,50,51,42,
		    42,51,52,43,
		    43,52,53,44,
		    44,53,54,45,
		    45,54,55,46,
		    46,55,56,47,
		    47,56,57,48};

  GLfloat mat_ambient[]={0,0,0,1};
  GLfloat mat_diffuse[]={.6,.45,0,1};
  GLfloat mat_specular[]={2,2,2,2};
  GLfloat mat_shininess = 127.0;
  glMaterialfv(GL_FRONT, GL_AMBIENT,mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,mat_specular);
  glMaterialf(GL_FRONT, GL_SHININESS,mat_shininess);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);

  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glNormalPointer(GL_FLOAT, 0, normals);

  glDrawElements(GL_QUADS,42*4 , GL_UNSIGNED_INT,indices);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
}

void MittelLochInnenverkleidung() {
  
  GLfloat vertices[]={6.5,68.5,5,
		      5.6,72.7,4.8,
		      5,74.6,4.65,
		      3.75,76.25,4.4,
		      2.05,77.2,4.2,
		      0,77.6,4.15,
		      -2.05,77.2,4.2,
		      -3.75,76.25,4.4,
		      -5,74.6,4.65,
		      -5.6,72.7,4.8,
		      -6.5,68.5,5,
		      6.5,68.5,2.5,
		      7.1,74.2,2.5,
		      6.2,75.5,2.5,
		      4.6,77.2,2.5,
		      2.8,78.4,2.5,
		      0,79,2.5,
		      -2.8,78.4,2.5,
		      -4.6,77.2,2.5,
		      -6.2,75.5,2.5,
		      -7.1,74.2,2.5,
		      -6.5,68.5,2.5,
		      6.5,68.5,-10,
		      7.1,74.2,-10,
		      6.2,75.5,-10,
		      4.6,77.2,-10,
		      2.8,78.4,-10,
		      0,79,-10,
		      -2.8,78.4,-10,
		      -4.6,77.2,-10,
		      -6.2,75.5,-10,
		      -7.1,74.2,-10,
		      -6.5,68.5,-10};

  GLfloat normals[]={-5.8,-1,-5,
		     -5.8,-1,-5,
		     -4,-2.8,-5,
		     -3.8,-4.4,-5,
		     -2,-5.6,-5,
		     0,-5.8,-5,
		     2,-5.6,-5,
		     3.8,-4.4,-5,
		     4,-2.8,-5,
		     5.8,-1,-5,
		     5.8,-1,-5,
		     -6.5,3.2,0,
		     -7.1,-.9,0,
		     -6.2,-3.8,0,
		     -4.6,-5.5,0,
		     -2.8,-6.8,0,
		     0,-7.2,0,
		     2.8,-6.8,0,
		     4.6,-5.5,0,
		     6.2,-3.8,0,
		     7.1,-.9,0,
		     -6.5,3.2,0,
		     -6.5,3.2,0,
		     -7.1,-.9,0,
		     -6.2,-3.8,0,
		     -4.6,-5.5,0,
		     -2.8,-6.8,0,
		     0,-7.2,0,
		     2.8,-6.8,0,
		     4.6,-5.5,0,
		     6.2,-3.8,0,
		     7.1,-.9,0,
		     -6.5,3.2,0};

  GLint indices[]={0,1,12,11,
		   1,2,13,12,
		   2,3,14,13,
		   3,4,15,14,
		   4,5,16,15,
		   5,6,17,16,
		   6,7,18,17,
		   7,8,19,18,
		   8,9,20,19,
		   9,10,21,20,
		   11,12,23,22,
		   12,13,24,23,
		   13,14,25,24,
		   14,15,26,25,
		   15,16,27,26,
		   16,17,28,27,
		   17,18,29,28,
		   18,19,30,29,
		   19,20,31,30,
		   20,21,32,31};

  GLfloat mat_ambient[]={0,0,0,1.0};
  GLfloat mat_diffuse[]={.3,.3,.3,1};
  GLfloat mat_specular[]={10.0,10.0,10.0,10.0};
  GLfloat mat_shininess = 127.0;

  glMaterialfv(GL_FRONT, GL_AMBIENT,mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,mat_specular);
  glMaterialf(GL_FRONT, GL_SHININESS,mat_shininess);


  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);

  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glNormalPointer(GL_FLOAT, 0, normals);

  glDrawElements(GL_QUADS,4*20, GL_UNSIGNED_INT,indices);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);

}

void EckLochInnenverkleidung() {

  GLfloat vertices[]={0,-8.2,5,
		      4.6,-3.2,4.8,
		      5.6,0,4.8,
		      5.2,2.1,4.8,
		      4,4,4.8,
		      2.1,5.2,4.8,
		      0,5.6,4.8,
		      -3.2,4.6,4.8,
		      -8.2,0,5,
		      0,-8.2,2.5,
		      5.7,-4,2.5,
		      6.3,0,2.5,
		      5.7,2.3,2.5,
		      4.3,4.3,2.5,
		      2.3,5.7,2.5,
		      0,6.3,2.5,
		      -4,5.7,2.5,
		      -8.2,0,2.5,
		      0,-8.2,-10,
		      5.7,-4,-10,
		      6.3,0,-10,
		      5.7,2.3,-10,
		      4.3,4.3,-10,
		      2.3,5.7,-10,
		      0,6.3,-10,
		      -4,5.7,-10,
		      -8.2,0,-10};
  
  GLfloat normals[]={0,8.2,-5,
		     -4.6,3.2,-4.8,
		     -5.6,0,-4.8,
		     -5.2,-2.1,-4.8,
		     -4,-4,-4.8,
		     -2.1,-5.2,-4.8,
		     0,-5.6,-4.8,
		     3.2,-4.6,-4.8,
		     8.2,0,-5,
		     0,8.2,0,
		     -5.7,4,0,
		     -6.3,0,0,
		     -5.7,-2.3,0,
		     -4.3,-4.3,0,
		     -2.3,-5.7,0,
		     0,-6.3,0,
		     4,-5.7,0,
		     8.2,0,0,
		     0,8.2,0,
		     -5.7,4,0,
		     -6.3,0,0,
		     -5.7,-2.3,0,
		     -4.3,-4.3,0,
		     -2.3,-5.7,0,
		     0,-6.3,0,
		     4,-5.7,0,
		     8.2,0,0,};

  GLint indices[]={0,1,10,9,
		   1,2,11,10,
		   2,3,12,11,
		   3,4,13,12,
		   4,5,14,13,
		   5,6,15,14,
		   6,7,16,15,
		   7,8,17,16,
		   9,10,19,18,
		   10,11,20,19,
		   11,12,21,20,
		   12,13,22,21,
		   13,14,23,22,
		   14,15,24,23,
		   15,16,25,24,
		   16,17,26,25};

  GLfloat mat_ambient[]={0,0,0,1.0};
  GLfloat mat_diffuse[]={.3,.3,.3,1};
  GLfloat mat_specular[]={10.0,10.0,10.0,10.0};
  GLfloat mat_shininess = 127.0;


  glMaterialfv(GL_FRONT, GL_AMBIENT,mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,mat_specular);
  glMaterialf(GL_FRONT, GL_SHININESS,mat_shininess);


  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);

  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glNormalPointer(GL_FLOAT, 0, normals);

  glDrawElements(GL_QUADS,4*16, GL_UNSIGNED_INT,indices);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);


}


void Holzbande(GLfloat Breite, GLint Unterteilungen, GLfloat TexFaktorX, GLfloat TexFaktorY) {

  GLfloat mat_diffuse[]={1.0,1.0,1.0,1.0};
  GLfloat mat_specular[]={1.0,1.0,1.0,1.0};
  GLfloat mat_shininess = 127.0;

  glMaterialfv(GL_FRONT, GL_AMBIENT,mat_diffuse);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,mat_specular);
  glMaterialf(GL_FRONT, GL_SHININESS,mat_shininess);

  GLfloat *vertices;
  GLfloat *normals;
  GLuint *indices;
  GLfloat *texcoord;
  
  vertices = (GLfloat*) malloc (3*7*(Unterteilungen+1)* sizeof(GLfloat));
  normals = (GLfloat*) malloc (3*7*(Unterteilungen+1)* sizeof(GLfloat));
  indices = (GLuint*) malloc (1000+4*6*Unterteilungen* sizeof(GLuint)); 
  texcoord = (GLfloat*) malloc (2*7*(Unterteilungen+1)* sizeof(GLfloat));

  GLfloat TeilBreite=Breite/Unterteilungen;

  int iv=0; int in=0; int ii=0; int it=0;

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  for (GLint u=0;u<=Unterteilungen;u++) {
    vertices[iv++]=u*TeilBreite;
    vertices[iv++]=0;
    vertices[iv++]=5;
    normals[in++]=0;
    normals[in++]=0;
    normals[in++]=1;
    texcoord[it++]=u*TexFaktorX/Unterteilungen;
    texcoord[it++]=0;

    vertices[iv++]=u*TeilBreite;
    vertices[iv++]=4.2;
    vertices[iv++]=4.8;
    normals[in++]=0;
    normals[in++]=.1;
    normals[in++]=1;
    texcoord[it++]=u*TexFaktorX/Unterteilungen;
    texcoord[it++]=.3*TexFaktorY;

    vertices[iv++]=u*TeilBreite;
    vertices[iv++]=8;
    vertices[iv++]=4.4;
    normals[in++]=0;
    normals[in++]=.25;
    normals[in++]=.97;
    texcoord[it++]=u*TexFaktorX/Unterteilungen;
    texcoord[it++]=.57*TexFaktorY;

    vertices[iv++]=u*TeilBreite;
    vertices[iv++]=11.5;
    vertices[iv++]=3.6;
    normals[in++]=0;
    normals[in++]=.4;
    normals[in++]=.91;
    texcoord[it++]=u*TexFaktorX/Unterteilungen;
    texcoord[it++]=.82*TexFaktorY;

    vertices[iv++]=u*TeilBreite;
    vertices[iv++]=13.3;
    vertices[iv++]=2.6;
    normals[in++]=0;
    normals[in++]=.71;
    normals[in++]=.71;
    texcoord[it++]=u*TexFaktorX/Unterteilungen;
    texcoord[it++]=.95*TexFaktorY;

    vertices[iv++]=u*TeilBreite;
    vertices[iv++]=14;
    vertices[iv++]=1.5;
    normals[in++]=0;
    normals[in++]=1;
    normals[in++]=0;
    texcoord[it++]=u*TexFaktorX/Unterteilungen;
    texcoord[it++]=TexFaktorY;

    vertices[iv++]=u*TeilBreite;
    vertices[iv++]=14;
    vertices[iv++]=-10;
    normals[in++]=0;
    normals[in++]=1;
    normals[in++]=0;
    texcoord[it++]=u*TexFaktorX/Unterteilungen;
    texcoord[it++]=.5*TexFaktorY;
  }

  for (GLint y=0;y<6;y++) {
    for (GLint x=0;x<Unterteilungen;x++) {
      indices[ii++]=x*7+y+1;
      indices[ii++]=x*7+y;
      indices[ii++]=(x+1)*7+y;
      indices[ii++]=(x+1)*7+y+1;
    }
  }

  glNormalPointer(GL_FLOAT, 0, normals);
  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glTexCoordPointer(2, GL_FLOAT, 0, texcoord);

  glDrawElements(GL_QUADS,4*6*Unterteilungen, GL_UNSIGNED_INT,indices);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);

  free(vertices);
  free(normals);
  free(indices);
  free(texcoord);
}

void HolzbandeOT(GLfloat Breite, GLint Unterteilungen) {

  GLfloat mat_diffuse[]={.45,.19,.03,1.0};
  GLfloat mat_specular[]={1.0,1.0,1.0,1.0};
  GLfloat mat_shininess = 127.0;

  glMaterialfv(GL_FRONT, GL_AMBIENT,mat_diffuse);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,mat_specular);
  glMaterialf(GL_FRONT, GL_SHININESS,mat_shininess);

  GLfloat *vertices;
  GLfloat *normals;
  GLuint *indices;
  
  vertices = (GLfloat*) malloc (3*7*(Unterteilungen+1)* sizeof(GLfloat));
  normals = (GLfloat*) malloc (3*7*(Unterteilungen+1)* sizeof(GLfloat));
  indices = (GLuint*) malloc (1000+4*6*Unterteilungen* sizeof(GLuint)); 

  GLfloat TeilBreite=Breite/Unterteilungen;

  int iv=0; int in=0; int ii=0;

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);

  for (GLint u=0;u<=Unterteilungen;u++) {
    vertices[iv++]=u*TeilBreite;
    vertices[iv++]=0;
    vertices[iv++]=5;
    normals[in++]=0;
    normals[in++]=0;
    normals[in++]=1;

    vertices[iv++]=u*TeilBreite;
    vertices[iv++]=4.2;
    vertices[iv++]=4.8;
    normals[in++]=0;
    normals[in++]=.1;
    normals[in++]=1;

    vertices[iv++]=u*TeilBreite;
    vertices[iv++]=8;
    vertices[iv++]=4.4;
    normals[in++]=0;
    normals[in++]=.25;
    normals[in++]=.97;

    vertices[iv++]=u*TeilBreite;
    vertices[iv++]=11.5;
    vertices[iv++]=3.6;
    normals[in++]=0;
    normals[in++]=.4;
    normals[in++]=.91;

    vertices[iv++]=u*TeilBreite;
    vertices[iv++]=13.3;
    vertices[iv++]=2.6;
    normals[in++]=0;
    normals[in++]=.71;
    normals[in++]=.71;

    vertices[iv++]=u*TeilBreite;
    vertices[iv++]=14;
    vertices[iv++]=1.5;
    normals[in++]=0;
    normals[in++]=1;
    normals[in++]=0;

    vertices[iv++]=u*TeilBreite;
    vertices[iv++]=14;
    vertices[iv++]=-10;
    normals[in++]=0;
    normals[in++]=1;
    normals[in++]=0;
  }

  for (GLint y=0;y<6;y++) {
    for (GLint x=0;x<Unterteilungen;x++) {
      indices[ii++]=x*7+y+1;
      indices[ii++]=x*7+y;
      indices[ii++]=(x+1)*7+y;
      indices[ii++]=(x+1)*7+y+1;
    }
  }

  glNormalPointer(GL_FLOAT, 0, normals);
  glVertexPointer(3, GL_FLOAT, 0, vertices);

  glDrawElements(GL_QUADS,4*6*Unterteilungen, GL_UNSIGNED_INT,indices);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);

  free(vertices);
  free(normals);
  free(indices);
}

void Banden(GLint richtung, GLint Multiply){ 
// Banden berechnen

//richtung=0 --> Banden links und rechts
//richtung=1 --> Banden oben und unten
  
   GLfloat *vertices;
   GLfloat *normals;
   GLuint *indices;
 
   vertices = (GLfloat*) malloc (3*8* sizeof(GLfloat));
   normals = (GLfloat*) malloc (3*8* sizeof(GLfloat));
   indices = (GLuint*) malloc (4*6* sizeof(GLfloat)); 

// Banden links und rechts 

   if (richtung==0) {

   vertices[0]=-132;       // Punkt 0
   vertices[1]=-60.3;
   vertices[2]=0;
   normals[0]=3.429;
   normals[1]=-1;
   normals[2]=-5;

   vertices[3]=-127;       // Punkt 1
   vertices[4]=-53.56;
   vertices[5]=3.429;
   normals[3]=3.429;
   normals[4]=-1;
   normals[5]=-5;

   vertices[6]=-127;        // Punkt 2
   vertices[7]=-53.56;
   vertices[8]=3.829;
   normals[6]=1.371;
   normals[7]=-1;
   normals[8]=5;

   vertices[9]=-132;        // Punkt 3
   vertices[10]=-60.3;
   vertices[11]=5;
   normals[9]=-3.829;
   normals[10]=-1;
   normals[11]=5;
  
   vertices[12]=-132;       // Punkt 4
   vertices[13]=60.3;
   vertices[14]=0;
   normals[12]=3.429;
   normals[13]=1;
   normals[14]=-5;

   vertices[15]=-127;       // Punkt 5
   vertices[16]=53.56;
   vertices[17]=3.429;
   normals[15]=3.429;
   normals[16]=1;
   normals[17]=-5;

   vertices[18]=-127;       // Punkt 6
   vertices[19]=53.56;
   vertices[20]=3.829;
   normals[18]=1.371;
   normals[19]=1;
   normals[20]=5;

   vertices[21]=-132;       // Punkt 7
   vertices[22]=60.3;
   vertices[23]=5;
   normals[21]=-3.829;
   normals[22]=1;
   normals[23]=5;

  indices[0]=0;
  indices[1]=4; 
  indices[2]=5;
  indices[3]=1;

  indices[4]=1;
  indices[5]=5; 
  indices[6]=6;
  indices[7]=2;
  
  indices[8]=2;
  indices[9]=6; 
  indices[10]=7;
  indices[11]=3;
  
  indices[12]=0;
  indices[13]=3;
  indices[14]=7;
  indices[15]=4;
  
  indices[16]=0;
  indices[17]=1;
  indices[18]=2;
  indices[19]=3;
  
  indices[20]=4;
  indices[21]=7;
  indices[22]=6;
  indices[23]=5;
  }

  // Banden in y-Richtung berechnen
  // für Multiply dann 1 oder -1 setzen!!

  else {
 
  vertices[0]=-123.8*Multiply;       // Punkt 0
  vertices[1]=68.5;
  vertices[2]=0;
  normals[0]=-1;
  normals[1]=-3.429;
  normals[2]=-5;

  vertices[3]=-117.16*Multiply;       // Punkt 1
  vertices[4]=63.5;
  vertices[5]=3.429;
  normals[3]=-1;
  normals[4]=-3.429;
  normals[5]=-5;

  vertices[6]=-117.16*Multiply;        // Punkt 2
  vertices[7]=63.5;
  vertices[8]=3.829;
  normals[6]=-1;
  normals[7]=-1.371;
  normals[8]=5;

  vertices[9]=-123.8*Multiply;        // Punkt 3
  vertices[10]=68.5;
  vertices[11]=5;
  normals[9]=-1;
  normals[10]=3.829;
  normals[11]=5;
 
  vertices[12]=-6.5*Multiply;       // Punkt 4
  vertices[13]=68.5;
  vertices[14]=0;
  normals[12]=1;
  normals[13]=-3.429;
  normals[14]=-5;

  vertices[15]=-7.38*Multiply;       // Punkt 5
  vertices[16]=63.5;
  vertices[17]=3.429;
  normals[15]=1;
  normals[16]=-3.429;
  normals[17]=-5;

  vertices[18]=-7.38*Multiply;       // Punkt 6
  vertices[19]=63.5;
  vertices[20]=3.829;
  normals[18]=1;
  normals[19]=-1.372;
  normals[20]=5;

  vertices[21]=-6.5*Multiply;       // Punkt 7
  vertices[22]=68.5;
  vertices[23]=5;
  normals[21]=1;
  normals[22]=3.829;
  normals[23]=5;

  if (Multiply == 1){
  indices[0]=0;
  indices[1]=4; 
  indices[2]=5;
  indices[3]=1;

  indices[4]=1;
  indices[5]=5; 
  indices[6]=6;
  indices[7]=2;
  
  indices[8]=2;
  indices[9]=6; 
  indices[10]=7;
  indices[11]=3;
  
  indices[12]=0;
  indices[13]=3;
  indices[14]=7;
  indices[15]=4;
  
  indices[16]=0;
  indices[17]=1;
  indices[18]=2;
  indices[19]=3;
  
  indices[20]=4;
  indices[21]=7;
  indices[22]=6;
  indices[23]=5;
  }

  if (Multiply == -1) {

  indices[0]=4;
  indices[1]=0;
  indices[2]=1;
  indices[3]=5;

  indices[4]=5;
  indices[5]=1; 
  indices[6]=2;
  indices[7]=6;

  indices[8]=6;
  indices[9]=2; 
  indices[10]=3;
  indices[11]=7;
  
  indices[12]=4;
  indices[13]=7; 
  indices[14]=3;
  indices[15]=0;

  indices[16]=4;
  indices[17]=5;
  indices[18]=6;
  indices[19]=7;
 
  indices[20]=1;
  indices[21]=0;
  indices[22]=3;
  indices[23]=2;
  }
  }

 glEnableClientState(GL_VERTEX_ARRAY);
 glEnableClientState(GL_NORMAL_ARRAY);
   
 glNormalPointer(GL_FLOAT, 0, normals);
 glVertexPointer(3, GL_FLOAT, 0, vertices);

 glDrawElements(GL_QUADS, 16+8 , GL_UNSIGNED_INT,indices);

 glDisableClientState(GL_VERTEX_ARRAY);
 glDisableClientState(GL_NORMAL_ARRAY);

 free(vertices);
 free(normals);
 free(indices);
}


void MittelLochRand() {
  
  GLfloat vertices[]={6.3,70.8,4.8,
		      6.2,72.7,4.7,
		      5.5,75,4.55,
		      4.1,76.6,4.3,
		      2.3,77.7,4.2,
		      0,78,4.05,
		      -2.3,77.7,4.1,
		      -4.1,76.6,4.2,
		      -5.5,75,4.55,
		      -6.2,72.7,4.7,
		      -6.3,70.8,4.8,
		      6.3,70.8,5.2,
		      6.2,72.7,5.1,
		      5.5,75,4.95,
		      4.1,76.6,4.7,
		      2.3,77.7,4.5,
		      0,78,4.45,
		      -2.3,77.7,4.5,
		      -4.1,76.6,4.6,
		      -5.5,75,4.95,
		      -6.2,72.7,5.1,
		      -6.3,70.8,5.2,
		      5.8,70.7,5.2,
		      5.3,72.8,5.1,
		      4.6,74.7,4.95,
		      3.3,75.7,4.7,
		      1.7,76.4,4.5,
		      0,76.5,4.45,
		      -1.7,76.4,4.5,
		      -3.3,75.7,4.7,
		      -4.6,74.7,4.95,
		      -5.3,72.8,5.1,
		      -5.8,70.7,5.2,
		      5.8,70.7,4.8,
		      5.3,72.8,4.7,
		      4.6,74.7,4.55,
		      3.3,75.7,4.3,
		      1.7,76.4,4.1,
		      0,76.5,4.05,
		      -1.7,76.4,4.1,
		      -3.3,75.7,4.3,
		      -4.6,74.7,4.55,
		      -5.3,72.8,4.7,
		      -5.8,70.7,4.8};


  GLfloat normals[]={
                     1,.1,-3,
		     1,0,-3,
		     .8,.6,-3,
		     .7,.7,-3,
		     .4,.9,-3,
		     0,1,-3,
		     -.4,.9,-3,
		     -.7,.7,-3,
		     -.8,.6,-3,
		     -1,0,-3,
		     -1,.1,-3,
                     1,.1,3,
		     1,0,3,
		     .8,.6,3,
		     .7,.7,3,
		     .4,.9,3,
		     0,1,3,
		     -.4,.9,3,
		     -.7,.7,3,
		     -.8,.6,3,
		     -1,0,3,
		     -1,.1,3,
                     -1,-.1,3,
		     -1,0,3,
		     -.8,-.6,3,
		     -.7,-.7,3,
		     -.4,-.9,3,
		     0,-1,3,
		     .4,-.9,3,
		     .7,-.7,3,
		     .8,-.6,3,
		     1,0,3,
		     1,-.1,3,
                     -1,-.1,-3,
		     -1,0,-3,
		     -.8,-.6,-3,
		     -.7,-.7,-3,
		     -.4,-.9,-3,
		     0,-1,-3,
		     .4,-.9,-3,
		     .7,-.7,-3,
		     .8,-.6,-3,
		     1,0,-3,
		     1,-.1,-3};

  GLint indices[]={0,1,12,11,
		   1,2,13,12,
		   2,3,14,13,
		   3,4,15,14,
		   4,5,16,15,
		   5,6,17,16,
		   6,7,18,17,
		   7,8,19,18,
		   8,9,20,19,
		   9,10,21,20,

		   11,12,23,22,
		   12,13,24,23,
		   13,14,25,24,
		   14,15,26,25,
		   15,16,27,26,
		   16,17,28,27,
		   17,18,29,28,
		   18,19,30,29,
		   19,20,31,30,
		   20,21,32,31,

		   22,23,34,33,
		   23,24,35,34,
		   24,25,36,35,
		   25,26,37,36,
		   26,27,38,37,
		   27,28,39,38,
		   28,29,40,39,
		   29,30,41,40,
		   30,31,42,41,
		   31,32,43,42,
		   0,11,22,33,
		   10,43,32,21};

  GLfloat mat_ambient[]={.1,.1,.1,1.0};
  GLfloat mat_diffuse[]={.3,.3,.3,1};
  GLfloat mat_specular[]={1.0,1.0,1.0,1.0};
  GLfloat mat_shininess = 127.0;

  glMaterialfv(GL_FRONT, GL_AMBIENT,mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,mat_specular);
  glMaterialf(GL_FRONT, GL_SHININESS,mat_shininess);


  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);

  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glNormalPointer(GL_FLOAT, 0, normals);

  glDrawElements(GL_QUADS,4*32, GL_UNSIGNED_INT,indices);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);

}

void EckLochRand() {
  
  GLfloat vertices[]={2.5,-5.9,4.8,
		      5,-3.5,4.7,
		      6.1,0,4.7,
		      5.8,2.3,4.7,
		      4.4,4.4,4.7,
		      2.3,5.8,4.7,
		      0,6.1,4.7,
		      -3.5,5,4.7,
		      -5.9,2.5,4.8,

		      2.5,-5.9,5.2,
		      5,-3.5,5.1,
		      6.1,0,5.1,
		      5.8,2.3,5.1,
		      4.4,4.4,5.1,
		      2.3,5.8,5.1,
		      0,6.1,5.1,
		      -3.5,5,5.1,
		      -5.9,2.5,5.2,

		      2.1,-5.5,5.2,
		      4.4,-3.1,5.1,
		      5,0,5.1,
		      4.4,1.8,5.1,
		      3.3,3.3,5.1,
		      1.8,4.4,5.1,
		      0,5,5.1,
		      -3.1,4.4,5.1,
		      -5.5,2.1,5.2,

		      2.1,-5.5,4.8,
		      4.4,-3.1,4.7,
		      5,0,4.7,
		      4.4,1.8,4.7,
		      3.3,3.3,4.7,
		      1.8,4.4,4.7,
		      0,5,4.7,
		      -3.1,4.4,4.7,
		      -5.5,2.1,4.8};


  GLfloat normals[]={.7,-.7,-3,
		     .8,-.5,-3,
		     1,0,-3,
		     .9,.4,-3,
		     .7,.7,-3,
		     .9,.4,-3,
		     1,0,-3,
		     .8,-.5,-3,
		     .7,-.7,-3,
		     
		     .7,-.7,3,
		     .8,-.5,3,
		     1,0,3,
		     .9,.4,3,
		     .7,.7,3,
		     .9,.4,3,
		     1,0,3,
		     .8,-.5,3,
		     .7,-.7,3,

		     -.7,.7,3,
		     -.8,.5,3,
		     -1,0,3,
		     -.9,-.4,3,
		     -.7,-.7,3,
		     -.9,-.4,3,
		     -1,0,3,
		     -.8,.5,3,
		     -.7,.7,3,
		     
		     -.7,.7,-3,
		     -.8,.5,-3,
		     -1,0,-3,
		     -.9,-.4,-3,
		     -.7,-.7,-3,
		     -.9,-.4,-3,
		     -1,0,-3,
		     -.8,.5,-3,
		     -.7,.7,-3};

  GLint indices[]={0,1,10,9,
		   1,2,11,10,
		   2,3,12,11,
		   3,4,13,12,
		   4,5,14,13,
		   5,6,15,14,
		   6,7,16,15,
		   7,8,17,16,

		   9,10,19,18,
		   10,11,20,19,
		   11,12,21,20,
		   12,13,22,21,
		   13,14,23,22,
		   14,15,24,23,
		   15,16,25,24,
		   16,17,26,25,

		   18,19,28,27,
		   19,20,29,28,
		   20,21,30,29,
		   21,22,31,30,
		   22,23,32,31,
		   23,24,33,32,
		   24,25,34,33,
		   25,26,35,34,

		   0,9,18,27,
		   35,26,17,8};



  GLfloat mat_ambient[]={.1,.1,.1,1.0};
  GLfloat mat_diffuse[]={.3,.3,.3,1};
  GLfloat mat_specular[]={1.0,1.0,1.0,1.0};
  GLfloat mat_shininess = 127.0;

  glMaterialfv(GL_FRONT, GL_AMBIENT,mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,mat_specular);
  glMaterialf(GL_FRONT, GL_SHININESS,mat_shininess);


  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);

  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glNormalPointer(GL_FLOAT, 0, normals);

  glDrawElements(GL_QUADS,4*26, GL_UNSIGNED_INT,indices);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);

}

void Diamant(GLfloat x, GLfloat y, GLfloat z) {
  glBegin(GL_QUADS);
  glNormal3f(0,0,1);
  glVertex3f(x+0.0,y+0.5,z);
  glVertex3f(x-0.5,y+0.0,z);
  glVertex3f(x+0.0,y-0.5,z);
  glVertex3f(x+0.5,y+0.0,z);
  glNormal3f(-0.235,0.235,0.94);
  glVertex3f(x+0.0,y+0.5,z-0.0);
  glVertex3f(x+0.0,y+1.5,z-0.3);
  glVertex3f(x-1.5,y+0.0,z-0.3);
  glVertex3f(x-0.5,y+0.0,z-0.0);
  glNormal3f(-0.235,-0.235,0.94);
  glVertex3f(x-0.5,y+0.0,z-0.0);
  glVertex3f(x-1.5,y+0.0,z-0.3);
  glVertex3f(x-0.0,y-1.5,z-0.3);
  glVertex3f(x-0.0,y-0.5,z-0.0);
  glNormal3f(0.235,-0.235,0.94);
  glVertex3f(x+0.0,y-0.5,z-0.0);
  glVertex3f(x+0.0,y-1.5,z-0.3);
  glVertex3f(x+1.5,y+0.0,z-0.3);
  glVertex3f(x+0.5,y+0.0,z-0.0);
  glNormal3f(0.235,0.235,0.94);
  glVertex3f(x+0.5,y+0.0,z-0.0);
  glVertex3f(x+1.5,y+0.0,z-0.3);
  glVertex3f(x-0.0,y+1.5,z-0.3);
  glVertex3f(x-0.0,y+0.5,z-0.0);
  glEnd();

}
