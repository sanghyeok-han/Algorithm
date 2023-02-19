#include <bits/stdc++.h>
using namespace std;

string s;
int cb, cc, r;

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> s;

  cb = cc = 0;
  for (auto v : s)
  {
    if (v == 'B')
    {
      cb += 1;
    }
    else
    {
      cc += 1;
    }
  }

  r = cb / 2 + cc / 2;

  cout << r << "\n";
}