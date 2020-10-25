#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Table.h"

#define PatLenBeg 10
#define PatLenEnd 15

using namespace std;

class Input {
private:
	//0 for DB music, 1 for Input music;
	vector<vector<int>> Index[2];
	vector<vector<int>> Melody[2];
	vector<vector<int>> Rhythm[2];
	vector<vector<int>> TopNote[2];
	vector<vector<int>> Pattern[PatLenEnd - PatLenBeg];

public:
	Input(string dbDir, string inputDir) {
		readMusic(dbDir, 0);
		readMusic(inputDir, 1);
		for (int len = PatLenBeg; len < PatLenEnd; len++)
			makePattern(len);
	}

	~Input() {}

	void readMusic(string dir, int f) {
		ifstream in(dir);
		while (!in.eof()) {
			string line;
			getline(in, line);
			if (line.size() < 5) continue;
			vector<int> I, M, R, T;
			string s;
			int cnt = 0;
			for (int i = 0; i < line.size(); i++) {
				if (line[i] == ' ') {
					if (cnt == 0) I.push_back(stoi(s));
					if (cnt == 1) M.push_back(stoi(s));
					if (cnt == 2) R.push_back(stoi(s));
					s.clear();
					cnt = (cnt + 1) % 3;
					continue;
				}
				s += line[i];
			}
			Index[f].push_back(I);
			Melody[f].push_back(M);
			Rhythm[f].push_back(R);

			for (int i = 0; i < M.size(); i++) {
				if (T.size() == I[i]) T.push_back(M[i]);
			
			}
			TopNote[f].push_back(T);
		}
		ofstream out("./out.txt");
		for (int i = 0; i < TopNote[f].size(); i++) {
			for (int j = 0; j < TopNote[f][i].size(); j++)
				out << TopNote[f][i][j] << " ";
			out << "\n";
		}
	}

	void makePattern(int len) {
		for (int i = 0; i < TopNote[1].size(); i++) {
			for (int j = 0; j <= TopNote[1][i].size() - len; j++) {
				vector<int> pat;
				for (int k = j; k < j + len; k++) {
					pat.push_back(TopNote[1][i][k]);
				}
				Pattern[len - PatLenBeg].push_back(pat);
			}
		}
	}

	vector<int> getText() {}
	
	vector<vector<int>> getPatternSet() {}

	vector<int> getPattern() {}

	void compressPattern(int len) {}
};