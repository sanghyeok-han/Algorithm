#include <bits/stdc++.h>
using namespace std;

int n, m, root;
int u, v;

vector<int> G[1001];
bool vt[1001];
vector<int> r_dfs;
vector<int> r_bfs;

void dfs(int value)
{
  r_dfs.push_back(value);
  vt[value] = true;

  for (auto v : G[value])
  {
    if (!vt[v])
    {
      dfs(v);
    }
  }
}

void bfs(int start)
{
  queue<int> que;
  int value;

  que.push(start);
  vt[start] = true;

  while (!que.empty())
  {
    value = que.front();
    r_bfs.push_back(value);
    que.pop();

    for (auto v : G[value])
    {
      if (!vt[v])
      {
        vt[v] = true;
        que.push(v);
      }
    }
  }
}

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> n >> m >> root;

  for (int i = 0; i < m; i++)
  {
    cin >> u >> v;

    G[u].push_back(v);
    G[v].push_back(u);
  }

  for (int i = 1; i < n + 1; i++)
  {
    sort(G[i].begin(), G[i].end());
  }

  fill(vt, vt + sizeof(vt), false);
  dfs(root);
  fill(vt, vt + sizeof(vt), false);
  bfs(root);

  for (auto value : r_dfs)
  {
    cout << value << " ";
  }
  cout << "\n";

  for (auto value : r_bfs)
  {
    cout << value << " ";
  }
  cout << "\n";
}