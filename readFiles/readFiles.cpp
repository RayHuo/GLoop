#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
	int num = 1;
	
	FILE* pfile;
	FILE* out;

	for(int i = 1; i < argc; i++, num++) {
		pfile = fopen(argv[i], "r");
		if(pfile != NULL) {
			string path_("./out/output");
			path_ += ('0' +num);
			out = fopen((path_ + ".txt").c_str(), "w");
			fprintf(out, "good\n");
			fclose(out);
		}
		fclose(pfile);
	}
	
	return 0;
}
