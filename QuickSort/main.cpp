#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdint.h>
using namespace std;

uint32_t ChoosePivot(int array[], int entryCount, int hi, int lo){

    int n = 2;
    if (n == 0)
        return lo;
    else if (n == 1) 
        return hi;
    else {
        int mid =0;
        if (entryCount%2 == 0)
            mid = (hi + lo)/2;
        else 
            mid = (hi + lo)/2;

        int retval = 0;

        if (array[hi] > array[mid]) {
            if (array[hi] > array[lo]) {
                if (array[lo] > array[mid])
                    retval = lo;
                else
                    retval = mid;
            } else {
                retval = hi;
            }
        } else {
            if (array[mid] > array[lo]){
                if (array[hi] > array[lo])
                    retval = hi;
                else
                    retval = lo;
            } else {
                retval = mid;
                
            }
        }
            
        return retval;
    }
}


uint32_t PartitionArray(int array[], int entryCount, int hi, int lo, int pivotIndex) {

    /*int temp1 = array[pivotIndex];
    array[pivotIndex] = array[0];
    array[0] = temp1;

    pivotIndex = 0; */
      
    int pivot = array[pivotIndex];
    int i = pivotIndex + 1;
    for(int j = pivotIndex+1; j <= hi; j++) {
        if (pivot > array[j]) {
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++;
        }
    }
    
    /*cout << "pivotIndex: " << pivotIndex << endl;
    cout << "pivot" << pivot << endl;
    cout << "array[i-1] " << array[i-1] << endl;
    cout << "array[pivotIndex] " << array[pivotIndex] << endl;*/
    int temp = array[pivotIndex];
    array[pivotIndex] = array[i-1];
    array[i-1] = temp;

    for (int i = lo; i <= hi; i++)
        cout << "array["<< i <<"]: " << array[i] << endl;
    return (i-1);

    //cout << "Partitioning" << endl;
   /* int pivot = array[pivotIndex];
    int i = pivotIndex - 1;
    for(int j = pivotIndex-1; j >= lo; j--) {
        //cout << i << ", " << j << endl;
        if (pivot < array[j]) {
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i--;
        }
    }

    //cout << "swapping" << endl;
    int temp = array[pivotIndex];
    array[pivotIndex] = array[i+1];
    array[i+1] = temp;
    return (i+1);*/
    
}



void QuickSort(int array[], int entryCount, int hi, int lo, uint64_t & comparisons) {

    if (entryCount <= 1)
        return;

    cout << "entryCount: " << entryCount << " hi: " << hi << " lo: " << lo << " comparisons: " << comparisons << endl;

    int index = ChoosePivot(array, entryCount, hi, lo);

    cout << "index: " << index << endl;
    int temp1 = array[index];
    array[index] = array[lo];
    array[lo] = temp1;
    index = lo;

    int pivotIndex = PartitionArray(array, entryCount, hi, lo, index);
    comparisons += entryCount -1;
    QuickSort(array, (pivotIndex - lo), (pivotIndex-1), lo, comparisons);
    QuickSort(array, (hi - pivotIndex), hi, (pivotIndex +1), comparisons);
    
}


int main (int argc, char* argv[]) {
    if (argc != 3)
        cout << "Usage: InversionCounter <input file> <number of entries>" << endl;

    ifstream numFile;
    numFile.open(argv[1]);

    int index = 0;
    int numOfEntries = atoi(argv[2]);
    int numArray[numOfEntries];

    if (numFile.is_open()) {
        while(!numFile.eof()) {
            numFile >> numArray[index];
            index++;

            if (index >= numOfEntries)
                break;
        }
    } else {
        cout << "error opening file :" << argv[1] << endl;
    }

    uint64_t comparisons = 0;
    QuickSort(numArray, numOfEntries,(numOfEntries -1), 0, comparisons);
   
    for (int i = 0; i < numOfEntries; i++)
        cout << "numArray["<< i <<"]: " << numArray[i] << endl;   
    cout << "Number of comparisons: " << comparisons << endl;
    return 0;
}

