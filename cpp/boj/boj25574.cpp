#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll inf = LLONG_MAX;

int t;

int n, a, b, c;
ll v;

ll cumul;

vector<int> cur;
ll max_r;
int s, e;
ll sv, nsv;
int fi;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> t;
    for (int tn = 0; tn < t; tn++)
    {
        vector<ll> vec;

        cin >> n >> a >> b >> c;
        for (int i = 0; i < n; i++)
        {
            cin >> v;
            vec.push_back(v);
        }

        vector<ll> prefix;

        prefix.push_back(0);
        cumul = 0;
        for (int i = 0; i < n; i++)
        {
            cumul += vec[i];
            prefix.push_back(cumul);
        }

        cur = {a, b, c};
        sort(cur.begin(), cur.end());

        max_r = -inf;
        do
        {
            vector<vector<vector<ll>>> dp;

            dp.push_back({{inf, inf, inf, inf}, {inf, inf, inf, inf}, {inf, inf, inf, inf}});

            for (int i = 0; i < n; i++)
            {
                if (i >= 1)
                {
                    dp.push_back(dp[i - 1]);
                }

                if (i + 1 - cur[0] >= 0)
                {
                    s = i - cur[0] + 1;
                    e = i;

                    sv = prefix[e + 1] - prefix[s];

                    if (sv >= 0)
                    {
                        if (dp[i][0][0] == inf)
                        {
                            dp[i][0][0] = sv;
                        }
                        else
                        {
                            dp[i][0][0] = max(dp[i][0][0], sv);
                        }

                        if (dp[i][0][1] == inf)
                        {
                            dp[i][0][1] = sv;
                        }
                        else
                        {
                            dp[i][0][1] = min(dp[i][0][1], sv);
                        }
                    }
                    else
                    {
                        if (dp[i][0][2] == inf)
                        {
                            dp[i][0][2] = sv;
                        }
                        else
                        {
                            dp[i][0][2] = min(dp[i][0][2], sv);
                        }

                        if (dp[i][0][3] == inf)
                        {
                            dp[i][0][3] = sv;
                        }
                        else
                        {
                            dp[i][0][3] = max(dp[i][0][3], sv);
                        }
                    }
                }

                for (int cur_i = 1; cur_i < 3; cur_i++)
                {
                    if (i - cur[cur_i] >= 0)
                    {
                        s = i - cur[cur_i] + 1;
                        e = i;

                        sv = prefix[e + 1] - prefix[s];
                        fi = i - cur[cur_i];

                        vector<ll> nsvs;
                        for (int j = 0; j < 4; j++)
                        {
                            if (dp[fi][cur_i - 1][j] != inf)
                            {
                                nsvs.push_back(dp[fi][cur_i - 1][j] * sv);
                            }
                        }

                        for (auto nsv : nsvs)
                        {
                            if (nsv >= 0)
                            {
                                if (dp[i][cur_i][0] == inf)
                                {
                                    dp[i][cur_i][0] = nsv;
                                }
                                else
                                {
                                    dp[i][cur_i][0] = max(dp[i][cur_i][0], nsv);
                                }

                                if (dp[i][cur_i][1] == inf)
                                {
                                    dp[i][cur_i][1] = nsv;
                                }
                                else
                                {
                                    dp[i][cur_i][1] = min(dp[i][cur_i][1], nsv);
                                }
                            }
                            else
                            {
                                if (dp[i][cur_i][2] == inf)
                                {
                                    dp[i][cur_i][2] = nsv;
                                }
                                else
                                {
                                    dp[i][cur_i][2] = min(dp[i][cur_i][2], nsv);
                                }
                                if (dp[i][cur_i][3] == inf)
                                {
                                    dp[i][cur_i][3] = nsv;
                                }
                                else
                                {
                                    dp[i][cur_i][3] = max(dp[i][cur_i][3], nsv);
                                }
                            }
                        }
                    }
                }
            }

            for (int j = 0; j < 4; j++)
            {
                if (dp[n - 1][2][j] != inf)
                {
                    max_r = max(max_r, dp[n - 1][2][j]);
                }
            }
        } while (next_permutation(cur.begin(), cur.end()));

        cout << max_r << "\n";
    }
}
