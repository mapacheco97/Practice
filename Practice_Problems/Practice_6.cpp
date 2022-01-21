#include <stdio.h>
#include <cmath>
using namespace std;

void update(int *a,int *b) {
    // Complete this function 
    int pa = *a;
    int pb = *b;

    *a = pa + pb;

    int diff = pa - pb;
    *b = abs(diff);
}

int main() {
    int a, b;
    int *pa = &a, *pb = &b;
    
    scanf("%d %d", &a, &b);
    update(pa, pb);
    printf("%d\n%d", a, b);

    return 0;
}