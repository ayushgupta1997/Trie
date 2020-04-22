class Solution {
 public:

    struct TrieNode {
        TrieNode *child[26];  
        bool eow;
    };
    
    TrieNode* make_node() {
        TrieNode* node = new TrieNode;
        node->eow = false;
        for (int i = 0; i < 26; i++) {
            node->child[i] = NULL;
        }
        return node;
    }
    
    void make_trie(TrieNode* root, string s) {
        int l = s.size();
        TrieNode* crawl = root;
        for (int i = 0; i < l; i++) {
            if(!crawl->child[(s[i]-'a')]) {
               crawl->child[s[i]-'a'] = make_node();
            }
           crawl = crawl->child[s[i]-'a'];
        }
        crawl->eow = true;
    }
    
    void searchSugg(TrieNode* root, string s, vector<string> &words) {
        if(words.size()==3) {
            return;
        }
        if(root->eow) {
            words.push_back(s);
        } 
        for (int i = 0; i < 26; i++){
            if(root->child[i]){
                s.push_back((char)(i+'a'));
                searchSugg(root->child[i],s, words);
                s.pop_back();
            }
        }
    }
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        vector<vector<string>> ans;
        int n = products.size();
        TrieNode* root = make_node();
        for (int i = 0; i < n; i++) {
            make_trie(root, products[i]);
        }
        int l = searchWord.size();
        string word;
        for (int i = 0; i < l; i++) {
            vector<string> words;
            word += searchWord[i];
            TrieNode *cur = root;
            bool ok = true;
            for (char c: word) {
                if (!cur->child[c - 'a']) {
                    ok =false;
                    break;
                }
                cur = cur->child[c - 'a'];
            }
            if(ok){
                searchSugg(cur, word, words);
            }
            ans.push_back(words);
        }
        return ans;
    }
};
