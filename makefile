CC = clang
#clang = compiler
CFLAGS := -Wall -Wextra -pedantic -fdiagnostics-color=always -g -O3 -Werror
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

ALL = borne_test borne_list_test borne_graph_test vehicule_test vehicule_list_test csv_handler_test utils_dijkstra_test path_test app horaire_test itineraire_test itineraire_array_test

all : $(ALL) clean

#Borne
borne_test.o : $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS) -c src/test/borne_test.c

borne.o : $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS) -c src/structs/borne.c

borne_test : borne.o borne_test.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^


#Borne_list
borne_list_test.o : $(wildcard src/structs/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS) -c src/test/borne_list_test.c

borne_list.o : $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS) -c src/structs/borne_list.c	

borne_list_test : borne_list.o borne_list_test.o borne.o timer.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

#Car
car_test.o : $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS) -c src/test/car_test.c

car.o : $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS) -c src/structs/car.c

car_test : car_test.o car.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

#Car_list
car_list_test.o : $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS) -c src/test/car_list_test.c

car_list.o : $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS) -c src/structs/car_list.c

car_list_test : car_list_test.o car_list.o car.o timer.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
    

#Timer
timer.o : $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS) -c src/utils/timer.c

clean :
	rm -f *.o
	rm -f bin/*
	rm -f src/include/*.gch
	mv $(ALL) bin/

remake :
	rm -f $(addprefix bin/, $(ALL))
	make all

