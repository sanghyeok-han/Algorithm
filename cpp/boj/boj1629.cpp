#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

//https://www.rookieslab.com/posts/fast-power-algorithm-exponentiation-by-squaring-cpp-python-implementation
ll fast_pow(ll base, ll power, int MOD) {
    ll result = 1;
    while(power > 0) {

        if(power & 1) {
            result = (result * base) % MOD;
        }
        base = (base * base) % MOD;
        power >>= 1;
    }
    return result;
}

int a, b, c;
ll r;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> a >> b >> c;

    r = fast_pow(a, b, c);

    cout << r;
}