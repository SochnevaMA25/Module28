// Module28.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <future>
#include <vector>

using namespace std;
bool make_thread = true;
void merge(int* arr, int l, int m, int r) {
    long nl = m - l + 1;
    long nr = r - m;

    // создаем временные массивы
    int* left = new int[nl];
    int* right = new int[nr];

      // копируем данные во временные массивы
    for (long i = 0; i < nl; i++)
        left[i] = arr[l + i];

    for (long j = 0; j < nr; j++)
        right[j] = arr[m + 1 + j];

    long i = 0, j = 0;
    long k = l;  // начало левой части

    while (i < nl && j < nr) {
        // записываем минимальные элементы обратно во входной массив
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        }
        else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    // записываем оставшиеся элементы левой части
    while (i < nl) {
        arr[k] = left[i];
        i++;
        k++;
    }
    // записываем оставшиеся элементы правой части
    while (j < nr) {
        arr[k] = right[j];
        j++;
        k++;
    }

    delete[] left, right;
}
void mergeSort(int* arr, int l, int r) {
    if (l >= r)
    {
        return;
    }
    else {

        long m = 0;
        m = (r + l) / 2; 

        if (make_thread && (r - l > 100000))
        {
            future<void> right = std::async(std::launch::async, [&](){ mergeSort(arr, l, m); });
            mergeSort(arr, m + 1, r);
        }
        else {
            mergeSort(arr, l, m);
            mergeSort(arr, m + 1, r);
        }

        merge(arr, l, m, r);
    }
}

int main()
{
    std::srand(0);
    long arr_size = 1000000;
    int* array = new int[arr_size];  

    for (long i = 0; i < arr_size; i++) 
    { 
        array[i] = std::rand() % 5000;
    }

    time_t start, end;

    // многопоточный запуск
    std::time(&start);
    mergeSort(array, 0, arr_size); 
    std::time(&end);

    double seconds = std::difftime(end, start);
    std::printf("The time: %f seconds\n", seconds);

    for (long i = 0; i < arr_size; i++) 
    { 
        if (array[i] > array[i + 1]) 
        {
            std::cout << "Unsorted " << i << std::endl;
            break;
        }
    }

    for (long i = 0; i < arr_size; i++) 
    { 
        array[i] = std::rand() % 5000;
    }

    // однопоточный запуск
    make_thread = false;
    std::time(&start);
    mergeSort(array, 0, arr_size);
    std::time(&end);

    seconds = std::difftime(end, start);
    std::printf("The time: %f seconds\n", seconds);

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
