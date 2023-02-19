#include <bits/stdc++.h>
using namespace std;

string s;
int total;
int ca;
char cur;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> s;
    total = ca = 0;
    cur = 'A' - 1;
    for (auto v: s){
        if (v != cur && v != cur + 1){
            ca = 0;
            
            if (v == 'A'){
                ca = 1;
                cur = 'A';
            }
            else{
                cur = 'A' - 1;
            }
           
            continue;
        }

        if (v == 'A'){
            ca += 1;
        }
        else if (v == 'Z'){
            total += ca;
        }

        if (v == cur + 1){
            cur += 1;
        }
    }

    cout << total << "\n";
}