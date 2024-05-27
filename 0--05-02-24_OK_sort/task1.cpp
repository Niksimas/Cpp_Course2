//
// Created by Nikita on 05.02.2024.
//
/* Класс контейнер для хранения записей с полями
 *      • ФИО
 *      • Дата рождения
 *      • Объем мозга
 * Методы ввода, вывода, добавления данных из массива
 * Не меньше 10 методов сортировки (не больше 4х простых) с указанием поля, по которому сортировать
 * Внести не менее 100 записей.
 * Добавить мониторинг количества сравнений и количества перезаписей элементов
 * */

#include <iostream>
#include <vector>
#include <time.h>
#include <random>
#include <algorithm>
#include <fstream>
#include <sys/time.h>

using namespace std;

random_device rd;
mt19937 gen(rd());
int random(int low, int high){
    uniform_int_distribution<> dist(low, high);
    return dist(gen);
}

struct Date{
    int day=0, month=0, year=0;
    Date() {
        day = random(1, 31);
        month = random(1, 12);
        year = random(1950, 2023);
    };

    friend ostream& operator << (ostream& stream, const Date& p){
        stream << p.day << "." << p.month << "." << p.year;
        return stream;
    }
};

struct People{
    string name;
    Date dr;
    int brain_volume;
    People() {
        brain_volume = random(1,1000);
        name = creat_str();
    }

    string creat_str(){
        string abc = "qazwsxedcrfvtgbyhnujmikolp";
        string new_str = "";
        for (int i=0; i<7; i++){
            new_str += abc[random(0,25)];
        }
        return new_str;
    }

    friend ostream& operator << (ostream& stream, const People& p){
        stream << p.name << "-|-" << p.dr  << "-|-" << p.brain_volume << endl;
        return stream;
    }
};

class Container {
    vector<People> main_array;
public:
    Container() {
//        for(int i=0; i<100; i++) {
//            People people;
//            main_array.emplace_back(people);
//        }
        read_from_file();
    }

//    void creat_data(){
//        main_array.emplace_back(People("lhjijii", Date(15,02,12), 15));
//    }

    void write_in_file() {
        ofstream out_data("record.txt", ios::out);
        if (!out_data.is_open()) cout << "Errors open file!\n";
        else {
            out_data << main_array.size() << endl;
            for (int i = 0; i < main_array.size(); i++) {
                out_data
                        << main_array[i].name << " "
                        << main_array[i].brain_volume << " "
                        << main_array[i].dr.day << " "
                        << main_array[i].dr.month << " "
                        << main_array[i].dr.year << "\n";
            }
        }
        out_data.close();
        cout << "Save and close\n";
    }

    void read_from_file() {
        main_array.clear();
        ifstream in_data("record.txt", ios::in);
        if (!in_data.is_open())cout << "Errors open file!\n";
        else {
            int k = 0;
            string name = "def";
            int day, month, year, br;
            People newr = People();
            in_data >> k;
            for (; 0 < k; k--) {
                in_data >> name >> br >> day >> month >> year;
                newr.name = name;
                newr.brain_volume = br;
                newr.dr.day = day;
                newr.dr.month = month;
                newr.dr.year = year;
                main_array.emplace_back(newr);
            }
        }
        in_data.close();
    }

    void get_record(int i) {cout << main_array[i];}

    void print() {
        for (int i = 0; i < 100; i++) {
            cout << i + 1 << ". ";
            get_record(i);
        }
    }

//-----------------1сортировка расческой----------------------------//
    void CombSort() {
        int iter = 0, swaps = 0;

        const double factor = 1.247; // Фактор уменьшения
        double step = main_array.size() - 1;

        while (step >= 1) {
            iter++;
            for (int i = 0; i + step < main_array.size(); ++i) {
                iter++;
                if (main_array[i].name > main_array[i + step].name) {
                    swaps++;
                    swap(main_array[i], main_array[i + step]);
                }
            }
            step /= factor;
        }
        cout << "1.Sortirovka Rascheskoy " << endl << "iter: " << iter << "   " << "swaps: " << swaps << endl;
    }

//-----------------2пузырьковая сортировка--------------------------//
    void bubble_sort() {
        int iter = 0, swaps = 0;
        int n = main_array.size();
        for (int i = 0; i < n - 1; ++i) {
            iter++;
            for (int j = 0; j < n - i - 1; ++j) {
                iter++;
                if (main_array[j].name > main_array[j + 1].name) {
                    swap(main_array[j], main_array[j + 1]);
                    swaps++;
                }
            }
        }
        cout << "2.Sortirovka Pyzerkom" << endl << "iter: " << iter << "   " << "swaps: " << swaps << endl;
    }

//-----------------3cортировка выбором------------------------------//
    void selection_sort() {
        int iter = 0, swaps = 0;
        int n = main_array.size();
        for (int i = 0; i < n - 1; ++i) {
            iter++;
            int min_idx = i;
            for (int j = i + 1; j < n; ++j) {
                iter++;
                if (main_array[j].name < main_array[min_idx].name) {
                    min_idx = j;
                }
            }
            swap(main_array[i], main_array[min_idx]);
            swaps++;
        }
        cout << "3.Sortirovka Viborom" << endl << "iter: " << iter << "   " << "swaps: " << swaps << endl;
    }

//---------------------------------------------4сортировка вставками-------------------------------------//
    void insertion_sort() {
        int iter = 0, swaps = 0;
        int n = main_array.size();
        for (int i = 1; i < n; ++i) {
            iter++;
            People key = main_array[i];
            int j = i - 1;
            while (j >= 0 && main_array[j].name > key.name) {
                iter++;
                main_array[j + 1] = main_array[j];
                --j;
                swaps++;
            }
            main_array[j + 1] = key;
        }
        cout << "4.Sortirovka Vstavkami  " << endl << "iter: " << iter << "   " << "swaps: " << swaps << endl;
    }

//----------------------------------5сортировка слиянием-----------------------------------------//
    int iter_m = 0, swaps_m = 0;

