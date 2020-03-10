CLIBFILE = $(wildcard lib/*.cpp)
TESTFILE = $(wildcard tests/test*.h)
OLIBFILE = $(CLIBFILE:.cpp=.o)
EULERFILE = $(wildcard euler*.cpp)
EULEROUT = $(EULERFILE:.cpp=.out)
TESTCOMPILER = $(wildcard test*.cpp)
TESTOUT = $(TESTCOMPILER:.cpp=.out)
INC = lib
TESTFOLDER = tests

CFLAGS = -I $(INC) -I $(TESTFOLDER) -MMD -Wall -lm -g -O
ARFLAGS = rcs

CXX = g++

LIBNAME = euler
LIBTRG = lib$(LIBNAME).a


all: $(LIBTRG) $(EULEROUT)

test:  $(LIBTRG) $(TESTOUT)
	@./$(TESTOUT)

$(LIBTRG): $(OLIBFILE)
	@ar $(ARFLAGS) $(LIBTRG) $^
	@echo $(LIBTRG) created

%.out:%.cpp
	@$(CXX) $(CFLAGS) -static $< -o $@ -L . -l $(LIBNAME)
	@echo $@ created

%.o:%.cpp
	@$(CXX) $(CFLAGS) -c $< -o $@
	@echo $@ created

-include *.d */*.d

clean:
	@rm *.out *.a *.o **/*.o **/*.d *.d
