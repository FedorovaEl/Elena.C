#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

struct patients {
    char name[20];
    int age;
};

patients* getPatiensInfo(int&); // Ïîëó÷åíèå èíôîðìàöèè èç ôàéëà
template <class T> void printPatiens(T*, int); // Âûâîä íà êîíñîëü
template <class T> void heapify(T*, int, int); // Ïîñòðîåíèå ïèðàìèäû. "Áàëàíñèðîâêà" óìåíüøåííîé êó÷è
template <class T> void heapSort(T*, int); // Ñàìà ñîðòèðîâêà
template <class T> void writeListToFile(T*, int); //Çàïèñü ñïèñêà â ôàéë

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
    int largest = i; // Èíèöèàëèçèðóåì íàèáîëüøèé ýëåìåíò êàê êîðåíü
    int left = 2 * i + 1; // Ëåâûé äî÷åðíèé ýëåìåíò
    int right = 2 * i + 2; // Ïðàâûé äî÷åðíèé ýëåìåíò

    // Åñëè ëåâûé äî÷åðíèé ýëåìåíò áîëüøå ðîäèòåëüñêîãî
    if (left < heap_size && A[left].age > A[largest].age) {
        largest = left;
    }
    // Åñëè ïðàâûé äî÷åðíèé ýëåìåíò áîëüøå, ÷åì ñàìûé áîëüøîé ýëåìåíò íà äàííûé ìîìåíò
    if (right < heap_size && A[right].age > A[largest].age) {
        largest = right;
    }
    // Åñëè ñàìûé áîëüøîé ýëåìåíò íå ðîäèòåëüñêèé, òî
    if (largest != i) {
        swap(A[i], A[largest]);
        // Ïðåîáðàçóåì â äâîè÷íóþ êó÷ó çàòðîíóòîå ïîääåðåâî
        heapify(A, heap_size, largest);
    }
}

template <class T>
void heapSort(T* A, int length) {
    // Ïîñòðîåíèå êó÷è/ïèðàìèäû (ïåðåãðóïïèðóåì ìàññèâ)
    for (int i = length / 2 - 1; i >= 0; i--) {
        heapify(A, length, i);
    }
    /* Îäèí çà äðóãèì èçâëåêàåì ýëåìåíòû èç êó÷è -
       ôîðìèðóåì êîíå÷íóþ îòñîðòèðîâàííóþ
       ïîñëåäîâàòåëüíîñòü è "áàëàíñèðóåì" ïèðàìèäó*/
    for (int i = length - 1; i >= 0; i--) {
        swap(A[0], A[i]); // Ïåðåìåùàåì òåêóùèé êîðåíü â êîíåö
        heapify(A, i, 0); // Âîññòàíàâëèâàåì áàëàíñ äëÿ óìåíüøåííîé êó÷è
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
