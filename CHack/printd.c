#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define INPUTBUFFER 256
#define MAXSEG 255
#define SEGM (MAXSEG - 2)
#define DEFAULT_DIGITS 2

#define type(var, TYPE) (__builtin_types_compatible_p(typeof(var), TYPE))
#define len(array, element) (sizeof(array) / sizeof(element))


int Int(char *str)
{
    return strtol(str, NULL, 10);
}

double Float(char *str)
{
    return strtof(str, NULL);
}

double roundF(double number, int ndigits){
    double pow10 = pow(10, (double) ndigits);
    double tmp = number * pow10;
    tmp = round(tmp);
    return tmp / pow10;
}

void split(char *str, char **strtoken, const char *sep)
{
    // automatic ignore the space
    // int init_size = strlen(str);
    char *ptr = strtok(str, sep);
    char **tmp = strtoken;

    char len = 0;
    while (ptr != NULL)
    {
        *tmp = ptr;
        ptr = strtok(NULL, sep);
        tmp += 1;
        len += 1;
    }
    *tmp = NULL;
    **(tmp + 1) = len;
}

void join(char * sep, char * dest, char * str1, char * str2)
{
    sprintf(dest, "%s%s", str1, sep);
    sprintf(dest, "%s%s", dest, str2);
}

void strjoin(char * sep, char *dest, char ** string){
    
}

void input(char *InputBuffer)
{
    scanf("%[^\n]%*c", InputBuffer);
}

void printChar(char c, const char *end)
{
    fflush(stdout);
    putchar(c);
    printf("%s", end);
}

void printStr(char *var, const char *end)
{
    fflush(stdout);
    printf("%s", var);
    printf("%s", end);
}

void printInt(int num, const char *end)
{
    fflush(stdout);
    printf("%d", num);
    printf("%s", end);
}

// void printF(double num, int ndigits, const char *end)
// {
//     fflush(stdout);
//     printf("%.*f", ndigits, num);
//     printf("%s", end);
// }
void printF(double num, const char *end)
{
    fflush(stdout);
    printf("%.*f", DEFAULT_DIGITS, num);
    printf("%s", end);
}

#define print(X, sep) _Generic((X),         \
    char: printChar,                        \
    int: printInt,                          \
    float: printF,                          \
    char *: printStr)(X, sep)



int main()
{

    // char Input[INPUTBUFFER];
    // char* Seg[SEGM];
    // char output[INPUTBUFFER];
    // // double array[SEGM];

    // // int i = 0;
    // // int tmp;
    // input(Input);
    // // // printStr(str, "");
    // split(Input, Seg, " ");

    // // join("-", output, Seg[0], Seg[1]);

    // // printStr(output, "\n");
    // int i = len(Seg, char *);
    // printInt(i, "\n");
    // // for (i = 0; Seg[i] != NULL; i++)
    // // {
    // //     // double(Seg[i]);
    // //     array[i] = Float(Seg[i]);
    // // }

    // // int len = *Seg[i + 1];
    // // printInt(len, "\n");

    // // for (i = 0; i < len; i++)
    // // {
    // //     printF(roundF(array[i], 2), 2, "\n");
    // // }

    // char seg[SEGM] = stradd(23, 3);
    // printStr(seg, "\n");
    // typeof(i) k = 3;
    // printInt(k, "\n");
    // if(type("123", char *)) {
    //     printf("doubleVar is of type double!");
    // }
    print(234, "\n");
}
