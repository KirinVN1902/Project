#include <iostream>
using namespace std;
int minimumSearch(int a[], int l, int r){
    while(l < r){
        int m = (l + r) / 2;
        if(a[m] > a[r]){
            l = m + 1;
        }
        else{
            r = m;
        }
    }
    return a[r];
}
int main(){
    int a[100], n;
    cin >> n;
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    cout << minimumSearch(a, 0, n - 1);
    return 0;
}