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

int mod = 1000000007;

ll nCk(int n, int k, ll* factos, ll* invs){
    ll temp;
    
    if (n < k){
        return 0;
    }
    
    temp = factos[n] * invs[k] % mod;
    temp = temp * invs[n - k] % mod;

    return temp;
}

int n, r;
ll result;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> r;

    int max_num = n;

    ll factos[max_num + 1];
    factos[0] = 1;
    ll invs[max_num + 1];

    ll cur = 1;
    for (int i=1;i<max_num + 1;i++){
        cur *= i;
        cur %= mod;
        factos[i] = cur;
    }

    invs[max_num] = fast_pow(factos[max_num], mod - 2, mod);
    for (int i=max_num - 1;i>-1;i-=1){
        invs[i] = (i + 1) * (invs[i + 1]) % mod;
    }

    result = nCk(n, r, factos, invs);

    cout << result << "\n";
}