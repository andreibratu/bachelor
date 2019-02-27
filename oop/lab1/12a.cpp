// Lab2 - Problem 12a

#include <iostream>
#include <assert.h>

using namespace std;

int gcd(int a, int b) {
    if (b==0) return a;
    a = (a>=b) ? a:b;
    else return gcd(b, a%b);
}

int main()
{
    int n;
    cin>>n;
    assert (n>0);
    cout<<n;
    for (int i=1; i<n; i++) {
        if(gcd(n, i) == 1) {
            cout<<i<<' ';
        }
    }

    return 0;
}
