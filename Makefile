# ============================================================
#  PolyCompiler Makefile
#  Multi-Language Compiler: C, C++, Java
# ============================================================

CXX      = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

TARGET   = polycompile

# ----------------------------------------------------------
#  Common sources
# ----------------------------------------------------------
COMMON_SRC = \
    compiler/common/Utilities/DiagnosticEngine.cpp \
    compiler/common/IR/IRGenerator.cpp \
    compiler/common/Optimizer/Optimizer.cpp \
    compiler/common/CodeGen/CodeGenerator.cpp \
    compiler/common/Executor/Executor.cpp

# ----------------------------------------------------------
#  C Frontend sources
# ----------------------------------------------------------
C_FRONT_SRC = \
    compiler/c/semantic/Semantic_C.cpp \
    compiler/c/frontend/Frontend_C.cpp

# ----------------------------------------------------------
#  C++ Frontend sources
# ----------------------------------------------------------
CPP_FRONT_SRC = \
    compiler/cpp/semantic/Semantic_CPP.cpp \
    compiler/cpp/frontend/Frontend_CPP.cpp

# ----------------------------------------------------------
#  Java Frontend sources
# ----------------------------------------------------------
JAVA_FRONT_SRC = \
    compiler/java/semantic/Semantic_Java.cpp \
    compiler/java/frontend/Frontend_Java.cpp

# ----------------------------------------------------------
#  All sources
# ----------------------------------------------------------
SRCS = \
    main.cpp \
    $(COMMON_SRC) \
    $(C_FRONT_SRC) \
    $(CPP_FRONT_SRC) \
    $(JAVA_FRONT_SRC)

OBJS = $(SRCS:.cpp=.o)

# ----------------------------------------------------------
#  Default target: build polycompile
# ----------------------------------------------------------
all: output $(TARGET)
	@echo ""
	@echo "  PolyCompiler built successfully!"
	@echo "  Run: ./$(TARGET) --help"
	@echo ""

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ----------------------------------------------------------
#  Create output directory
# ----------------------------------------------------------
output:
	@mkdir -p output

# ----------------------------------------------------------
#  Test targets
# ----------------------------------------------------------
test-c: all
	@echo "--- Testing C Frontend ---"
	./$(TARGET) --debug examples/hello.c

test-cpp: all
	@echo "--- Testing C++ Frontend ---"
	./$(TARGET) --debug examples/hello.cpp

test-java: all
	@echo "--- Testing Java Frontend ---"
	./$(TARGET) --debug examples/Hello.java

test-all: test-c test-cpp test-java
	@echo "--- All tests completed ---"

test-tokens-c: all
	@echo "--- Tokens (C) ---"
	./$(TARGET) --tokens examples/hello.c

test-ast-cpp: all
	@echo "--- AST (C++) ---"
	./$(TARGET) --ast examples/hello.cpp

test-tac-java: all
	@echo "--- TAC (Java) ---"
	./$(TARGET) --tac examples/Hello.java

test-opt-c: all
	@echo "--- Optimized TAC (C) ---"
	./$(TARGET) --opt examples/hello.c

test-asm-cpp: all
	@echo "--- Assembly (C++) ---"
	./$(TARGET) --asm examples/hello.cpp

# ----------------------------------------------------------
#  Windows build target (using g++ on MinGW)
# ----------------------------------------------------------
win: output $(TARGET).exe
	@echo ""
	@echo "  PolyCompiler (Windows) built successfully!"
	@echo "  Run: $(TARGET).exe --help"
	@echo ""

