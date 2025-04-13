# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
INCLUDES = -Iinclude -Isrc/matrix -Isrc/output
LIBS = -lcunit

# Исходники
SRC = src/matrix/matrix.c src/output/output.c
MAIN = src/main.c
TESTS = tests/tests_matrix.c tests/tests_output.c tests/tests_main.c

# Форматирование кода через clang-format
format:
	clang-format -style=LLVM -i $(wildcard src/*.c src/*.h)


# Генерация конфигурационного файла .clang-format
generate-clang-format-config:
	$(CLANG_FORMAT) -style=LLVM -dump-config > .clang-format

# Статический анализ кода через cppcheck
lint:
	cppcheck --enable=all --inconclusive src/


# Запуск автотестов CUnit
test:
	$(CUNIT)

# Цели
all: build/main

build/main: $(MAIN) $(SRC) | build
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

# CUnit-тесты
tests: build/tests_matrix build/tests_output build/tests_main

build/tests_matrix: tests/tests_matrix.c $(SRC) | build
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ $(LIBS)

build/tests_output: tests/tests_output.c $(SRC) | build
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ $(LIBS)

build/tests_main: tests/tests_main.c $(SRC) | build
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ $(LIBS)

run_tests: tests
	./build/tests_matrix
	./build/tests_output
	./build/tests_main

# Создание папки build, если не существует
build:
	mkdir -p build

clean:
	rm -rf build/*

rebuild: clean all

