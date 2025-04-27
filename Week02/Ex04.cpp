#include <iostream>
using namespace std;
int maxArray(int a[], int n){
    int max = a[0];
    for (int i = 0; i < n; i++){
        if(a[i] > max){
            max = a[i];
        }
    }
    return max;
}
int leastWeight(int weight[], int n, int day){
    int least = maxArray(weight, n);
    int largest = 0;
    for (int i = 0; i < n; i++){
        largest += weight[i];
    }
    while(least < largest){
        int mid = (least + largest) / 2;
        int requireDays = 0, cur = 0;
        for (int i = 0; i < n; i++){
            if(cur + weight[i] > mid){
                requireDays++;
                cur = 0;
            }
            cur += weight[i];
        }
        if(requireDays < day){
            largest = mid;
        }
        else{
            least = mid + 1;
        }
    }
    return least;
}
int main(){
    int a[100], n;
    cin >> n;
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    int days;
    cout << "Enter number of days: ";
    cin >> days;
    cout << leastWeight(a, n, days);
    return 0;
}