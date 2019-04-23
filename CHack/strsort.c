#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lexicographic_sort(const void *a, const void *b) {
  const char *aa = *(const char **)a;
  const char *bb = *(const char **)b;
  return strcmp(aa, bb);
}

int lexicographic_sort_reverse(const void *a, const void *b) {
  const char *aa = *(const char **)a;
  const char *bb = *(const char **)b;
  return strcmp(bb, aa);
}

int sort_by_number_of_distinct_characters(const void *a, const void *b) {
  const char *aa = *(const char **)a;
  const char *bb = *(const char **)b;
  char hashaa[26];
  char hashbb[26];
  for (int ia = 0; aa[ia] != '\0'; ia += 1) {
    hashaa[aa[ia] - 'a'] = 1;
  }
  for (int ib = 0; bb[ib] != '\0'; ib += 1) {
    hashbb[bb[ib] - 'a'] = 1;
  }
  int lena = 0;
  int lenb = 0;
  for (int i = 0; i < 26; i++) {
    if (hashaa[i] != 0)
      lena += 1;
    if (hashbb[i] != 0)
      lenb += 1;
  }
  if (lena == lenb) {
    return strcmp(aa, bb);
  } else
      return (lena - lenb);
}

int sort_by_length(const void *a, const void *b) {
  const char *aa = *(const char **)a;
  const char *bb = *(const char **)b;
  if (strlen(aa) == strlen(bb)){
      return strcmp(aa, bb);
  }else 
    return (strlen(aa) - strlen(bb));
}

void string_sort(char **arr, const int len,
                 int (*cmp_func)(const void *a, const void *b)) {
  qsort(arr, len, sizeof(char *), cmp_func);
}

int main() 
{
    int n;
    scanf("%d", &n);
  
    char** arr;
	arr = (char**)malloc(n * sizeof(char*));
  
    for(int i = 0; i < n; i++){
        *(arr + i) = malloc(1024 * sizeof(char));
        scanf("%s", *(arr + i));
        *(arr + i) = realloc(*(arr + i), strlen(*(arr + i)) + 1);
    }

    printf("\n");
    string_sort(arr, n, lexicographic_sort);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);
    printf("\n");

    string_sort(arr, n, lexicographic_sort_reverse);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]); 
    printf("\n");

    string_sort(arr, n, sort_by_length);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);    
    printf("\n");

    string_sort(arr, n, sort_by_number_of_distinct_characters);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]); 
    printf("\n");
}