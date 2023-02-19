#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll inf = LLONG_MAX;

int mod = 1000000000;

int n;

ll derangement()
{
  vector<ll> dp = {1, 0, 1, 2};
  ll nv;

  for (int i = 4; i < n + 1; i++)
  {
    nv = (dp[i - 2] + dp[i - 1]) % mod * (i - 1) % mod;
    dp.push_back(nv);
  }

  return dp[n];
}

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> n;

  ll result;

  result = derangement();

  cout << result;
}
