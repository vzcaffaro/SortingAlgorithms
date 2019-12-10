#include <iostream>
#include <fstream>
#include <time.h> //package to track periods of time
#include <chrono> //package to print current time

using namespace std;

class fileReader
{
public:
    fileReader();
    fileReader(int maxSize, string file);
    ~fileReader();

    void merge(float array[], int front, int mid, int back); //helper function for merge sort
    void mergeSort(float array[], int front, int back);
    void quickSort(float array[], int front, int back);
    void insertSort(float array[], int len);
    void bubbleSort(float array[], int len);
    void selectionSort(float array[], int len);



    ifstream inf; //in stream for reading files

    float* arr1; //declares arrays pointers, using dynamic memory allocation
    float* arr2;
    float* arr3;
    float* arr4;
    float* arr5;

    time_t timer = time(NULL); //basic time object works as a stopwatch
};
