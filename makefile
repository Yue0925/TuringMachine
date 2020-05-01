SHELL=bash
GCC=g++ -std=c++11 -Wall -Wextra -Werror -Wno-sign-compare -O2 -Wno-deprecated

BIN = ./bin/
SRC = ./src/
INC = ./include/
VIS = ./visual/

EXEC=myTuring

.PHONY: 

clean:
	rm -f *.o $(INC)*.h.gch a.out $(VIS)*.dot $(VIS)*.pdf ./test/*.log

%.o: $(SRC)%.cc $(INC)%.h
	$(GCC) -c $< -o $@

$(BIN)$(EXEC) : Reader.o TuringMachine.o drawer.o argparse.o  $(INC)argparse.h $(SRC)run.cc
	$(GCC) Reader.o TuringMachine.o drawer.o argparse.o $(SRC)run.cc -o $@

#make ./bin/myTuring