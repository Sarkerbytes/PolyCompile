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
    compiler/c/lexer/Lexer_C.cpp \
    compiler/c/parser/Parser_C.cpp \
    compiler/c/semantic/Semantic_C.cpp \
    compiler/c/frontend/Frontend_C.cpp

# ----------------------------------------------------------
#  C++ Frontend sources
# ----------------------------------------------------------
CPP_FRONT_SRC = \
    compiler/cpp/lexer/Lexer_CPP.cpp \
    compiler/cpp/parser/Parser_CPP.cpp \
    compiler/cpp/semantic/Semantic_CPP.cpp \
    compiler/cpp/frontend/Frontend_CPP.cpp

# ----------------------------------------------------------
#  Java Frontend sources
# ----------------------------------------------------------
JAVA_FRONT_SRC = \
    compiler/java/lexer/Lexer_Java.cpp \
    compiler/java/parser/Parser_Java.cpp \
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

.PHONY: all win clean output test-c test-cpp test-java test-all \
        test-tokens-c test-ast-cpp test-tac-java test-opt-c test-asm-cpp
