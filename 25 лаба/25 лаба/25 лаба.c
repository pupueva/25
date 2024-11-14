//25 ����
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define CRT_NO_SECURE_DEPRECATE

#define K 10 // �������� �������� ��� �����������

// ������� ��� ��������� ���������� ������ ����� �� 1 �� mmax
int rand10(int mmax) {
    return 1 + rand() % mmax;
}

// ������� ��� ��������� ���������� ������������� ����� � ��������� �� dmin �� dmax
double rand_double(double dmin, double dmax) {
    return dmin + ((double)rand() / RAND_MAX) * (dmax - dmin);
}

// ������� ��� ��������� ������� n ��������� ����� ����� �� 1 �� mmax
int* rand10_n(int n, int mmax) {
    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("������ ��������� ������\n");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        arr[i] = rand10(mmax);
    }
    return arr;
}

// ������� ��� ��������� ������� n ��������� ������������ ����� �� -dm �� +dm
double* rand_double_n(int n, double dm) {
    double* arr = (double*)malloc(n * sizeof(double));
    if (arr == NULL) {
        printf("������ ��������� ������\n");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        arr[i] = rand_double(-dm, dm);
    }
    return arr;
}

// ������� ��� ������ ������� ����� �����
void print_int_array(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// ���������� ������������ ����������� ������� ��������� ��������
void histogram(int* array, int n, int k, int max_symbols) {
    int counter[K] = { 0 }; // ������ ���������, ������������������ ������

    // ��������� ��������
    for (int i = 0; i < n; i++) {
        if (array[i] >= 1 && array[i] <= k) {
            counter[array[i] - 1]++;
        }
    }

    // ���������� ������������ �������� � ��������� ��� ������������
    int nmax = 0;
    for (int i = 0; i < k; i++) {
        if (counter[i] > nmax) {
            nmax = counter[i];
        }
    }

    // ���������� �����������
    printf("\n����������� ������� ��������� ��������:\n");
    for (int i = 0; i < k; i++) {
        int stars = (nmax > 0) ? (counter[i] * max_symbols) / nmax : 0;
        printf("%2d: ", i + 1);
        for (int j = 0; j < stars; j++) {
            printf("*");
        }
        printf(" (%d)\n", counter[i]);
    }
}

// ������� ��� ������������ ������ ������� ����� �� k �������
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

    // ������ �����
    int m = 1 + rand() % 10;
    int k;
    printf("�������� ����� �� 1 �� 10: ");
    scanf_s("%d", &k);
    if (k == m) {
        printf("�� �������!\n");
    }
    else {
        printf("�� �� �������. ���������� �����: %d\n", m);
    }

    // ������������� ������� ��� ��������� ��������� �����
    int n = 20; // ���������� ��������� �����
    int mmax = 10;
    int max_symbols = 20; // ������������ ����� �������� '*' � ������

    printf("\n��������� %d ��������� ����� ����� �� 1 �� %d:\n", n, mmax);
    int* int_array = rand10_n(n, mmax);
    print_int_array(int_array, n);

    // ���������� ����������� ��� ������� ����� �����
    histogram(int_array, n, K, max_symbols);

    // ������ ������������ ������ �����
    int rotate_by = 3;
    printf("\n������ ����� ������������ ������ ����� �� %d:\n", rotate_by);
    rotate_left(int_array, n, rotate_by);
    print_int_array(int_array, n);

    // ������������ ������
    free(int_array);

    return 0;
}
