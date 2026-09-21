CC = gcc
CFLAGS = -O2 -std=gnu99 -D_DEFAULT_SOURCE -I$(SRC_DIR)
LIBS = -lncurses -lm

SRC_DIR = src
TARGET = sineview

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

# ATENÇÃO AQUI: $(LIBS) deve ficar no final da linha de linkagem
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LIBS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SRC_DIR)/*.o $(TARGET)

.PHONY: all clean
