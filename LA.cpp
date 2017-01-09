/* FILE LA.C */
// Routines for C++ classes of float Vectors and matrices,


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "LA.h"

/**********************************************************************/
//                 VECTOR CLASS:
/**********************************************************************/


FVector::FVector(long new_nl, long new_nh)
{
  default_FVector();
  if (new_nh>=new_nl) alloc_FVector(new_nl,new_nh);
}

FVector::FVector(const FVector &w)
{
  long i;

  default_FVector();
  if (!w.allocated()) return; 
  alloc_FVector(w.nl,w.nh);

  for (i=nl;i<=nh;i++)
	v[i]=w.v[i]; 
}

void FVector::default_FVector()
{
  v=NULL;
  nh=0;
  nl=0;
}

void FVector::alloc_FVector(long new_nl, long new_nh)
{
  if (allocated()) {
#ifndef _WIN32
    printf("Error in FVector::alloc: v!=NULL.\n");
#endif
    exit(-1);
  }
  
  nl = new_nl;
  nh = new_nh;

  // Numerical Recipes allocation routine (nrutil.c).
  v=(float *)malloc((size_t) ((nh-nl+1)*sizeof(float)));
  if (!v) {
#ifndef _WIN32
    printf("allocation failure in vector()");
#endif
    exit(0);
  }
  v += (-nl); // v[nl] points to element 0 now.
}  

void FVector::free_FVector()
{  
  if (!allocated()) {
#ifndef _WIN32
    printf("Error in FVector::free_FVector: not allocated.\n");
#endif
    exit(-1);
  }

  // Numerical Recipes routine (nrutil.c).
  free((char*) (v+nl));

  default_FVector();
}

FVector::~FVector()
{
  if (allocated()) 
	free_FVector(); 
}


/**********************************************************************/

void FVector::copy_from(const FVector &source)
{
  long i;
  for (i=nl;i<=nh;i++)
    v[i]=source.v[i]; 
}



void FVector::set_const(float c)
{
  long i;
   for (i=nl;i<=nh;i++)
     v[i] = c;
}






/**********************************************************************/
//                 MATRIX CLASS:
/**********************************************************************/



FMatrix::FMatrix(long new_nrl, long new_nrh,long new_ncl, long new_nch)
{
  default_FMatrix();
  if (new_nrh >= new_nrl && new_nch >= new_ncl) 
    alloc_FMatrix(new_nrl,new_nrh,new_ncl,new_nch);
}

FMatrix::FMatrix(const FMatrix &w)
{
  long i,j;

  default_FMatrix();
  if (!w.allocated()) return; 
  alloc_FMatrix(w.nrl,w.nrh,w.ncl,w.nch);

  for (i=nrl;i<=nrh;i++)
	for (j=ncl;j<=nch;j++)
	  m[i][j]=w.m[i][j]; 
}

void FMatrix::default_FMatrix()
{
  m=NULL;
  nrh=0;
  nrl=0;
  nch=0;
  ncl=0;
}

void FMatrix::alloc_FMatrix(long new_nrl, long new_nrh,
						  long new_ncl, long new_nch)
{
  long i, nrow,ncol;

  if (allocated()) {
#ifndef _WIN32
    printf("Error in FMatrix::alloc: v!=NULL.\n");
#endif
    exit(-1);
  }

  nrl = new_nrl;
  nrh = new_nrh;
  ncl = new_ncl;
  nch = new_nch;
  nrow=nrh-nrl+1;
  ncol=nch-ncl+1;
  // Numerical Recipes allocation routine (nrutil.c).

  /* allocate pointers to rows */
  m=(float **) malloc((size_t)((nrow)*sizeof(float*)));
  if (!m) {
#ifndef _WIN32
    printf("allocation failure 1 in matrix()");
#endif
    exit(0);
  }
  m -= nrl;
  
  /* allocate rows and set pointers to them */
  m[nrl]=(float *) malloc((size_t)((nrow*ncol)*sizeof(float)));
  if (!m[nrl])  {
#ifndef _WIN32
    printf("allocation failure 2 in matrix()");
#endif
    exit(0);
  }
  m[nrl] -= ncl;
  
  for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;
}  

void FMatrix::free_FMatrix()
{  
  if (!allocated()) {
#ifndef _WIN32
    printf("Error in FMatrix::free_FMatrix: not allocated.\n");
#endif
    exit(-1);
  }

  // Numerical Recipes routine (nrutil.c).
  free((char *) (m[nrl]+ncl));
  free((char *) (m+nrl));

  default_FMatrix();
}

FMatrix::~FMatrix()
{
  if (allocated()) 
	free_FMatrix(); 
}

/*********************************************************************/


void FMatrix::copy_from(const FMatrix &source)
{
  long i,j;

  if (nrl!=source.nrl || nrh!=source.nrh || ncl!=source.ncl || nch!=source.nch) {
#ifndef _WIN32
    printf("Error in  FMatrix::copy_from: Wrong dimensions.\n");
#endif
    exit(-1);
  }

  for (i=nrl;i<=nrh;i++)
	for (j=ncl;j<=nch;j++)
	  m[i][j]=source.m[i][j]; 
}




void FMatrix::set_const(float c)
{
  long i,j;
  
  for (i=nrl;i<=nrh;i++)
	for (j=ncl;j<=nch;j++)
	  m[i][j]=c;
}