$(TARGET).exe: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# ----------------------------------------------------------
#  Clean
# ----------------------------------------------------------
clean:
	@rm -f $(OBJS)
	@rm -f $(TARGET) $(TARGET).exe
	@rm -f output/*.txt output/*.asm
	@echo "Cleaned build artifacts."

# ----------------------------------------------------------
#  Flex + Bison  –  C Language
#  Step 1: bison -d generates parser_c.tab.c + parser_c.tab.h
#  Step 2: flex  generates lex.yy_c.c (needs parser_c.tab.h)
#  Step 3: g++   links both into test_c / test_c.exe
# ----------------------------------------------------------
FLEX  = flex
BISON = bison

C_LEXER_L   = compiler/c/lexer/lexer_c.l
C_PARSER_Y  = compiler/c/parser/parser_c.y
C_LEX_C     = compiler/c/lexer/lex.yy_c.c
C_TAB_C     = compiler/c/parser/parser_c.tab.c
C_TAB_H     = compiler/c/parser/parser_c.tab.h

bison-c:
	$(BISON) -d -o $(C_TAB_C) $(C_PARSER_Y)
	@cp $(C_TAB_H) compiler/c/lexer/parser_c.tab.h

flex-c: bison-c
	$(FLEX) -o $(C_LEX_C) $(C_LEXER_L)

test-fb-c: flex-c
	g++ -std=gnu++11 -w -o test_c.exe $(C_TAB_C) $(C_LEX_C)
	@echo "Built: test_c.exe  ->  run: test_c.exe examples/hello.c"

# ----------------------------------------------------------
#  Flex + Bison  –  C++ Language
# ----------------------------------------------------------
CPP_LEXER_L  = compiler/cpp/lexer/lexer_cpp.l
CPP_PARSER_Y = compiler/cpp/parser/parser_cpp.y
CPP_LEX_C    = compiler/cpp/lexer/lex.yy_cpp.c
CPP_TAB_C    = compiler/cpp/parser/parser_cpp.tab.c
CPP_TAB_H    = compiler/cpp/parser/parser_cpp.tab.h

bison-cpp:
	$(BISON) -d -o $(CPP_TAB_C) $(CPP_PARSER_Y)
	@cp $(CPP_TAB_H) compiler/cpp/lexer/parser_cpp.tab.h

flex-cpp: bison-cpp
	$(FLEX) -o $(CPP_LEX_C) $(CPP_LEXER_L)

test-fb-cpp: flex-cpp
	g++ -std=gnu++11 -w -o test_cpp.exe $(CPP_TAB_C) $(CPP_LEX_C)
	@echo "Built: test_cpp.exe  ->  run: test_cpp.exe examples/hello.cpp"

# ----------------------------------------------------------
#  Flex + Bison  –  Java Language
# ----------------------------------------------------------
JAVA_LEXER_L  = compiler/java/lexer/lexer_java.l
JAVA_PARSER_Y = compiler/java/parser/parser_java.y
JAVA_LEX_C    = compiler/java/lexer/lex.yy_java.c
JAVA_TAB_C    = compiler/java/parser/parser_java.tab.c
JAVA_TAB_H    = compiler/java/parser/parser_java.tab.h

bison-java:
	$(BISON) -d -o $(JAVA_TAB_C) $(JAVA_PARSER_Y)
	@cp $(JAVA_TAB_H) compiler/java/lexer/parser_java.tab.h

flex-java: bison-java
	$(FLEX) -o $(JAVA_LEX_C) $(JAVA_LEXER_L)

test-fb-java: flex-java
	g++ -std=gnu++11 -w -o test_java.exe $(JAVA_TAB_C) $(JAVA_LEX_C)
	@echo "Built: test_java.exe  ->  run: test_java.exe examples/Hello.java"

# ----------------------------------------------------------
#  Build ALL three Flex/Bison parsers at once
# ----------------------------------------------------------
fb-all: test-fb-c test-fb-cpp test-fb-java
	@echo ""
	@echo "  All three Flex/Bison parsers built:"
	@echo "    test_c.exe      (C parser)"
	@echo "    test_cpp.exe    (C++ parser)"
	@echo "    test_java.exe   (Java parser)"
	@echo ""

# ----------------------------------------------------------
#  Clean Flex/Bison generated files
# ----------------------------------------------------------
clean-fb:
	@rm -f $(C_LEX_C) $(C_TAB_C) $(C_TAB_H)
	@rm -f compiler/c/lexer/parser_c.tab.h
	@rm -f $(CPP_LEX_C) $(CPP_TAB_C) $(CPP_TAB_H)
	@rm -f compiler/cpp/lexer/parser_cpp.tab.h
	@rm -f $(JAVA_LEX_C) $(JAVA_TAB_C) $(JAVA_TAB_H)
	@rm -f compiler/java/lexer/parser_java.tab.h
	@rm -f test_c.exe test_cpp.exe test_java.exe
	@echo "Cleaned Flex/Bison generated files."

.PHONY: all win clean output test-c test-cpp test-java test-all \
        test-tokens-c test-ast-cpp test-tac-java test-opt-c test-asm-cpp \
        bison-c flex-c test-fb-c \
        bison-cpp flex-cpp test-fb-cpp \
        bison-java flex-java test-fb-java \
        fb-all clean-fb
