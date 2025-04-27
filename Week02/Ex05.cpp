#include <iostream>
using namespace std;
int minimalLength(int a[], int n, int target){
    int min = 1000000, i = 0;
    while (i < n){
        int sum = 0, cnt = 0;
        for (int j = i; j < n; j++){
            if(sum >= target){
                break;
            }
            sum += a[j];
            cnt++;
        }
        if(cnt < min && sum >= target){
            min = cnt;
        }
        i++;
    }
    return min;
}
int main(){
    int a[100], n;
    cin >> n;
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    int target; cin >> target;
    cout << minimalLength(a, n, target);
    return 0;
}