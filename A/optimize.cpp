#include<bits/stdc++.h>
using namespace std;


#define maratona std::ios_base::sync_with_stdio(false);
#define muito std::cout.tie(NULL);
#define coxa std::cin.tie(NULL);
#define MAX 5012


int main(){
    maratona muito coxa
    int i, n, k; cin >> n >> k;
    multiset<int> files;
    vector<int> disks(k);
    int ans = 0;
    for(i = 0; i < n; i++) { 
        int a; cin >> a;
        files.insert(a);
    }

    for (i = 0; i < k; i++){
        int a; cin >> a;
        disks[i] = a;
    } 
    for(i = disks.size()-1; i >=0; i--){
        if(*files.begin() > disks[i]) break;
        auto it = files.lower_bound(disks[i]); 
        cout << "disk: " << disks[i] << '\n';
        if(*it > disks[i]) it--;
        ans += *it;
        cout << "*it: " << *it << '\n';
        files.erase(*it);
    }    
    cout << ans << '\n';
    return 0;
}
