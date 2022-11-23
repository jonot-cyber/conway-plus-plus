run: conway
	./$<

conway: conway.cc
	$(CXX) -O2 $^ -o $@
