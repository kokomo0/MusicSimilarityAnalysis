#include "Input.h"
#include "MultipleMatching.h"
#include "KMismatchMatching.h"
#include <string>

class MusicChecker {
	Input* input;
	MultipleMatching* OPM;
	KMismatchMatching* KMM;
	int* weight;

	MusicChecker(string dbDir, string inputDir, int* weight) {
		input = new Input(dbDir, inputDir);
		this->weight = weight;
		vector<int> text = input->getText();
		vector<int> pattern = input->getPattern();
		vector<vector<int>> patternSet = input->getPatternSet();
		int bSize; //
		int k;//
		OPM = new MultipleMatching(text, patternSet, bSize);
		KMM = new KMismatchMatching(text, pattern, k);
	}
};