    void merge_corting() {
        merge_sort(0, main_array.size());
        cout << "5.Sortirovka Sliyaniem " << endl << "iter: " << iter_m << "   " << "swaps: " << swaps_m << endl;
    }

    void merge_sort(int low, int high) {
        if (low < high) {
            int mid = low + (high - low) / 2;
            merge_sort(low, mid);
            merge_sort(mid + 1, high);
            merge(low, mid, high);
        }
    }

    void merge(int low, int mid, int high) {
        int n1 = mid - low + 1;
        int n2 = high - mid;

        vector<People> L(n1), R(n2);
        for (int i = 0; i < n1; ++i) {
            iter_m++;
            L[i] = main_array[low + i];
        }
        for (int j = 0; j < n2; ++j) {
            iter_m++;
            R[j] = main_array[mid + 1 + j];
        }

        int i = 0, j = 0, k = low;
        while (i < n1 && j < n2) {
            iter_m++;
            if (L[i].brain_volume <= R[j].brain_volume) {
                main_array[k] = L[i];
                ++i;
                swaps_m++;
            } else {
                main_array[k] = R[j];
                ++j;
                swaps_m++;
            }
            ++k;
        }

        while (i < n1) {
            iter_m++;
            main_array[k] = L[i];
            ++i;
            ++k;
            swaps_m++;
        }

        while (j < n2) {
            iter_m++;
            main_array[k] = R[j];
            ++j;
            ++k;
            swaps_m++;
        }
    }

//----------------------------------6сортировка шелла-----------------------------------------//
    void shell_sort() {
        int iter = 0, swaps = 0;
        int n = main_array.size();
        for (int gap = n / 2; gap > 0; gap /= 2) {
            iter++;
            for (int i = gap; i < n; ++i) {
                iter++;
                People temp = main_array[i];
                int j;
                for (j = i; j >= gap && main_array[j - gap].name > temp.name; j -= gap) {
                    main_array[j] = main_array[j - gap];
                    swaps++;
                }
                main_array[j] = temp;
            }
        }
        cout << "6.Sortirovka Shell " << endl << "iter: " << iter << "   " << "swaps: " << swaps << endl;
    }

//----------------------------------7сортировка кучей-----------------------------------------//
int iter_h=0, swaps_h=0;
    void heap_sort() {
        int n = main_array.size();
        for (int i = n / 2 - 1; i >= 0; --i) {
            iter_h++;
            heapify(n, i);
        }
        for (int i = n - 1; i > 0; --i) {
            iter_h++;
            swap(main_array[0], main_array[i]);
            swaps_h++;
            heapify(i, 0);
        }
        cout << "7.Sortirovka Kychey " << endl << "iter: " << iter_h << "   " << "swaps: " << swaps_h << endl;
    }

    void heapify(int n, int i) {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (l < n && main_array[l].name > main_array[largest].name) { largest = l; }
        if (r < n && main_array[r].name > main_array[largest].name) { largest = r; }
        if (largest != i) {
            swap(main_array[i], main_array[largest]);
            swaps_h++;
            heapify(n, largest);
        }
    }

    //--------------------------------------8быстрая сортировка---------------------------//
    int iter_q=0, swaps_q=0;
    int partition(int start, int pivot){
        int i = start;
        while(i < pivot){
            iter_q++;
            if(main_array[i].name > main_array[pivot].name && i == pivot-1){
                swap(main_array[i], main_array[pivot]);
                swaps_q++;
                pivot--;
            }
            else if(main_array[i].name > main_array[pivot].name){
                swap(main_array[pivot - 1], main_array[pivot]);
                swaps_q++;
                swap(main_array[i], main_array[pivot]);
                swaps_q++;
                pivot--;
            }
            else i++;
        }
        return pivot;
    }

