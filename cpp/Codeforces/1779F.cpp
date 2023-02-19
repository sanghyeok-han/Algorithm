#include <bits/stdc++.h>
#define max_num 200010
using namespace std;

// basics
typedef long long ll;
ll inf = LLONG_MAX;

// globals
int n;
int a[max_num];
vector<int> G[max_num];
int av, pv;
int c_num, p_num;

int dp[max_num][32];
vector<vector<int>> info;
int temp;

int nxt_num = 1;

int sub_sizes[max_num];

// {a, b}, {0, to_zero}, {0, 0}

// functions
void dfs(int value)
{
    int size = 1;
    int num = a[value];

    if (G[value].empty())
    {
        dp[value][num] = nxt_num;
        info.push_back({0, 0});
        nxt_num += 1;
        sub_sizes[value] = 1;

        return;
    }

    int cur[32] = {0,};
    int nxt[32] = {0,};

    cur[0] = nxt_num;
    info.push_back({0, 0});
    nxt_num += 1;

    for (auto v : G[value])
    {
        dfs(v);

        // cout << value << " " << v << "\n";
        // for (int i=0;i<32;i++){
        //     cout << cur[i] << " ";
        // }
        // cout << "\n";

        // for (int i=0;i<32;i++){
        //     cout << dp[v][i] << " ";
        // }
        // cout << "\n";    

        for (int av = 0; av < 32; av++)
        {
            if (cur[av] == 0)
            {
                continue;
            }
            for (int bv = 0; bv < 32; bv++)
            {
                if (dp[v][bv] == 0)
                {
                    continue;
                }
                temp = av ^ bv;

                if (nxt[temp] == 0)
                {
                    nxt[temp] = nxt_num;
                    info.push_back({cur[av], dp[v][bv]});
                    nxt_num += 1;
                }
            }
        }

        for (int i = 0; i < 32; i++)
        {
            cur[i] = nxt[i];
            nxt[i] = 0;
        }
        size += sub_sizes[v];
    }

    for (int i=0;i<32;i++){
        if (cur[i] != 0){
            temp = num ^ i;
            dp[value][temp] = cur[i];
        }
    }

    sub_sizes[value] = size;

    if (sub_sizes[value] % 2 == 0 && dp[value][0] == 0)
    {
        dp[value][0] = nxt_num;
        info.push_back({0, value});
        nxt_num += 1;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> av;
        a[i + 1] = av;
    }

    for (int i = 0; i < n - 1; i++)
    {
        c_num = i + 2;
        cin >> p_num;

        G[p_num].push_back(c_num);
    }

    if (n % 2 == 0)
    {
        cout << 2 << "\n";
        cout << 1 << " " << 1 << "\n";
    }
    else
    {
        info.push_back({0, 0});

        dfs(1);

        // for (int i = 1; i <= n; i++)
        // {
        //     cout << i << " ";
        //     for (auto c : G[i])
        //     {
        //         cout << c << " ";
        //     }

        //     cout << "\n";
        // }

        // for (int i = 1; i < n + 1; i++)
        // {
        //     cout << i << "\n";
        //     for (int j = 0; j < 32; j++)
        //     {
        //         cout << dp[i][j] << " ";
        //     }

        //     cout << "\n";
        // }

        // for (int i=0;i<info.size();i++)
        // {
        //     cout << i << "\n";
        //     for (auto v : info[i])
        //     {
        //         cout << v << " ";
        //     }
        //     cout << "\n";
        // }
        // cout << "\n";

        if (dp[1][0] == 0)
        {
            cout << -1 << "\n";
        }
        else
        {
            vector<int> result;
            queue<int> que;
            int value;

            que.push(dp[1][0]);

            while (!que.empty())
            {
                value = que.front();
                que.pop();

                // cout << value << "\n";
                // for (auto vv: info[value]){
                //     cout << vv << " " ;
                // }
                // cout << "\n\n";

                if (info[value][0] == 0 && info[value][1] != 0)
                {
                    result.push_back(info[value][1]);
                    result.push_back(info[value][1]);
                }
                else if (info[value][0] != 0)
                {
                    que.push(info[value][0]);
                    que.push(info[value][1]);
                }
            }

            cout << result.size() + 1 << "\n";
            for (int i = result.size() - 1; i >= 0; i--)
            {
                cout << result[i] << " ";
            }
            cout << 1 << " ";
        }
    }
}