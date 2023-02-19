#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll inf = 100000 * 200;

int n, m;
int a, b;
ll c;
ll G[200][200];

vector<vector<ll>> floyd(int n)
{
  vector<vector<ll>> dists;
  vector<ll> temp_vec;
  ll temp;

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      temp = G[i][j];
      temp_vec.push_back(temp);
    }
    dists.push_back(temp_vec);
    vector<ll>().swap(temp_vec);
  }

  for (int i = 0; i < n; i++)
  {
    dists[i][i] = 0;
  }

  for (int mid = 0; mid < n; mid++)
  {
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
      {
        dists[i][j] = min(dists[i][j], dists[i][mid] + dists[mid][j]);
      }
    }
  }

  return dists;
}

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> n;
  cin >> m;

  for (int i = 0; i < n; i++)
  {
    fill(G[i], G[i] + sizeof(G[i]), inf);
  }

  for (int i = 0; i < m; i++)
  {
    cin >> a >> b >> c;
    a -= 1;
    b -= 1;

    G[a][b] = min(G[a][b], c);
  }

  vector<vector<ll>> r_dists;

  r_dists = floyd(n);

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if (r_dists[i][j] == inf)
      {
        r_dists[i][j] = 0;
      }

      cout << r_dists[i][j] << " ";
    }
    cout << "\n";
  }
}