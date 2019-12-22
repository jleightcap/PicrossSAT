SRCS  := $(wildcard *.cpp)
OBJS  := $(filter-out ../solve.o, $(wildcard ../*.o))
PROGS := $(patsubst %.cpp, %, $(SRCS))

CXXFLAGS := -g -Wall -lgtest -lgtest_main -I ..

all: $(PROGS)

%: %.cpp sources
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $<

sources:
	cd .. && make

test: all 
	for ii in *.cpp; do echo $$ii && ./$${ii%%.*}; done && make clean

clean:
	rm -f *.o $(PROGS) 
