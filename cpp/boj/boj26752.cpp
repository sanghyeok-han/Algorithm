#include <bits/stdc++.h>
using namespace std;

int h, m, s;

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> h >> m >> s;

  s += 1;

  if (s == 60)
  {
    s = 0;
    m += 1;
  }

  if (m == 60)
  {
    m = 0;
    h += 1;
  }

  if (h == 24)
  {
    h = 0;
  }

  cout << setfill('0') << setw(2) << h;
  cout << ":";
  cout << setfill('0') << setw(2) << m;
  cout << ":";
  cout << setfill('0') << setw(2) << s;
  cout << "\n";
}