#include <bits/stdc++.h>
using namespace std;

tuple<vector<int>, vector<int>> linear_sieve(int max_num){
  int sp[max_num + 1] = {0,};
  vector<int> vec_sp;
  vector<int> primes;
  int j;

  for (int i=2;i<max_num + 1;i++){
    if (sp[i] == 0){
      sp[i] = i;
      primes.push_back(i);
    }

    j = 0;
    while (j < primes.size() && i * primes[j] <= max_num && primes[j] <= sp[i]){
      sp[i * primes[j]] = primes[j];
      j += 1;
    }
  }

  for (int i=0;i<max_num + 1;i++){
    vec_sp.push_back(sp[i]);
  }

  return make_tuple(primes, vec_sp);
}

vector<int> get_factors(const vector<int>& sp, int n){
    vector<int> r;
    while (n > 1){
        r.push_back(sp[n]);
        n /= sp[n];
    }

    return r;
}

tuple<vector<int>, vector<int>> temp_tp;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    vector<int> primes;
    vector<int> sp;
    temp_tp = linear_sieve(5000005);

    primes = get<0>(temp_tp);
    sp = get<1>(temp_tp);

    int n, v;
    cin >> n;

    vector<int> result;

    for (int i=0;i<n;i++){
        cin >> v;

        result = get_factors(sp, v);

        for (auto f: result){
            cout << f << " ";
        }
        cout << "\n";
    }
}