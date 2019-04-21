#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
//Complete the following function.
#define INPUTBUFFER 256
#define MAXSEG 255
#define SEGM (MAXSEG - 1)
#define DEFAULT_DIGITS 2

#define type(var, TYPE) (__builtin_types_compatible_p(typeof(var), TYPE))
#define len(array, element) (sizeof(array) / sizeof(element))

typedef char *string;

// we define the char *seg[N] like:
// the seg[N-1] need to be set NULL.

void printChar(char c, const string end) {
  fflush(stdout);
  putchar(c);
  printf("%s", end);
}

void printStr(string var, const string end) {
  fflush(stdout);
  printf("%s", var);
  printf("%s", end);
}

void printInt(int num, const string end) {
  fflush(stdout);
  printf("%d", num);
  printf("%s", end);
}

void printF(double num, const string end) {
  fflush(stdout);
  printf("%.*f", DEFAULT_DIGITS, num);
  printf("%s", end);
}

#define print(X, sep)                                                          \
  do {                                                                         \
    _Generic((X), char                                                         \
             : printChar, int                                                  \
             : printInt, float                                                 \
             : printF, string                                                  \
             : printStr)(X, sep);                                              \
  } while (0)


void calculate_the_maximum(int n, int k) {
  //Write your code here.
  int a = 1;
  int b = 1;
  int max_and = 0;
  int max_or = 0;
  int max_xor = 0;
  int tmp = 0;

  for(; a < n; a++){
      for (b = a + 1; b <= n; b++){
            tmp = a & b;
            if (tmp > max_and && tmp < k){
                max_and = tmp;
            }
            tmp = a | b;
            if (tmp > max_or && tmp < k) {
                max_or = tmp;
            }
            tmp = a ^ b;
            if (tmp > max_xor && tmp < k) {
                max_xor = tmp;
            }
      }
  }
  print(max_and, "\n");
  print(max_or, "\n");
  print(max_xor, "\n");
  
}

int main() {
    int n, k;
  
    scanf("%d %d", &n, &k);
    calculate_the_maximum(n, k);
 
    return 0;
}
