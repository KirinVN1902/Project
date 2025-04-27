#include "Function.h"
using namespace std;
int main(){
    int data[4] = {0, 1, 2, 3};
    int elements[4] = {10000, 30000, 50000};
    long long c = 0;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 3; j++){
            int a[elements[j]];
            GenerateData(a, elements[j], data[i]);
            string type = "flash-sort";
            typeToSort(a, elements[j], type, c);
            cout << c << endl;
            c = 0;
        }
    }
    return 0;
}