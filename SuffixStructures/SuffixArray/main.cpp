#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Kärkkäinen-Sanders
class KSSuffixArrayBuilder {
private:
	std::vector<unsigned int> s;
	std::vector<int> suffixArray;
	bool haveAnswer;

	class CompareSuffixesStupid;
    class CompareSuffixesForMerge;
public:
	KSSuffixArrayBuilder();
	KSSuffixArrayBuilder(std::string const &_s);
	KSSuffixArrayBuilder(std::vector<unsigned int> const &_s);
	template<typename Iterator>
	KSSuffixArrayBuilder(Iterator const &itBegin, Iterator const &itEnd);

	void solve();
	std::vector<int> const &getArray();
};

class KasaiLCPBuilder { // lcp[i] - lcp of string i - 1 and i
private:
	std::string const &s;
	std::vector<int> const &suffixArray;
	std::vector<int> lcp;
	bool haveAnswer;
public:
	KasaiLCPBuilder(std::string const &_s,
			std::vector<int> const &_suffixArray);

	void solve();
	std::vector<int> const &getLCP();
};

int main() {
	std::ios_base::sync_with_stdio(false);
	int k;
	std::string s;
	std::cin >> k;
	std::getline(std::cin, s);
	std::getline(std::cin, s);
	int n = (int)s.size();
	for (int i = 0; i < k; ++i) {
		s.push_back(s[i]);
	}
	s.push_back('$');
	KSSuffixArrayBuilder ks(s);
	std::vector<int> const &suffixArray = ks.getArray();
	KasaiLCPBuilder kasai(s, suffixArray);
	std::vector<int> const &lcp = kasai.getLCP();
	for (int i = 0; i < n; ++i) {
		long long ans = (long long)k * (k + 1) / 2;
		int currentLCP = 0;
		for (int j = 0; j < (int)suffixArray.size(); ++j) {
			currentLCP = std::min(currentLCP, lcp[j]);
			if (suffixArray[j] >= i && suffixArray[j] < i + k) {
				ans -= std::min(currentLCP, i + k - suffixArray[j]);
				currentLCP = std::max(i + k - suffixArray[j], currentLCP);
			}
		}
		std::cout << ans << " ";
	}
	std::cout << "\n";
	return 0;
}

namespace Utils {
	template <typename T, typename GetDigit>
	void countingSort(std::vector<T> &x, size_t max, GetDigit const &digit) {
		std::vector<std::vector<T> > ans(max);
		for (int i = 0; i < (int)x.size(); ++i) {
			ans[digit(x[i])].push_back(x[i]);
		}
		x.clear();
		for (int i = 0; i < (int)ans.size(); ++i) {
			for (int j = 0; j < (int)ans[i].size(); ++j) {
				x.push_back(ans[i][j]);
			}
		}
	}
	
	template<typename T, typename GetDigit>
	class GetDigitByNumber {
	private:
		int k;
		GetDigit const &getDigit;
	public:
		GetDigitByNumber(int _k, GetDigit const &_getDigit) : k(_k), getDigit(_getDigit) {}
		int operator()(T const &x) const {
			return getDigit(k, x);
		}
	};
	
	template <typename T, typename getDigit>
	void radixSort(std::vector<T> &x, size_t max, size_t digitCount,
			getDigit const &dig) {
		for (int i = (int)digitCount - 1; i >= 0; --i) {
			GetDigitByNumber<T, getDigit> sd(i, dig);
			countingSort(x, max, sd);
		}
	}
};

KSSuffixArrayBuilder::KSSuffixArrayBuilder() : haveAnswer(false) {}
KSSuffixArrayBuilder::KSSuffixArrayBuilder(std::string const &_s) : 
		haveAnswer(false) {
	s.resize(_s.size());
	for (int i = 0; i < (int)s.size(); ++i) {
		s[i] = (unsigned int)_s[i];
	}
}
KSSuffixArrayBuilder::KSSuffixArrayBuilder(std::vector<unsigned int> 
		const &_s) : s(_s), haveAnswer(false) {}
