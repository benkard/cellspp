CXX = clang++
CXXFLAGS = -g -O0 -stdlib=libc++ -std=c++11

.PHONY: all clean distclean

all: cells-test dynvars-test

dynvars-test: dynvars-test.cpp dynvars.hpp dynvars-impl.hpp
	$(CXX) $(CXXFLAGS) dynvars-test.cpp -o dynvars-test

cells-test: cells-test.cpp dynvars.hpp dynvars-impl.hpp cells.hpp cells-impl.hpp
	$(CXX) $(CXXFLAGS) cells-test.cpp   -o cells-test

clean:
	rm -f dynvars-test cells-test
	rm -rf dynvars-test.dSYM cells-test.dSYM

distclean: clean
	rm -f *~
