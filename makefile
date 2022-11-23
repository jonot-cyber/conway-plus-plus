run: conway
	./$<

conway: conway.cc
	$(CXX) -O2 -std=c++20 $^ -o $@
