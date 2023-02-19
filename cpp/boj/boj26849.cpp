#include <bits/stdc++.h>
using namespace std;

int n;
double a, b;
double min_v, max_v, sv;
vector<double> vec;

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);

  cout << fixed << setprecision(8);

  cin >> n;
  min_v = max_v = sv = 0;

  for (int i = 0; i < n; i++)
  {
    cin >> a >> b;
    sv += a / b;
    vec.push_back(a / b);
  }

  min_v = *min_element(vec.begin(), vec.end());
  max_v = *max_element(vec.begin(), vec.end());

  cout << min_v << " " << max_v << " " << sv;
}