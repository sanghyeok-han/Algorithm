#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<int> get_factos(int num){
    vector<int> r;
    for (int mod=2;mod<int(pow(num, 0.5)) + 1;mod++){
        while (num % mod == 0){
            num /= mod;
            r.push_back(mod);
        }
    }

    if (num != 1){
        r.push_back(num);
    }

    return r;
}

int n;
vector<int> r;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    r = get_factos(n);

    for (auto v: r){
        cout << v << "\n";
    }
}