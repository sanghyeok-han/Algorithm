#include <bits/stdc++.h>
using namespace std;

int n;
string s1, s2, s3, s4, s5, s6, s7, s8, s9;

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> n;

  s1 = " @@@   @@@  ";
  s2 = "@   @ @   @ ";
  s3 = "@    @    @ ";
  s4 = "@         @ ";
  s5 = " @       @  ";
  s6 = "  @     @   ";
  s7 = "   @   @    ";
  s8 = "    @ @     ";
  s9 = "     @      ";

  for (int i = 0; i < n; i++)
  {
    cout << s1 << "\n"
         << s2 << "\n"
         << s3 << "\n"
         << s4 << "\n"
         << s5 << "\n"
         << s6 << "\n"
         << s7 << "\n"
         << s8 << "\n"
         << s9 << "\n";
  }
}