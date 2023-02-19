#include <bits/stdc++.h>
using namespace std;

int main(){
    string s;
    cin >> s;

    int ca, cb;
    ca = cb = 0;

    for (auto v: s){
        if (v == 'A'){
            ca += 1;
        }
        else{
            cb += 1;
        }
    }

    cout << ca << " : " << cb;
}