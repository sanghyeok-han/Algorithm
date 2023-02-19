#include <bits/stdc++.h>
using namespace std;

int n;
int nn, max_v, max_v_num;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    max_v = max_v_num = -1;

    nn = n;
    for (int i=0;i<8;i++){
        if (200 <= nn && nn <= 209){
            nn += 1;
        }
    }

    if (nn >= max_v){
        max_v = nn;
        max_v_num = 1;
    }

    nn = n;
    for (int i=0;i<4;i++){
        if (200 <= nn && nn <= 219){
            nn += 1;
        }
    }

    if (nn >= max_v){
        max_v = nn;
        max_v_num = 2;
    }  

    nn = n;
    for (int i=0;i<2;i++){
        if (200 <= nn && nn <= 229){
            nn += 1;
        }
    }

    if (nn >= max_v){
        max_v = nn;
        max_v_num = 3;
    }  

    nn = n;
    for (int i=0;i<1;i++){
        if (200 <= nn && nn <= 239){
            nn += 1;
        }
    }

    if (nn >= max_v){
        max_v = nn;
        max_v_num = 4;
    }  

    cout << max_v_num;
}