template<typename Iterator>
KSSuffixArrayBuilder::KSSuffixArrayBuilder(Iterator const &itBegin,
		Iterator const &itEnd) : haveAnswer(false) {
	s.resize(itEnd - itBegin + 1); // one terminal symbol
	int i = 0;
	for (Iterator it = itBegin; it != itEnd; it++) {
		s[i] = *it;
		i++;
	}
	s[i] = '$';
}

class KSSuffixArrayBuilder::CompareSuffixesStupid {
private:
	std::vector<unsigned int> const &s;
public:
	CompareSuffixesStupid(std::vector<unsigned int> const &_s) : s(_s) {}
	bool operator()(int a, int b) const {
		if (a == b) {
			return false;
		}
		while (std::max(a, b) < (int)s.size() && s[a] == s[b]) {
			a++;
			b++;
		}
		if (a == (int)s.size()) {
			return true;
		}
		if (b == (int)s.size()) {
			return false;
		}
		return (s[a] < s[b]);
	}
};

class KSSuffixArrayBuilder::CompareSuffixesForMerge {
private:
    std::vector<unsigned int> const &s;
    std::vector<int> const &ans0;
    std::vector<int> const &ans12;
    std::vector<int> rank0;
    std::vector<int> rank12;
    int n;
public:
    CompareSuffixesForMerge(std::vector<unsigned int> const &_s, std::vector<int> const &_ans0,
                            std::vector<int> const &_ans12, int _n) :
            s(_s), ans0(_ans0), ans12(_ans12),
            rank0(_ans0.size() + _ans12.size(), -1), rank12(_ans0.size() + _ans12.size(), -1), n(_n) {
        for (int i = 0; i < (int)ans0.size(); ++i) {
            rank0[ans0[i]] = i;
        }
        for (int i = 0; i < (int)ans12.size(); ++i) {
            rank12[ans12[i]] = i;
        }
    }

    bool operator()(int t1, int t2) {
        int i = rank12[t1];
        int j = rank0[t2];

        if (ans12[i] >= n) {
            return true;
        }
        if (ans0[j] >= n) {
            return false;
        }

        if (s[ans12[i]] < s[ans0[j]]) {
            return true;
        }
        if (s[ans12[i]] > s[ans0[j]]) {
            return false;
        }

        if (ans12[i] % 3 == 1) {
            if (rank12[ans12[i] + 1] < rank12[ans0[j] + 1]) {
                   return true;
            } else {
                return false;
            }
        } else { // ans12[i] % 3 == 2
            if (s[ans12[i] + 1] < s[ans0[j] + 1]) {
                return true;
            }
            if (s[ans12[i] + 1] > s[ans0[j] + 1]) {
                return false;
            }
            // equal
            if (rank12[ans12[i] + 2] < rank12[ans0[j] + 2]) {
                return true;
            } else {
                return false;
            }
        }
    }
};

class GetElementByNumber {
public:
	unsigned int operator()(int x, std::vector<unsigned int> const &a) const {
		return a[x];
	}
};

class GetSecondElementOfPair {
public:
	unsigned int operator()(std::pair<int, unsigned int> const &x) const {
		return x.second;
	}
};

