#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <map>
#include <cstring>

using namespace std;

#define PEALNUM 2       // how many peals
#define PEALSIZE 5      // how many nodes in every peal

int graph[PEALSIZE][PEALSIZE] = {0};

int main() {
    FILE* fout;
    fout = fopen("peal2_5.in", "w");
    if(!fout) {
        printf("File open failed!\n");
        return 0;
    }
    
    memset(graph, 0, sizeof(graph));
    for(int i = 0; i < PEALSIZE; i++)
        for(int j = 0; j < PEALSIZE; j++)
            if(i != j)
                graph[i][j] = 1;

    return 0;
}