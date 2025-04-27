#include <iostream>
using namespace std;
int linearSearch(int a[], int n, int k){
    for (int i = 0; i < n; i++){
        if (a[i] == k){
            return i;
        }
    }
    return -1;
}
int main(){
    int a[100], n, k;
    cin >> n; 
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    cin >> k;
    cout << linearSearch(a, n, k);
    return 0;
}