#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

struct patients {
    char name[20];
    int age;
};

patients* getPatiensInfo(int&); // ��������� ���������� �� �����
template <class T> void printPatiens(T*, int); // ����� �� �������
template <class T> void heapify(T*, int, int); // ���������� ��������. "������������" ����������� ����
template <class T> void heapSort(T*, int); // ���� ����������
template <class T> void writeListToFile(T*, int); //������ ������ � ����

int main() {
    setlocale(0, "");
    int n;
    patients* list = getPatiensInfo(n);
    printPatiens(list, n);
    heapSort(list, n);
    printPatiens(list, n);
    writeListToFile(list, n);
    delete[] list;
    return 0;
}

patients* getPatiensInfo(int& n) {
    patients list;
    ifstream fin;
    string file;
    cout << "name of input file:\n";
    cin >> file;
    fin.open(file);
    if (!fin) {
        cout << file << "can't open file\n";
        exit(1);
    }
    n = 0;
    do {
        fin >> list.name >> list.age;
        n++;
    } while (fin.good());
    fin.close();

    fin.open(file);
    patients* pl = new patients[n];
    if (pl == NULL) {
        cout << "\nno memory\n";
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        fin >> pl[i].name >> pl[i].age;
    }
    fin.close();
    return pl;
}

template <class T>
void heapify(T* A, int heap_size, int i) {
    int largest = i; // �������������� ���������� ������� ��� ������
    int left = 2 * i + 1; // ����� �������� �������
    int right = 2 * i + 2; // ������ �������� �������

    // ���� ����� �������� ������� ������ �������������
    if (left < heap_size && A[left].age > A[largest].age) {
        largest = left;
    }
    // ���� ������ �������� ������� ������, ��� ����� ������� ������� �� ������ ������
    if (right < heap_size && A[right].age > A[largest].age) {
        largest = right;
    }
    // ���� ����� ������� ������� �� ������������, ��
    if (largest != i) {
        swap(A[i], A[largest]);
        // ����������� � �������� ���� ���������� ���������
        heapify(A, heap_size, largest);
    }
}

template <class T>
void heapSort(T* A, int length) {
    // ���������� ����/�������� (�������������� ������)
    for (int i = length / 2 - 1; i >= 0; i--) {
        heapify(A, length, i);
    }
    /* ���� �� ������ ��������� �������� �� ���� -
       ��������� �������� ���������������
       ������������������ � "�����������" ��������*/
    for (int i = length - 1; i >= 0; i--) {
        swap(A[0], A[i]); // ���������� ������� ������ � �����
        heapify(A, i, 0); // ��������������� ������ ��� ����������� ����
    }
}

template <class T>
void printPatiens(T* list, int n) {
    cout << '\n' << setw(21) << left << "name:" << "age:\n";
    for (int i = 0; i < n; i++) {
        cout << setw(21) << left << list[i].name << list[i].age << '\n';
    }
}

template <class T>
void writeListToFile(T* list, int n) {
    ofstream fout;
    string file;
    cout << "name of output file:\n";
    cin >> file;
    fout.open(file);
    if (!fout.good()) {
        cout << file << " not created\n";
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        fout << setw(21) << left << list[i].name << list[i].age << '\n';
    }
    fout.close();
}