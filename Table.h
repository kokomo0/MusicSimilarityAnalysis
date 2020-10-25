#include <vector>
using namespace std;

struct LocationTable {
	int* Lmax;
	int* Lmin;
	LocationTable() {
		Lmax = Lmin = nullptr;
	}
	LocationTable(int len) {
		Lmax = new int[len];
		Lmin = new int[len];
	}
	/*
	~LocationTable() {
		delete[] Lmax;
		delete[] Lmin;
	}
	*/
};

struct HashTable {
	vector<vector<int>> Hash;
	HashTable() {}
	HashTable(int finger) {
		Hash.resize(finger);
	}
	~HashTable() {}
};


struct ShiftTable {
	int* Shift;
	ShiftTable() {
		Shift = nullptr;
	}
	ShiftTable(int finger) {
		Shift = new int[finger];
	}

	/*
	~ShiftTable() {
		delete[] Shift;
	}
	*/
};