    void quickSortProcess(int start, int end){
        if(start < end){
            int pivot = partition(start, end);
            quickSortProcess(start, pivot - 1);
            quickSortProcess(pivot + 1, end);
        }
    }

    void quick_sort(){
        quickSortProcess(0, main_array.size());
        cout << "8.Sortirovka Bistraya  " << endl << "iter: " << iter_q << "   " << "swaps: " << swaps_q << endl;
    }

    //--------------------------------------9гномья сортировка---------------------------//
    void gnomeSort() {
        int iter=0, swaps=0;
        int index = 0;
        while (index < main_array.size()) {
            iter++;
            if (index == 0)
                index++;
            if (main_array[index].name >= main_array[index - 1].name)
                index++;
            else {
                swap(main_array[index], main_array[index - 1]);
                swaps++;
                index--;
            }
        }
        cout << "9.Sortirovka Gnome  " << endl << "iter: " << iter << "   " << "swaps: " << swaps << endl;
    }

    //--------------------------------------10пирамидальная сортировка---------------------------//
    int iter_p=0, swaps_p=0;
    void heapify(unsigned int n, unsigned int i) {
        unsigned int largest = i;
        unsigned int left = 2 * i + 1;
        unsigned int right = 2 * i + 2;
        if (left < n && main_array[left].name > main_array[largest].name) {largest = left;}
        if (right < n && main_array[right].name > main_array[largest].name) {largest = right;}
        if (largest != i) {
            swap(main_array[i], main_array[largest]);
            swaps_p++;
            heapify(n, largest);
        }
    }

    void heapSort() {
        for (int i = main_array.size() / 2 - 1; i >= 0; i--) {
            iter_p++;
            heapify(main_array.size(), i);
        }
        for (int i = main_array.size() - 1; i > 0; i--) {
            iter_p++;
            if (main_array[0].name > main_array[i].name) {
                swap(main_array[0], main_array[i]);
                swaps_p++;
                heapify(i, 0);
            }
        }
        cout << "10.Sortirovka Pyramid  " << endl << "iter: " << iter_p << "   " << "swaps: " << swaps_p << endl;
    }

};



int main(){
    Container cont;
//    cont.print();
    struct timeval start, end;
    ios_base::sync_with_stdio(false);
    double time_taken;

    gettimeofday(&start, NULL);
    cont.CombSort();
    gettimeofday(&end, NULL);
    time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;
    cout << fixed;
    cout.precision(6);
    cout << time_taken << "sec" << endl<<endl;
//    cont.print();

    cont.read_from_file();
    gettimeofday(&start, NULL);
    cont.bubble_sort();
    gettimeofday(&end, NULL);
    time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;
    cout << time_taken << "sec" << endl << endl;
//    cont.print();

    cont.read_from_file();
    gettimeofday(&start, NULL);
    cont.selection_sort();
    gettimeofday(&end, NULL);
    time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;
    cout << time_taken << "sec" << endl<< endl;
//    cont.print();

    cont.read_from_file();
    gettimeofday(&start, NULL);
    cont.insertion_sort();
    gettimeofday(&end, NULL);
    time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;
    cout << time_taken << "sec" << endl<< endl;
//    cont.print();

    cont.read_from_file();
    gettimeofday(&start, NULL);
    cont.merge_corting();
    gettimeofday(&end, NULL);

    cout << cont.iter_m << cont.swaps_m ;

    time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;
    cout << time_taken << "sec" << endl<< endl;
//    cont.print();

    cont.read_from_file();
    gettimeofday(&start, NULL);
    cont.shell_sort();
    gettimeofday(&end, NULL);
    time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;
    cout << time_taken << "sec" << endl<< endl;
//    cont.print();

    cont.read_from_file();
    gettimeofday(&start, NULL);
    cont.heap_sort();
    gettimeofday(&end, NULL);
    time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;
    cout << time_taken << "sec" << endl<< endl;
//    cont.print();

    cont.read_from_file();
    gettimeofday(&start, NULL);
    cont.quick_sort();
    gettimeofday(&end, NULL);
    time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;
    cout << time_taken << "sec" << endl<< endl;
//    cont.print();

    cont.read_from_file();
    gettimeofday(&start, NULL);
    cont.gnomeSort();
    gettimeofday(&end, NULL);
    time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;
    cout << time_taken << "sec" << endl<< endl;
//    cont.print();

    cont.read_from_file();
    gettimeofday(&start, NULL);
    cont.heapSort();
    gettimeofday(&end, NULL);
    time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;
    cout << time_taken << "sec" << endl<< endl;
//    cont.print();


    return 0;
}