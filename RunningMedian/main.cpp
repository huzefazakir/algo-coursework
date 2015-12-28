#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdint.h>
#include <queue>          // std::priority_queue
#include <vector>         // std::vector

using namespace std;

class mycomparison {
    public: 
        mycomparison(const bool & reverse=false) {reverse_ = reverse;}
        bool operator() (const uint32_t& lhs, const uint32_t& rhs) const {
            if (reverse_) return (lhs > rhs);
            else return (lhs < rhs);
        }
    private:
        bool reverse_;
};

int main (int argc, char* argv[]) {

    if (argc != 2) {
        cout << "Usage RunningMedian <input file>" << endl;
        exit(-1);
    }

    ifstream numFile;
    numFile.open(argv[1]);
    uint32_t x = 0;
    uint32_t lowHeapSize = 0;
    uint32_t highHeapSize = 0;
    uint32_t lowMax = 0;
    uint32_t highMin = 0;
    uint32_t medianSum = 0;
    uint32_t count = 0;

    priority_queue<uint32_t, vector<uint32_t>, mycomparison> highHeap(mycomparison(true));
    priority_queue<uint32_t> lowHeap;    

    if (numFile.is_open()) {
        while( numFile >> x) {

            lowHeapSize = lowHeap.size();
            highHeapSize = highHeap.size();

            if (lowHeapSize == 0 && highHeapSize == 0) {
                count = x;
                lowHeap.push(x);
            } else if (lowHeapSize != 0 && highHeapSize == 0) {
                lowMax = lowHeap.top();
                lowHeap.pop();

                if (lowMax > x) {
                    count += x;
                    lowHeap.push(x);
                    highHeap.push(lowMax);
                } else {
                    count+=lowMax;
                    lowHeap.push(lowMax);
                    highHeap.push(x);
                }
                
            } else if (lowHeapSize == 0 && highHeapSize != 0) {
                highMin = highHeap.top();
                highHeap.pop();

                if (highMin > x) {
                    count += x;
                    lowHeap.push(x);
                    highHeap.push(highMin);
                } else {
                    count+=highMin;
                    lowHeap.push(highMin);
                    highHeap.push(x);
                }
            } else {
                lowMax = lowHeap.top();
                highMin = highHeap.top();

                lowHeap.pop();
                highHeap.pop();

                if (lowMax > x) {

                    if (lowHeapSize > highHeapSize) {
                        highHeap.push(highMin);
                        highHeap.push(lowMax);
                        lowHeap.push(x);
                    } else {
                        highHeap.push(highMin);
                        lowHeap.push(lowMax);
                        lowHeap.push(x);
                    }

                } else if (x > highMin) {

                    if (lowHeapSize > highHeapSize) {
                        highHeap.push(highMin);
                        highHeap.push(x);
                        lowHeap.push(lowMax);
                    } else {
                        highHeap.push(x);
                        lowHeap.push(lowMax);
                        lowHeap.push(highMin);
                    }                  
                } else {
                    
                    if (lowHeapSize > highHeapSize) {
                        highHeap.push(highMin);
                        highHeap.push(x);
                        lowHeap.push(lowMax);
                    } else {
                        highHeap.push(highMin);
                        lowHeap.push(lowMax);
                        lowHeap.push(x);
                    }
                }
                
                count+=lowHeap.top();
            }
            
            cout << "count: " << count << endl;
            cout << endl;
            
        }
    } else {
        cout << "error opening file :" << argv[1] << endl;
    }
        
}
