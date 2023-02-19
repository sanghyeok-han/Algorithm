#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll all_num = pow(2, 31) - 1;
int t;
int n;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> t;
    for (int tn=0;tn<t;tn++){
        cin >> n;
        ll arr[n] = {0,};
        ll temp;

        for (int i=0;i<n;i++){
            cin >> temp;
            arr[i] = temp;
        }

        vector<pair<ll, ll>> vec;

        for (int i=0;i<n;i++){
            vec.push_back({arr[i], i});
        }

        vector<ll> result;
        for (int c=0;c<31;c++){
            sort(vec.begin(), vec.end());

            auto [used_v, used_i] = vec[vec.size() - 1];
            result.push_back(used_i);

            // cout << used_v << " " << used_i << "\n";

            vec.pop_back();

            if (vec.empty()){
                break;
            }

            ll to_and = all_num - used_v;
            for (int i=0;i<vec.size();i++){
                vec[i].first &= to_and;
            }
        }

        set<ll> result_st;

        for (auto v: result){
            result_st.insert(v);
        }

        for (int i=0;i<n;i++){
            if (result_st.find(i) == result_st.end()){
                result.push_back(i);
            }
        }

        // for (int i=0;i<n;i++){
        //     cout << arr[i] << " " << result[i] << "\n";
        // }

        for (auto v: result){
            cout << arr[v] << " ";
        }
        cout << "\n";
    }
}
