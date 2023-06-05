CC = clang
#clang = compiler
CFLAGS := -Wall -Wextra -pedantic -fdiagnostics-color=always -g -O2 -Werror
#Wall = all warnings
#Wextra = extra warnings
#pedantic = all warnings demanded by strict ISO C and ISO C++
#fdiagnostics-color=always = colorize the output
#Werror = treat all warnings as errors
#O0 = no optimization
#O2 = optimize even more
LDFLAGS = -fsanitize=address -fsanitize=undefined
#fsanitize=address = enable address sanitizer
#fsanitize=undefined = enable undefined behavior sanitizer

#ALL = $(wildcard src/*_test.c)

ALL = borne_test bornes_list_test bornes_graph_test vehicule_test vehicule_list_test csv_handler_test utils_dijkstra_test path_test app horaire_test itineraire_test itineraire_array_test

all : $(ALL) clean

#Borne
borne_test.o : $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS) -c src/test/borne_test.c

borne.o : $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS) -c src/borne.c

borne_test : borne.o borne_test.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^


