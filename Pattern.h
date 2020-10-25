#include <vector>
#include "Table.h"
using namespace std;

class Pattern {
	int* pattern;
	int length;
	LocationTable* locationTable;
	int* signature;

	void makeLocationTable() {
		locationTable = new LocationTable(length);
		for (int i = 0; i < length; i++) {
			int ret = i;
			for (int j = 0; j < i; j++) {
				if (pattern[j] > pattern[i]) continue;
				if (ret == i || pattern[j] >= pattern[ret]) ret = j;
			}
			ret = (ret == i) ? -1 : ret;
			locationTable->Lmax[i] = ret;
		}
		for (int i = 0; i < length; i++) {
			int ret = i;
			for (int j = 0; j < i; j++) {
				if (pattern[j] < pattern[i]) continue;
				if (ret == i || pattern[j] <= pattern[ret]) ret = j;
			}
			ret = (ret == i) ? -1 : ret;
			locationTable->Lmin[i] = ret;
		}
	}

	void calculateSignature() {
		signature = new int[length];
		for (int i = 0; i < length; i++) {
			int idx = i;
			for (int j = 0; j < length; j++) {
				if (pattern[j] > pattern[i]) continue;
				if (idx == i || pattern[j] >= pattern[idx]) idx = j;
			}
			signature[i] = idx - i + 1;
		}
	}

public:
	Pattern() { 
		pattern = NULL;
		locationTable = NULL;
		signature = NULL;
		length = 0;
	}
	
	Pattern(vector<int> pattern) {
		this->length = pattern.size();
		this->pattern = new int[length];
		for (int i = 0; i < length; i++)
			this->pattern[i] = pattern[i];
		locationTable = NULL;
		signature = NULL;
	}
	
	Pattern(vector<int> pattern, int sz) {
		this->length = sz;
		this->pattern = new int[length];
		for (int i = 0; i < length; i++)
			this->pattern[i] = pattern[i];
		locationTable = NULL;
		signature = NULL;
	}
	/*
	~Pattern() {
		delete[] pattern;
		delete[] locationTable;
	}
	*/
	int len() { return this->length; }

	LocationTable* getLocationTable() { return locationTable; }

	void setLocationTable() { makeLocationTable(); }

	int* getSignature() { return signature; }

	void setSignature() { calculateSignature(); }

	int getVal(int idx) { return this->pattern[idx]; }

	int* getPattern() { return this->pattern; }
};