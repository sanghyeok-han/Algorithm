#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll inf = LLONG_MAX;

ll x_1, y_1, x_2, y_2, x_3, y_3;

int ccw(ll x_1, ll y_1, ll x_2, ll y_2, ll x_3, ll y_3)
{
  ll temp;

  temp = x_1 * y_2 + x_2 * y_3 + x_3 * y_1 - x_2 * y_1 - x_3 * y_2 - x_1 * y_3;

  if (temp < 0)
  {
    return -1;
  }
  else if (temp > 0)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> x_1 >> y_1 >> x_2 >> y_2 >> x_3 >> y_3;

  ll result;

  result = ccw(x_1, y_1, x_2, y_2, x_3, y_3);

  cout << result << "\n";
}