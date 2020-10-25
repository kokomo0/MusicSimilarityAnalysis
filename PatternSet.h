#include "Table.h"
#include "Pattern.h"
#include <vector>
#include <algorithm>
using namespace std;

class PatternSet {
	Pattern* patternSet;
	Pattern* prPatternSet;
	int numOfPattern;
	int* lenOfPattern;
	int minLen;
	int blockSize;
	int blockFac;
	int fingerSize;
	HashTable* hashTable;
	ShiftTable* shiftTable;

	void makeHashTable() {
		for (int i = 0; i < numOfPattern; i++) {
			int finger = 0;
			int fac = 0;
			for (int j = minLen - blockSize; j < minLen; j++, fac++) {
				int cnt = 0;
				int ret = prPatternSet[i].getVal(j);
				for (int k = minLen - blockSize; k < j; k++) {
					int tmp = prPatternSet[i].getVal(k);
					if (tmp < ret) cnt++;
				}
				finger += cnt * fac;
			}
			hashTable->Hash[finger].push_back(i);
		}
	}

	void makeShiftTable() {
		for (int i = 0; i < blockFac; i++)
			shiftTable->Shift[i] = minLen - blockSize + 1;

		for (int i = 0; i < numOfPattern; i++) {
			for (int j = 0; j <= minLen - blockSize; j++) {
				int finger = 0;
				int fac = 0;
				for (int k = 0; k < blockSize; k++, fac++) {
					int cnt = 0;
					int ret = prPatternSet[i].getVal(j + k);
					for (int l = 0; l < k; l++) {
						int tmp = prPatternSet[i].getVal(j + l);
						if (tmp < ret) cnt++;
					}
					finger += cnt * fac;
				}
				shiftTable->Shift[finger] = min(shiftTable->Shift[finger], minLen - j + blockSize + 1);
			}
		}
	}

public:
	PatternSet() {
		patternSet = prPatternSet = NULL;
		lenOfPattern = NULL;
		hashTable = NULL;
		shiftTable = NULL;
		numOfPattern = minLen = blockSize = blockFac = 0;
	}

	PatternSet(vector<vector<int>> patternSet, int bSize) {
		numOfPattern = patternSet.size();
		this->patternSet = new Pattern[numOfPattern];
		for (int i = 0; i < numOfPattern; i++) {
			Pattern tmp = Pattern(patternSet[i]);
			this->patternSet[i] = tmp;
		}
		lenOfPattern = new int[numOfPattern];
		minLen = this->patternSet[0].len();
		for (int i = 0; i < numOfPattern; i++) {
			lenOfPattern[i] = this->patternSet[i].len();
			minLen = (minLen < lenOfPattern[i]) ? minLen : lenOfPattern[i];
		}
		this->prPatternSet = new Pattern[numOfPattern];
		for (int i = 0; i < numOfPattern; i++) {
			Pattern tmp = Pattern(patternSet[i], minLen);
			this->prPatternSet[i] = tmp;
		}
		blockSize = bSize;
		blockFac = 1;
		for (int i = 1; i <= blockSize; i++) blockFac *= i;
		hashTable = new HashTable(blockFac);
		shiftTable = new ShiftTable(blockFac);
	}

	~PatternSet() {}

	HashTable* getHashTable() { return hashTable; }

	void setHashTable() { makeHashTable(); }

	int getShiftTable(int finger) { return shiftTable->Shift[finger]; }

	void setShiftTable() { makeShiftTable(); }

	LocationTable* getlocationTable(int idx) {
		if (patternSet[idx].getLocationTable() == NULL) {
			patternSet[idx].setLocationTable();
		}
		return patternSet[idx].getLocationTable();
	}

	void setlocationTable() {
		for (int i = 0; i < numOfPattern; i++)
			patternSet[i].setLocationTable();
	}

	int getMinLen() { return minLen; }

	int getLen(int idx) {
		return patternSet[idx].len();
	}
};