#include <sstream>
#include <fstream>
#include <set>
#include <vector>
#include <list>

#include "spelling.hxx"
#include "trie.hxx"

void transform_file(const std::string &filename_in, const std::string &filename_out) {
    
    std::ifstream fin(filename_in);
    if (!fin.is_open()) {
        std::cerr << "Error: couldn't open " << filename_in << std::endl;
        exit(1);
    }
    std::ofstream fout(filename_out);
    if (!fout.is_open()) {
        std::cerr << "Error: couldn't open " << filename_out << std::endl;
        fin.close();
        exit(1);
    }
    auto cond_toupper = [](char c) {
        return (c >= 'a' && c <= 'z') ? char(c+('A'-'a')) : c;
    };

    std::string t;
    while (getline(fin, t)) {
        std::stringstream ss(t);
        std::string newstr;
        while (ss >> newstr) {
            std::transform(newstr.begin(), newstr.end(), newstr.begin(), cond_toupper);
            newstr.append("\n");
            fout << newstr;
        }
    }
    fin.close();
    fout.close();
}


std::vector<std::string> &permutate(std::vector<std::string> &v, const std::string s) {

    std::string newstr(s);
    do {
        v.push_back(newstr);
    }
    while (std::next_permutation(newstr.begin(), newstr.end()));
    return v;
}

std::vector<std::string> &anagram(std::vector<std::string> &v, Trie &t, const std::string& s) {

    std::string newstr(s);
    do {
        if (t.isWord(newstr)) v.push_back(newstr);
    }
    while (std::next_permutation(newstr.begin(), newstr.end()));
    // Remove duplicates
    sort(v.begin(), v.end());
    auto last = std::unique(v.begin(), v.end());
    v.erase(last, v.end());
    v.shrink_to_fit();
    return v;
}

std::vector<std::string> &anagram_wildcards(std::vector<std::string> &v, Trie &t, const std::string& s) {

    static const std::string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static const std::string WILDCARDS = "*%?";
    
    // First, replace all the wildcards
    v.push_back(s);
    bool reduced;
    for (std::size_t i = 0; i < v.size();) {
        std::string t(v.at(i));
        reduced = false;
        for (auto w : WILDCARDS) {
            std::size_t pos;
            if ((pos = t.find(w, 0)) != std::string::npos) {
                reduced = true;
                for (auto a : ALPHABET) {
                    t.at(pos) = a;
                    v.push_back(t);
                }
            }
        }
        // Erasing at an index implies we should look at that index again
        if (reduced) {
            v.erase(v.begin()+i);
        } else {
            i++; // Nothing was erased, so move along
        }
    }
    // All wildcards are removed
    // Continue generating permutations from natural chars and return words
    std::vector<std::string> w(v);
    v.clear();
    for (const auto &cs : w) {
        std::string newstr(cs);
        do {
            if (t.isWord(newstr)) v.push_back(newstr);
        }
        while (std::next_permutation(newstr.begin(), newstr.end()));
    }
    // Remove duplicates O(n lg n)
    sort(v.begin(), v.end());
    auto last = std::unique(v.begin(), v.end());
    v.erase(last, v.end());
    v.shrink_to_fit();
    return v;
}

void string_powerset(std::list<std::string> &out, const std::string &str) {

    const std::size_t len = str.length();
    for (auto i = 0; i < (2 << len); i++) {
        std::string temp = "";
        for (auto b = 0; b < len; b++)
            if (i & (1 << b)) temp += str.at(b);
        out.push_back(temp);
    }
}

std::vector<std::string> &anagram_exhaustively(std::vector<std::string> &v, Trie &t, const std::string &s) {

    std::list<std::string> str_ps;
    string_powerset(str_ps, s);
    // remove entries that are too short
    for (auto it = str_ps.begin(); it != str_ps.end();) {
        if ((*it).size() > 1) it++;
        else it = str_ps.erase(it); // list erasure is faster than vector erasure
    }

    for (auto new_s : str_ps) {
        v = anagram_wildcards(v, t, new_s);
    }

    return v;
}

void benchmark(const std::string &str) {

    std::vector<std::string> v;
    auto start = std::chrono::steady_clock::now();
    Trie twl(TWL3);
    Trie collins(COLLINS);

    v = anagram_exhaustively(v, twl, str);
    v.clear();
    v = anagram_exhaustively(v, collins, str);

    auto stop = std::chrono::steady_clock::now();

    std::cout << "Benchmark time: " 
        << std::chrono::duration<double>(stop-start).count() << " s" << std::endl;
}