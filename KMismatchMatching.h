#include "Pattern.h"
#include "Table.h"
#include <vector>
using namespace std;

class KMismatchMatching {
	int* text;
	int* textSig;
	int* patternSig;
	Pattern* pattern;
	int k;
	int textLength;
	int patternLength;

public:
	KMismatchMatching() {
		text = textSig = patternSig = NULL;
		pattern = NULL;
		k = textLength = patternLength = 0;
	}

	KMismatchMatching(vector<int> text, vector<int> pattern, int k) {
		textLength = text.size();
		this->k = k;
		this->text = new int[textLength];
		textSig = new int[patternLength];
		patternSig = new int[patternLength];
		for (int i = 0; i < textLength; i++)
			this->text[i] = text[i];
		this->pattern = new Pattern(pattern);
		this->pattern->setSignature();
		patternSig = this->pattern->getSignature();
		patternLength = pattern.size();
	}

	vector<int> filtering(int pos) {
		int* patternSig = pattern->getSignature();
		vector<int> ret;
		for (int i = 0; i < patternLength; i++) {
			int idx = i + pos;
			for (int j = 0; j < patternLength; j++) {
				if (text[j + pos] > text[i + pos]) continue;
				if (idx == i + pos || text[j + pos] >= text[idx + pos]) idx = j + pos;
			}
			textSig[i] = idx - pos + i - 1;
		}
		for (int i = 0; i < patternLength; i++)
			if (patternSig[i] != textSig[i]) ret.push_back(i);
		if (ret.size() <= 3 * k) return ret;
		ret.clear();
		return ret;
	}

	vector<int> getSeq(vector<int> differ, vector<int>& weight) {
		vector<int> seq;
		vector<int> pred;
		pred.resize(patternLength);
		for (int i = 0; i < patternLength; i++)
			pred[i] = patternSig[i] + i;
		for (int i = 0; i < differ.size(); i++) {
			int d = differ[i];
			int w = 0;
			while (pred[d] != -1) {
				d = pred[d];
				w++;
			}
			seq.push_back(pattern->getVal(w));
			weight.push_back(w);
		}
		return seq;
	}

	int HIS(vector<int> seq, vector<int> weight) {
		/*int* dp = new int[seq.size()];
		int ans = 0;
		for (int i = 0; i < seq.size(); i++) {
			int ret = 0;
			for (int j = 0; j < i; j++) {
				if (seq[i] > seq[j]) ret = (ret > dp[i]) ? ret : dp[i];
			}
			dp[i] = ret + 1;
			ans = (ans > dp[i]) ? ans : dp[i];
		}
		return ans;
		*/
	}

	void verifying(vector<int> seq, vector<int> weight) {
		if (HIS(seq, weight) <= k) {
			//match
		}
	}

	void searching() {
		for (int i = 0; i <= textLength - patternLength; i++) {
			vector<int> differ = filtering(i);
			if (differ.size()) {
				vector<int> weight;
				vector<int> seq;
				seq = getSeq(differ, weight);
				verifying(seq, weight);
			}
		}
	}
};