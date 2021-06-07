CXX = g++
CXXFLAGS =
DEPS=rules.hxx trie.hxx spelling.hxx

spelling: spelling.cpp main.cpp $(DEPS)
	$(CXX) spelling.cpp main.cpp -o spelling

clean:
	rm spelling