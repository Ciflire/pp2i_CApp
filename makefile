CC = clang
#clang = compiler
CFLAGS := -Wall -Wextra -pedantic -fdiagnostics-color=always -Werror -g -O3 
#Wall = all warnings
#Wextra = extra warnings
#pedantic = all warnings demanded by strict ISO C and ISO C++
#fdiagnostics-color=always = colorize the output
#Werror = treat all warnings as errors
#O0 = no optimization
#O2 = optimize even more
LDFLAGS =  -fsanitize=undefined -lm #-fsanitize=address
#fsanitize=address = enable address sanitizer
#fsanitize=undefined = enable undefined behavior sanitizer

#ALL = $(wildcard src/*_test.c)

ALL = borne_test borne_list_test  data_importer_test car_test car_list_test pathFinding_test horaire_test horaire_list_test app

OBJ = borne.o borne_list.o car.o car_list.o horaire.o horaire_list.o csvParser.o line_array.o line.o data_importer.o timer.o pathfinding.o time_wait.o

all : $(ALL) clean

#App
app.o : $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS) -c  src/utils/app.c
app : $(OBJ) app.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^


#Borne
borne_test.o : $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS) -c src/test/borne_test.c

borne.o : $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS) -c src/structs/borne.c

borne_test : $(OBJ) borne_test.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^


#Borne_list
borne_list_test.o : $(wildcard src/structs/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS) -c src/test/borne_list_test.c

borne_list.o : $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS) -c src/structs/borne_list.c	

borne_list_test : $(OBJ) borne_list_test.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

#Car
car_test.o : $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS) -c src/test/car_test.c

car.o : $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS) -c src/structs/car.c

car_test : $(OBJ) car_test.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

#Car_list
car_list_test.o : $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS) -c src/test/car_list_test.c

car_list.o : $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS) -c src/structs/car_list.c

car_list_test : $(OBJ) car_list_test.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

#horaire
horaire.o: $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS) -c  src/structs/horaire.c

horaire_test.o: $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS) -c src/test/horaire_test.c

horaire_test: $(OBJ) horaire_test.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

#horaire_list
horaire_list.o: $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS)  -c src/structs/horaire_list.c

horaire_list_test.o: $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS)  -c src/test/horaire_list_test.c

horaire_list_test: $(OBJ) horaire_list_test.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

#csvParser
csvParser.o : $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS) -c src/utils/csvParser.c

line_array.o : $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS) -c src/structs/line_array.c

#Line
line.o : $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS) -c  src/structs/line.c

#Data_importer & Parser
data_importer_test.o : $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS) -c src/test/data_importer_test.c

data_importer.o : $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS) -c src/utils/data_importer.c

data_importer_test : data_importer_test.o $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

#time_wait
time_wait.o : $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) -c src/utils/time_wait.c

#Timer
timer.o : $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS) -c src/utils/timer.c

#pathFinding
pathFinding_test.o : $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS) -c  src/test/pathFinding_test.c

pathfinding.o : $(wildcard src/*.c) $(wildcard src/include/*.h) $(wildcard src/test/*.c)
	$(CC) $(CFLAGS) -c  src/utils/pathfinding.c

pathFinding_test : pathFinding_test.o $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

clean :
	rm -f *.o
	rm -f bin/*
	rm -f src/include/*.gch
	mv $(ALL) bin/

remake :
	rm -f $(addprefix bin/, $(ALL))
	make all

