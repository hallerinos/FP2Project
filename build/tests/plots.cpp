#include <stdio.h>
#include <math.h>
 
#define PI 3.14159
 
int main()
{ 
  int i,j;
  for(j=0; j<5; j++) {
    for(i=0; i<20; i++) {
      printf("%f\t",sinf(i * PI / 10.0 + j*PI/10));
    }
    printf("\n");
  }
 
  return 0;
}
