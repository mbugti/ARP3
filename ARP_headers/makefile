
SUBDIRS = addresstable misc bitvector connection handshake initstep message statistics
# VPATH := $(patsubst %, %:, $(SUBDIRS))
DEP_OBJ := $(foreach dir, $(SUBDIRS), $(wildcard $(dir)/*.o))

all: libarpnet.a
	@echo static library compiled

.PHONY: subdirs $(SUBDIRS) clean all

subdirs: $(SUBDIRS)

$(SUBDIRS):
	+$(MAKE) -s -C $@

libarpnet.a: $(SUBDIRS) $(DEP_OBJ)
	ar rc $@ $(DEP_OBJ)
	ranlib $@
	
clean:
	rm -rf $(DEP_OBJ)
# to compile the source simply do
# gcc -L <path_to_ARP_headers> -o file file.c -larpnet
# after including "arpnet.h" in the file