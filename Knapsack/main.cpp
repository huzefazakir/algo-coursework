#include <iostream>
#include <vector>
#include <stdint.h>
#include <fstream>
#include <sstream>
#include <stdlib.h>


using namespace std;

struct item {
    uint32_t value;
    uint32_t weight;
};


uint32_t max(uint32_t & x1, uint32_t & x2)
{
    if (x1 > x2)
        return x1;

    return x2;
}

int main (int argc, char* argv[])
{

    if (argc != 4) {
        cout << "Usage: knapsack <input file> <knapsack size> <num of items>" << endl;
        return -1;
    }

    uint32_t kSize = atoi(argv[2]);
    uint32_t iSize = atoi(argv[3]);

    vector<item> items;

    ifstream numFile;
    string line;
    numFile.open(argv[1]);

    if (numFile) {
        getline (numFile, line);

        while (getline(numFile, line)) {
        
            std::istringstream iss(line);
            uint32_t n = 0;
            uint32_t j = 0;
            item tmpItem;
        
            while (iss >> n) {
                if (j == 0) 
                    tmpItem.value = n;
                else
                    tmpItem.weight = n;

                j++;
            }

            j = 0;
            items.push_back(tmpItem);
        }

    } else{
        cout << "error opening file :" << argv[1] << endl;
        return -1;

    }



    uint64_t * v1 = new uint64_t [kSize+1];
    uint64_t * v2 = new uint64_t [kSize+1];
    uint64_t wt = 0;

    uint64_t *val1 = v1;
    uint64_t *val2 = v2;

    for (uint64_t size = 0; size <= kSize; size++) {
        val1[size] = 0;
        val2[size] = 0;
    }


    for (uint64_t i = 1; i <= iSize; i++) {
         for (uint64_t x = 0; x <= kSize; x++) {
            if (items[i-1].weight > x) {
                continue;
            }
            else {
                if (x == items[i-1].weight) {
                    if (val1[x] < items[i-1].value) {
                        val2[x] = items[i-1].value;
                    }
                } else {
                    wt = x - items[i-1].weight;
                    if ((val1[wt] + items[i-1].value) > val1[x]) {
                        val2[x] = (val1[wt] + items[i-1].value);
                        
                    }  
                }
                                        
            }
                
         }

        for (uint64_t size = 0; size <= kSize; size++) {
                //cout << "val1[" << size << "]:" << val1[size] << endl;
                //cout << "val2[" << size << "]: " << val2[size] << endl;
                val1[size] = val2[size];
        }
    } 
  
    //for (uint64_t size = 0; size <= kSize; size++)
        //cout << "val3[" << size << "]: " << val[size] << endl; 
    //cout << "sol: " << A[iSize][kSize] << endl;
    cout << "sol: " << val1[kSize] << endl;

    //for (vector<item>::iterator itr = items.begin(); itr != items.end(); itr++)
        //cout << "value = " << itr->value << " weight: " << itr->weight << endl;

    delete [] v1;
    delete [] v2;
    
}

