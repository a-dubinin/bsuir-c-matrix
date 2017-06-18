/**
 * Программа поиска в матрице столбца с наименьшей суммой элементов
 * и строки с наибольшей суммой элементов.
 * Разработчик - Дубинин А. В. (http://dubinin.net)
 * 27.11.2016
 */

// Подключение файлов из стандартной библиотеки
#include <locale.h>
#include <stdio.h>
#include <string.h>

// Объявление макроса (перевод курсора на новую строку)
#define BR putchar('\n')

// Объявление символических констант
#define DIMENSION          5
#define MSG_MATRIX_TITLE  "Матрица %dx%d\n"
#define ELEMENT_PATTERN   "%4d"
#define RESULT_PATTERN    "№%-2d"
#define MSG_RESULT_COLUMN "Столбец с наименьшей суммой элементов: "
#define MSG_RESULT_ROW    "Строка с наибольшей суммой элементов: "
#define MSG_RESULT_ALL    "Все %s имеют одинаковую сумму элементов\n"
#define MSG_APP_EXIT      "Для выхода из программы нажмите любую клавишу"

/*
 * Прототипы функций hr, displayResult
 */
void hr();
void displayResult(int, int[], char[], char[]);

void main()
{
    setlocale(LC_ALL, "");  // установка локализации
    int columns[DIMENSION]; // номера столбцов с min суммой элементов
    int rows[DIMENSION];    // номера строк с max суммой элементов

    /*
     * Объявление переменных типа int
     */
    int i, j;
    int currentNumber;     // номер текущего столбца/строки
    int currentSumColumn;  // сумма значений эл-в текущего столбца
    int currentSumRow;     // сумма значений эл-в текущей строки
    int minSumColumn;      // min сумма значений эл-в столбца
    int maxSumRow;         // max сумма значений эл-в строки
    int minSumColumnCount; // кол-во столбцов с min суммой значений эл-в
    int maxSumRowCount;    // кол-во строк с max суммой значений эл-в

    /*
     * Объявление и инициализация матрицы
     */
    int matrix[DIMENSION][DIMENSION] = {
        {1, 2, 33, 41, 5},
        {7, 12, 3, 14, 89},
        {1, 2, 15, 8, 5},
        {9, 16, 9, 4, 8},
        {11, 2, 53, 15, 5}
    };
//    int matrix[DIMENSION][DIMENSION] = {
//        {1, 1, 33, 1, 5},
//        {17, 2, 3, 2, 19},
//        {31, 3, 52, 3, 25},
//        {9, 2, 9, 2, 8},
//        {33, 1, 54, 1, 25}
//    };
//    int matrix[DIMENSION][DIMENSION] = {
//        {1, 2, 3, 4, 5},
//        {1, 2, 3, 4, 5},
//        {1, 2, 3, 4, 5},
//        {1, 2, 3, 4, 5},
//        {1, 2, 3, 4, 5}
//    };
//    int matrix[DIMENSION][DIMENSION] = {
//        {1, 1, 1, 1, 1},
//        {2, 2, 2, 2, 2},
//        {3, 3, 3, 3, 3},
//        {4, 4, 4, 4, 4},
//        {5, 5, 5, 5, 5}
//    };
//    int matrix[DIMENSION][DIMENSION] = {
//        {1, 1, 1, 1, 1},
//        {1, 1, 1, 1, 1},
//        {1, 1, 1, 1, 1},
//        {1, 1, 1, 1, 1},
//        {1, 1, 1, 1, 1}
//    };

    /*
     * Вывод на экран элементов матрицы.
     * Поиск столбцов с min суммой значений эл-в
     * и строки с max суммой значений эл-в.
     */
    printf(MSG_MATRIX_TITLE, DIMENSION, DIMENSION);
    hr();
    for (i = 0; i < DIMENSION; i++) {
        currentSumColumn = 0;
        currentSumRow = 0;
        for (j = 0; j < DIMENSION; j++) {
            printf(ELEMENT_PATTERN, matrix[i][j]); // вывод элемента матрицы
            currentSumColumn += matrix[j][i]; // суммирование эл-в столбца
            currentSumRow += matrix[i][j];    // суммирование эл-в строки
        }
        BR;

        /*
         * Присвоение переменной minSumColumn значения суммы эл-в 1-го столбца,
         * переменной maxSumRow - суммы эл-в 1-ой строки.
         * Добавление в массивы columns и rows номера 1, т.к. считаем,
         * что первый столбец имеет min сумму эл-в, и первая строка -
         * max сумму эл-в.
         * Переменным minSumColumnCount и maxSumRowCount присваивается
         * значение 1.
         * Переход к следующей итерации цикла.
         */
        currentNumber = i + 1;
        if (i == 0) {
            minSumColumn = currentSumColumn;
            maxSumRow = currentSumRow;
            columns[0] = currentNumber;
            rows[0] = currentNumber;
            minSumColumnCount = 1;
            maxSumRowCount = 1;
            continue;
        }

        /*
         * Сравнение суммы эл-в текущего столбца с min суммой.
         * Если меньше, то переменной minSumColumn присваивается значение
         * суммы эл-в текущего столбца. При этом массив columns очищается,
         * в него заносится значение номера текущего столбца, переменной
         * minSumColumnCount присваивается значение 1.
         * Если сумма эл-в текущего столбца равна min сумме, то в массив
         * columns добавляется значение номера текущего столбца,
         * кол-во столбцов с min суммой (minSumColumnCount) инкрементируется.
         */
        if (currentSumColumn < minSumColumn) {
            minSumColumn = currentSumColumn;
            memset(columns, 0, sizeof columns);
            columns[0] = currentNumber;
            minSumColumnCount = 1;
        } else if (currentSumColumn == minSumColumn) {
            columns[minSumColumnCount] = currentNumber;
            minSumColumnCount++;
        }

        /*
         * Алгоритм анализа суммы эл-в текущего строки с max суммой
         * аналогичен алгоритму для столбца, за исключением знака
         * сравнения значений.
         */
        if (currentSumRow > maxSumRow) {
            maxSumRow = currentSumRow;
            memset(rows, 0, sizeof rows);
            rows[0] = currentNumber;
            maxSumRowCount = 1;
        } else if (currentSumRow == maxSumRow) {
            rows[maxSumRowCount] = currentNumber;
            maxSumRowCount++;
        }
    }
    hr();
    BR;

    // Вывод на экран результатов
    displayResult(minSumColumnCount, columns, MSG_RESULT_COLUMN, "столбцы");
    displayResult(maxSumRowCount, rows, MSG_RESULT_ROW, "строки");
    hr();

    // Вывод на экран диалога выхода из программы
    printf(MSG_APP_EXIT);
    getchar();
    return;
}

/*
 * Функция вывода на всю ширину окна
 * горизонтальной полосы
 */
void hr()
{
    int i;
    for (i = 0; i <= 79; i++) {
        putchar('-');
    }
    return;
}

/*
 * Функция вывода на экран результата.
 * Если кол-во (параметр count) столбцов/строк (параметр resultList[])
 * с наименьшей/наибольшей суммой элементов равно размерности матрицы,
 * то выводится соответствующее сообщение.
 * Иначе, выводятся найденные номера столбцов/строк.
 *
 * count - параметр типа int,
 * resultList[] - параметр массив элементов типа int,
 * msg[], entity[] - параметры строки (массивы элементов типа char).
 */
void displayResult(int count, int resultList[], char msg[], char entity[])
{
    if (count == DIMENSION) {
        printf(MSG_RESULT_ALL, entity);
    } else {
        printf("%s", msg);
        int i;
        for (i = 0; i < count; i++) {
            printf(RESULT_PATTERN, resultList[i]);
        }
        BR;
    }
    return;
}
