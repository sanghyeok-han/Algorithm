#include <bits/stdc++.h>
using namespace std;

int t = 0;
int a1, p1, r1, p2;
double ratio1, ratio2;
double pi = 3.14159265359;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> t;

    for (int tn=0;tn<t;tn++){
        cin >> a1 >> p1;
        cin >> r1 >> p2;

        ratio1 = a1 / p1;
        ratio2 = pi * r1 * r1 / p2;

        if (ratio1 < ratio2){
            cout << "Whole pizza" << "\n";
        }
        else{
            cout << "Slice of pizza" << "\n";
        }
    }
}