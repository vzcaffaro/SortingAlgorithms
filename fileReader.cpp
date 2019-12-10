#include "fileReader.h"
#include <iostream>


using namespace std;

fileReader::fileReader()
{
    arr1 = new float[100];
    arr2 = new float[100];
    arr3 = new float[100];
    arr4 = new float[100];
    arr5 = new float[100];
}

fileReader::fileReader(int maxSize, string file_arg) //overloaded constructor, contains bulk of code
{
    arr1 = new float[maxSize];
    arr2 = new float[maxSize];
    arr3 = new float[maxSize];
    arr4 = new float[maxSize];
    arr5 = new float[maxSize];
    string line;

    inf.open(file_arg);
    getline(inf, line); //we've already read the first line in the main

    for(int i = 0 ; i<maxSize ; i++) //reads through file
    {
        getline(inf, line);
        float temp = stof(line); //records value as float
        arr1[i] = temp;
        arr2[i] = temp;
        arr3[i] = temp;
        arr4[i] = temp;
        arr5[i] = temp;
    }
    inf.close();


    cout<<"\nQuick Sort: "<<endl;
    auto start = chrono::high_resolution_clock::now(); //quick sort is recursive, so the time signature couldn't be printed within its method
    timer=time(NULL);
    cout<<"Time quick sort started: "<<ctime(&timer)<<endl;
    quickSort(arr1, 0, maxSize - 1);
    auto end = chrono::high_resolution_clock::now();
    timer=time(NULL);
    cout<<"Time quick sort ended: "<<ctime(&timer)<<endl;
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout<<"The time to run quick sort is: "<<duration.count()<<" microseconds."<<endl<<endl;


    cout<<"\nMerge Sort: "<<endl;
    auto start = chrono::high_resolution_clock::now(); //merge sort is also recursive
    timer=time(NULL);
    cout<<"Time merge sort started: "<<ctime(&timer)<<endl;
    mergeSort(arr2, 0, maxSize-1);
    auto end = chrono::high_resolution_clock::now();
    timer=time(NULL);
    cout<<"Time merge sort ended: "<<ctime(&timer)<<endl;
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout<<"The time to run merge sort is: "<<duration.count()<<" microseconds."<<endl<<endl;

    
    cout<<"\nBubble Sort: "<<endl;
    bubbleSort(arr3, maxSize);


    cout<<"\nInsert Sort: "<<endl;
    insertSort(arr4, maxSize);


    cout<<"\nSelection Sort: "<<endl;
    selectionSort(arr5, maxSize);


    bool correct = false; //tracks whether all arrays are the same
    int index; //tracks index of array where error happened
    for(int i =0; i<maxSize;i++)
    {
        if(arr1[i] == arr2[i] && arr2[i] == arr3[i] && arr3[i] == arr4[i] && arr4[i] == arr5[i])
            correct = true;
        else
        {
            correct = false;
            index = i;
            break;
        }
    }
    if(correct)
    {
        ofstream outf;
        outf.open("Ordered.txt");
        outf<<maxSize<<endl;
        for(int j=0; j<maxSize; j++) //writes out array to ordered.txt
            outf<<arr1[j]<<endl;
    }
    else //if the arrays aren't sorted equally
        cout<<"Not all methods correctly sorted the file. There was an error at line: "<<index<<endl;
}


fileReader::~fileReader()
{
    delete arr1;
    delete arr2;
    delete arr3;
    delete arr4;
    delete arr5;
}

void fileReader::quickSort(float array[], int front, int back)

{
    int p_index, x, y;
    float temp;
    if(front < back)
    {
        p_index = front; // pivot
        x = front;
        y = back;

        while(x < y) //compares array working outside in
        {
            while(array[x] <= array[p_index] && x<back)
                x++;

            while(array[y] > array[p_index])
                y--;

            if(x < y)
            {
                temp = array[x]; //swaps elements of x and y
                array[x] = array[y];
                array[y] = temp;
            }
        }

        temp = array[p_index]; //swaps elements of p_index and y
        array[p_index] = array[y];
        array[y] = temp;

        quickSort(array, front, y-1); //calls quicksort from front to before pivot
        quickSort(array, y+1, back); //calls quicksort from one after pivot to end
    }

}


