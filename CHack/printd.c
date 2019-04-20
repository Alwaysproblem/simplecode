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

typedef char *  string;

// we define the char *seg[N] like:
// the seg[N-1] need to be set NULL.

void printChar(char c, const string end)
{
    fflush(stdout);
    putchar(c);
    printf("%s", end);
}

void printStr(string var, const string end)
{
    fflush(stdout);
    printf("%s", var);
    printf("%s", end);
}

void printInt(int num, const string end)
{
    fflush(stdout);
    printf("%d", num);
    printf("%s", end);
}

void printF(double num, const string end)
{
    fflush(stdout);
    printf("%.*f", DEFAULT_DIGITS, num);
    printf("%s", end);
}

#define print(X, sep) do{                   \
    _Generic((X),                           \
    char: printChar,                        \
    int: printInt,                          \
    float: printF,                          \
    string : printStr)(X, sep);             \
    }while(0)

int Int(string str)
{
    return strtol(str, NULL, 10);
}

double Float(string str)
{
    return strtof(str, NULL);
}

void float2str(string dest, double number){
    sprintf(dest, "%*f", DEFAULT_DIGITS, number);
}

void Int2str(string dest, int number){
    sprintf(dest, "%d", number);
}

#define str(dest, number) do{               \
    _Generic((number),                      \
    int: Int2str,                           \
    float: float2str)(dest, number);        \
    }while(0)


double roundF(double number, int ndigits){
    double pow10 = pow(10, (double) ndigits);
    double tmp = number * pow10;
    tmp = round(tmp);
    return tmp / pow10;
}

void split(string str, string *strtoken, const string sep)
{
    // automatic ignore the space
    // int init_size = strlen(str);
    string ptr = strtok(str, sep);
    string *tmp = strtoken;

    int len = 0;
    while (ptr != NULL)
    {
        *tmp = ptr;
        ptr = strtok(NULL, sep);
        tmp += 1;
        len += 1;
    }
    *tmp = ptr;
}

void join(string  sep, string  dest, string  str1, string  str2)
{
    sprintf(dest, "%s%s", str1, sep);
    sprintf(dest, "%s%s", dest, str2);
}

void strjoin(string  sep, string dest, string * s){
    int i = 0;
    strcpy(dest, s[0]);
    for(i = 1; s[i] != NULL; i++){
        join(sep, dest, dest, s[i]);
    }
}

void input(string InputBuffer)
{
    scanf("%[^\n]%*c", InputBuffer);
}


// void printF(double num, int ndigits, const string end)
// {
//     fflush(stdout);
//     printf("%.*f", ndigits, num);
//     printf("%s", end);
// }




int main()
{
    int a = 0;
    int b = 0;
    float x = 0.0;
    float y = 0.0;
    char InputBuffer[INPUTBUFFER];
    string Seg[SEGM];
    input(InputBuffer);
    split(InputBuffer, Seg, " ");
    a = Int(Seg[0]);
    b = Int(Seg[1]);
    input(InputBuffer);
    split(InputBuffer, Seg, " ");
    x = Float(Seg[0]);
    y = Float(Seg[1]);

    print(a + b, " ");
    print(a - b, "\n");
    print(x + y, " ");
    print(x - y, " ");

    return 0;
}
