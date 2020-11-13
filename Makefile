EXECS = tester
OBJS = ASM.o ASMParser.o Instruction.o Opcode.o RegisterTable.o LabelTable.o

CC = g++
CCFLAGS = -std=c++11 -Wall -Wno-deprecated -Werror=return-type -g

all: $(EXECS)

tester: $(OBJS)
	$(CC) $(CCFLAGS) $^ -o $@

%.o: %.cpp *.h
	$(CC) $(CCFLAGS) -c $<

%.o: %.cpp
	$(CC) $(CCFLAGS) -c $<

clean:
	/bin/rm -f a.out $(OBJS) $(EXECS)
