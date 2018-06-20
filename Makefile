CC=g++
CXXFLAGS=	-Wall					\
			-O3								\
			-I include				\
			-std=c++11				\
			-c
VPATH=src
BUILDDIR=build

OBJ =	$(BUILDDIR)/cpu.o				\
			$(BUILDDIR)/machine.o		\
			$(BUILDDIR)/main.o

all: checkdirs main

main:	$(OBJ)
	$(CC) $(OBJ) -o main.elf -lpthread

checkdirs: $(BUILDDIR)

$(BUILDDIR):
	@mkdir -p $@

$(BUILDDIR)/%.o: %.cpp
	$(CC) $(CXXFLAGS) $< -o $@

clean:
	rm -fr build main *.log
