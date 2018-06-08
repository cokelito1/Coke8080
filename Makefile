CC=g++
CXXFLAGS=	-Wall				\
					-O2					\
					-I include	\
					-std=c++11	\
					-ggdb				\
					-c
VPATH=src
BUILDDIR=build

OBJ =	$(BUILDDIR)/cpu.o				\
			$(BUILDDIR)/machine.o		\
			$(BUILDDIR)/main.o

all: checkdirs main

main:	$(OBJ)
	$(CC) $(OBJ) -o main.elf

checkdirs: $(BUILDDIR)

$(BUILDDIR):
	@mkdir -p $@

$(BUILDDIR)/%.o: %.cpp
	$(CC) $(CXXFLAGS) $< -o $@

clean:
	rm -fr build main
