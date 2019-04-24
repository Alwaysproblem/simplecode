#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

// int main(){
    
//     char s[100];
//     scanf("%[^\n]%*c", &s);
//     printf("Hello, World!\n");
//     printf("%s", s);
//     /* Enter your code here. Read input from STDIN. Print output to STDOUT
//         */
//     return 0;
// }

// int main() {

//     /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
//     int n;
//     scanf("%d", &n);
//     int *arr = (int *) malloc(n * sizeof(int));
//     for(int i = 0; i < n; i += 1){
//         scanf("%d%*c", &arr[i]);
//     }
//     int sum = 0;
//     for (int i = 0; i < n; i += 1) {
//         sum += arr[i];
//     }

//     free(arr);
//     return 0;
// }

// void swap(int *p, int * q){
//     int t = *p;
//     *p = *q;
//     *q = t;
// }


int main()
{
    int hash[26] = {};
    for(int i = 0; i< 26; i++){
        printf("%d", hash[i]);
    }
    // int num, *arr, i;
    // scanf("%d", &num);
    // arr = (int*) malloc(num * sizeof(int));
    // for(i = 0; i < num; i++) {
    //     scanf("%d", arr + i);
    // }

    // for (i = 0; i < num / 2 ; i += 1) {
    //     swap(&arr[i], &arr[num - i - 1]);
    // }

//     /* Write the logic to reverse the array. */

//     for(i = 0; i < num; i++)
//         printf("%d ", *(arr + i));
//     free(arr);
//     return 0;
}

// typedef char *  string;

// int lenstrarray(string * s){
//     int len = 0;
//     for(;s[len] != NULL; len++);
//     return len;
// }

// void split(string str, string *strtoken, const string sep) {
//   // automatic ignore the space
//   // int init_size = strlen(str);
//   string ptr = strtok(str, sep);
//   string *tmp = strtoken;

//   int len = 0;
//   while (ptr != NULL) {
//     *tmp = ptr;
//     ptr = strtok(NULL, sep);
//     tmp += 1;
//     len += 1;
//   }
//   *tmp = ptr;
// }

// int main() {
//     string *chop = (string *) malloc(sizeof(string) * 1024);
//     char *s;
//     s = malloc(1024 * sizeof(char));
//     scanf("%[^\n]", s);
//     s = realloc(s, strlen(s) + 1);
//     //Write your logic to print the tokens of the sentence here.
//     split(s, chop, " ");
//     int lens = lenstrarray(chop);
//     string *tmp = (string *)realloc(chop, sizeof(string) * (lens + 1));
//     if (tmp == NULL){
//         printf("fuck me");
//         return  0;
//     }
//     chop = tmp;
//     for(int len =0; len < lens; len++){
//         printf("%s\n", chop[len]);
//     }


//     return 0;
// }


// int main() {
//     int *count = (int *)calloc(10, sizeof(int));
//     char s[1000];
//     scanf("%[^\n]%*c", s);
//     for(int ind = 0; s[ind] != '\0'; ind++){
//         if(s[ind] >= '0' && s[ind] =< '9'){
//             count[s[ind] - '0'] += 1;
//         }
//     }

//     for(int i = 0; i<10; i += 1){
//         printf("%d ", count[i]);
//     }


//     free(count);
//     /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
//     return 0;
// }


/*
 * This stores the total number of books in each shelf.
 */
// int* total_number_of_books;

// /*
//  * This stores the total number of pages in each book of each shelf.
//  * The rows represent the shelves and the columns represent the books.
//  */
// int** total_number_of_pages;



// int main()
// {
//     int total_number_of_shelves;
//     scanf("%d", &total_number_of_shelves);
    
//     int total_number_of_queries;
//     scanf("%d", &total_number_of_queries);

//     total_number_of_books = (int *) calloc(total_number_of_shelves, sizeof(int));
//     total_number_of_pages = (int **) calloc(total_number_of_shelves, sizeof(int *));
//     for (int ind = 0; ind < total_number_of_shelves; ind += 1){
//         total_number_of_pages[ind] =
//             (int *)malloc(sizeof(int));
//     }

//       while (total_number_of_queries--) {
//         int type_of_query;
//         scanf("%d", &type_of_query);
        
//         if (type_of_query == 1) {
//             /*
//              * Process the query of first type here.
//              */
//             int x, y;
//             scanf("%d %d", &x, &y);
//             total_number_of_books[x] += 1;
//             int *p = 
//                 (int *)realloc(total_number_of_pages[x],
//                         total_number_of_books[x]);
//             if (p == NULL){
//                 printf("fuck");
//                 return -9;
//             }
//             total_number_of_pages[x] = p;
//             total_number_of_pages[x][total_number_of_books[x] - 1] = y;

//         } else if (type_of_query == 2) {
//             int x, y;
//             scanf("%d %d", &x, &y);
//             printf("%d\n", *(*(total_number_of_pages + x) + y));
//         } else {
//             int x;
//             scanf("%d", &x);
//             printf("%d\n", *(total_number_of_books + x));
//         }
//     }

//     if (total_number_of_books) {
//         free(total_number_of_books);
//     }
    
//     for (int i = 0; i < total_number_of_shelves; i++) {
//         if (*(total_number_of_pages + i)) {
//             free(*(total_number_of_pages + i));
//         }
//     }
    
//     if (total_number_of_pages) {
//         free(total_number_of_pages);
//     }
    
//     return 0;
// }

