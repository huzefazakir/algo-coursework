#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdint.h>
using namespace std;

void MergeAndCountSplitInv (int array[], int sarray[], int start, int middle, int end, uint64_t & count) {

    int i = start;
    int j = middle + 1;
    
    for (int k=start; k<=end; k++) {

        if (j > end) {
            sarray[k] = array[i];
            i++;
            continue;
        } 

        if (i > middle) {
            sarray[k] = array[j];
            j++;
            continue;
        }

        if (array[i] > array[j]) {
            sarray[k] = array[j];
            count += middle - i + 1;
            j++;
        } else {
            sarray[k] = array[i];
            i++;
        }

    }

    for (int k = 0; k<=end; k++) {
        array[k] = sarray[k];
    }
    
}


void SortArrayAndCountInv(int array[], int sarray[], int start, int end, uint64_t & count)
{
    if (start < end) {
        int middle = (start+end)/2;
        SortArrayAndCountInv(array, sarray, start, middle, count);
        SortArrayAndCountInv(array, sarray, middle+1, end, count);
        MergeAndCountSplitInv(array, sarray, start, middle, end, count);

    }
}


int main (int argc, char* argv[]) {
    if (argc != 3)
        cout << "Usage: InversionCounter <input file> <number of entries>" << endl;

    ifstream numFile;
    numFile.open(argv[1]);

    int index = 0;
    int numOfEntries = atoi(argv[2]);
    int numArray[numOfEntries];
    int sarray[numOfEntries];
    
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

    uint64_t inversions = 0;
    SortArrayAndCountInv(numArray, sarray, 0, numOfEntries-1, inversions);
    cout << "Number of Inversions: " << inversions << endl;
    return 0; 
}

