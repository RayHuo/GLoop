#include <bits/stdc++.h>

using namespace std;

#define RUN_CMD "claspD 0 --file=sample.in"
#define OUTPUT_FILE "output.txt"
#define BUFF_SIZE 1024

set< set<string> > deal()
{
    // 管道调用 RUN_CMD 计算并将其结果写进 OUTPUT_FILE
    char buff[BUFF_SIZE];
    FILE *pipe_file = popen(RUN_CMD, "r");
    FILE *output_file = fopen(OUTPUT_FILE, "w");
    while (fgets(buff, BUFF_SIZE, pipe_file)) {
        fprintf(output_file, "%s", buff);
    }
    pclose(pipe_file);
    fclose(output_file);
    // 提取answer set
    set< set<string> > ret;
    string line, str;
    ifstream answer_in(OUTPUT_FILE);
    bool flag = false;
    while (getline(answer_in, line)) {
        if (line.substr(0, 6) == "Answer") {
            flag = true;
            continue;
        }
        if (flag) {
            flag = false;
            stringstream ss(line);
            set<string> ans;
            while (ss >> str) {
                ans.insert(str);
            }
            ret.insert(ans);
        }
    }
    answer_in.close();
    // 显示结果，测试
    for (set< set<string> >::const_iterator i = ret.begin();
            i != ret.end(); ++ i) {
        set<string> tmp = *i;
        for (set<string>::const_iterator j = tmp.begin();
                j != tmp.end(); ++ j) {
            cout << *j << " ";
        }
        cout << endl;
    }
    return ret;
}

//int main()
//{
//    deal();
//    return 0;
//}
