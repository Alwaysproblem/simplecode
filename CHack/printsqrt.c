#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef char * string;

void printInt(int num, const string end) {
  printf("%d", num);
  printf("%s", end);
}

int main() 
{

    int n;
    int i,j;
    scanf("%d", &n);
  	
    for(i=0; i<= 2*n-1; i+=1){
        for(j=0; j< 2*n-1; j+=1){
            if(i <= n - 1){
                if(j < i) printInt(n - j, " ");
                else if (j >= i && j < 2*n - i - 1) printInt(n - i, " ");
                else if (j >= 2*n - i - 1) printInt(j + 2 - n, " ");
            }else if (i > n)
            {
                int t = 2 * n - i - 1;
                if(j < t) printInt(n - j, " ");
                else if (j >= t && j < 2*n - t - 1) printInt(n - t, " ");
                else if (j >= 2*n - t - 1) printInt(j + 2 - n, " ");
            }
        }
        if(i != n - 1) printf("\n");
    }
    return 0;
}

