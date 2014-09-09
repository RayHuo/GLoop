/* 
 * File:   main.cpp
 * Author: yzf
 *
 * Created on July 10, 2013, 2:17 PM
 */

#include <cstdlib>
#include <cstdio>
#include <assert.h>
#include "Vocabulary.h"
#include "structs.h"
#include "ClakeCompletion.h"
#include "SATSolver.h"
#include "DependenceGraph.h"
#include "CNFUtils.h"
#include "GLTranslator.h"
#include "BodyHeadDependenceGraph.h"
#include <set>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <time.h>

using namespace std;

FILE* summary;
FILE* unit;
extern FILE* yyin;
extern vector<Rule> G_NLP;
extern set<int> U;
extern int *atomState;
extern int *ruleState;
extern int yyparse();
FILE* result_out;
FILE* count_out;        // 保存所有输入文件中的“Atoms(b_U(P)) \ U”数量


void io(const char* iPathName, const char* oPathName, const char* sPathName) {
    yyin = fopen(iPathName, "r");
    unit = fopen(oPathName, "w+");
    summary = fopen(sPathName, "a+");
    
    if (! yyin) {
        printf("IO Error: cannot open the input file.\n" );
        assert(0);
    }
    if (!summary || !unit) {
        printf("IO Error: cannot open the output file.\n");
        assert(0);
    }
}

int main(int argc, char** argv) {
    
    count_out = fopen("IO/count_out.txt", "a");
    yyin = fopen(argv[1], "r");
    if (!yyin) {
        printf("IO Error: cannot open the input file.\n" );
        assert(0);
    }

    string outPath("IO/output/output_");
    string tmp(argv[1]);
    outPath.append(tmp.substr(tmp.find_last_of("/")+1, tmp.size()-4));
//        printf("%s\n", outPath.c_str());
    result_out = fopen((outPath + ".txt").c_str(), "w");
    if (!result_out) {
        printf("IO Error: cannot open the output file.\n");
        assert(0);
    }

    printf("Start Parser\n");
    yyparse();
    printf("End Parser\n");

    fprintf(result_out, "Total Atom size = %d\n", Vocabulary::instance().apSize());
    DependenceGraph dpdg;
    long start = clock();
    U = dpdg.calU();
    dpdg.splitting(result_out);
//    dpdg.calbuU();
    long end = clock();

    fprintf(result_out, "\nTime cost : %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    fclose(result_out);
    fclose(yyin);
    
    return 0;
}