#include <sstream>
#include <fstream>

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

std::vector<std::string> &anagram(std::vector<std::string> &v, Trie &t, const std::string s) {

    std::string newstr(s);
    do {
        if (t.isWord(newstr)) v.push_back(newstr);
    }
    while (std::next_permutation(newstr.begin(), newstr.end()));
    return v;
}

std::vector<std::string> &anagram_wildcards(std::vector<std::string> &v, Trie &t, const std::string& s) {

    static const std::string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static const std::string WILDCARDS = "*%?";
    auto contains_wildcards = [](const std::string& str) {
        for (auto c : str)
            for (auto w : WILDCARDS)
                if (c == w) return true;
        return false;
    };
    // First, replace all the wildcards
    v.push_back(s);
    for (std::size_t i = 0; i < v.size();) {
        std::string t(v.at(i));
        bool reduced = false;
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
    // Second, prune the vector of non-words
    for (auto i = 0; i < v.size();) {
        if (t.isWord(v.at(i))) {
            i++;
        } else {
            v.erase(v.begin()+i);
        }
    }
    v.shrink_to_fit();
    return v;
}