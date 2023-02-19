#include <bits/stdc++.h>
using namespace std;
#define INF 5000000
#define max_num 200050
typedef long long ll;

// globals
int t;
int n, c0;
int cs[max_num];
int temp;

vector<int> G[max_num];
int u, v;

int mdfb[max_num]; // min dist from black
int cur_r;
int cv;

// functions
void bfs(int start){
    queue<int> q;
    q.push(start);

    mdfb[start] = 0;

    int ndist;
    while (!q.empty()){
        auto value = q.front();
        q.pop();

        ndist = mdfb[value] + 1;
        if (ndist < cur_r){
            for (auto v : G[value]){
                if (ndist < mdfb[v]){
                    mdfb[v] = ndist;
                    q.push(v);
                }
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> t;
    for (int tn=0;tn<t;tn++){
        cin >> n >> c0;
        for (int i=0;i<n - 1;i++){
            cin >> temp;
            cs[i] = temp;
        }

        fill(G, G + n + 2, vector<int>());
        for (int i=0;i<n - 1;i++){
            cin >> u >> v;

            G[u].push_back(v);
            G[v].push_back(u);
        }

        fill(mdfb, mdfb + n + 5, INF);

        cur_r = INF;
        bfs(c0);
        
        for (int ci=0;ci<n - 1;ci++){
            if (cur_r == 1){
                cout << cur_r << " ";
            }
            else{
                cv = cs[ci];
                
                cur_r = min(cur_r, mdfb[cv]);
                bfs(cv);

                cout << cur_r << " ";
            }
        }
        cout << "\n";
    }
}
