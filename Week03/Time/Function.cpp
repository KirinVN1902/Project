#include "Function.h"
using namespace std;
template <class T>
void HoanVi(T &a, T &b)
{
	T x = a;
	a = b;
	b = x;
}

//-------------------------------------------------

// Hàm phát sinh mảng dữ liệu ngẫu nhiên
void GenerateRandomData(int a[], int n)
{
	srand((unsigned int)time(NULL));

	for (int i = 0; i < n; i++)
	{
		a[i] = rand()%n;
	}
}

// Hàm phát sinh mảng dữ liệu có thứ tự tăng dần
void GenerateSortedData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}
}

// Hàm phát sinh mảng dữ liệu có thứ tự ngược (giảm dần)
void GenerateReverseData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = n - 1 - i;
	}
}

// Hàm phát sinh mảng dữ liệu gần như có thứ tự
void GenerateNearlySortedData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}
	srand((unsigned int) time(NULL));
	for (int i = 0; i < 10; i ++)
	{
		int r1 = rand()%n;
		int r2 = rand()%n;
		HoanVi(a[r1], a[r2]);
	}
}

void GenerateData(int a[], int n, int dataType)
{
	switch (dataType)
	{
	case 0:	// ngẫu nhiên
		GenerateRandomData(a, n);
		break;
	case 1:	// có thứ tự
		GenerateSortedData(a, n);
		break;
	case 2:	// có thứ tự ngược
		GenerateReverseData(a, n);
		break;
	case 3:	// gần như có thứ tự
		GenerateNearlySortedData(a, n);
		break;
	default:
		printf("Error: unknown data type!\n");
	}
}
void swap(int &x, int &y){
    int tmp = x;
    x = y;
    y = tmp;
}
void selectionSort(int a[], int n){
    long long c = 0;
    for (int i = 0; c++ >= 0, i < n; i++){
        int minPos = i;
        for (int j = i + 1; c++ >= 0, j < n; j++){
            c++;
            if(a[j] < a[minPos]){
                minPos = j;
            }
        }
        swap(a[i], a[minPos]);
    }
    cout << c << endl;
}
void insertionSort(int a[], int n){
    long long c = 0;
    for (int i = 1; c++ >= 0, i < n; i++){
        int curNum = a[i];
        for (int j = i - 1; c++ >= 0, j >= 0; j--){
            c++;
            if(curNum < a[j]){
                a[j + 1] = a[j];
                c++;
                if(j == 0){
                    a[j] = curNum;
                }
            }
            else{
                a[j + 1] = curNum;
                break;
            }
        }
    }
    cout << c << endl;
}
void bubbleSort(int a[], int n){
    long long c = 0;
    for(int i = 0; c++, i < n; i++){
        for (int j = 0; c++, j < n - i - 1; j++){
            c++;
            if(a[j] > a[j + 1]){
                swap(a[j], a[j + 1]);
            }
        }
    }
    cout << c << endl;
}
void shakerSort(int a[], int n){
    int left = 0, right = n - 1, k = 0;
    long long c = 0;
    while (c++, left < right){
        for (int i = left; c++, i < right; i++){
            c++;
            if(a[i] > a[i + 1]){
                swap(a[i], a[i + 1]);
                k = i;
            }
        }
        right = k;
        for (int i = right; c++, i > left; i--){
            c++;
            if(a[i] < a[i - 1]){
                swap(a[i], a[i - 1]);
                k = i;
            }
        }
        left = k;
    }
    cout << c << endl;
}
void shellSort(int a[], int n){
    long long c = 0;
    int dis = 1;
    while(dis < n){
        c++;
        dis = dis * 3 + 1;
    }
    c++;
    while(dis > 0){
        c++;
        for (int i = dis; i < n; i++){
            c++;
            int tmp = a[i];
            int j = i;
            while(j >= dis && a[j - dis] > tmp){
                c += 2;
                a[j] = a[j - dis];
                j -= dis;
            }
            c++;
            a[j] = tmp;
        }
        c++;
        dis = (dis - 1) /3;
    }
    c++;
    cout << c << endl;
}
void heapify(int a[], int n, int i, long long &c){
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int largest = i;
    if(left <= n - 1 && a[left] > a[largest]){
        c += 2;
        largest = left;
    }
    c++;
    if(right <= n - 1 && a[right] > a[largest]){
        c += 2;
        largest = right;
    }
    c++;
    if(largest != i){
        c++;
        swap(a[i], a[largest]);
        heapify(a, n, largest, c);
    }
    c++;
}
void heapSort(int a[], int n, long long &c){
    for (int i = n / 2 - 1; c++, i >= 0; i--){
        heapify(a, n, i, c);
    }
    for (int i = n - 1; c++, i >= 0; i--){
        swap(a[i], a[0]);
        heapify(a, i, 0, c);
    }
}
void merge(int a[], int l, int m, int r, long long &c){
    vector<int> vl(a + l, a + m + 1);
    vector<int> vr(a + m + 1, a + r + 1);
    int i = 0, j = 0;
    while(i < vl.size() && j < vr.size()){
        c += 2;
        if(vl[i] <= vr[j]){
            c++;
            a[l] = vl[i];
            l++; i++;
        }
        else{
            c++;
            a[l] = vr[j];
            l++; j++;
        }
    }
    c++;
    while(i < vl.size()){
        c++;
        a[l] = vl[i];
        l++; i++;
    }
    while(l < vr.size()){
        c++;
        a[l] = vr[j];
        l++; j++;
    }
}
void mergeSoft(int a[], int l, int r, long long &c){
    c++;
    if(l >= r){
        return;
    }
    int m = l + (r - l) / 2;
    mergeSoft(a, l, m, c);
    mergeSoft(a, m + 1, r, c);
    merge(a, l, m, r, c);
}
int partition(int a[], int n, int l, int r, long long &c){
    int m = l + (r - l) / 2;
    int pivot = a[m];
    int i = l - 1, j = r + 1;
    while(i < j){
        c++;
        do{
            i++;
            c++;
        } while (a[i] < pivot && i <= r);
        do{
            j--;
            c++;
        } while (a[j] > pivot && j >= l);
        if(i < j){
            c++;
            swap(a[i], a[j]);
        }
        else{
            c++;
            return j;
        }
    }
}
void quickSort(int a[], int n, int l, int r, long long &c){
    c++;
    if(l >= r) return;
    int p = partition(a, n, l, r, c);
    quickSort(a, n, l, p, c);
    quickSort(a, n, p + 1, r, c);
}
void countingSort(int a[], int n, long long &c){
    int b[200000] = {0};
    for (int i = 0; i < n; i++){
        c++;
        b[a[i]]++;
    }
    c++;
    int index = 0;
    for (int i = 0; i < 200000; i++){
        c++;
        while (b[i] > 0){
            c++;
            a[index++] = i;
            b[i]--;
        }
        c++;
    }
    c++;
}
void countingSortForRadixSort(int a[], int n, int exp, long long &c){
    int count[10] = {0};
    int *output = new int[n];
    for (int i = 0; i < n; i++){
        c++;
        count[(a[i] / exp) % 10]++;
    }
    c++;
    for (int i = 1; i < 10; i++){
        c++;
        count[i] += count[i - 1];
    }
    c++;
    for (int i = n - 1; i >= 0; i--){
        c++;
        output[count[(a[i] / exp) % 10] - 1] = a[i];
        count[(a[i] / exp) % 10]--;
    }
    c++;
    for (int i = 0; i < n; i++){
        c++;
        a[i] = output[i];
    }
    c++;
    delete []output;
}
int maxDigit(int a[], int n, long long &c){
    int res = 0;
    int max = a[0];
    for (int i = 1; i < n; i++){
        c++;
        c++;
        if(a[i] > max){
            max = a[i];
        }
    }
    c++;
    while(max != 0){
        c++;
        res++;
        max /= 10;
    }
    c++;
    return res;
}
void radixSort(int a[], int n, long long &c){
    int max = maxDigit(a, n, c);
    int exp = 1;
    for (int i = 1; i <= max; i++){
        c++;
        countingSortForRadixSort(a, n, exp, c);
        exp *= 10;
    }
    c++;
}
void flashSort(int a[], int n, long long &c) {
    if (n <= 1) return;

    vector<int> arr(a, a + n);
    int maxVal = arr[0], minVal = arr[0], maxIndex = 0;

    // Tìm min và max
    for (int i = 1; i < n; i++) {
        c++;
        c++;
        if (arr[i] > maxVal) {
            maxVal = arr[i];
            maxIndex = i;
        }
        c++;
        if (arr[i] < minVal) {
            minVal = arr[i];
        }
    }
    c++;

    if (maxVal == minVal) return; // Mảng toàn phần tử bằng nhau

    int bucket = 0.43 * n;
    c++;
    if (bucket < 2) bucket = 2; 

    int* cnt = new int[bucket]();

    // Đếm phần tử vào từng bucket
    for (int i = 0; i < n; i++) {
        c++;
        long long k = ((arr[i] - minVal) * (bucket - 1)) / (maxVal - minVal);
        if (k >= bucket) k = bucket - 1;
        cnt[k]++;
    }
    c++;

    // Biến cnt thành chỉ số bắt đầu
    for (int i = 1; i < bucket; i++) {
        c++;
        cnt[i] += cnt[i - 1];
    }
    c++;

    // Đưa phần tử lớn nhất về đầu mảng
    if (maxIndex != 0){
        c++;
        swap(arr[0], arr[maxIndex]);
    }

    int move = 0, j = 0;
    int flash;

    while (move < n - 1) {
        c++;
        long long stage;
        while (j < n) {
            c++;
            stage = ((arr[j] - minVal) * (bucket - 1)) / (maxVal - minVal);
            if (stage >= bucket) stage = bucket - 1;
            if (j < cnt[stage]) break;
            j++;
        }
        c++;
        if (j >= n) break;

        flash = arr[j];

        while (true) {
            c++;
            long long k = ((flash - minVal) * (bucket - 1)) / (maxVal - minVal);
            if (k >= bucket){ k = bucket - 1;
            }

            int target = --cnt[k];
            if (target == j) break;
            if (target < 0 || target >= n) {
                cerr << "Lỗi truy cập mảng tại vị trí " << target << endl;
                delete[] cnt;
                return;
            }

            swap(flash, arr[target]);
            move++;
        }
        c++;

        arr[j] = flash;
        move++;
    }
    c++;

    // Insertion sort cuối để đảm bảo đúng thứ tự trong từng bucket
    for (int i = 1; i < n; i++) {
        c++;
        int temp = arr[i], k = i - 1;
        while (k >= 0 && temp < arr[k]) {
            c += 2;
            arr[k + 1] = arr[k];
            k--;
        }
        c++;
        arr[k + 1] = temp;
    }
    c++;

    // Sao chép kết quả ngược lại mảng gốc
    for (int i = 0; i < n; i++) {
        c++;
        a[i] = arr[i];
    }

    delete[] cnt;
}

void typeToSort(int a[], int n, string type, long long &c){
    int l = 0, r = n - 1;
    if(type == "selection-sort"){
        selectionSort(a, n);
    }
    else if(type == "insertion-sort"){
        insertionSort(a, n);
    }
    else if(type == "bubble-sort"){
        bubbleSort(a, n);
    }
    else if(type == "shaker-sort"){
        shakerSort(a, n);
    }
    else if(type == "shell-sort"){
        shellSort(a, n);
    }
    else if(type == "heap-sort"){
        heapSort(a, n, c);
    }
    else if(type == "merge-sort"){
        mergeSoft(a, l, r, c);
    }
    else if(type == "quick-sort"){
        quickSort(a, n, l, r, c);
    }
    else if(type == "counting-sort"){
        countingSort(a, n, c);
    }
    else if(type == "radix-sort"){
        radixSort(a, n, c);
    }
    else if(type == "flash-sort"){
        flashSort(a, n, c);
    }
    else{
        cout << "Enter an invalid sort!";
    }
}
void time(int a[], int n, string type, long long &c){
        auto start = chrono::high_resolution_clock::now();
        typeToSort(a, n, type, c);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << duration.count() << endl;
}
