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

ALL = borne_test bornes_list_test bornes_graph_test vehicule_test vehicule_list_test csv_handler_test utils_dijkstra_test

all : $(ALL) clean

#Borne
borne_test.o : $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS) -c src/test/borne_test.c

borne.o : $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS) -c src/borne.c

borne_test : borne.o borne_test.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

#Borne_list
bornes_list_test.o : $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS) -c src/test/bornes_list_test.c

bornes_list.o : $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS) -c src/bornes_list.c

bornes_list_test : bornes_list.o bornes_list_test.o borne.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

#Borne_graph
bornes_graph_test.o : $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS) -c src/test/bornes_graph_test.c

bornes_graph.o : $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS) -c src/bornes_graph.c

bornes_graph_test : borne.o bornes_list.o bornes_graph.o bornes_graph_test.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

#Vehicule
vehicule_test.o : $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS) -c src/test/vehicule_test.c

vehicule.o : $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS) -c src/vehicule.c

vehicule_test : vehicule.o vehicule_test.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

#vehicule_list
vehicule_list_test.o : $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS) -c src/test/vehicule_list_test.c

vehicule_list.o : $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS) -c src/vehicule_list.c

vehicule_list_test : vehicule_list.o vehicule_list_test.o vehicule.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

#csv_handler
csv_handler_test.o : $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS) -c src/test/csv_handler_test.c

csv_handler.o : $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS) -c src/csv_handler.c

csv_handler_test : csv_handler.o csv_handler_test.o borne.o bornes_list.o bornes_graph.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

#dijkstra
#dijkstra.o: $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
#	$(CC) $(CFLAGS) -c src/dijkstra.c

#dijkstra : dijkstra.o
#	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

#utils_dijkstra
utils_dijkstra.o: $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS) -c src/utils_dijkstra.c

utils_dijkstra_test.o: $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS) -c src/test/utils_dijkstra_test.c

utils_dijkstra_test : utils_dijkstra.o utils_dijkstra_test.o bornes_graph.o bornes_list.o borne.o vehicule.o vehicule_list.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^


#clean
clean :
	rm -f *.o
	rm -f bin/*
	rm -f src/include/*.gch
	mv $(ALL) bin/

#remake all the executables
remake :
	rm -f $(addprefix bin/, $(ALL))
	make all