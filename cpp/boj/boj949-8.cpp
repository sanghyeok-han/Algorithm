#include <bits/stdc++.h>
using namespace std;
#define max_num 1000

typedef long long ll;
ll inf = LLONG_MAX;

int n;
vector<int> arr[max_num];
int B[max_num][3];

int dp[max_num][3];
bool vt[max_num];

int max_r;
int colors[max_num];

void dfs(int value)
{
    vt[value] = true;

    int som_01, som_02, som_12;
    som_01 = som_02 = som_12 = 0; // sum of maxes
    for (auto v : arr[value])
    {
        if (vt[v])
        {
            continue;
        }

        dfs(v);

        som_01 += max(dp[v][0], dp[v][1]);
        som_02 += max(dp[v][0], dp[v][2]);
        som_12 += max(dp[v][1], dp[v][2]);
    }

    dp[value][0] = B[value][0] + som_12;
    dp[value][1] = B[value][1] + som_02;
    dp[value][2] = B[value][2] + som_01;
}

void dfs2(int value, int fcolor)
{
    vt[value] = true;

    int max_v = 0;
    int max_v_color = -1;
    for (int color = 0; color < 3; color++)
    {
        if (color == fcolor)
        {
            continue;
        }
        if (dp[value][color] > max_v)
        {
            max_v = dp[value][color];
            max_v_color = color;
        }
    }

    colors[value] = max_v_color;
    for (auto v : arr[value])
    {
        if (vt[v])
        {
            continue;
        }

        dfs2(v, max_v_color);
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    int u, v;
    for (int i = 0; i < n - 1; i++)
    {
        cin >> u >> v;
        arr[u].push_back(v);
        arr[v].push_back(u);
    }

    int temp;
    for (int i = 1; i < n + 1; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cin >> temp;
            B[i][j] = temp;
        }
    }

    dfs(1);

    max_r = *max_element(dp[1], dp[1] + 3);
    fill(vt, vt + max_num, false);
    dfs2(1, -1);

    cout << max_r << "\n";

    for (int i = 1; i < n + 1; i++)
    {
        if (colors[i] == 0)
        {
            cout << "R";
        }
        else if (colors[i] == 1)
        {
            cout << "G";
        }
        else
        {
            cout << "B";
        }
    }
}