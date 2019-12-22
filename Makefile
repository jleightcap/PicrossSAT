BIN  := solve 
SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)

CXXFLAGS := -g -Wall -pedantic -std=c++11

$(BIN): $(OBJS)
	$(CXX) -o $@ $(OBJS)

%.o: %.cpp $(wildcard *.h)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

test: $(BIN)
	(cd tests && make test)

clean:
	rm -f *.o $(BIN) && cd tests && make clean
