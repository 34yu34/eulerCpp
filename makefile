CFILE = $(wildcard lib/*.cpp)
OFILE = $(CFILE:.cpp=.o)
HFILE = $(CFILE:.cpp=.h)
EULERFILE = $(wildcard euler*.cpp)
EULEROUT = $(EULERFILE:.cpp=.out)
INC = lib

CFLAGS = -I $(INC) -MMD -Wall -lm -g -O
ARFLAGS = rcs

CXX = g++

LIBNAME = euler
LIBTRG = lib$(LIBNAME).a


all: $(LIBTRG) $(EULEROUT) 

%.out:%.cpp
	@$(CXX) $(CFLAGS) -static $< -o $@ -L . -l $(LIBNAME)
	@echo $@ created

$(LIBTRG): $(OFILE)
	@ar $(ARFLAGS) $(LIBTRG) $^
	@echo $(LIBTRG) created

%.o:%.cpp $(HFILE)
	@$(CXX) $(CFLAGS) -c $< -o $@
	@echo $@ created

-include *.d */*.d

clean:
	@rm *.out *.a **/*.o **/*.d *.d
