CPP_FILES := $(wildcard *.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
LD_FLAGS := -gstabs+
CC_FLAGS := -gstabs+

SudokuSolver: $(OBJ_FILES)
	g++ $(LD_FLAGS) -o $@ $^

obj/%.o: %.cpp
	g++ $(CC_FLAGS) -c -o $@ $<

clean: $(OBJ_FILES)
	rm $(OBJ_FILES)