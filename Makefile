CC=g++
CXXFLAGS=	-Wall					\
			-O3								\
			-I include				\
			-std=c++11				\
			-c

VPATH=src test
BUILDDIR=build

OBJ =	$(BUILDDIR)/cpu.o				\
			$(BUILDDIR)/machine.o		\
			$(BUILDDIR)/main.o

TEST_OBJ = $(BUILDDIR)/endianness.o

all: checkdirs main

main:	$(OBJ) $(TEST_OBJ)
	$(CC) $(OBJ) -o main.elf
	$(CC) $(TEST_OBJ) -o endiannes_test

checkdirs: $(BUILDDIR)

$(BUILDDIR):
	@mkdir -p $@

$(BUILDDIR)/%.o: %.cpp
	$(CC) $(CXXFLAGS) $< -o $@

clean:
	rm -fr build main.elf endiannes_test *.log
