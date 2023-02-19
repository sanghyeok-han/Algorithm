#include <bits/stdc++.h>
using namespace std;

int t = 0;
string s;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> t;
    getline(cin, s);
    for (int tn=0;tn<t;tn++){
        getline(cin, s);

        if (s[s.size() - 1] == '.'){
            cout << s << "\n";
        }
        else {
            cout << s << '.' << "\n";
        }
    }
}