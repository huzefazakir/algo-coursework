#include <iostream>
#include <list>
#include <fstream>
#include <stdint.h>
#include <stdlib.h>
#include <sstream>

using namespace std;

uint32_t t = 0;
uint32_t s = 0;


void DFS(list<uint32_t> alist[], uint32_t node, bool explored[], uint32_t finishTime[], uint32_t leader[], uint32_t pass) {

    explored[node] = true;
    if (pass == 2)
        leader[s]++;

    for (list<uint32_t>::iterator itr = alist[node].begin(); itr != alist[node].end(); itr++) {
        if (explored[*itr] ==  false) {
            DFS(alist, *itr, explored, finishTime, leader, pass);
        } 
    }    
    
    if (pass == 1) {
        t++; 
        finishTime[t] = node;
    }
    
}

void sscComputation(list<uint32_t> alist[], list<uint32_t> rlist[], uint32_t numOfEntries) {

   bool * explored = new bool[numOfEntries + 1]; 
   uint32_t * finishTime = new uint32_t[numOfEntries + 1];
   uint32_t * leader = new uint32_t[numOfEntries + 1];

    for (uint32_t i = 0; i <= numOfEntries; i++) {
        explored[i] = false;
        finishTime[i] = 0;
        leader[i] = 0;
    }

    for (uint32_t node = numOfEntries; node >= 1; node--) {
        if (explored[node] == false) {
            s = node;
            DFS(rlist, node, explored, finishTime, leader, 1);
        }
    }

    for (uint32_t i = 0; i <= numOfEntries; i++) {
        explored[i] = false;
        //cout << "finishTime[" << i << "]: " << finishTime[i] << endl; 
    }

    for (uint32_t index = numOfEntries; index >= 1; index--) {
        uint32_t node = finishTime[index];
        if (explored[node] == false) {
            s = node;
            DFS(alist, node, explored, finishTime, leader, 2);
        }
    }

    uint32_t first, second, third, fourth, fifth;
    first = second = third = fourth = fifth = 0;

    /*for (uint32_t i = 1; i <= numOfEntries; i++) {
        cout << "leader[" << i << "]: " << leader[i] << endl;
    }*/

    for (uint32_t j = 1; j <= numOfEntries; j++) {
        if (leader[j] > first) {
            fifth = fourth;
            fourth = third;
            third = second;
            second = first;
            first = leader[j]; 
        } else if (leader[j] > second) {
            fifth = fourth;
            fourth = third;
            third = second;
            second = leader[j];    
        } else if (leader[j] > third) {
            fifth = fourth;
            fourth = third;
            third = leader[j];
        } else if (leader[j] > fourth) {
            fifth = fourth;
            fourth = leader[j];
        } else if (leader[j] > fifth) {
            fifth = leader[j];
        }
    }

    cout << first << ", " << second << ", " << third << ", " << fourth << ", " << fifth <<endl;

    delete [] explored;
    delete [] finishTime;
    delete [] leader;

} 

int main (int argc, char * argv[]) {

    if (argc != 3) {
        cout << "Usage: InversionCounter <input file> <number of entries>" << endl;
        return -1;
    }

    ifstream numFile;
    string line;
    numFile.open(argv[1]);

    uint32_t numOfEntries = atoi(argv[2]);
    list<uint32_t> * alist = new list<uint32_t>[numOfEntries + 1];
    list<uint32_t> * rlist = new list<uint32_t>[numOfEntries + 1];

    if (numFile.is_open()) {

        while (getline (numFile, line)) {
            std::istringstream iss(line);
            uint32_t n;
            uint32_t i = 0;
            uint32_t vertex = 0;
            uint32_t rvertex = 0;

            while (iss >> n) {
                if (i == 0) {
                    vertex = n;
                    //rnode = n;
                    //list[vertex].push_back(n);
                } else {
                    rlist[n].push_back(vertex);
                    alist[vertex].push_back(n);
                }

                i++;
            }
        }
    
    } else {
        cout << "error opening file :" << argv[1] << endl;
    }


    /*for (uint32_t i=1; i <= numOfEntries; i++) {
        cout << "alist[" << i << "]:";
        for (list<uint32_t>::iterator it = alist[i].begin(); it != alist[i].end(); it++)
            cout << *it << " ";

        cout << endl;
    }

    for (uint32_t i=1; i <= numOfEntries; i++) {
        cout << "rlist[" << i << "]:";
        for (list<uint32_t>::iterator it = rlist[i].begin(); it != rlist[i].end(); it++)
            cout << *it << " ";

        cout << endl;
    }*/


    
    sscComputation(alist, rlist, numOfEntries);

    delete [] alist;
    delete [] rlist;
 
}
