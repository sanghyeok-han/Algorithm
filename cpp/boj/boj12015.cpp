#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll inf = LLONG_MAX;

int n;
vector<ll> vec;

int lis()
{
  int result = 0;
  int index;

  vector<ll> nvec;
  nvec.push_back(vec[0]);

  for (int i = 1; i < n; i++)
  {
    index = lower_bound(nvec.begin(), nvec.end(), vec[i]) - nvec.begin();

    if (index == nvec.size())
    {
      nvec.push_back(vec[i]);
    }
    else
    {
      nvec[index] = vec[i];
    }
  }

  result = nvec.size();

  return result;
}

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);

  ll temp;
  ll result;

  cin >> n;
  for (int i = 0; i < n; i++)
  {
    cin >> temp;
    vec.push_back(temp);
  }

  result = lis();

  cout << result << "\n";
}