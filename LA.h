
/* FILE LA.H */
// Routines for C++ classes of float Vectors and matrices,
// to be used in combination with Numerical Recipes subroutines.
// VB, 20.5.97

#ifndef __LA_H__
#define __LA_H__

#include <stdio.h>


class FVector {
public:
  FVector(long new_nl=1, long new_nh=0); // by default, do not allocate.
  FVector(const FVector &w);
  ~FVector();

  void default_FVector();
  void alloc_FVector(long new_nl, long new_nh);
  inline short allocated() const {return (v != NULL);}  
  void free_FVector();

  void copy_from(const FVector &source);         // v[i] = source[i].
  void set_const(float c);                       // all v[i] = c.

  float *v;        // Pointer to actual data.
  long nl;         // lowest index.
  long nh;         // highest index.
} ;



class FMatrix {
public:
  // by default, do not allocate.
  FMatrix(long new_nrl=1, long new_nrh=0,long new_ncl=1, long new_nch=0);
  FMatrix(const FMatrix &w);
  ~FMatrix();

  void default_FMatrix();
  void alloc_FMatrix(long new_nrl, long new_nrh,long new_ncl, long new_nch);
  inline short allocated() const {return (m != NULL);}  
  void free_FMatrix();

  void copy_from(const FMatrix &source); // M = source
  void set_const(float c);

  inline int width()  const {return (nch-ncl+1);}  
  inline int height() const {return (nrh-nrl+1);}  

  float **m;         // Pointer to actual data.  m[row][col].
  long nrl;         // lowest  row index.
  long nrh;         // highest row index.
  long ncl;         // lowest  column index.
  long nch;         // highest column index.
} ;


/**********************************************************************/

#endif /* !__LA_H__ */

