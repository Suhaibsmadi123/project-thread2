#include <iostream>
#include <thread>
#include <vector>
#include <fstream>
#include <algorithm>
#include<mutex>
using namespace std;
//#include "../../../Downloads/final (2).cpp"
//using namespace ThreadArgs;


mutex stt;
mutex Ab;
mutex Eq;
mutex Be;
mutex co;
mutex suhib;
int state = 0;
int Above = 0;
int Equal = 0;
int Below = 0;


////////////////////////////////////////////////


// Merge two sorted subarrays into one sorted array
void merge(std::vector<int>& arr, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    std::vector<int> L(n1);
    std::vector<int> R(n2);

    // Copy data to temp arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[middle + 1 + j];  int i = 0;
    int j = 0;
    int k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;

       

    }

    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Recursive function to perform merge sort on the array
void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        
        int middle = left + (right - left) / 2;

        stt.lock();
        state++;
        stt.unlock();
        
        // Sort first and second halves
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);

        // Merge the sorted halves
        merge(arr, left, middle, right);
        
       stt.lock();
        state--;
        stt.unlock();
        
    }
    /*if (state == 0)
    {


       for (int j = 0;j < 1;j++) {
            for (int i = left; i <= right; i++) {

                if (arr[i] < th ) {
                    Be.lock();
                    Below++;
                    Be.unlock();
                }
                else if (arr[i] > th) {
                   Ab.lock();
                    Above++;
                    Ab.unlock();
                }
                else {
                    Eq.lock();
                    Equal++;
                    Eq.unlock();
                }
            }

        }

    

    }*/
}
void tt(std::vector<int>& arr, int left, int right, int th, int thnum,int low,int high) {
    suhib.lock();
    cout << "Starting thread " << thnum<<": " << "low = " <<low << ", high = " << high << endl;
    suhib.unlock();
    mergeSort(arr, left, right);
    
    for (int j = 0;j < 1;j++) {
        for (int i = left; i <= right; i++) {

            if (arr[i] < th) {
                Be.lock();
                Below++;
                Be.unlock();
            }
            else if (arr[i] > th) {
                Ab.lock();
                Above++;
                Ab.unlock();
            }
            else {
                 Eq.lock();
                Equal++;
                Eq.unlock();
            }
        }

    }



}



void f(int i) {
    co.lock();
    cout << "Thread number" << i << " they have no work to do" << endl << endl;
    co.unlock();
}
////////////////////////////////////////////////

int main()
{
    fstream input;
    vector <int> List;
    int T;
    int  L, TH;
    input.open("in.txt", ios::in);
    if (!input.is_open()) {
        cerr << "Unable to open input file." << endl;
        return EXIT_FAILURE;
    }
    if (input.peek() == EOF)
    {
        cout << "The file is Empty";
        return EXIT_FAILURE;
    }
    if (sizeof("in.txt") < 2)
    {
        cout << "The file is Empty";
        return EXIT_FAILURE;
    }
    

    input >> L >> TH;
    int count = 0;
    for (int i = 0; i < L; i++) {
        int c;
        input >> c;
        List.emplace_back(c);
    }
    input.close();
    
    
    std::vector<std::thread> threads;

    std::vector<int> sorted_values;
        std::vector<std::vector<int>> arrays;
    if (List.empty())
        cout << "List is empty" << endl;
    else {
        cout << "Main: Starting sorting with N=" << L << ", TH=" << TH << endl;
        cout << "Enter number of Thread " << endl;
        cin >> T;
          
        if (T == 0) {
            cout << "The number of thread is not valid";
            return EXIT_FAILURE;

        }


        if (L > T && L % T == 0 && L != T) {


            //std::vector<int> arrays;
            int count = 0;
            for (int i = 0;i < T;i++) {
                vector<int> tem;
                for (int j = 0;j < L / T;j++)
                    tem.emplace_back(List[count++]);

                arrays.emplace_back(tem);
            }
            for (int i = 0; i < T; i++) {
                threads.emplace_back(std::thread(tt, std::ref(arrays[i]), 0, (L / T) - 1, TH, i, i * L / T, (i * L / T) + (L / T) - 1));
            }
            
        }
        else if (L > T && L % T != 0 && L != T) {

            

            int count = 0;
            for (int i = 0;i < T;i++) {
                vector<int> tem;
                if (i != T - 1) {
                    for (int j = 0;j < L / T;j++)
                        tem.emplace_back(List[count++]);
                    arrays.emplace_back(tem);
                }
                else { // اذا العدد القيم 11 وانا مسموحلي بس 3 ثريد اول اريي بده يكون فيها 3 الثانيه 3 الثالثه 3 زائد باقي قسمة ال11 على 3
                    for (int j = 0;j < (L / T) + (L % T);j++)
                        tem.emplace_back(List[count++]);
                    arrays.emplace_back(tem);
                }
            }

            for (int i = 0; i < T; i++) {
                if (i != T - 1)
                    threads.emplace_back(std::thread(tt, std::ref(arrays[i]), 0, (L / T) - 1, TH, i, i * (L / T), i * (L / T) + (L / T) - 1));
                else
                    threads.emplace_back(std::thread(tt, std::ref(arrays[i]), 0, ((L / T) + (L % T)) - 1, TH, i, i * (L / T), i * (L / T) + ((L / T) + (L % T)) - 1));

            }
        }


        else if (T >= L)
        {
            int count = 0;
            // std::vector<int> arrays;
            for (int i = 0;i < L;i++) {
                vector<int>tem;
                for (int j = 0;j < 1;j++)
                    tem.push_back(List[count++]);
                arrays.emplace_back(tem);
                // threads.emplace_back(std::thread(tt, std::ref(arrays[i]), 0, 0, TH, i,i*1,i*1));
            }
            for (int i = 0; i < T; ++i) {
                if (i < L)
                    threads.emplace_back(std::thread(tt, std::ref(arrays[i]), 0, 0, TH, i, i * 1, i * 1));
                else
                    threads.emplace_back(std::thread(f, i));
            }
        }
        else
            cout << "the value if L is not correct" << endl;
    }
    for (int i = 0; i < T; ++i) {
        threads[i].join();
    }

    cout << "Main: Above Threshold = " << Above << endl;
    cout << "Main: Equals Threshold = " << Equal << endl;
    cout << "Main: Below Threshold = " << Below << endl;

    for (int i = 0; i < arrays.size(); ++i) {

        sorted_values.insert(sorted_values.end(), arrays[i].begin(), arrays[i].end());
        mergeSort(sorted_values, 0, sorted_values.size() - 1);
    }    //sort(sorted_values.begin(), sorted_values.end());

    input.open("out.txt", ios::out);
    input << "Sorted array:" << endl;
    for (int val : sorted_values) {
        input << val << " ";
    }
    input.close();

    return 0;
}
