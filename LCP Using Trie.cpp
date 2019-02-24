//Reference :GeeksForGeeks
#include <bits/stdc++.h>
using namespace std;
#define SIZE 26

struct trieNode {
	struct trieNode *children[SIZE];
	bool isLeaf;
};

trieNode* newNode(void) {
	trieNode *nn = new trieNode;
	if(nn) {
		int i;
		nn->isLeaf = false;
		for (int i = 0; i < SIZE; i++) {
			nn->children[i] = NULL;
		}
	}
	return nn;
}

void insert(string s, trieNode* root) {
	int l = s.length();
	trieNode* pCrawl = root;
	for (int i = 0; i < l; i++) {
		int index = s[i]-'a';
		if(!pCrawl->children[index]) {
			pCrawl->children[index] = newNode();
		}
		pCrawl = pCrawl->children[index];
	}
	pCrawl->isLeaf = true;
}
void constructTrie(std::vector<string> s, int n, trieNode* root) {
	for (int i = 0; i < n; i++) {
		insert(s[i], root);
	}
	return;
}

int countChild(trieNode* node, int* index) {
	int cnt = 0;
	//cout<<*index<<endl;
	for (int i = 0; i < SIZE; i++) {
		if(node->children[i] != NULL) {
			cnt++;
			*index = i;
		}
	}
	return cnt;
}
string solveTrie(trieNode* root) {
	string res;
	trieNode* pCrawl = root;
	int index;
	while(countChild(pCrawl, &index)==1 && pCrawl->isLeaf==false) {
		pCrawl = pCrawl->children[index];
		res.push_back('a'+index);
	}
	return res;
}

int main() {
	int n;
	cin >> n;
	vector<string> s(n);
	for (int i = 0; i < n; i++) {
		cin >> s[i];
	}
	trieNode* root = newNode();
	constructTrie(s, n, root);
	cout << solveTrie(root);
}
