#include <iostream>
#include <fstream>
#include <stdlib.h>     
#include <sstream>
#include <stdint.h>
#include <limits>

using namespace std;

int main (int argc, char * argv[]) {

    if (argc != 3) {
        cout << "Usage: apsp <input file> <number of vertices>" << endl;
        return -1;
    }

    ifstream numFile;
    string line;
    numFile.open(argv[1]);

    const uint32_t numOfVertices = atoi(argv[2]);

    double **A, **B, **A1, **B1;

    A1 = new double*[numOfVertices + 1];
    B1 = new double*[numOfVertices + 1];

    for (uint32_t row=0; row <= numOfVertices; row++) {
        A1[row] = new double[numOfVertices + 1];
        B1[row] = new double[numOfVertices + 1];
    }

    
    for (uint32_t row=0; row <= numOfVertices; row++) {
        for (uint32_t col=0; col<=numOfVertices; col++) {
            if (row == col) {
                A1[row][col] = 0;
                B1[row][col] = 0;
            } else {
                A1[row][col] = numeric_limits<float>::infinity();
                B1[row][col] = numeric_limits<float>::infinity();
            }
        } 
    }

    if (numFile) {
        getline (numFile, line);

        while (getline (numFile, line)) {
            std::istringstream iss(line);
            int n = 0, j=0;
            int srcVertex = 0;
            int dstVertex = 0;
            int dist = 0;

            while (iss >> n) {
                if (j == 0)
                    srcVertex = n;
                else if (j == 1)
                    dstVertex = n;
                else
                    dist = n;
                j++;                
            }

            j = 0;
            A1[srcVertex][dstVertex] = dist;
            //cout << "A[" << srcVertex << "][" << dstVertex << "]: " << dist << endl; 
        }

    } else {
        cout << "could not open " << argv[1] << endl;
        return -1;
    }
   
    A = A1;
    B = B1;

    double shortestShort = numeric_limits<float>::infinity();

    for (uint32_t k = 1; k <= numOfVertices; k++) {
        for(uint32_t i = 1; i <= numOfVertices; i++) {
            for (uint32_t j = 1; j <= numOfVertices; j++) {
                
                if (A[i][j] < (A[i][k] + A[k][j]))
                    B[i][j] = A[i][j];
                else {
                    B[i][j] = (A[i][k] + A[k][j]);
        
                    if (B[i][j] < shortestShort)
                        shortestShort = B[i][j];
                }
                
                //cout << "B[" << i << "][" << j << "]: " << B[i][j] << endl;
            }
        }
       
        if ( k%2 == 0) { 
            A = A1;
            B = B1;
        } else {
            B = A1;
            A = B1;
        }        

    }

    for (uint32_t row=0; row <= numOfVertices; row++) {
        for (uint32_t col=0; col<=numOfVertices; col++) {
            cout << "B[" << row << "][" << col << "]: " << B[row][col] << endl;           
        }
    }

    uint32_t index = 0;
    for (index = 1; index <= numOfVertices; index++) {
        if ((A[index][index] < 0) || (B[index][index] < 0)) {
            cout << "negative cycle in the graph" << endl;
            break;
        }        
    }   

    if (index > numOfVertices)
        cout << "shortestShort: " << shortestShort << endl;

    
    for (uint32_t row=0; row <= numOfVertices; row++) {
        delete [] A1[row];
        delete [] B1[row];
    } 
   
    delete [] A1;
    delete [] B1; 

}
