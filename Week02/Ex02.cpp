#include <iostream>
using namespace std;
int linearSearchWithSentinel(int a[], int n, int k){
    int last = a[n - 1];
    a[n - 1] = k;
    int i = 0;
    for (; i < n; i++){
        if(a[i] == k){
            break;
        }
    }
    a[n - 1] = last;
    if(i < n - 1 || last == k){
        return i;
    }
    return -1;
}
int main(){
    int a[100], n;
    cin >> n; 
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    int k;
    cin >> k;
    cout << linearSearchWithSentinel(a, n, k);
    return 0; 
}