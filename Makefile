CC = gcc
CFLAGS = -Wall -g -I src/include
    
DEPEND = src/interpreter.o src/instruction.o src/ops.o src/debug.o src/vm.o

default: uvm

uvm: src/main.o $(DEPEND)
	$(CC) $(CFLAGS) src/main.o $(DEPEND) -o $@

ussembler: src/assembler.o $(DEPEND)
	$(CC) $(CFLAGS) src/assembler.o $(DEPEND) -o $@

clean:
	rm -f src/*.o
	rm -f uvm
