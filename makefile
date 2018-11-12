CFILE = $(wildcard lib/*.cpp)
OFILE = $(CFILE:.cpp=.o)
HFILE = $(CFILE:.cpp=.h)

CFLAGS = -Wall -lm -g -O
ARFLAGS = rcs

CXX = g++

LIBNAME = euler

all:
	$(CXX) -static main.cpp -l$(LIBNAME)

lib: $(OFILE)
	@ar $(ARFLAGS) lib$(LIBNAME).a $^
	@echo lib$(LIBNAME) created

%.o:%.cpp $(HFILE)
	@$(CXX) $(CFLAGS) -c $< -o $@
	@echo $@ created
