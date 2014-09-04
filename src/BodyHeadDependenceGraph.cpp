#include "BodyHeadDependenceGraph.h"
#include "Utils.h"
#include "structs.h"
#include "Vocabulary.h"
#include "Rule.h"
#include <vector>
#include <map>
#include <set>

using namespace std;

extern vector<Rule> G_NLP;

/*
 * 默认构造函数，主要认为是根据G_NLP构造出body-head dependence graph
 * 遍历一次G_NLP，同时构造好bhdg_aB和bhdg_Ba。
 */
BodyHeadDependenceGraph::BodyHeadDependenceGraph() {
    for(vector<Rule>::iterator git = G_NLP.begin(); git != G_NLP.end(); git++) {
        if(git->type == RULE) {
            // bhdg_aB
            if(bhdg_aB.find(git->head) != bhdg_aB.end()) {
                bhdg_aB[git->head].push_back(git->body_lits);
            }
            else{
                vector< set <int> > tmp;
                tmp.push_back(git->body_lits);
                bhdg_aB.insert(pair<int, vector< set<int> > >(git->head, tmp));
            }
            
            // bhdg_Ba
            if(bhdg_Ba.find(git->body_lits) != bhdg_Ba.end()) {
                for(set<int>::iterator blit = (git->body_lits).begin(); blit != (git->body_lits).end(); blit++) {
                    if((*blit) >= 0){
                        bhdg_Ba[git->body_lits].insert(*blit);
                    }
                }
            }
            else {
                set<int> tmp;
                for(set<int>::iterator blit = (git->body_lits).begin(); blit != (git->body_lits).end(); blit++) {
                    if((*blit) >= 0) {
                        tmp.insert(*blit);
                    }
                }
                bhdg_Ba.insert(pair< set<int>, set<int> >(git->body_lits, tmp));
            }
        }
    }
}

BodyHeadDependenceGraph::BodyHeadDependenceGraph(BodyHeadDependenceGraph& bhdg) {
    this->bhdg_aB = bhdg.bhdg_aB;
    this->bhdg_Ba = bhdg.bhdg_Ba;
}

BodyHeadDependenceGraph::~BodyHeadDependenceGraph() {
    bhdg_aB.clear();
    bhdg_Ba.clear();
}

void BodyHeadDependenceGraph::showBHDGraph(FILE* out) {
    fprintf(out, "\nThe body-head dependence graph : \n");
    fprintf(out, "\n(a, B) part : \n");
    fflush(out);
    for(map< int, vector< set<int> > >::iterator it = bhdg_aB.begin(); it != bhdg_aB.end(); it++) {
        fprintf(out, "%s : \n", Vocabulary::instance().getAtom(it->first));     fflush(out);
        for(vector< set<int> >::iterator vsit = (it->second).begin(); vsit != (it->second).end(); vsit++) {
            for(set<int>::iterator sit = vsit->begin(); sit != vsit->end(); sit++) {
                if((*sit) < 0) {    
                    fprintf(out, " not %s", Vocabulary::instance().getAtom(-(*sit)));      fflush(out);
                }
                else {
                    fprintf(out, " %s", Vocabulary::instance().getAtom(*sit));  fflush(out);
                }
            }
            fprintf(out, "\n"); fflush(out);
        }
        fprintf(out, "\n");     fflush(out);
    }
    
    fprintf(out, "\n(B, a) part : \n"); fflush(out);
    for(map< set<int>, set<int> >::iterator it = bhdg_Ba.begin(); it != bhdg_Ba.end(); it++) {
        for(set<int>::iterator hit = (it->first).begin(); hit != (it->first).end(); hit++) {
            if((*hit) < 0) {
                fprintf(out, "not %s ", Vocabulary::instance().getAtom(-(*hit)));  fflush(out);
            }
            else {
                fprintf(out, "%s ", Vocabulary::instance().getAtom(*hit));  fflush(out);
            }
        }
        fprintf(out, " : \n");    fflush(out);
        for(set<int>::iterator bit = (it->second).begin(); bit != (it->second).end(); bit++) {
            if((*bit) < 0) {
                fprintf(out, "Error!!!\n");  fflush(out);
            }
            else {
                fprintf(out, "  %s\n", Vocabulary::instance().getAtom(*bit));  fflush(out);
            }
        }
        fprintf(out, "\n");     fflush(out);
    }
}



/*
 * 寻找miniCut R的过程
 */

/*
 * eliminating the vertexs in Atoms(P) 
 */ 
map< set<int>, set<int> > eliminatingAtomsP() {
    
}          

/*
 * changing directed graph to undirected
 */
map< set<int>, set<int> > changeToUndirected() {
    
}

/*
 * make infinity edges and replace each vertex by two new vertexes
 */
map< set<int>, set<int> > fission() {
    
}

/*
 * 寻找miniCut的集合
 */
void MiniCut() {
    
}

/*
 * 获取得到miniCut对应的rules
 */
vector<Rule> getR() {
    
}

