# Компилятор
CC = gcc

# Флаги компиляции
CFLAGS = -Wall -Wextra -g -std=c11 -Iinclude

# Каталоги
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Исходники и объектные файлы
SRC = $(wildcard $(SRC_DIR)/*.c) main.c
OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(SRC)))

# Имя исполняемого файла
TARGET = $(BIN_DIR)/matrix_main

# Правило по умолчанию
all: $(TARGET)

# Компиляция исполняемого файла
$(TARGET): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Компиляция .c в .o
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Очистка
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Пересборка
rebuild: clean all

# Отладочная сборка
debug: CFLAGS += -DDEBUG
debug: rebuild

