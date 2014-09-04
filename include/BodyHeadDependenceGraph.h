#ifndef BODYHEADDEPENDENCEGRAPH_H
#define	BODYHEADDEPENDENCEGRAPH_H

#include <map>
#include <vector>
#include <set>
#include "Rule.h"
#include "Utils.h"

class BodyHeadDependenceGraph {
private:
    /* 下面两个map组成了整个Body-head正依赖图，其中a是head(r)，B是body(r)，
     * 根据Rule的结构有head(r)用int表示，body(r)用set<int>来表示。int都代表
     * 了对应atom的id，若为负id，即为对应的负文字。
     */
    map< int, vector< set<int> > > bhdg_aB;       // body-head正依赖图中的(a,B)边集
    map< set<int>, set<int> > bhdg_Ba;  // body-head正依赖图中的(B,a)边集
    
public:
    BodyHeadDependenceGraph();          // 构造函数，使用G_NLP来构造body-head dependence graph
    ~BodyHeadDependenceGraph();         // 析构函数，把bhdg_aB和bhdg_Ba清空。
    BodyHeadDependenceGraph(BodyHeadDependenceGraph& bhdg);     // 拷贝构造函数。
    
    void showBHDGraph(FILE* out);       // 辅助函数，输出bhdg_aB和bhdg_Ba来查看构造结果是否正确。
    
    
    /*
     * 计算splitting的过程函数
     */
    map< set<int>, set<int> > eliminatingAtomsP();           // eliminating the vertexs in Atoms(P)
    map< set<int>, set<int> > changeToUndirected();          // changing directed graph to undirected
    map< set<int>, set<int> > fission();                     // make infinity edges and replace each vertex by two new vertexes
    void MiniCut();                                          // 寻找miniCut的集合
    vector<Rule> getR();                                     // 获取得到miniCut对应的rules
    
};
#endif	/* BODYHEADDEPENDENCEGRAPH_H */

