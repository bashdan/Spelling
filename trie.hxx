#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype> // toupper
#include <algorithm>

#ifndef _TRIE_HXX_
#define _TRIE_HXX_

#define ALPHA_SIZE 26

class Trie {
    class TrieNode {
    public:
        bool endOfWord;
        TrieNode *children[ALPHA_SIZE];
        static TrieNode *create(void) {
            TrieNode *node = new TrieNode;
            node->endOfWord = false;
            for (auto i = 0; i < ALPHA_SIZE; i++) {
                node->children[i] = nullptr;
            }
            return node;
        }
        static void destroy(TrieNode *p) {
            for (auto i = 0; i < ALPHA_SIZE; i++) {
                if (p->children[i]) TrieNode::destroy(p->children[i]);
            }
            delete p;
        }
    }; // TrieNode

private:
        TrieNode *root;
        bool initialized;
    void print_rec(TrieNode *p, const std::string& s) {

        std::string r(s);
        if (p->endOfWord) std::cout << s << "\n";
        
        for (auto i = 0; i < ALPHA_SIZE; i++) {
            if (p->children[i]) {
                r.append(1, char('A'+i));
                print_rec(p->children[i], r);
                r.erase(r.size()-1);
            }
        }
    }
public:
    Trie(void) {
        this->root = TrieNode::create();
        this->initialized = true;
    }
    Trie(std::string filename) {
        
        std::ifstream fin(filename);
        if (!fin.is_open()) {
            std::cerr << "Error: couldn't open " << filename << std::endl;
            this->initialized = false;
            return;
        }

        this->root = TrieNode::create();
        this->initialized = true;
        std::string t;
        while (getline(fin, t)) {
            std::stringstream ss(t);
            std::string w;
            ss >> w;
            this->insert(w);
        }
        fin.close();
    }
    ~Trie(void) {
        TrieNode::destroy(this->root);
    }
    void print(void) {
        if (!this->initialized) {
            std::cerr << "Error: attempted to call print on uninitialized trie" << std::endl;
            return;
        }
        // prints newline if the tree is empty
        this->print_rec(this->root, "");
    }
    void insert(std::string s) {
        if (!this->initialized) {
            std::cerr << "Error: attempted to call insert on uninitialized trie" << std::endl;
            return;
        }
        // force capitalization
        std::transform(s.begin(), s.end(), s.begin(), toupper);
        TrieNode *t = this->root;
        const std::size_t len = s.size();
        for (std::size_t i = 0; i < len; i++) {
            auto c = s.at(i) - 'A';
            if (t->children[c] == nullptr) {
                t->children[c] = TrieNode::create();
            }
            t = t->children[c];
        }
        t->endOfWord = true;
    }
    bool isPrefix(std::string& s) {
        if (!this->initialized) {
            std::cerr << "Error: attempted to call isPrefix on uninitialized trie" << std::endl;
            exit(1);
        }
        TrieNode *t = this->root;
        std::transform(s.begin(), s.end(), s.begin(), toupper);
        for (auto c : s) {
            auto i = c - 'A';
            if (!t->children[i]) return false;
            t = t->children[i];
        }
        return true;
    }
    bool isWord(std::string& s) {
        if (!this->initialized) {
            std::cerr << "Error: attempted to call isWord on uninitialized trie" << std::endl;
            exit(1);
        }
        TrieNode *t = this->root;
        std::transform(s.begin(), s.end(), s.begin(), toupper);
        for (auto c : s) {
            auto i = c - 'A';
            if (!t->children[i]) return false;
            t = t->children[i];
        }
        return t->endOfWord;
    }
    
};

#endif
