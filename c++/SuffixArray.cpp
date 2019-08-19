// A dynamic programming solution to construct [Suffix Array](https://en.wikipedia.org/wiki/Suffix_array) in O(log(N)^2 * N) time.
// The original idea is posted by [Bruno Oliveira](https://discuss.codechef.com/t/a-tutorial-on-suffix-arrays/2950).
// Some useful link:
// MIT 6.851: Advanced Data Structures [Lecture 16 Strings](http://courses.csail.mit.edu/6.851/spring12/lectures/L16.html?notes=8).
// O(N * lgN) time construct suffix array by [Skew algorithm](https://gist.github.com/markormesher/59b990fba09972b4737e7ed66912e044).
#include<vector>
#include<cmath>
#include<utility>
#include<algorithm>
class SuffixArray {
private:
	std::vector<int> A;
	struct Triple {
		int first;
		int second;
		int index;
		bool operator <(const Triple& a) {
			if (first < a.first) {
				return true;
			}
			if (first > a.first) {
				return false;
			}
			return second < a.second;
		}
		bool operator == (const Triple& a) {
			return first == a.first && second == a.second;
		}
	};
public:
	const int& operator [](std::size_t i) const {
		return A[i];
	}
	std::size_t size() {
		return A.size();
	}
	SuffixArray(const std::string& str) {
		std::vector<std::vector<int>> dp(static_cast<std::size_t>(log2(str.size())) + 2, std::vector<int>(str.size()));
		std::vector<Triple> tmp(str.size());
		for (std::size_t i = 0; i < str.size(); i++) {
			dp[0][i] = str[i] - 'a';
		}
		int step = 1;
		int len = 1;
		while (len < str.size()) {
			for (int i = 0; i < str.size(); i++) {
				if (i + len < str.size()) {
					tmp[i] = { dp[step - 1][i],dp[step - 1][i + len],i };
				}
				else {
					tmp[i] = { dp[step - 1][i],-1,i };
				}
			}
			std::sort(tmp.begin(), tmp.end());
			dp[step][tmp[0].index] = 0;
			for (auto i = 1; i < tmp.size(); i++) {
				if (tmp[i] == tmp[i - 1]) {
					dp[step][tmp[i].index] = dp[step][tmp[i - 1].index];
				}
				else {
					dp[step][tmp[i].index] = dp[step][tmp[i - 1].index] + 1;
				}
			}
			len *= 2;
			step++;
		}
		std::vector<std::pair<int, int>> t(str.size());
		for (std::size_t i = 0; i < str.size(); i++) {
			t[i] = { dp[step-1][i],i };
		}
		sort(t.begin(), t.end());
		A.resize(str.size());
		for (std::size_t i = 0; i < t.size(); i++) {
			A[i] = t[i].second;
		}
	}
};