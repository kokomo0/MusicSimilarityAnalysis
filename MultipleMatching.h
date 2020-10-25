#include "PatternSet.h"
#include "Table.h"
#include <vector>
using namespace std;

class MultipleMatching {
	int* text;
	PatternSet* patternSet;
	int textLength;
	int blockSize;

public:
	MultipleMatching() {
		text = NULL;
		patternSet = NULL;
		textLength = blockSize = 0;
	}

	MultipleMatching(vector<int> text, vector<vector<int>> patternSet, int bSize) {
		textLength = text.size();
		blockSize = bSize;
		this->text = new int[textLength];
		for (int i = 0; i < textLength; i++)
			this->text[i] = text[i];
		this->patternSet = new PatternSet(patternSet, bSize);
	}

	void preprocessing() {
		patternSet->setHashTable();
		patternSet->setShiftTable();
		patternSet->setlocationTable();
	}

	int getTextFinger(int idx) {
		int finger = 0;
		int fac = 0;
		for (int i = idx; i < idx + blockSize; i++, fac++) {
			int cnt = 0;
			for (int j = idx; j < i; j++)
				if (text[j] < text[i]) cnt++;
			finger += cnt * fac;
		}
	}

	void verifying(int pos, int finger) {
		HashTable* hash = patternSet->getHashTable();
		for (int i = 0; i < hash->Hash[finger].size(); i++) {
			int patternIdx = hash->Hash[finger][i];
			LocationTable* location = patternSet->getlocationTable(patternIdx);
			int len = patternSet->getLen(patternIdx);
			int beg = pos - len + 1;
			for (int j = 0; j < len; j++) {
				int lmax = location->Lmax[j];
				int lmin = location->Lmin[j];
				int yc, yd;
				if (lmax == -1) yc = -1;
				else yc = text[beg + lmax];
				if (lmin == -1) yd = -1;
				else yd = text[beg + lmin];
				if ((yc<text[beg + j] && yd>text[beg + j]) || (yc == text[beg + j] && yd == text[beg + j])) {
					//match
				}
			}
		}
	}

	void searching() {
		preprocessing();
		int pos = patternSet->getMinLen() - 1;
		while (pos < textLength) {
			int finger = getTextFinger(pos - blockSize + 1);
			int shift = patternSet->getShiftTable(finger);
			if (shift == 0) {
				verifying(pos, finger);
				pos++;
			}
			else pos += shift;
		}
	}
};