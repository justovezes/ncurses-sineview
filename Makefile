CC = gcc
CFLAGS = -std=gnu99
SRC_DIR = src
TARGET = sineview

# Busca todos os arquivos .c dentro da pasta src/
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Gera os nomes dos arquivos .o dentro da pasta src/
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

# Linka os objetos para gerar o executável na raiz
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LIBS)

# Regra para compilar cada .c da pasta src/ em .o
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpa o executável e os arquivos .o dentro de src/
clean:
	rm -f $(SRC_DIR)/*.o $(TARGET)

.PHONY: all clean
