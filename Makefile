# Compiler and flags.
CXX := g++ -std=c++17 
FLAGS := -Wall -Werror -Wextra -Wconversion -pedantic -Wfloat-equal -Wduplicated-branches -Wduplicated-cond -Wshadow -Wdouble-promotion -Wundef
OPT := -O3 -DNDEBUG
DEBUG := -ggdb3 -DDEBUG

# Executable name and linked files without extensions.
EXE := demo
LINKED_FILES := color standard_color high_intensity_color rgb_color greyscale_color colored_string

# Expand the linked file names into lists of .cpp and .o files.
LINKED_CPP := $(foreach file, $(LINKED_FILES), $(file).cpp)
LINKED_O := $(foreach file, $(LINKED_FILES), $(file).o)

# Build optimized executable.
release : $(EXE).cpp $(LINKED_CPP)
	$(CXX) $(FLAGS) $(OPT) -c $(EXE).cpp $(LINKED_CPP)
	$(CXX) $(FLAGS) $(OPT) $(EXE).o $(LINKED_O) -o $(EXE)

# Build with debug features.
debug : $(EXE).cpp $(LINKED_CPP)
	$(CXX) $(FLAGS) $(DEBUG) -c $(EXE).cpp $(LINKED_CPP)
	$(CXX) $(FLAGS) $(DEBUG) $(EXE).o $(LINKED_O) -o $(EXE)

# Remove executable binary and generated objected files.
.PHONY : clean
clean : 
	rm -f $(EXE) $(EXE).o $(LINKED_O)
