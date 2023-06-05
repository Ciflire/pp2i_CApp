# Made by Xavie Monard
CC=clang
CFLAGS=-std=c99 -Wall -Wextra -pedantic -fdiagnostics-color=always
CFLAGS+=-O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls
SRC= source/
OUT= executable/

# Implicit rules
%.o: $(SRC)%.c $(SRC)%.h
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: $(SRC)structure/%.c $(SRC)structure/%.h
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: $(SRC)%.c $(SRC)*.h
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: $(SRC)%.c
	$(CC) $(CFLAGS) -c -o $@ $<

%: %.o
	$(CC) $(CFLAGS) $^ -o $(OUT)$@

%: %.o *.o
	$(CC) $(CFLAGS) $^ -o $(OUT)$@

%:
	$(CC) $(CFLAGS) $^ -o $(OUT)$@
