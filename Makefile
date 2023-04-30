# Define variables
CC = gcc
CFLAGS = -std=c11 -Wall -g
SRCDIR = src
SOURCES = $(wildcard $(SRCDIR)/*.c)
HEADERS = $(SRCDIR)/structures.h
TEST_SRC=$(wildcard $(SRCDIR)/test_*.c)
TEST_OBJ=$(patsubst $(SRCDIR)/%.c,$(SRCDIR)/%.o,$(TEST_SRC))
TEST_FILES=$(TEST_SRC:.c=)
TEST_TARGETS=$(TEST_SRC:$(SRCDIR)/%.c=%)
TEST_OUTPUT=$(patsubst %,bin/%,$(TEST_TARGETS))
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(SRCDIR)/%.o,$(SOURCES))

LOG= bin/log
EXECUTABLE = chess

# Default target
all: $(EXECUTABLE)

# Build target
$(EXECUTABLE): $(filter-out $(TEST_OBJ),$(OBJECTS))
	$(CC) $(CFLAGS) $(filter-out $(TEST_OBJ),$(OBJECTS)) -o bin/$(EXECUTABLE)

test_1:$ test_1.o $(filter-out $(SRCDIR)/main.o $(TEST_OBJ), $(OBJECTS))
	$(CC) $(CFLAGS) $^ -o bin/$@

test_2:$ test_2.o  $(filter-out $(SRCDIR)/main.o $(TEST_OBJ), $(OBJECTS))
	$(CC) $(CFLAGS) $^ -o bin/$@

test: $(TEST_TARGETS)
	./bin/test_1 > ./bin/test/test1_output
	./bin/test_2 > ./bin/test/test2_output
	

# Clean target
clean:
	rm -f $(OBJECTS) bin/$(EXECUTABLE) $(TEST_OUTPUT)
	rm -f bin/test/*
	rm test_1.o test_2.o



# Tarball target
tar: clean
	tar -czf ChessAlpha.tar.gz *

# Define dependencies
main.o: main.c chess.c $(HEADERS)
chess.o: chess.c $(HEADERS)
board.o: board.c $(HEADERS)
movegen.o: movegen.c $(HEADERS) 
test_%.o: $(SRCDIR)/test_%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@


