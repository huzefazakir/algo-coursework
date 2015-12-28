#include <iostream>
#include <unordered_set>
#include <stdint.h>
#include <fstream>
#include <vector>
#include <stdint.h>

using namespace std;

int main (int argc, char * argv[])
{
    if (argc != 5) {
        cout << "Usage: twosum <input file> <number of entries> <min> <max>" << endl;
        return -1;
    }

    uint64_t numOfEntries = atoi(argv[2]);
    unordered_set<int64_t> entryLookupHashTbl;
    vector<int64_t> inputArr;
    ifstream numFile;
    numFile.open(argv[1]);
    int64_t num = 0;
    int64_t index = 0;
    int64_t count = 0;
    int64_t min = atoi(argv[3]);
    int64_t max = atoi(argv[4]);
    unordered_set<int64_t>::iterator got;


    if (numFile.is_open()) {
        while(!numFile.eof()) {
            numFile >> num;
            if ( index == 0  ||  (entryLookupHashTbl.find(num) == entryLookupHashTbl.end())) {
                entryLookupHashTbl.insert(num);
                inputArr.push_back(num);
                cout << "num " << num << "inserted" << endl;      
                //index++;
            }
            
            cout << "num " << num << "discarded" << endl;
            index++;
            if (index >= numOfEntries)
                break;
            //cout << "index: " << index << endl;
        }
    } else {
        cout << "error opening file :" << argv[1] << endl;
    }

    cout << "done reading file" << endl;

    for (int64_t i = min; i <= max; i++) {
    
        for (vector<int64_t>::iterator itr = inputArr.begin(); itr != inputArr.end(); itr++) {
            if ( (got = entryLookupHashTbl.find((i - (*itr)))) != entryLookupHashTbl.end()) {
               
                cout <<"got: " << (*got) << " itr: " << (*itr) << " i: " << i <<endl; 
                //cout <<"sum :" << (*got) + (*itr) << endl;
                if ((*got) != (*itr)) {
                    count++;
                    cout <<"sum :" << (*got) + (*itr) << endl;
                    break;
                }
            }
        }
    }

    cout << "count: " << count << endl;
    //cout << "count: " << count/2 << endl;      
}
