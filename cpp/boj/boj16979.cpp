// tle
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// globals
int n, m;
int r;
int node, s, e;
int qs, qe;
vector<int> vec;
vector<vector<int>> seg;

int sz;

vector<vector<int>> qu;
int result[100001];

// functions
vector<int> constuct(int node, int s, int e, vector<int>& vec){
    if (s == e){
        seg[node] = vec;
        return vec;
    }

    int mid = (s + e) / 2;

    int left_len = mid - s + 1;
    int right_len = e - s + 1 - left_len;

    vector<int> left;
    vector<int> right;

    for (int i=0;i<vec.size();i++){
        if (i < left_len){
            left.push_back(vec[i]);
        }
        else{
            right.push_back(vec[i]);
        }
    }

    left = constuct(node * 2, s, mid, left);
    right = constuct(node * 2 + 1, mid + 1, e, right);

    vector<int> nvec;

    int left_i = 0;
    int right_i = 0;

    while (left_i < left_len && right_i < right_len){
        if (left[left_i] < right[right_i]){
            nvec.push_back(left[left_i]);
            left_i += 1;
        }
        else{
            nvec.push_back(right[right_i]);
            right_i += 1;
        }
    }

    while (left_i < left_len){
        nvec.push_back(left[left_i]);
        left_i += 1;
    }
    while (right_i < right_len){
        nvec.push_back(right[right_i]);
        right_i += 1;
    }

    seg[node] = nvec;

    return nvec;
}

int query_larger(int node, int s, int e, int qnum){
    if (qe < s || e < qs){
        return 0;
    }
    else if (qs <= s && s <= e && e <= qe){
        int index = lower_bound(seg[node].begin(), seg[node].end(), qnum + 1) - seg[node].begin();

        return e - s + 1 - index;
    }
    else{
        int mid = (s + e) / 2;

        int t1 = query_larger(node * 2, s, mid, qnum);
        int t2 = query_larger(node * 2 + 1, mid + 1, e, qnum);

        return t1 + t2;
    }
}

int query_smaller(int node, int s, int e, int qnum){
    if (qe < s || e < qs){
        return 0;
    }
    else if (qs <= s && s <= e && e <= qe){
        int index = lower_bound(seg[node].begin(), seg[node].end(), qnum) - seg[node].begin();

        return index;
    }
    else{
        int mid = (s + e) / 2;

        int t1 = query_smaller(node * 2, s, mid, qnum);
        int t2 = query_smaller(node * 2 + 1, mid + 1, e, qnum);

        return t1 + t2;
    }
}

void add(int cur_i, int is_right){
    int v = vec[cur_i];
    int qnum;

    if (!is_right){
        qnum = v;
        if (qs <= qe){
            r += query_smaller(1, 0, n - 1, qnum);
            // cout << "11 " << r << "\n";
        }
    }
    else{
        qnum = v;
        if (qs <= qe){
            r += query_larger(1, 0, n - 1, qnum);
            // cout << "22 " << r << "\n";
        }
    }
}

void sub(int cur_i, int is_right){
    int v = vec[cur_i];
    int qnum;

    if (!is_right){
        qnum = v;
        if (qs <= qe){
            r -= query_smaller(1, 0, n - 1, qnum);
            // cout << "33 " << r << "\n";
        }
    }
    else{
        qnum = v;
        if (qs <= qe){
            r -= query_larger(1, 0, n - 1, qnum);
            // cout << "44 " << r << "\n";
        }
    }
}

bool cust_compare(vector<int> &a, vector<int> &b)
{
  int a1, b1, a2, b2;

  a1 = a[0] / sz;
  b1 = b[0] / sz;

  a2 = a[1];
  b2 = b[1];

  if (a1 < b1)
  {
    return true;
  }
  else if (a1 > b1)
  {
    return false;
  }

  if (a2 < b2)
  {
    return true;
  }
  else
  {
    return false;
  }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    int temp;
    for (int i=0;i<n;i++){
        cin >> temp;
        vec.push_back(temp);
    }

    unordered_map<int, int> ch;

    vector<int> sorted_vec = vec;
    sort(sorted_vec.begin(), sorted_vec.end());

    vector<int> to_ori;
    int v;
    int fv = -1;
    int nxt = 0;
    for (int i=0;i<n;i++){
        v = sorted_vec[i];
        if (fv != v){
            to_ori.push_back(v);
            fv = v;
            ch[v] = nxt;
            nxt += 1;
        }
    }

    for (int i=0;i<n;i++){
        vec[i] = ch[vec[i]];
    }

    sz = pow(2, ceil(log2(n)) + 1) + 1; 
    for (int i=0;i<sz;i++){
        seg.push_back(vector<int>());
    }

    constuct(1, 0, n - 1, vec);

    int a, b;
    for (int qi; qi < m; qi++)
  {
    cin >> a >> b;

    qu.push_back({a - 1, b - 1, qi});
  }

  sort(qu.begin(), qu.end(), cust_compare);

  int s = qu[0][0];
  int e = qu[0][1];
  int o_qi = qu[0][2];
  for (int i = s; i < e + 1; i++)
  {
    qs = s;
    qe = i - 1;
    add(i, 1);
  }

  result[o_qi] = r;

  int fs = s;
  int fe = e;
  for (int qi = 1; qi < m; qi++)
  {
    s = qu[qi][0];
    e = qu[qi][1];
    o_qi = qu[qi][2];

    if (fe < e)
    {
      for (int i = fe + 1; i < e + 1; i++)
      {
        qs = s;
        qe = i - 1;
        add(i, 1);
      }
    }

    if (fs > s)
    {
      for (int i = fs - 1; i > s - 1; i--)
      {
        qs = i + 1;
        qe = fe;
        add(i, 0);
      }
    }

    if (fe > e)
    {
      for (int i = fe; i > e; i--)
      {
        qs = s;
        qe = i - 1;
        sub(i, 1);
      }
    }

    if (fs < s)
    {
      for (int i = fs; i < s; i++)
      {
        qs = i + 1;
        qe = fe;
        sub(i, 0);
      }
    }

    result[o_qi] = r;

    fs = s;
    fe = e;
  }

  for (int i = 0; i < m; i++)
  {
    cout << result[i] << "\n";
  }
}
