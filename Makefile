EXECS = tester
OBJS =  ASMParser.o Instruction.o Opcode.o RegisterTable.o LabelTable.o ALU.o ALUControlUnit.o Multiplexer.o PC.o RegisterFile.o RegisterMemory.o ShiftLeft.o SignExtend.o DataMemory.o MainProcessor.o ControlUnit.o test.o

CC = g++
CCFLAGS = -std=c++17 -Wall -Wno-deprecated -Werror=return-type -g

all: $(EXECS)

tester: $(OBJS)
	$(CC) $(CCFLAGS) $^ -o $@

%.o: %.cpp *.h
	$(CC) $(CCFLAGS) -c $<

%.o: %.cpp
	$(CC) $(CCFLAGS) -c $<

clean:
	/bin/rm -f a.out $(OBJS) $(EXECS)
