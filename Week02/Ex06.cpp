#include <iostream>
using namespace std;
int checkEqual(int a[], int n, int target){
    int l = 0, r = n - 1;
    while(l < r){
        if(a[l] + a[r] == target){
            return 1;
        }
        else if(a[l] + a[r] > target){
            r--;
        }
        else{
            l++;
        }
    }
    return 0;
}
int main(){
    int a[100], n;
    cin >> n;
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    int target; cin >> target;
    int res = checkEqual(a, n, target);
    if(res == 1){
        cout << "YES" << endl;
    }
    else{
        cout << "NO" << endl;
    }
    return 0;
}