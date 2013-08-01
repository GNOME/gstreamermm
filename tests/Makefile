CXX=g++
MODULES=gstreamermm-1.0
CXXFLAGS=-c -std=c++0x
CXXFLAGS+=$(shell pkg-config --cflags $(MODULES))
LDFLAGS = -lgtest -lpthread 
LDFLAGS+=$(shell pkg-config --libs $(MODULES))
SRC = $(wildcard *.cc plugins/*.cc)
OBJ = $(SRC:.cc=.o)
EXEC = test-all

all: $(SRC) $(EXEC)

$(EXEC): $(OBJ) 
	$(CXX) $(OBJ) -o $@ $(LDFLAGS) 

%.cpp%.o:
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXEC)
