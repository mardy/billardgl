/*GLint Zeit() {
  struct timeval tp;
  gettimeofday(&tp,NULL);               
  return ((tp.tv_sec%10000)*100+(tp.tv_usec/10000));
}*/

#include <GL/glut.h>
#include "Zeit.h"

GLint Zeit() {
  return glutGet(GLUT_ELAPSED_TIME)/10;
}
