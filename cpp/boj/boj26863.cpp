#include <bits/stdc++.h>
using namespace std;

vector<int> vec;
int v;
int pad;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    for (int i=0;i<4;i++){
        cin >> v;

        vec.push_back(v);
    }

    cin >> pad;

    sort(vec.begin(), vec.end());

    if ((vec[0] == vec[1] && vec[1] == vec[2] && vec[2] == vec[3]) || (vec[0] + pad == vec[1] && vec[1] == vec[2] && vec[2] == vec[3])){
        cout << 1 << "\n";
    }
    else{
        cout << 0 << "\n";
    }
}