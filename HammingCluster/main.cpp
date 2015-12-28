#include <iostream>
#include <queue>
#include <stdint.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <unordered_map>


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


void merge(uint32_t cluster1, uint32_t cluster2, vector<node> & nodes) {

    uint32_t leader = 0;
    uint32_t follower = 0;

    if (nodes[cluster1].size > nodes[cluster2].size) {
        leader = cluster1;
        follower = cluster2;
    } else {
        leader = cluster2;
        follower = cluster1;
    }

    for (uint32_t vertex = 0; vertex <= nodes.size(); vertex++) {

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


uint32_t maxClusterSpacing(priority_queue<edge, vector<edge>, edge> &edges, vector<node> & nodes) {

    uint32_t clusterCount = 0;
    edge cEdge;

    while (!edges.empty()) {
        cEdge = edges.top();
        //cout << "first vertex: " << cEdge.firstVertex << " second vertex: " << cEdge.secondVertex << " distance: " << cEdge.distance << endl;
        if (nodes[cEdge.firstVertex].cluster != nodes[cEdge.secondVertex].cluster) {
            merge(nodes[cEdge.firstVertex].cluster, nodes[cEdge.secondVertex].cluster, nodes);
            clusterCount++;
        }

        edges.pop();
        //cout << "clusterCount: " << clusterCount << endl;
    }


    return clusterCount;

}


int main (int argc, char* argv[])
{

    if (argc != 4) {
        cout << "Usage: hcluster <input file> <bitCount> <vertices>" << endl;
        return -1;
    }


    uint32_t bitCount = atoi(argv[2]);
    uint32_t vertexCount = atoi(argv[3]);

    vector<uint32_t> nc1;
    vector<uint32_t> nc2;
    
    unordered_map<uint32_t, uint32_t> vertices;
    
    

    for (uint32_t i = 0; i < bitCount;  i++) {
        nc1.push_back(1 << i);
        //cout << "nc1[" << i << "]: " << nc1[i] << endl;
    }

    uint32_t num1,num2 =0;
    uint32_t index = 0;
    for (uint32_t i = 0; i < bitCount; i++) {
        
        num1 = (1 << i);
        num2 = (1 << (i+1));

        for (uint32_t j = 0; j < (bitCount -i -1); j++) {
            nc2.push_back(num1 | (num2 << j));

            //cout << "nc2[" << index << "]: " << nc2[index] << endl;
            index++;
        }
    }

    //cout << "nc1 size: " << nc1.size() << "\tnc2 size: " << nc2.size() << endl;

    ifstream numFile;
    string line;
    numFile.open(argv[1]);

    uint32_t vNum = 0;
    priority_queue<edge, vector<edge>, edge> edges;
    edge cEdge;
    vector<node> nodes;
    node cNode;
    uint32_t hDist = 0;
    std::pair<uint32_t, uint32_t> vertex;

    if (numFile) {

        getline (numFile, line);

        while (getline (numFile, line)) {
            std::istringstream iss(line);
            uint32_t n = 0;
            uint32_t j = bitCount -1;

            while (iss >> n) {
                hDist |= (n << j);
                j--;
            }

            //cout << "hDist: " << hDist << " j: " << j << endl;
            //vertex = 0;

            //if (vertices.find(vertex) == vertices.end())
            vertex.first = hDist;
            vertex.second = vNum;
            vertices.insert(vertex);

            cNode.cluster = vNum;
            cNode.size = 1;

            nodes.push_back(cNode);

            vNum++;
            hDist = 0;
           
        }
        
        
    } else {
        cout << "error opening file :" << argv[1] << endl;
        return -1;
    }



    uint32_t xVertex = 0;

    std::unordered_map<uint32_t, uint32_t>::const_iterator got;

    for (unordered_map<uint32_t, uint32_t>::iterator it = vertices.begin(); it != vertices.end(); it++) {
        
        edge cEdge;
        node cNode;
        for (uint32_t i = 0; i < nc1.size(); i++) {
            xVertex = (it->first) ^ nc1[i];
            
            if ((got = vertices.find(xVertex)) != vertices.end()) {
                cEdge.firstVertex = it->second;
                cEdge.secondVertex = got->second;
                cEdge.distance = 1;
                edges.push(cEdge);
            }            
        }

       for (uint32_t i = 0; i < nc2.size(); i++) {
            xVertex = (it->first) ^ nc2[i];

            if ((got = vertices.find(xVertex)) != vertices.end()) {
                cEdge.firstVertex = it->second;
                cEdge.secondVertex = got->second;
                cEdge.distance = 2;
                edges.push(cEdge);
                
            }
        }
        
    }

    cout << "number of vertices: " << vertices.size() << endl;
    cout << "number of edges: " << edges.size() << endl;
    cout << "max clusters: " << vertices.size() - maxClusterSpacing(edges, nodes) << endl;
    
}



















































