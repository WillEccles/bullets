SRC=src/main.cpp
CXXFLAGS=-std=c++14 -O3
OUT=output

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)