void KSSuffixArrayBuilder::solve() {
	if (s.size() <= 4) {
		suffixArray.resize(s.size());
		for (int i = 0; i < (int)suffixArray.size(); ++i) {
			suffixArray[i] = i;
		}
		CompareSuffixesStupid x(s);
		std::sort(suffixArray.begin(), suffixArray.end(), x);
		haveAnswer = true;
		return;
	}
	int n = (int)s.size();
	//s.push_back('#');
	while (s.size() % 3 != 0) {
		s.push_back('#');
	}
	// build 1, 2
	std::vector<std::vector<unsigned int> > alph;
	int alphSize = 0;
	for (int i = 0; i < (int)s.size(); ++i) {
		alphSize = std::max(alphSize, int(s[i]) + 1);
		if (i % 3 != 0) {
			std::vector<unsigned int> cur(4);
			cur[0] = s[i];
			cur[1] = (i + 1 < (int)s.size() ? s[i + 1] : '#');
			cur[2] = (i + 2 < (int)s.size() ? s[i + 2] : '#');
			cur[3] = (unsigned int)i;
			alph.push_back(cur);
		}
	}
    Utils::radixSort(alph, alphSize, 3, GetElementByNumber());

    std::vector<unsigned int> newLetter(s.size());
	unsigned int curLet = 'a';
	for (int i = 0; i < (int)alph.size(); ++i) {
		if (i > 0) {
			bool eq = true;
			for (int j = 0; j < 3; ++j) {
				if (alph[i][j] != alph[i - 1][j]) {
					eq = false;
				}
			}
			if (!eq) {
				curLet++;
			}
		}
		newLetter[alph[i][3]] = curLet;
	}
	std::vector<unsigned int> newString;
	for (int i = 1; i < (int)s.size(); i += 3) {
		newString.push_back(newLetter[i]);
	}
	for (int i = 2; i < (int)s.size(); i += 3) {
		newString.push_back(newLetter[i]);
	}
	KSSuffixArrayBuilder _x(newString);
	std::vector<int> const &newAns = _x.getArray();
	std::vector<int> ans12;
	for (int i = 0; i < (int)newAns.size(); ++i) {
		if (newAns[i] < (int)s.size() / 3) {
			ans12.push_back(3 * newAns[i] + 1);
		} else {
			ans12.push_back(3 * (newAns[i] - (int)s.size() / 3) + 2);
		}
	}
	// build 0
	std::vector<std::pair<int, unsigned int> > _ans0;
	for (int i = 0; i < (int)ans12.size(); ++i) {
		if (ans12[i] % 3 == 1) {
			_ans0.push_back(std::make_pair(ans12[i], s[ans12[i] - 1]));
		}
	}
	Utils::countingSort(_ans0, alphSize, GetSecondElementOfPair());

    std::vector<int> ans0(_ans0.size());
    for (int i = 0; i < (int)_ans0.size(); ++i) {
        ans0[i] = _ans0[i].first - 1;
    }

    // merge
    std::vector<int> resultOfMerge(ans0.size() + ans12.size());
    std::merge(ans0.begin(), ans0.end(), ans12.begin(), ans12.end(), resultOfMerge.begin(),
               CompareSuffixesForMerge(s, ans0, ans12, n));

    suffixArray.clear();
    for (int i = 0; i < (int)resultOfMerge.size(); ++i) {
        if (resultOfMerge[i] < n) {
            suffixArray.push_back(resultOfMerge[i]);
        }
    }
	haveAnswer = true;
}

std::vector<int> const &KSSuffixArrayBuilder::getArray() {
	if (!haveAnswer) {
		solve();
	}
	return suffixArray;
}

////////////////////////////////////////////////////////////////////////

KasaiLCPBuilder::KasaiLCPBuilder(std::string const &_s, 
		std::vector<int> const &_suffixArray) : 
		s(_s), suffixArray(_suffixArray), haveAnswer(false) {}

void KasaiLCPBuilder::solve() {
	int n = (int)s.size();
	std::vector<int> rank(n);
	for (int i = 0; i < n; ++i) {
		rank[suffixArray[i]] = i;
	}
	lcp.resize(n);
	for (int i = 0, k = 0; i < n; ++i) {
		k = std::max(0, k - 1);
		if (rank[i] == n - 1) { 
        	lcp[0] = 0;
			k = 0;
			continue;
        }
		int j = suffixArray[rank[i] + 1];
		while (std::max(i + k, j + k) < (int)s.size() && s[i + k] == s[j + k]) {
			k++;
		}
		lcp[rank[i] + 1] = k;
	}
	haveAnswer = true;
}

std::vector<int> const &KasaiLCPBuilder::getLCP() {
	if (!haveAnswer) {
		solve();
	}
	return lcp;
}