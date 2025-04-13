#ifndef CONFIG_H
#define CONFIG_H

/**
 * @file config.h
 * @brief Конфиг для глобальных настроек
 */ 

// Базовый тип элементов матриц (можно заменить на float, int и т.д.)
typedef double elem_t;

// Формат вывода (используется в printf/scanf)
#define ELEM_FMT "%d"

// Кол-во знаков после запятой при печати
#define PRINT_PRECISION 2

#endif

