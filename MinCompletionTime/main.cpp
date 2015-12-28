#include <iostream>
#include <fstream>
#include <sstream>
#include <stdint.h>
#include <queue>          // std::priority_queue
#include <vector>         // std::vector
using namespace std;

class job {
    bool m_ratio;

public:
    job(bool ratio = true): m_ratio(ratio) {}
    double length;
    double weight;

    bool operator() (const job& lhs, const job& rhs) const
    {
        double lhsDiff = 0; 
        double rhsDiff = 0;

        if (!m_ratio) {
            lhsDiff = lhs.weight - lhs.length;
            rhsDiff = rhs.weight - rhs.length;
        } else {
            lhsDiff = lhs.weight/lhs.length;
            rhsDiff = rhs.weight/rhs.length;
        }

        if (rhsDiff == lhsDiff) {
            return (lhs.weight < rhs.weight);
        } else {
            return (lhsDiff < rhsDiff);
        } 
    }
};

uint64_t MinCompTime (priority_queue<job, vector<job>, job> &jobQueue) {
    
    uint64_t minCompTime = 0;
    uint64_t aggLength = 0;

    while (!jobQueue.empty()) {
        job wJob = jobQueue.top();
        aggLength += wJob.length;
        minCompTime += wJob.weight * aggLength;
        jobQueue.pop(); 
    }

    return minCompTime; 
    
}

int main (int argc, char* argv[]) {

    if (argc != 2) {
        cout << "Usage: mincompletiontime <input file>" << endl;
        return -1;
    }

    ifstream numFile;
    string line;
    numFile.open(argv[1]);
    job wJob;
    uint32_t numOfEntries = 0;
    uint32_t i = 0;
    priority_queue<job, vector<job>, job> jobQueue;

    if (numFile) {

        while (getline (numFile, line)) {
            std::istringstream iss(line);
            uint32_t n;
            uint8_t j = 0;
            
            while (iss >> n) {
                if (i == 0) {
                    numOfEntries = n;
                    cout << "num of entries: " << numOfEntries <<endl;     
                } else {
                    if (j == 0) {
                        wJob.weight = n;
                    } else {
                        wJob.length = n;
                    }
                }
                j++;
            }

            if (i != 0)
                jobQueue.push(wJob);
                
            i++;
        }

    } else {
         cout << "error opening file :" << argv[1] << endl;
            return -1;
    }

    cout << "minimum completion time: " << MinCompTime(jobQueue) << endl;


    /*for (uint32_t index = 0; index < numOfEntries; index++) {
        cout << "jobs[" << index <<"].weight: " << jobs[index].weight << " jobs[" << index << "].length: " << jobs[index].length << endl;
    }*/
    
}
