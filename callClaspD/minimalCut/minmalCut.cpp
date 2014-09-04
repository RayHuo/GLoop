#include <bits/stdc++.h>

using namespace std;

set<int> calU(map< int, set<int> > graph)
{
    set<int> ret;
    map<int, bool> isVisited;
    //以id最小的点为源点，找出最远点
    queue<int> que;
    int attack = graph.begin()->first;
    que.push(attack);
    isVisited[attack];
    int endure = -1;//最远的点的id
    while (! que.empty()) {
        int cur = que.front();
        que.pop();
        set<int> &adj = graph[cur];
        for (set<int>::iterator it = adj.begin(); it != adj.end(); ++ it) {
            int next = *it;
            if (! isVisited[next]) {
                isVisited[next] = true;
                que.push(next);
            }
        }
        endure = cur;
    }
    if (graph[attack].find(endure) != graph[attack].end()) {//直接相连
        return ret;
    }

    set<int> attackSet, attackOneSet;//攻的集和、一次被攻推到的集合
    set<int> endureSet, endureOneSet;//受的集合、一次被受推到的集合
    set<int> bothOneSet, unknownSet;//攻受都可以一次推到的集合、未确定的集合

    for (map< int, set<int> >::iterator it = graph.begin();
            it != graph.end(); ++ it) {
        unknownSet.insert(it->first);
    }
    unknownSet.erase(attack);
    attackSet.insert(attack);
    for (set<int>::iterator it = graph[attack].begin();
            it != graph[attack].end(); ++ it) {
        unknownSet.erase(*it);
        attackOneSet.insert(*it);
    }
    unknownSet.erase(endure);
    endureSet.insert(endure);
    for (set<int>::iterator it = graph[endure].begin();
            it != graph[endure].end(); ++ it) {
        if (attackOneSet.find(*it) != attackOneSet.end()) {
            attackOneSet.erase(*it);
            bothOneSet.insert(*it);
        }
        else {
            unknownSet.erase(*it);
            endureOneSet.insert(*it);
        }
    }

    while (! attackOneSet.empty() || ! endureOneSet.empty()) {
        if (! attackOneSet.empty()) {
            int cur = *(attackOneSet.begin());
            attackOneSet.erase(cur);
            attackSet.insert(cur);
            set<int> &adj = graph[cur];
            for (set<int>::iterator it = adj.begin();
                    it != adj.end(); ++ it) {
                if (unknownSet.find(*it) != unknownSet.end()) {
                    unknownSet.erase(*it);
                    attackOneSet.insert(*it);
                }
                else if (endureOneSet.find(*it) != endureOneSet.end()) {
                    endureOneSet.erase(*it);
                    bothOneSet.insert(*it);
                }
            }
        }
        if (! endureOneSet.empty()) {
            int cur = *(endureOneSet.begin());
            endureOneSet.erase(cur);
            endureSet.insert(cur);
            set<int> &adj = graph[cur];
            for (set<int>::iterator it = adj.begin();
                    it != adj.end(); ++ it) {
                if (unknownSet.find(*it) != unknownSet.end()) {
                    unknownSet.erase(*it);
                    endureOneSet.insert(*it);
                }
                else if (attackOneSet.find(*it) != attackOneSet.end()) {
                    attackOneSet.erase(*it);
                    bothOneSet.insert(*it);
                }
            }
        }
    }

    for (map< int, set<int> >::iterator it = graph.begin();
            it != graph.end(); ++ it) {
        if (attackSet.find(it->first) == attackSet.end() &&
                endureSet.find(it->first) == endureSet.end()) {
            ret.insert(it->first);
        }
    }

    return ret;
}

int main()
{
    freopen("input.txt", "r", stdin);
    map< int, set<int> > graph;
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++ i) {
        graph[i] = set<int>();
    }
    int a, b;
    while (cin >> a >> b) {
        graph[a].insert(b);
        graph[b].insert(a);
    }
    set<int> ans = calU(graph);
    for (set<int>::iterator it = ans.begin();
            it != ans.end(); ++ it) {
        cout << *it << " ";
    }
    cout << endl;
    return 0;
}
