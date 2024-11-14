//25 лаба
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define CRT_NO_SECURE_DEPRECATE

#define K 10 // диапазон значений для гистограммы

// Функция для генерации случайного целого числа от 1 до mmax
int rand10(int mmax) {
    return 1 + rand() % mmax;
}

// Функция для генерации случайного вещественного числа в диапазоне от dmin до dmax
double rand_double(double dmin, double dmax) {
    return dmin + ((double)rand() / RAND_MAX) * (dmax - dmin);
}

// Функция для генерации массива n случайных целых чисел от 1 до mmax
int* rand10_n(int n, int mmax) {
    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        arr[i] = rand10(mmax);
    }
    return arr;
}

// Функция для генерации массива n случайных вещественных чисел от -dm до +dm
double* rand_double_n(int n, double dm) {
    double* arr = (double*)malloc(n * sizeof(double));
    if (arr == NULL) {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        arr[i] = rand_double(-dm, dm);
    }
    return arr;
}

// Функция для вывода массива целых чисел
void print_int_array(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Построение вертикальной гистограммы частоты выпадения значений
void histogram(int* array, int n, int k, int max_symbols) {
    int counter[K] = { 0 }; // массив счётчиков, инициализированный нулями

    // Заполняем счетчики
    for (int i = 0; i < n; i++) {
        if (array[i] >= 1 && array[i] <= k) {
            counter[array[i] - 1]++;
        }
    }

    // Определяем максимальное значение в счетчиках для нормализации
    int nmax = 0;
    for (int i = 0; i < k; i++) {
        if (counter[i] > nmax) {
            nmax = counter[i];
        }
    }

    // Построение гистограммы
    printf("\nГистограмма частоты выпадения значений:\n");
    for (int i = 0; i < k; i++) {
        int stars = (nmax > 0) ? (counter[i] * max_symbols) / nmax : 0;
        printf("%2d: ", i + 1);
        for (int j = 0; j < stars; j++) {
            printf("*");
        }
        printf(" (%d)\n", counter[i]);
    }
}

// Функция для циклического сдвига массива влево на k позиций
void rotate_left(int* arr, int n, int k) {
    int* temp = (int*)malloc(k * sizeof(int));
    for (int i = 0; i < k; i++) {
        temp[i] = arr[i];
    }
    for (int i = 0; i < n - k; i++) {
        arr[i] = arr[i + k];
    }
    for (int i = 0; i < k; i++) {
        arr[n - k + i] = temp[i];
    }
    free(temp);
}

int main() {
    setlocale(LC_CTYPE, "RUS");
    srand((unsigned int)time(0));

    // Угадай число
    int m = 1 + rand() % 10;
    int k;
    printf("Угадайте число от 1 до 10: ");
    scanf_s("%d", &k);
    if (k == m) {
        printf("Вы угадали!\n");
    }
    else {
        printf("Вы не угадали. Загаданное число: %d\n", m);
    }

    // Использование функций для генерации случайных чисел
    int n = 20; // количество случайных чисел
    int mmax = 10;
    int max_symbols = 20; // максимальное число символов '*' в строке

    printf("\nГенерация %d случайных целых чисел от 1 до %d:\n", n, mmax);
    int* int_array = rand10_n(n, mmax);
    print_int_array(int_array, n);

    // Построение гистограммы для массива целых чисел
    histogram(int_array, n, K, max_symbols);

    // Пример циклического сдвига влево
    int rotate_by = 3;
    printf("\nМассив после циклического сдвига влево на %d:\n", rotate_by);
    rotate_left(int_array, n, rotate_by);
    print_int_array(int_array, n);

    // Освобождение памяти
    free(int_array);

    return 0;
}
