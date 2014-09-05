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

//#define SOLVE
//#define GRAPH
//#define BODYHEAD
#define SPLITTING

FILE* summary;
FILE* unit;
extern FILE* yyin;
extern vector<Rule> G_NLP;
extern set<int> U;
extern int *atomState;
extern int *ruleState;
extern int yyparse();
FILE* result_out;

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
    
    yyin = fopen("IO/sample.in", "r");
    result_out = fopen("IO/sample.out", "w+");
    
    if (!yyin) {
        printf("IO Error: cannot open the input file.\n" );
        assert(0);
    }
    if (!result_out) {
        printf("IO Error: cannot open the output file.\n");
        assert(0);
    }
    
    printf("Start Parser\n");
    yyparse();
    printf("End Parser\n");
    
//    Vocabulary::instance().dumpVocabulary(result_out);
//    U.insert(1);
    
//    int method, all, type;
//    
//    if(argc < 3) {
//#ifdef SOLVE
//        yyin = fopen("res/input/hc/gr_cutNode", "r");
//        summary = fopen("res/input/hc/cutNode.out", "w+");        
//        unit = fopen("res/input/hc/cutNode.re", "w+");   
//        
//        method = 0;
//        all = 0;
//#endif
//        
//#ifdef GRAPH
//         yyin = fopen("experiment/pearl_graph/gringo_input/2_6_2", "r");
//         type = 2  ;
//         summary = fopen("experiment/pearl_graph/test_re1", "w+");
//         
//#endif
//    }
//    else {
//#ifdef SOLVE
//        io(argv[1], argv[2], argv[3]);
//        method = argv[4][0] - '0';
//        all = argv[5][0] - '0';
//#endif
//        
//#ifdef GRAPH
//        yyin = fopen(argv[1], "r");
//        //summary = fopen(argv[2], "a+");
//        summary = stdout;
//        
//        if(strlen(argv[2]) == 1 && argv[2][0] >= '0' && argv[2][0] <= '2') type = argv[2][0] - '0';
//        else {
//            fprintf(summary, "input of loop type wrong");
//            return 0;
//        }
//#endif
//    }
//    
//    clock_t hbegin, begin, end;
//    hbegin = begin = clock();
//    
//    yyparse();
//
//#ifdef SOLVE    
//    end = clock();
//    fprintf(summary, "Parse Time: %lf\n", (float)(end - begin)/1000000);
//    begin = clock();
//#endif
//    
//    fclose(yyin);
//    
//#ifdef GRAPH
//    DependenceGraph dpg;
//    vector<Loop> cloops;
//    
//    begin = clock();
//    if(type == 0) cloops = dpg.findAllProperLoops();
//    if(type == 1) cloops = dpg.findAllElementaryLoops();
//    if(type == 2) cloops = dpg.findProperLoopsWithCut2();
//    end = clock();
//    fprintf(summary, "%s \nloop Number: %d \ncheckTimes: %d \ntime: %lf\n", argv[1], cloops.size(), dpg.properTimes, (float)(end - begin)/1000000);
//    
////    for(int i = 0; i < cloops.size(); i++) {
////        cloops[i].print(summary);
////    }
////    fprintf(unit, "cut method proper loops: size: %d\n", cloops.size());
////    for(int i = 0; i < cloops.size(); i++) {
////        cloops[i].print(unit);
////    }
////    
////    printf("elementary loops:\n");
////    for(int i = 0; i < eloops.size(); i++) {
////        eloops[i].print(stdout);
////    }  
//#endif
//    
//#ifdef SOLVE
//    atomState = new int[Vocabulary::instance().apSize() + 1];
//    memset(atomState, 0, sizeof(int) * (Vocabulary::instance().apSize() + 1));
//    ruleState = new int[G_NLP.size()];
//    memset(ruleState, 0, sizeof(int) * G_NLP.size());
//    
//    SATSolver sat(Vocabulary::instance().apSize());
////    SATSolver tsat(Vocabulary::instance().apSize());
//    ClakeCompletion cc;
////    cc.test();
//    
//    end = clock();
//    fprintf(summary, "Completion Time: %lf\n", (float)(end - begin)/1000000);
//    begin = clock();
//    
//    sat.addNewVar(cc.newVar);
//    sat.addNewClauses(cc.completion);
//    
////    tsat.addNewVar(cc.newVar);
////    tsat.addNewClauses(cc.completion);
//    
//    bool isTight = false;
//    int loadCount = 0;
//    int loopFormulaCount = 0;
//    
//    DependenceGraph dpg;
////    dpg.findAllProperLoops();
//    vector<Loop> pre = dpg.findSCC();
//    
//    if(pre.size() == 0) isTight = true;
//    
//    vector< set<int> > AnswerSets;
//    
////    tsat.invokeSAT();
////    printf("completion model: %d \n", tsat.models.size());
//    
//    if(isTight) {
//       fprintf(unit, "Is tight\n");
//       sat.invokeSAT();
//       AnswerSets = sat.models;
//    }
//// ASSAT
//    else {
//        GLTranslator glt(G_NLP);
//        while(sat.isExistModel()) {                        
//            set<int> model = sat.models.back();
//            ++loadCount;
//            
//            begin = clock();
//            set<int> comp = glt.getComplementSet(model);                       
//            end = clock();
//            fprintf(summary, "GL, M^- Time: %lf\n", (float)(end - begin)/1000000);
//
//            
//            if(comp.size() == 0) {
//                AnswerSets.push_back(model);
//                if(all == 0) break;
//            }
//            else {
//               // fprintf(unit, "is't Answerset\n");
//                begin = clock();
//                vector<Loop> mls = dpg.findCompMaximal(comp, method);
//                //vector<Loop> mls = dpg.findProperLoops(comp);               
//                end = clock();
//                fprintf(summary, "Find loop Time: %lf\n", (float)(end - begin)/1000000);
//               
//            
//                for(int i = 0; i < mls.size(); i++) {
//                    mls[i].print(unit);
//                }
//                loopFormulaCount += mls.size();
//                
//                for(vector<Loop>::iterator imls = mls.begin(); imls != mls.end();
//                        imls++) {
//                    begin = clock();
//                    int newVarNum = dpg.computeLoopFormulas(*imls);                   
//                    end = clock();
//                    fprintf(summary, "Cal lf Time: %lf\n", (float)(end - begin)/1000000);
//                    
//                    
//                    sat.addNewVar(newVarNum);
//                    for(vector< set<int> >::iterator ilfs = imls->loopFormulas.begin(); 
//                            ilfs != imls->loopFormulas.end(); ilfs++) {
//                        sat.addNewClause(*ilfs);
//                    }
//                }
//            }
//            if(sat.badEnd) break;
//        }
//    }
//    fprintf(unit, "answer: %d\n", AnswerSets.size());
//    for(int ai = 0; ai < AnswerSets.size(); ai++) {
//        fprintf(unit, "\nset %d:\n", ai + 1);
//        for(set<int>::iterator sit = AnswerSets[ai].begin(); sit != AnswerSets[ai].end(); sit++) {
//            fprintf(unit, "%s ", Vocabulary::instance().getAtom(*sit));
//        }
//    }
//    end = clock();
//    fprintf(summary, "%s: loading: %d loop formula: %d time: %lf\n", argv[1], loadCount, loopFormulaCount, (float)(end - hbegin)/1000000);
//
//#endif    
    
#ifdef BODYHEAD
    BodyHeadDependenceGraph bhdg;     // = new BodyHeadDependenceGraph();
    bhdg.showBHDGraph(result_out);
#endif

#ifdef SPLITTING
    DependenceGraph dpdg;
    long start = clock();
    U = dpdg.calU();
    dpdg.splitting(result_out);
    long end = clock();
//    printf("\nMinimal Cut : ");
//    for(set<int>::iterator it = result.begin(); it != result.end(); it++) {
//        printf("%s ", Vocabulary::instance().getAtom(*it));
//    }
//    printf("\n");
    
    printf("\nTime cost : %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    
#endif   
    
    fclose(result_out);
    fclose(yyin);
    return 0;
}