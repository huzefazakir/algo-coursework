#include <iostream>
#include <list>
#include <fstream>
#include <math.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <string>
#include <sstream>
#include <unistd.h>

using namespace std;
int totalNumOfEntries;
int randomContraction (list<int> alist[], int numOfEntries) {

    if (numOfEntries == 2) {
        return alist[1].size();
    }

    //srand (time(NULL));
    int u, v;
    while (true) {
        u = rand() % (totalNumOfEntries + 1);
        v = rand() % (totalNumOfEntries + 1);

        //cout << "u: " << u << " v: " << v << endl;
        if (u == v) { 
            //cout << "u = v" << endl;
            continue;
        }

        if (alist[v].size() == 0 || alist[u].size() == 0) {
            //cout << "u or v is empty" << endl;
            continue;
        }
    
        list<int>::iterator it;

        for (it=alist[v].begin(); it != alist[v].end(); ++it) {
            if (*it == u)
                break;
              
        }
        
        if (it != alist[v].end())
            break;
        
    }
 
    //cout << "-->u: " << u << " v: " << v << endl;
    list<int>::iterator it;

    int remove, contract;
    if (u > v) {
        remove = u;
        contract = v; 
    } else {
        contract = u;
        remove = v;
    }

    /*for (int i=1; i <= totalNumOfEntries; i++) {
        cout << "--> before alist[" << i << "]:";
        for (list<int>::iterator itr = alist[i].begin(); itr != alist[i].end(); itr++)
            cout << *itr << " ";

        cout << endl;
    }*/


    alist[contract].remove(remove);
    alist[remove].remove(contract);
    
    /*for (int i=1; i <= totalNumOfEntries; i++) {
        cout << "--> before alist[" << i << "]:";
        for (list<int>::iterator itr = alist[i].begin(); itr != alist[i].end(); itr++)
            cout << *itr << " "; 
            
        cout << endl;
    }*/


    for (it = alist[remove].begin(); it != alist[remove].end(); it++) {
        //cout << "---->it: " << *it << endl;
        alist[*it].push_back(contract);
        alist[*it].remove(remove);
    }
    

    it = alist[contract].end();
    alist[contract].splice(it, alist[remove]);
    alist[remove].erase(alist[remove].begin(), alist[remove].end());

    /*for (int i=1; i <= totalNumOfEntries; i++) {
        cout << "--> after alist[" << i << "]:";
        for (list<int>::iterator itr = alist[i].begin(); itr != alist[i].end(); itr++)
            cout << *itr << " ";

        cout << endl;
    }*/
 
    return randomContraction(alist, numOfEntries - 1);     
       

}

int main (int argc, char * argv[]) {

    if (argc != 3) {
        cout << "Usage: InversionCounter <input file> <number of entries>" << endl;
        return -1;
    }

    ifstream numFile;
    numFile.open(argv[1]);

    int mincut = -1;
    int cut = -1;
    int index = 0;
    int numOfEntries = atoi(argv[2]);
    totalNumOfEntries = numOfEntries;
    list<int> alist[numOfEntries + 1];
    list<int> blist[numOfEntries + 1];
    string line;   

    if (numFile.is_open()) {

    while (getline (numFile, line)) {
        std::istringstream iss(line);
        int n;
        int i = 0;
        int vertex = 0;

        while (iss >> n)
        {
            if (i == 0)
                vertex = n;
            else {
                alist[vertex].push_back(n);
                blist[vertex].push_back(n);
            }
            i++;
        }
    }

    /*for (int i=1; i <= numOfEntries; i++) {
        cout << "alist[" << i << "]:";
        for (list<int>::iterator it = alist[i].begin(); it != alist[i].end(); it++)
            cout << *it << " ";

        cout << endl;
    }*/

    } else {
        cout << "error opening file :" << argv[1] << endl;
    }

    int repeat = numOfEntries * numOfEntries * (int)ceil(log(numOfEntries));

    //cout <<"repeat: " << repeat << endl;   
    for (int i = 0; i <= repeat; i++) {
        //usleep (100);
        srand (i);
        cut = randomContraction(alist, numOfEntries);
        //cout << "cut: " << cut << " i " << i << endl;

        if (cut < mincut || mincut == -1)
            mincut = cut;

        for (int u=1; u<=numOfEntries; u++)
            alist[u].assign(blist[u].begin(), blist[u].end());

    }

    cout << "mincut: " << mincut << endl;

}
