CC = gcc
CFLAGS = -O2 -std=gnu99
LIBS = -lncurses -lm

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
TARGET = sineview

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
