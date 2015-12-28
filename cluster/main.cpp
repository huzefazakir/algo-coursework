#include <iostream>
#include <queue>
#include <stdint.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdlib.h>

using namespace std;

struct node {
    uint32_t cluster;
    uint32_t size;
};

class edge {
    
public:
    uint32_t firstVertex;
    uint32_t secondVertex;
    uint32_t distance;

    bool operator() (const edge& lhs, const edge& rhs) const {
        return (lhs.distance > rhs.distance);
    }
};


void merge(uint32_t cluster1, uint32_t cluster2, uint32_t vertexCount, node nodes[]) {

    uint32_t leader = 0;
    uint32_t follower = 0;

    if (nodes[cluster1].size > nodes[cluster2].size) {
        leader = cluster1;
        follower = cluster2;
    } else {
        leader = cluster2;
        follower = cluster1;
    }

    for (uint32_t vertex = 1; vertex <= vertexCount; vertex++) {

        if (nodes[vertex].cluster == follower){
            nodes[vertex].cluster = leader;
            nodes[leader].size++;
            nodes[follower].size--;
        }
    
        if (nodes[follower].size == 0)
            break;

    }

    //cout << "leader: " << leader << " follower: " << follower << " follower size: " << nodes[follower].size << " leader Size: " <<  nodes[leader].size << endl;    
}

uint32_t maxClusterSpacing(priority_queue<edge, vector<edge>, edge> &edges, uint32_t clusterCount, uint32_t finalClusterCount, uint32_t vertexCount, node nodes[]) {

    edge cEdge;
    while (clusterCount != (finalClusterCount-1)) {
        cEdge = edges.top();
        //cout << "first vertex: " << cEdge.firstVertex << " second vertex: " << cEdge.secondVertex << " distance: " << cEdge.distance << endl;
        if (nodes[cEdge.firstVertex].cluster != nodes[cEdge.secondVertex].cluster) {
            merge(nodes[cEdge.firstVertex].cluster, nodes[cEdge.secondVertex].cluster, vertexCount, nodes);
            clusterCount--;
        }

        edges.pop();
        //cout << "clusterCount: " << clusterCount << endl;
    }


    return (cEdge.distance);

        
}

int main (int argc, char* argv[])
{

    if (argc != 3) {
        cout << "Usage: cluster <input file> <cluster count>" << endl;
        return -1;
    }

    ifstream numFile;
    string line;
    numFile.open(argv[1]);

    uint32_t clusterCount, numOfEntries = 0;
    uint32_t finalClusterCount = atoi(argv[2]);
    uint32_t i = 0;
    priority_queue<edge, vector<edge>, edge> edges;
    edge cEdge;
    node *nodes;

    if (numFile) {

        while (getline (numFile, line)) {
            std::istringstream iss(line);
            uint32_t n;
            uint8_t j = 0;

            while (iss >> n) {
                if (i == 0) {
                    clusterCount = numOfEntries = n;
                    cout << "num of entries: " <<  clusterCount<< endl;
                    cout << "final cluster count: " << finalClusterCount << endl;
                    nodes = new node[clusterCount + 1]; 

                    for (uint32_t index = 1; index <= clusterCount; index++) {
                        nodes[index].cluster = index;
                        nodes[index].size = 1;
                    }

                } else {
                    if (j == 0)
                        cEdge.firstVertex = n; 
                    else if (j == 1)
                        cEdge.secondVertex = n;
                    else
                        cEdge.distance = n;                        
                }
                j++;
            }

            if (i != 0) {
                edges.push(cEdge);
                //cout << i << ". " << cEdge.firstVertex << " " << cEdge.secondVertex << " " << cEdge.distance << endl;
            }

            i++;
        }
    } else {
        cout << "error opening file:" << argv[1] << endl;
        return -1;
    }

    cout << "Max cluster spacing is:  " << maxClusterSpacing(edges, clusterCount, finalClusterCount, numOfEntries, nodes) << endl;
    
    delete [] nodes;    

}
