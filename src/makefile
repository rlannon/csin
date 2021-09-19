SRC_DIR=.
PARSER_DIR=./parser
OBJ_DIR=./bin
PARSER_DIR=$(SRC_DIR)/parser
STATEMENT_DIR=$(PARSER_DIR)/statement
EXPRESSION_DIR=$(PARSER_DIR)/expression
SRC_FILES=$(wildcard $(PARSER_DIR)/*.cpp $(PARSER_DIR)/statement/*.cpp $(PARSER_DIR)/expression/*.cpp $(SRC_DIR)/util/*.cpp $(SRC_DIR)/cgen/*.cpp $(SRC_DIR)/cgen/common/*.cpp)
OBJ_FILES=$(patsubst %.cpp, $(OBJ_DIR)/%.o, $(notdir $(SRC_FILES)))
cc=g++
cppversion=c++17
flags=-std=$(cppversion) -g
target=csin

default: $(target)

$(target): $(OBJ_FILES)
	@echo Finishing build...
	$(cc) $(flags) -o $@ main.cpp $^
	@echo Done.

$(OBJ_DIR)/%.o: $(PARSER_DIR)/statement/%.cpp
	$(cc) $(flags) -c -o $@ $<

$(OBJ_DIR)/%.o: $(PARSER_DIR)/expression/%.cpp
	$(cc) $(flags) -c -o $@ $<

$(OBJ_DIR)/%.o: $(PARSER_DIR)/%.cpp
	$(cc) $(flags) -c -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/util/%.cpp
	$(cc) $(flags) -c -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/compile/%.cpp
	$(cc) $(flags) -c -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/compile/generators/%.cpp
	$(cc) $(flags) -c -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/compile/common/%.cpp
	$(cc) $(flags) -c -o $@ $<

clean:
	rm bin/*.o

.PHONY: $(target) clean
