// calculate the mid-day time given sunrise time and sunset time

#include <stdio.h>
#include <stdlib.h>

char * halfday(char* sunrise, char* sunset);

int main()
{
    char sunrise[] = "06:00";
    char sunset[] = "18:12";
    printf("please input sunrise time:\n");
    scanf("%s", sunrise);
    printf("please input sunset time:\n");
    scanf("%s", sunset);
    char *a = halfday(sunrise, sunset);
    printf("%s", a);
    free(a);
    return 0;
}

char * halfday(char* sunrise, char* sunset){
    int hour, min;
    int sunR = 0;
    int sunS = 0;
    int half = 0;
    char *ans = malloc(sizeof(char)*6);
    sscanf(sunrise, "%d:%d",&hour, &min);
    sunR = hour * 60 + min;
    sscanf(sunset, "%d:%d",&hour, &min);
    sunS = hour * 60 + min;
    half = (sunS+sunR+1)/2;
    // sprintf(ans, "%2d:%2d", int(half/60), int(half%60));
    sprintf(ans, "%02d:%02d", half/60, half%60);
    return ans;
}