void fileReader::mergeSort(float array[], int front, int back)
{
    int len = back - front;

    if(front < back)
    {
        int mid = front + len/2;

        mergeSort(array, front, mid);//sorts first half of array
        mergeSort(array, mid+1, back);//sorts second half of array
        merge(array, front, mid, back);//joins two arrays
    }

}

void fileReader::merge(float array[], int front, int mid, int back)
{
    int leftSize = mid - front + 1;
    int rightSize = back - mid;

    float left[leftSize]; //left hand array
    float right[rightSize]; //right hand array

    for(int i = 0; i<leftSize; ++i)
        left[i] = array[i + front]; //assigns array values for left side
    for(int j = 0; j<rightSize; ++j)
        right[j] = array[j + mid + 1];//assigns array values for right side

    int l = 0;
    int r = 0;
    int index = front;

    while(l < leftSize && r < rightSize)
    {
        if(left[l] <= right[r])
            array[index++] = left[l++];//if left is smaller moves low value to front of main array, increments indeces
        else
            array[index++] = right[r++];//if right is smaller moves low value to front of main array, increments indeces
    }
    while (l < leftSize)//in case there more left in the left array
        array[index++] = left[l++];

    while(r < rightSize)//in case theres more values left in the right array
        array[index++] = right[r++];


}

void fileReader::bubbleSort(float array[], int len)
{
    auto start = chrono::high_resolution_clock::now();
    timer=time(NULL);
    cout<<"Time bubble sort started: "<<ctime(&timer)<<endl;
    for(int i =0; i<len ; i++)
    {
        float temp = 0;
        for(int j = 0; j<len-1 ; ++j)
        {
            if(array[j] > array[j+1])
            {
                temp = array[j+1];
                array[j+1] = array[j];
                array[j] = temp;
            }
        }
    }


    auto end = chrono::high_resolution_clock::now();
    timer=time(NULL);
    cout<<"Time bubble sort ended: "<<ctime(&timer)<<endl;
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout<<"The time to run bubble sort is: "<<duration.count()<<" microseconds."<<endl<<endl;
}

void fileReader::insertSort(float array[] , int len)
{
    auto start = chrono::high_resolution_clock::now();
    timer=time(NULL);
    cout<<"Time insert sort started: "<<ctime(&timer)<<endl;
    for(int j = 0 ; j<len ; j++)
    {
        float temp = array[j];
        int k = j;
        while(k>0 && array[k-1] >= temp)
        {
            array[k] =array[k-1];
            --k;
        }
        array[k] = temp;
    }

    auto end = chrono::high_resolution_clock::now();
    timer=time(NULL);
    cout<<"Time insert sort ended: "<<ctime(&timer)<<endl;
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout<<"The time to run insert sort is: "<<duration.count()<<" microseconds."<<endl<<endl;
}


void fileReader::selectionSort(float array[], int len)
{
    float temp;
    int minIndex;
    auto start = chrono::high_resolution_clock::now();
    timer=time(NULL);
    cout<<"Time selection sort started: "<<ctime(&timer)<<endl;
    for(int i=0; i<len-1 ; ++i)
    {
        minIndex = i;
        for(int j = i+1 ; j<len ; ++j)
        {
            if(array[j] < array[minIndex])
                minIndex = j;
        }
        if(minIndex != i)
        {
            temp = array[i];
            array[i] = array[minIndex];
            array[minIndex] = temp;
        }
    }



    auto end = chrono::high_resolution_clock::now();
    timer=time(NULL);
    cout<<"Time selection sort ended: "<<ctime(&timer)<<endl;
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout<<"The time to run selection sort is: "<<duration.count()<<" microseconds."<<endl<<endl;
}
