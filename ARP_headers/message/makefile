OBJ := message
DEP := addresstable bitvector misc
CPPFLAGS := $(patsubst %, -I ../%, $(DEP))
DEP_SRC := addresstable.c bitvector.c random_index.c
VPATH := $(patsubst %, ../%:, $(DEP))

all: $(OBJ).o
	@echo $(OBJ) compiled
	
$(OBJ).o: $(OBJ).c $(OBJ).h $(DEP_SRC)
	gcc -c $(CPPFLAGS) -o $@ $<
	
.PHONY: clean

clean:
	rm -f $(OBJ).o