OBJ := random_index

all: $(OBJ).o
	@echo $(OBJ) compiled
	
$(OBJ).o: $(OBJ).c $(OBJ).h
	gcc -c $< -o $@
	
.PHONY: clean

clean:
	rm -f $(OBJ).o