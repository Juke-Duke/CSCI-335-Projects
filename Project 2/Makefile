########################################
##
## Makefile
## LINUX compilation
##
##############################################

# Flags
C++FLAG = -g -std=c++14 -Wall

# Math library
MATH_LIBS = -lm
EXEC_DIR=.

# Rule for .cpp files
# .SUFFIXES : .cpp.o

.cc.o:
	g++ $(C++FLAG) $(INCLUDES)  -c $< -o $@

# Includes.
INCLUDES=  -I.
LIBS_ALL = -L/usr/lib -L/usr/local/lib $(MATH_LIBS)

ALL_OBJ0=query_tree.o
PROGRAM_0=query_tree
$(PROGRAM_0): $(ALL_OBJ0)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ0) $(INCLUDES) $(LIBS_ALL)

ALL_OBJ1=test_tree.o
PROGRAM_1=test_tree
$(PROGRAM_1): $(ALL_OBJ1)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ1) $(INCLUDES) $(LIBS_ALL)

ALL_OBJ2=test_tree_mod.o
PROGRAM_2=test_tree_mod
$(PROGRAM_2): $(ALL_OBJ2)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ2) $(INCLUDES) $(LIBS_ALL)

# Compiling all

all:
	make $(PROGRAM_0)
	make $(PROGRAM_1)
	make $(PROGRAM_2)

run1avl: all
	./$(PROGRAM_0) Tests/rebase210.txt < Tests/input_part2a.txt

run2avl: all
	./$(PROGRAM_1) Tests/rebase210.txt Tests/sequences.txt

run3avl: all
	./$(PROGRAM_2) Tests/rebase210.txt Tests/sequences.txt

# Clean obj files
clean:
	(rm -f *.o; rm -f test_tree; rm -f query_tree; rm -f test_tree_mod)

(:
