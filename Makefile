CXX = g++
CXXFLAGS =
DEPS=trie.hxx spelling.hxx

spelling: spelling.cpp trie.cpp $(DEPS)
	$(CXX) -c spelling.cpp -o spelling

clean:
	rm spelling