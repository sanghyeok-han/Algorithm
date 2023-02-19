#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll inf = LLONG_MAX;

int n;
ll ct;

vector<ll> merge_sort(const vector<ll> &vec)
{
  if (vec.size() <= 1)
  {
    return vec;
  }

  vector<ll> left;
  vector<ll> right;
  vector<ll> nvec;
  int l_i, r_i;

  int n = vec.size();

  int mid = n / 2;

  for (int i = 0; i < mid; i++)
  {
    left.push_back(vec[i]);
  }

  for (int i = mid; i < n; i++)
  {
    right.push_back(vec[i]);
  }

  left = merge_sort(left);
  right = merge_sort(right);

  int nl = left.size();
  int nr = right.size();
  l_i = r_i = 0;
  while (true)
  {
    if (left[l_i] <= right[r_i])
    {
      nvec.push_back(left[l_i]);
      ct += r_i;
      l_i += 1;

      if (l_i == nl)
      {
        while (r_i < nr)
        {
          nvec.push_back(right[r_i]);
          r_i += 1;
        }
        break;
      }
    }
    else
    {
      nvec.push_back(right[r_i]);
      r_i += 1;

      if (r_i == nr)
      {
        while (l_i < nl)
        {
          nvec.push_back(left[l_i]);
          ct += r_i;
          l_i += 1;
        }
        break;
      }
    }
  }

  return nvec;
}

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);

  vector<ll> vec;
  ll v;

  cin >> n;
  for (int i = 0; i < n; i++)
  {
    cin >> v;

    vec.push_back(v);
  }

  merge_sort(vec);

  cout << ct << "\n";
}