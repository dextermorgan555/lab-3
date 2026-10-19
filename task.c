#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <windows.h> // <--- 1. Додано бібліотеку для роботи з консоллю Windows

#define GROUP_NUM   79   
#define VARIANT_NUM 5    
#define COURSE_NUM  4    

/* ---------- Завдання 1 ---------- */
/* Змінні передаються за адресою (вказівники), тому функція
   змінює оригінальні змінні з main. */

void Calculations(double *a, double *b, double *c)
{
    double sum  = *a + *b + *c;
    double prod = *a * *b * *c;
    double trig;

    if (VARIANT_NUM % 2 == 0)
        trig = sin(sum);    
    else
        trig = cos(prod); 

    *a = sum;
    *b = prod;
    *c = trig;
}

/* ---------- Завдання 2 ---------- */
/* Рекурсивна сума цифр без циклів.
   Базовий випадок: n == 0 -> 0.
   Крок: остання цифра (n % 10) + сума цифр числа n / 10. */

int sum_of_digits(int n)
{
    if (n < 0)
        n = -n;                 
    if (n == 0)
        return 0;
    return (n % 10) + sum_of_digits(n / 10);
}

/* ---------- Завдання 4 ---------- */

void task4(void)
{
    int n;
    printf("Введіть розмір масиву N: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Некоректний розмір масиву.\n");
        return;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Помилка виділення пам'яті.\n");
        return;
    }

    srand((unsigned)time(NULL));

    /* Заповнення випадковими числами (0..99) */
    int *ptr = arr;
    for (int i = 0; i < n; i++)
        *(ptr++) = rand() % 100;

    /* 1. Початковий масив з адресами */
    printf("\nПочатковий масив:\n");
    ptr = arr;
    for (int i = 0; i < n; i++, ptr++)
        printf("значення: %3d, адреса: %p\n", *ptr, (void *)ptr);

    /* Пошук мінімуму та максимуму */
    int *min_ptr = arr;
    int *max_ptr = arr;
    for (ptr = arr + 1; ptr < arr + n; ptr++) {
        if (*ptr < *min_ptr) min_ptr = ptr;
        if (*ptr > *max_ptr) max_ptr = ptr;
    }

    /* 2. Знайдені елементи */
    printf("\nМінімум: значення %d, адреса %p\n", *min_ptr, (void *)min_ptr);
    printf("Максимум: значення %d, адреса %p\n", *max_ptr, (void *)max_ptr);

    /* Обмін через розіменування */
    int tmp = *min_ptr;
    *min_ptr = *max_ptr;
    *max_ptr = tmp;

    /* 3. Результуючий масив */
    printf("\nМасив після обміну:\n");
    for (ptr = arr; ptr < arr + n; ptr++)
        printf("%d ", *ptr);
    printf("\n");

    free(arr);
}

int main(void)
{
    // <--- 2. Встановлюємо кодування UTF-8 (65001) для виводу та вводу консолі
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    /* ---------- Завдання 1 ---------- */
    printf("=== Завдання 1 ===\n");
    double group   = GROUP_NUM;
    double variant = VARIANT_NUM;
    double course  = COURSE_NUM;

    printf("До обчислень:\n");
    printf("Група: %.0f, Варіант: %.0f, Курс: %.0f\n", group, variant, course);

    Calculations(&group, &variant, &course);

    printf("Після обчислень:\n");
    printf("Група (сума): %.4f\n", group);
    printf("Варіант (добуток): %.4f\n", variant);
    printf("Курс (%s): %.4f\n",
           VARIANT_NUM % 2 == 0 ? "синус суми" : "косинус добутку", course);

    /* ---------- Завдання 2 ---------- */
    printf("\n=== Завдання 2 ===\n");
    int number;
    printf("Введіть ціле число: ");
    if (scanf("%d", &number) == 1)
        printf("Сума цифр числа %d дорівнює %d\n", number, sum_of_digits(number));
    else
        printf("Некоректне введення.\n");

    /* ---------- Завдання 3 ---------- */
    printf("\n=== Завдання 3 ===\n");
    double arr[] = {1, 2, group, variant, course};   
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Початковий масив:\n");
    for (int i = 0; i < size; i++)
        printf("%.4f ", arr[i]);
    printf("\n");

    arr[0] = GROUP_NUM;     
    arr[1] = COURSE_NUM;   
    for (int i = 0; i < size; i++)
        arr[i] += VARIANT_NUM;

    printf("Новий масив:\n");
    for (int i = 0; i < size; i++)
        printf("%.4f ", arr[i]);
    printf("\n");

    /* ---------- Завдання 4 ---------- */
    printf("\n=== Завдання 4 ===\n");
    task4();

    return 0;
}