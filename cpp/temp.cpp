#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll inf = LLONG_MAX;

int n, k;

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);

  int t;
  cin >> t;
  for (int tn=0;tn<t;tn++){
    cin >> n >> k;
    ll li[n] = {0,};
    ll colds[k] = {0,};
    ll hots[k] = {0,};

    ll temp = 0;
    for (int i=0;i<n;i++){
      cin >> temp;
      li[i] = temp - 1;
    }

    for (int i=0;i<k;i++){
      cin >> temp;
      colds[i] = temp;
    }  

    for (int i=0;i<k;i++){
      cin >> temp;
      hots[i] = temp;
    }  

    ll dp[n + 1][n + 1] = {0,};

    for (int i=0;i<n + 1;i++){
      for (int j=0;j<n + 1;j++){
        dp[i][j] = inf;
      }
    }

      dp[0][1] = colds[li[0]];
      dp[1][0] = colds[li[0]];
      for (int i=1;i<n;i++){
        temp = -1;
        if (li[i - 1] == li[i]){
            temp = dp[0][i] + hots[li[i]];
        }
        else{
            temp = dp[0][i] + colds[li[i]];
        }

        dp[0][i + 1] = temp;
        dp[i + 1][0] = temp;
      }
  
      for (int i=0;i<n;i++){
          for (int j=0;j<n;i++){
              if (i == j){
                  continue;
              }

              int nxt = i;
              if (j > nxt){
                nxt = j;
              }
              nxt += 1;
  
              ll to_add = -1;
              if (i - 1 >= 0 && li[i - 1] == li[nxt - 1]){
                  to_add = hots[li[nxt - 1]];
              }
              else{
                  to_add = colds[li[nxt - 1]];
              }
  
              dp[nxt][j] = min(dp[nxt][j], dp[i][j] + to_add);
  
              to_add = -1;
              if (j - 1 >= 0 && li[j - 1] == li[nxt - 1]){
                  to_add = hots[li[nxt - 1]];
              }
              else{
                  to_add = colds[li[nxt - 1]];
              }
  
              if (dp[i][j] + to_add < dp[i][nxt]){
                dp[i][nxt] = dp[i][j] + to_add;
              }
          }
      }
  
      ll min_r = inf;
      for (int j=0;j<n + 1;j++){
        if (dp[n][j] < min_r){
          min_r = dp[n][j];
        }
      }
  
      for (int i=0;i<n + 1;i++){
        if (dp[i][n] < min_r){
          min_r = dp[i][n];
        }
      }
  
      cout << min_r << "\n";
  }
}