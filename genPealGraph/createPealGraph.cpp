/* 
 * File:   main.cpp
 * Author: ray
 *
 * Created on September 9, 2014, 10:47 AM
 */

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <set>

using namespace std;

#define PEALNUM 2
#define PEALSIZE 5

int main() {
    FILE* fout; 
    FILE* fcuts;
    fout = fopen("output/nv14a2.txt", "w");
    if(!fout) {
        printf("Fail to open output file.\n");
        return 0;
    }

    fcuts = fopen("output/cuts.txt", "w");
    if(!fcuts) {
        printf("Fail to open cuts file.\n");
        return 0;
    }

    srand(time(0));
    int total = PEALNUM*PEALSIZE;
    bool visited[PEALNUM*PEALSIZE];
    memset(visited, false, sizeof(visited));

    // print all vertexs in file
    for(int i = 0; i < total; i++) {
    	fprintf(fout, "vertex(%d).\n", i);		fflush(fout);
    }
    visited[0] = true;	// while visited[i] = true, vertex[i] can not be choose as a connect node

    // print all arcs in the each peal Test
    for(int t = 0; t < PEALNUM; t++)
        for(int i = 0; i< PEALSIZE; i++)
            for(int j = i+1; j< PEALSIZE; j++) {
                fprintf(fout, "arc(%d, %d).\n", i+t*PEALSIZE, j+t*PEALSIZE);	fflush(fout);
                fprintf(fout, "arc(%d, %d).\n", j+t*PEALSIZE, i+t*PEALSIZE);	fflush(fout);
            }

    // generate connect edge for every two nodes
    set<int> cuts;				// hold all cut vertexs             
    int st = -1, ed = -1;

    // first node to second node
    do {
        st = rand() % PEALSIZE;
    }while(visited[st]);
    visited[st] = true;		cuts.insert(st);
    do {
        ed = rand() % PEALSIZE + PEALSIZE;
    }while(visited[ed]);
    visited[ed] = true;		cuts.insert(ed);
    fprintf(fout, "arc(%d, %d).\n", st, ed);	fflush(fout);

    // second node to first node
    do {
        st = rand() % PEALSIZE + PEALSIZE;
    }while(visited[st]);
    visited[st] = true;		cuts.insert(st);
    do {
        ed = rand() % PEALSIZE;
    }while(visited[ed]);
    visited[ed] = true;		cuts.insert(ed);
    fprintf(fout, "arc(%d, %d).\n", st, ed);	fflush(fout);

    // print out total line num to judge whether a correct output
    // int lines = ((PEALSIZE-1)*PEALSIZE) * PEALNUM + PEALNUM + 2*PEALSIZE;
    // fprintf(fout, "Total lines should be %d\n", lines);		fflush(fout);

    // print out all cut vertexs with reached(i)
    for(set<int>::iterator it = cuts.begin(); it != cuts.end(); it++) {
        fprintf(fcuts, "reached(%d)\n", *it); 	fflush(fout);
    }

    fclose(fcuts);
    fclose(fout);             
    return 0;
}

