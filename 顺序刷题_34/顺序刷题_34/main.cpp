#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<stack>
using namespace std;

int search(vector<int>&nums,int begin,int end,int target) {
	while (begin <= end) {
		int mid = (begin + end) / 2;
		if (nums[mid] == target)return mid;
		else if (nums[mid] < target)begin = mid + 1;
		else end = mid - 1;
	}
	return -1;
}

vector<int> searchRange(vector<int>& nums, int target) {
	int size = nums.size();
	int mid = search(nums, 0, size - 1, target);
	if (mid == -1)return{ -1,-1 };
	int left=mid, right=mid;
	int t_left=search(nums,0,left-1,target);
	while (t_left != -1) {
		left = t_left;
		t_left = search(nums, 0, t_left - 1, target);
	}
	int t_right = search(nums, right+1, size-1, target);
	while (t_right != -1) {
		right= t_right;
		t_right = search(nums, right+1, size-1, target);
	}
	return { left,right };
}

string dfs(string str) {
	string ans;
	int size = str.length();
	int count=1;
	for (int i = 0; i < size;) {
		for (int j= i + 1; j < size; j++) {
			if (str[j] == str[i])count++;
			else break;
		}
		ans += count+48;
		ans += str[i];
		i += count;
		count = 1;
	}
	return ans;
}

string countAndSay(int n) {
	string res="1";
	for (int i = 1; i < n; i++) {
		res = dfs(res);
	}
	return res;
}

vector<int>ans;
vector<vector<int>>res;
void get_ans(vector<int>& candidates,int begin,int target,int size) {	
	if (candidates[begin] > target)return;
	else if (candidates[begin] == target) {
		ans.push_back(candidates[begin]);
		res.push_back(ans);
		ans.pop_back();
		return;
	}
	else {
		ans.push_back(candidates[begin]);
		for(int i=begin+1;i<size;){
			get_ans(candidates, i, target - candidates[begin],size);
			i++;
			while (i < size && candidates[i] == candidates[i - 1])i++;
		}
		ans.pop_back();
	}
}

vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
	int size = candidates.size();
	sort(candidates.begin(),candidates.end());
	for (int i = 0; i < size; ) {
		if (candidates[i] > target)return res;
		get_ans(candidates, i, target,size);
		i++;
		while (i < size && candidates[i] == candidates[i - 1])i++;
	}
	
	return res;
}

void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

int firstMissingPositive(vector<int>& nums) {
	int size = nums.size();
	for (int i = 0; i < size; i++) {
		while (nums[i] != i + 1) {
			if (nums[i] <= 0 || nums[i] > size)break;
			else {
				swap(nums[i], nums[nums[i] - 1]);
			}
		}
	}
	for (int i = 0; i < size; i++) {
		if (nums[i] != i + 1)return i + 1;
	}
}

int numDistinct(string s, string t) {
	int size1 = s.size();
	int size2 = t.size();
	vector<vector<long int>>dp(size2, vector<long int>(size1, 0));
	if (s[0] == t[0])dp[0][0] = 1;
	for (int i = 1; i < size1; i++) {
		if (s[i] == t[0])dp[0][i] = dp[0][i - 1] + 1;
		else dp[0][i] = dp[0][i - 1];
	}

	for (int i = 1; i < size2; i++) {
		for (int j = i; j <size1; j++) {
			if (s[j] == t[i])dp[i][j] = dp[i - 1][j - 1] + dp[i][j - 1];
			else dp[i][j] = dp[i][j - 1];
		}
	}
	return dp[size2 - 1][size1 - 1];
}

int trap(vector<int>& height) {
	int size1 = height.size();
	int volume = 0;
	int flag=-1;
	for (int i = 2; i < size1; i++) {
		if (height[i] > height[i - 1]) {
			int t_vol=0;
			for (int j = i - 1; j >= 0; j--) {
				     if (height[j] >= height[i]) {
					if (j <= flag) {
						int v = (height[i] - height[i - 1]) * (i - j);
						volume += v;
					}
					volume += t_vol;
					break;
				}
				else {
					t_vol += height[i] - height[j];
				}
			}
		}
	}
}


int main() {
	string s = "babgbag";
	string t = "bag";
	cout << numDistinct(s,t);
	return 1;
}