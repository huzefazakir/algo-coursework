#include <iostream>
#include <list>
#include <fstream>
#include <stdlib.h>     /* srand, rand */
#include <sstream>
#include <stdint.h>
using namespace std;

struct directedEdge {
    uint32_t vertex;
    uint32_t distance;
};

void dsp(list<directedEdge> alist[], list<uint32_t> xlist, int pathlength[], int numOfEntries) {


    if (xlist.size() == numOfEntries)
        return;

    directedEdge nextEdge;
    int minDist = -1;

    for(list<uint32_t>::iterator itr = xlist.begin(); itr != xlist.end(); itr++) {
        for (list<directedEdge>::iterator edgeItr = alist[*itr].begin(); edgeItr != alist[*itr].end(); edgeItr++) {
            if (pathlength[(*edgeItr).vertex] == 1000000) {
                if ((minDist == -1) || (((*edgeItr).distance + pathlength[*itr]) < minDist)) {
                    minDist = (*edgeItr).distance + pathlength[*itr];
                    nextEdge.vertex = (*edgeItr).vertex;
                    nextEdge.distance = (*edgeItr).distance + pathlength[*itr];
                }
            }
        }
    }

    xlist.push_back(nextEdge.vertex);

    //cout << "next edge vertex: " << nextEdge.vertex << endl;
    //cout << "pathlength: " << nextEdge.distance << endl;
    pathlength[nextEdge.vertex] = nextEdge.distance;
    dsp(alist, xlist, pathlength, numOfEntries);

}
int main (int argc, char * argv[]) {

    if (argc != 3) {
        cout << "Usage: DSP <input file> <number of entries>" << endl;
        return -1;
    }

    ifstream numFile;
    string line;
    numFile.open(argv[1]);

    int numOfEntries = atoi(argv[2]);
    list<directedEdge> alist[numOfEntries + 1];
    list<uint32_t> xlist;
    int pathlength[numOfEntries + 1];

    for (uint32_t i = 0; i <= numOfEntries; i++)
        pathlength[i] = 1000000;

    if (numFile) {

        while (getline (numFile, line)) {
            std::istringstream iss(line);
            int n;
            int i = 0;
            int vertex = 0;
            char t;
            directedEdge edge;

            while (iss >> n)
            {
                if (i == 0)
                    vertex = n;
                else if ((i%2) == 1) {
                    edge.vertex = n;
                    iss >> t;
                } else {
                    edge.distance = n; 
                    alist[vertex].push_back(edge);
                    //cout << "vertex: " << vertex << " edge.vertex: " << edge.vertex << " edge.distance: " << edge.distance << endl;
                }
               
                i++;
            }
        }

    /*for (int i=1; i <= numOfEntries; i++) {
        cout << "alist[" << i << "]:    ";
        for (list<directedEdge>::iterator it = alist[i].begin(); it != alist[i].end(); it++)
            cout << (*it).vertex << "," << (*it).distance << "    ";

        cout << endl;
    }*/

    

    } else {
        cout << "error opening file :" << argv[1] << endl;
    }

    xlist.push_back(1);
    pathlength[1] = 0;
    dsp(alist, xlist, pathlength, numOfEntries);

    /*for (uint32_t i = 1; i <= numOfEntries; i++)
        cout << "pathlength[" << i << "]: " << pathlength[i] << endl;*/

    cout << "pathlength[7]" << pathlength[7] << endl;
    cout << "pathlength[37]" << pathlength[37] << endl;
    cout << "pathlength[59]" << pathlength[59] << endl;
    cout << "pathlength[82]" << pathlength[82] << endl;
    cout << "pathlength[99]" << pathlength[99] << endl;
    cout << "pathlength[115]" << pathlength[115] << endl;
    cout << "pathlength[133]" << pathlength[133] << endl;
    cout << "pathlength[165]" << pathlength[165] << endl;
    cout << "pathlength[188]" << pathlength[188] << endl;
    cout << "pathlength[197]" << pathlength[197] << endl;










}
