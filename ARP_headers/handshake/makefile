OBJ := handshake
DEP := bitvector addresstable
CPPFLAGS := $(patsubst %, -I ../%, $(DEP))
# LIBS := $(patsubst %, ../%/%.h, $(DEP))
DEP_SRC := $(patsubst %, %.c, $(DEP))
VPATH := $(patsubst %, ../%:, $(DEP))

all: $(OBJ).o
	@echo $(OBJ) compiled
	
$(OBJ).o: $(OBJ).c $(OBJ).h version.h $(DEP_SRC)
	gcc -c $(CPPFLAGS) -o $@ $<
	
.PHONY: clean

clean:
	rm -f $(OBJ).o