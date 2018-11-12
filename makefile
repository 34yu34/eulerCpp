CFILE = $(wildcard lib/*.cpp)
OFILE = $(CFILE:.cpp=.o)
HFILE = $(CFILE:.cpp=.h)
EULERFILE = $(wildcard euler*.cpp)
EULEROUT = $(EULERFILE:.cpp=.out)

CFLAGS = -Wall -lm -g -O
ARFLAGS = rcs

CXX = g++

LIBNAME = euler
LIBTRG = lib$(LIBNAME).a


all: $(EULEROUT) $(LIBTRG)

%.out:%.cpp
	@$(CXX) -static $< -o $@ -L . -l $(LIBNAME)
	@echo

$(LIBTRG): $(OFILE)
	@ar $(ARFLAGS) $(LIBTRG) $^
	@echo $(LIBTRG) created

%.o:%.cpp $(HFILE)
	@$(CXX) $(CFLAGS) -c $< -o $@
	@echo $@ created
