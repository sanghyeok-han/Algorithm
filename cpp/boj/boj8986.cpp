#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll inf = LLONG_MAX;

int n;
vector<ll> vec;
ll temp;

ll result;

ll get_value(ll mid)
{
  ll cur, sv;
  cur = sv = 0;

  for (int i = 1; i < n; i++)
  {
    cur += mid;
    sv += abs(vec[i] - cur);
  }

  return sv;
}

ll termary_search(ll start, ll end)
{
  ll result = inf;
  ll mid1, mid2, t1, t2, mid;

  while (start <= end)
  {
    mid1 = (start * 2 + end) / 3;
    mid2 = (start + end * 2) / 3;

    t1 = get_value(mid1);
    t2 = get_value(mid2);

    result = min(result, t1);
    result = min(result, t2);

    if (end - start <= 5)
    {
      for (ll mid = start; mid < end + 1; mid++)
      {
        result = min(result, get_value(mid));
      }
      break;
    }

    if (t1 >= t2)
    {
      start = mid1;
    }
    else
    {
      end = mid2;
    }
  }

  return result;
}

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> n;
  for (int i = 0; i < n; i++)
  {
    cin >> temp;
    vec.push_back(temp);
  }

  result = termary_search(1, 1000000000);

  cout << result << "\n";
}