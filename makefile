CC = clang
#clang = compiler
cflags.common := -Wall -Wextra -pedantic -fdiagnostics-color=always
#Wall = all warnings
#Wextra = extra warnings
#pedantic = all warnings demanded by strict ISO C and ISO C++
#fdiagnostics-color=always = colorize the output
cflags.debug := -Werror -O0
#Werror = treat all warnings as errors
#O0 = no optimization
cflags.release := -O2
#O2 = optimize even more
CFLAGS = $(cflags.common) $(cflags.$(BUILD))
LDFLAGS = -fsanitize=address -fsanitize=undefined
#fsanitize=address = enable address sanitizer
#fsanitize=undefined = enable undefined behavior sanitizer

#ALL = $(wildcard src/*_test.c)

ALL = borne_test bornes_list_test bornes_graph_test

all : $(ALL) clean

#Borne
borne_test.o : src/borne_test.c src/borne.h
	$(CC) $(CFLAGS) -c src/borne_test.c

borne.o : src/borne.c src/borne.h
	$(CC) $(CFLAGS) -c src/borne.c

borne_test : borne_test.o borne.o
	$(CC) $(CFLAGS) -o borne_test borne_test.o borne.o

#Borne_list
bornes_list_test.o : src/bornes_list_test.c src/bornes_list.h
	$(CC) $(CFLAGS) -c src/bornes_list_test.c

bornes_list.o : src/bornes_list.c src/bornes_list.h
	$(CC) $(CFLAGS) -c src/bornes_list.c

bornes_list_test : bornes_list_test.o bornes_list.o borne.o
	$(CC) $(CFLAGS) -o bornes_list_test bornes_list_test.o bornes_list.o borne.o

#Borne_graph
bornes_graph_test.o : src/bornes_graph_test.c src/bornes_graph.h
	$(CC) $(CFLAGS) -c src/bornes_graph_test.c

bornes_graph.o : src/bornes_graph.c src/bornes_graph.h
	$(CC) $(CFLAGS) -c src/bornes_graph.c

bornes_graph_test : bornes_graph_test.o bornes_graph.o borne.o
	$(CC) $(CFLAGS) -o bornes_graph_test bornes_graph_test.o bornes_graph.o borne.o

#clean
clean :
	rm -f *.o