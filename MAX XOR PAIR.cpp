#include <bits/stdc++.h>
using namespace std;

class trieNode{
public:
	trieNode *left;
	trieNode *right;
};

void insert(int n, trieNode* head) {
	trieNode* curr = head;
	for (int i=31; i>=0; i--) {
		int bit = (n>>i)&1;
		if(bit == 0) {
			if(!curr->left) {
				curr->left = new trieNode();
			}
			curr=curr->left;
		}
		else {
			if(!curr->right) {
				curr->right = new trieNode();
			}
			curr=curr->right;
		}
	}
}

int solve(trieNode* head, int *arr, int n) {
	int max_xor = INT_MIN;
	for (int i = 0; i < n; i++) {
		int curr_xor = 0;
		trieNode* curr = head;
		for (int j=31; j>=0; j--) {
			int bit = (arr[i]>>j)&1;
			if(bit==1) {
				if(curr->left) {
					curr_xor += (1<<j);
					curr = curr->left;
				}
				else {
					curr = curr->right;
				}
			}
			else {
				if(curr->right) {
					curr_xor += (1<<j);
					curr = curr->right;
				}
				else {
					curr = curr->left;
				}

			}
		}
		max_xor = max(max_xor, curr_xor);
	}
	return max_xor;

}

int main() {
	int n;
	cin >> n;
	int arr[n];
	for (int i = 0; i<n; i++) {
		cin >> arr[i];
	}
	trieNode* head = new trieNode();
	for (int i = 0; i < n; i++) {
		insert(arr[i], head);
	}
	cout << solve(head, arr, n);
	return 0;
}
