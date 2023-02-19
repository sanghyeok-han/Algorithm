#include <bits/stdc++.h>
using namespace std;

int main(){
    string s;
    cin >> s;

    int cs[26];

    fill(cs, cs + 26, 0);

    for(auto v: s){
        cs[v - 'a'] += 1;
    }

    for(auto v: cs){
        cout << v << " ";
    }
}