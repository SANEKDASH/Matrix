#include <stdio.h>

#include "matrix.h"
#include "debug.h"
#include "color_print.h"

void CleverPrintMatrix(const double *matrix, const size_t size_y, const size_t size_x)
{
    CHECK(matrix);

    for (size_t y = 0; y < size_y; y++)
    {
        for (size_t x = 0; x < size_x; x++)
        {
            printf("(%d, %d) = %5.2lf     ", y + 1, x + 1, *(matrix + y * size_x + x));
        }
        printf("\n\n");
    }

}

void Multiply(const double *matrix_a,
              const double *matrix_b,
                    double *matrix_c,
              const size_t size_y,
              const size_t size_x)
{
    CHECK(matrix_a);
    CHECK(matrix_b);
    CHECK(matrix_c);

    for (size_t y = 0; y < size_y; y++)
    {
        for (size_t x = 0; x < size_x; x++)
        {
            for (size_t m = 0; m < size_x; m++)
            {
                *(matrix_c + y * size_x + x) += *(matrix_a + y * size_x + m) *
                                                *(matrix_b + m * size_x + x);
            }
        }
    }
}

void PrintTriangleMatrix(const int* matrix, const size_t size_y)
{
    CHECK(matrix);
    CHECK(size_y != 0);

    for (size_t y = 0; y < size_y; y++)
    {
        size_t x = 0;

        for (; x < y; x++)
        {
            printf("(%d, %d) - %d    ", y + 1, x + 1, *( (matrix + (y) * (y - 1) / 2) + x ));//do formula
        }

        printf("(%d, %d) - X\n", x + 1, y + 1);
    }
}

void EnterTriangleMatrix(int* matrix, const size_t size_y)
{
    CHECK(matrix);

    for (size_t y = 0; y < size_y; y++)
    {
        for (size_t x = 0; x <= y; x++)
        {
            ColorPrintf(kGold, "#/ enter (%d, %d) slot value: ", y + 1, x + 1);
            scanf("%lf", matrix + x + y);  //�������� �� ���-�� ���������� � �����������
        }
    }
}

int MyMemset(int *array, size_t count)
{
    for (size_t i = 0; i < count; ++i)
    {
        array[i] = 0;
    }

    return 0;
}


