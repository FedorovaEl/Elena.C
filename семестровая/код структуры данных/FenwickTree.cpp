#include <iostream>
using namespace std;

void addToElement(int T[], int n, int idx, int value); 
int prefixSum(int T[], int r);
int ElemByIdx(int T[], int idx);
void changeValue(int T[], int n, int idx, int value);
int sumSlice(int T[], int idx1, int idx2);
int *initFenwickTreeFromArray(int a[], int n);
int *createFenwickTree(int n, int startValue = 0);

int main() {

    int n = 12;
    int *t1 = createFenwickTree(n);
    
    for (int i = 0; i < n; i++) {
        changeValue(t1, n, i, i);
    }
    
    cout << "(T): \t\t";
    for (int i = 0; i < n; i++) {
        cout << t1[i] << " ";
    }
    
    cout << endl << "(T -> A): \t";
    for (int i = 0; i < n; i++) {
        cout << ElemByIdx(t1, i) << " ";
    }
    cout << endl << "Output of sumSlice(T1, 3, 6): " << sumSlice(t1, 3, 6) << endl;


   int arr[] = {12, 3, 34, 42, 123, 23, 79};
   int size = sizeof(arr)/sizeof(arr[0]);
   int *t2 = initFenwickTreeFromArray(arr, size);
   cout << "Idx: \t\t";
   for (int i = 0; i < size; i++) {
       cout << i << " ";
   }
   cout << endl << "A: \t\t";
   for (int i = 0; i < size; i++) {
       cout << arr[i] << " ";
   }
   cout << endl << "T: \t\t";
   for (int i = 0; i < size; i++) {
       cout << t2[i] << " ";
   }
   cout << endl << "T -> A: \t";
   for (int i = 0; i < size; i++) {
       cout << ElemByIdx(t2, i) << " ";
   }
   changeValue(t2, size, 2, 5);
   cout << endl << "Modified A: \t";
   
   for (int i = 0; i < size; i++) {
       cout << ElemByIdx(t2, i) << " ";
   }
   
   cout << endl << "Modified T: \t";
   for (int i = 0; i < size; i++) {
       cout << t2[i] << " ";
   }
}

void addToElement(int T[], int n, int idx, int value) {
    while (idx < n) {
        T[idx] += value;
        idx = idx | (idx + 1);
    }
}

int prefixSum(int T[], int r) {
    int result = 0;
    do {
        result += T[r];
        r = ((r + 1) & r) - 1;
    } while (r > 0);
    return result;
}

int ElemByIdx(int T[], int idx) {
    if (idx <= 0) {
        return prefixSum(T, 0);
    } else {
        return prefixSum(T, idx) - prefixSum(T, idx - 1);
    }
}

void changeValue(int T[], int n, int idx, int value) {
    addToElement(T, n, idx, value - ElemByIdx(T, idx));
}

int sumSlice(int T[], int idx1, int idx2) {
    return prefixSum(T, idx2 - 1) - prefixSum(T, idx1 - 1);
}

int *initFenwickTreeFromArray(int a[], int n) {
    int *T = new int[n];
    for (int i = 0; i < n; i++) {
        T[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        addToElement(T, n, i, a[i]);
    }
    return T;
}

int *createFenwickTree(int n, int startValue = 0) {
    int *T = new int[n];
    for (int i = 0; i < n; i++) {
        T[i] = 0;
    }
    return T;
}
