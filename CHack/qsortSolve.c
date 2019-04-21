#include <stdlib.h>

// /* Comparison function. Receives two generic (void) pointers to the items under comparison. */
// int compare_ints(const void *p, const void *q) {
//     int x = *(const int *)p;
//     int y = *(const int *)q;

//     /* Avoid return x - y, which can cause undefined behaviour
//        because of signed integer overflow. */
//     if (x < y)
//         return -1;  // Return -1 if you want ascending, 1 if you want descending order. 
//     else if (x > y)
//         return 1;   // Return 1 if you want ascending, -1 if you want descending order. 

//     return 0;
// }

// /* Sort an array of n integers, pointed to by a. */
// void sort_ints(int *a, size_t n) {
//     qsort(a, n, sizeof *a, &compare_ints);
// }

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct triangle
{
	int a;
	int b;
	int c;
};

typedef struct triangle triangle;

float S(triangle tr){
    double p = (tr.a + tr.b + tr.c) / 2.0;
    return sqrt(p * (p - tr.a) * (p - tr.b) * (p- tr.c));
}

/* Comparison function. Receives two generic (void) pointers to the items under comparison. */
int key(const void *p, const void *q) {
    triangle x = *(triangle *)p;
    triangle y = *(triangle *)q;

    /* Avoid return x - y, which can cause undefined behaviour
       because of signed integer overflow. */
    if (S(x) < S(y))
        return -1;  // Return -1 if you want ascending, 1 if you want descending order. 
    else if (S(x) > S(y))
        return 1;   // Return 1 if you want ascending, -1 if you want descending order. 

    return 0;
}

void sort_by_area(triangle* tr, int n) {
    qsort(tr, n, sizeof(*tr), &key);
}

int main()
{
	int n;
	scanf("%d", &n);
	triangle *tr = malloc(n * sizeof(triangle));
	for (int i = 0; i < n; i++) {
		scanf("%d%d%d", &tr[i].a, &tr[i].b, &tr[i].c);
	}
	sort_by_area(tr, n);
	for (int i = 0; i < n; i++) {
		printf("%d %d %d\n", tr[i].a, tr[i].b, tr[i].c);
	}
	return 0;
}
