#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll nCk(int n, int k){
    ll num, denom;
    num = denom = 1;

    if (n - k < k){
        k = n - k;
    }

    for (int i=n;i>n-k;i-=1){
        num *= i;
    }

    for (int i=2;i<k + 1;i++){
        denom *= i;
    }

    return num / denom;
}

int n, m;
ll r;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    r = nCk(n, m);

    cout << r;
}