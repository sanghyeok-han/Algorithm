#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    string s;
    cin >> s;

    int cs[26];

    fill(cs, cs + 26, 0);

    for(auto v: s){
        cs[v - 'A'] = 1;
    }

    char result;
    for(int i=0;i<26;i++){
        if(cs[i] == 0){
            result = char(i + 65);
        }
    }

    cout << result;
}