################################################################################
#
# Makefile @[src/codegen_arith]
#
################################################################################

default: run



################################################################################
#
# project environment
#
################################################################################

#detect upper directories
updir1 = $(abspath $(PWD)/..)
updir2 = $(abspath $(updir1)/..)
updir3 = $(abspath $(updir2)/..)
updir4 = $(abspath $(updir3)/..)
updir5 = $(abspath $(updir4)/..)

#set project environment
export PROJHOME = $(updir2)



################################################################################
#
# generate lexical analyzer and parser source
#
################################################################################

GEN_SRC_FILES += lexer.h
GEN_SRC_FILES += parser.h
GEN_SRC_FILES += lex.yy.cpp
GEN_SRC_FILES += parser.tab.cpp
GEN_SRC_FILES += lexer.h

lexer.h lex.yy.cpp: lexer.flex
	flex --header-file=lexer.h --outfile=lex.yy.cpp $^

parser.h parser.tab.cpp: parser.y
	bison --defines=parser.h --output=parser.tab.cpp $^

gen: $(GEN_SRC_FILES)

gen.clean:
	rm -f $(GEN_SRC_FILES)
	rm -f stack.hh


################################################################################
#
# compilation rules
#
################################################################################

CC = g++

INC_DIRS += .

PROG_MODULES += SymbTbl Instruction InstructionList
PROG_MODULES += ParseTreeNode ParseTree

HEADER_FILES += $(addsuffix .h, $(PROG_MODULES))
HEADER_FILES += codegen.h
HEADER_FILES += lexer.h parser.h

CPP_SRC_FILES += $(addsuffix .cpp, $(PROG_MODULES))
CPP_SRC_FILES += parser.tab.cpp lex.yy.cpp
CPP_SRC_FILES += codegen_arith.cpp

OBJFILES += $(addsuffix .o, $(PROG_MODULES))
OBJFILES += parser.tab.o lex.yy.o
OBJFILES += codegen_arith.o

EXE_FILES += codegen_arith.exe

CCFLAGS += -g
CCFLAGS += $(addprefix -I, $(INC_DIRS))

#LINK_FLAGS += -lfl

%.o: $(HEADER_FILES) %.cpp
	$(CC) -c $(CCFLAGS) $*.cpp

%.exe: $(OBJFILES) %.o
	$(CC) $(LINK_FLAGS) $^ -o $@

compile: $(EXE_FILES)

objfiles: $(OBJFILES)

compile.clean_tmp:
	rm -f *.o

compile.clean: compile.clean_tmp
	rm -f *.exe



################################################################################
#
# user interface
#
################################################################################

all: $(EXE_FILES)

run: codegen_arith.exe
	./$<

clean_tmp: compile.clean_tmp

clean: compile.clean gen.clean
	rm -f *.out

show_var:
	@echo HEADER_FILES=$(HEADER_FILES)



