#include <iostream>
using namespace std;
void swap(int &a, int &b){
    int tmp = a;
    a = b;
    b = tmp;
}
void heapify(int a[], int n, int i){
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int largest = i;
    if(left <= n - 1 && a[left] > a[largest]){
        largest = left;
    }
    if(right <= n - 1 && a[right] > a[largest]){
        largest = right;
    }
    if(largest != i){ 
        swap(a[i], a[largest]); 
        heapify(a, n, largest); 
    }
}
void heapSort(int a[], int n){
    for (int i = n / 2 - 1; i >= 0; i--){
        heapify(a, n, i);
    }
    for (int i = n - 1; i >= 0; i--){
        swap(a[0], a[i]);
        heapify(a, i, 0);
    }
}
void findTripletsSum(int a[], int n){
    for (int i = 0; i < n - 2; i++){
        int l = i + 1, r = n - 1;
        while(l < r){
            if((a[l] + a[r]) == -a[i]){
                cout << a[i] << " " << a[l] << " " << a[r] << endl;
                break;
            }
            else if(a[l] + a[r] > - a[i]){
                r--;
            }
            else{
                l++;
            }
        }
    }
}
int main(){
    int a[100], n;
    cin >> n;
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    heapSort(a, n);
    findTripletsSum(a, n);
    return 0;
}