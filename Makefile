CXX = g++
CXXFLAGS =
DEPS=trie.hxx spelling.hxx

spelling: spelling.cpp trie.cpp $(DEPS)
	$(CXX) spelling.cpp trie.cpp -o spelling

clean:
	rm spelling