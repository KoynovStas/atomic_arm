CFLAGS     += -O2  -s  -Wall  -lpthread -lrt
#CFLAGS     += -D_GNU_SOURCE -std=c11

GCC         =  arm-uid01_rev2_toolchain_buildroot-linux-uclibcgnueabi-gcc
#GCC         = arm-gcc_4.9.2_cortex_a15-linux-uclibcgnueabi-gcc




# list of tests for build
TESTS  = atomic_test \
         atomic_vs_mutex_test \
         atomic_vs_spin_test  \
         atomic_vs_sem_test



.PHONY: all
all: clean  $(TESTS)



.PHONY: clean
clean:
	-@rm -f *.o
	-@rm -f *.*~
	-@rm -f $(TESTS)



# Our implementation of atomic functions
atomic_arm.o:
	$(GCC)  -c atomic_arm.S $(CFLAGS)



.PHONY: $(TESTS)
$(TESTS): atomic_arm.o
	$(GCC)  $@.c -o $@  atomic_arm.o  $(CFLAGS)
	@echo "  ---- Compiled $@ ----"
	@echo ""



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

