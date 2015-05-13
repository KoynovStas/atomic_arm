CFLAGS     += -O2  -s  -Wall
GCC         =  arm-uid01_rev2_toolchain_buildroot-linux-uclibcgnueabi-gcc





# list of tests for build
TESTS  = atomic_test



.PHONY: all
all: clean  $(TESTS)



.PHONY: clean
clean:
	-@rm  *.o
	-@rm  *.*~
	-@rm  $(TESTS)



# Our implementation of atomic functions
atomic_arm.o:
	$(GCC)  -c atomic_arm.S $(CFLAGS)



.PHONY: $(TESTS)
$(TESTS): atomic_arm.o
	$(GCC)  $@.c -o $@  atomic_arm.o  $(CFLAGS)
	@echo "  ---- Compiled $@ ----"



.PHONY: debug
debug: CFLAGS  += -DDEBUG
debug: all



.PHONY: help
help:
	@echo "make [command]"
	@echo "command is:"
	@echo "   clean   -  remove all binary files"
	@echo "   all     -  clean and build all tests"
	@echo "   debug   -  build in debug mode (#define DEBUG 1)"
	@echo "   help    -  This help"

