// Lab2 - Problem 12a

#include <stdio.h>
#include <assert.h>

int gcd(int a, int b) {
    if (b==0) return a;
    a = (a>=b) ? a:b;
    return gcd(b, a%b);
}

int first(int* result)
{
    printf("Please input n:\n");
    int n;
    scanf("%d", &n);
    assert (n>0);
    int i;
    printf("Numbers relative prime with n and smaller:\n");
    int idx = 0;
    for (i = 1;i<n; i++) {
        if(gcd(n, i) == 1) {
            result[idx++] = i;
        }
    }
    return idx;
}
