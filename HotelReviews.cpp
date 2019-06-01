//https://www.interviewbit.com/problems/hotel-reviews/
struct TrieNode{
    int isleaf;
    TrieNode* child[26];
};

TrieNode* getNode() { // to create new trie node
    TrieNode* node = new TrieNode();
    for (int i = 0; i < 26; i++) {
        node->child[i] = NULL;
    }
    node->isleaf = 0;
    return node;
} 
void convert(string &A) {
    int l = A.size();
    for (int i = 0; i < l; i++) {
        if(A[i] == '_') {
            A[i]=' ';
        }
    }
    return;
}
void insert(TrieNode* root, string s) {
    TrieNode* curr = root;
    for (int i  = 0; i  < s.size(); i++) {
        if(curr->child[s[i]-97]) {
            curr = curr->child[s[i]-97];
            continue;
        }
        else {
            curr->child[s[i]-97] = getNode();
            curr = curr->child[s[i]-97];
        }
    }
    curr->isleaf = 1;
}
bool cmp(pair<int, int> a, pair<int, int> b) {
    if(a.first==b.first) {
        return a.second < b.second;
    }
    return a.first > b.first;
}
bool search(TrieNode* root, string word) {
    TrieNode* curr = root;
    for (int i = 0; i < word.size(); i++) {
        if(!curr->child[word[i]-97]) {
            return false;
        }
        curr = curr->child[word[i]-97];
    }
    return (curr && curr->isleaf);
}
vector<int> Solution::solve(string A, vector<string> &B) {
    TrieNode* root = getNode();
    convert(A);
    A+=" ";
    int l = A.size();
    int pre = 0;
    for (int i = 0; i < l; i++) {
        if(A[i] == ' ') {
            string temp = A.substr(pre, i-pre);
            pre = i+1;
            insert(root, temp);
        }
    }
     string word;
   
    stringstream ss;
    int cnt;
    vector<pair<int, int>> v;
    for (int i = 0; i < B.size(); i++) {
       ss.clear();
        for (int j = 0; j < B[i].size(); j++) {
            if(B[i][j] == '_') {
                B[i][j] = ' ';
            }
        }
        cnt = 0;
        ss<<B[i];
        while(ss>>word) {
            if(search(root, word)) {
                cnt++;
            }
        }
       
        v.push_back({cnt,i});
    }
    vector<int> ans;
    sort(v.begin(), v.end(), cmp);
    for (int i = 0; i < B.size(); i++) {
        ans.push_back(v[i].second);
    }
    return ans;
    
}
