#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n, m;
vector<int> pa;
vector<int> rk;

int find(int v){
    if (v != pa[v]){
        pa[v] = find(pa[v]);
    }
    return pa[v];
}

void uni(int a, int b){
    if (rk[a] < rk[b]){
        swap(a, b);
    }

    pa[b] = a;
    if (rk[a] == rk[b]){
        rk[a] += 1;
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    for (int i=0;i<n + 1;i++){
        pa.push_back(i);
        rk.push_back(0);
    }

    int u, v, ru, rv;
    for (int i=0;i<m;i++){
        cin >> u >> v;

        ru = find(u);
        rv = find(v);

        if (ru != rv){
            uni(ru, rv);
        }
    }

    int lec[n] = {0,};
    int temp;
    for (int i=0;i<n;i++){
        cin >> temp;
        lec[i] = temp;
    }

    int total = 0;
    for (int i=1;i<n;i++){
        if (find(lec[i - 1]) != find(lec[i])){
            total += 1;
        }
    }

    cout << total << "\n";
}