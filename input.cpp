#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "input.h"
#include "debug.h"
#include "matrix.h"

static const int kMaxBuf = 257;

//! Cuts spaces out of buffer and full the 'command' with the remaining string.
//!
//! @param buf    buffer,
//! @param command    command keyword.
//!
//! @return false if there are more then one word in buffer. True if there is one word in buffer.

static bool CutSpaces(const char *buf, char *command);

InputResults GetMatrixSize(size_t *table_size)
{
    static char buf[kMaxBuf] = {0};
    buf[0] = '\0';

    int i = 0;

    int c = 0;

    bool BufferOverflowStatus = false;

    while ((c = getc(stdin)) != '\n')
    {
        if (i < kMaxBuf - 1)
        {
            if (c != EOF)
            {
                buf[i++] = (char) c;
            }
            else
            {
                return kEofError;
            }
        }
        else
        {
            BufferOverflowStatus = true;
        }
    }

    if (buf[0] == '\0')
    {
        return kZeroStr;
    }

    if (BufferOverflowStatus)
    {
        return kBufferOverflowError;
    }

    if (i > 0)
    {
        buf[i] = '\0';
    }

    char *number_end = nullptr;

    size_t matrix_size = (size_t) strtol(buf, &number_end, 10);

    while (isspace(*number_end))
    {
        number_end++;
    }

    if (*number_end == '\0')
    {
        *table_size = matrix_size;

        return kInputSuccess;
    }
    else
    {
        return kInputError;
    }
}

InputResults GetInput(FILE *ptr_file, int *table, size_t command_count)
{
    if (ferror(ptr_file))
    {
        return kInputFileError;
    }

    CHECK(ptr_coefficients);
    CHECK(ptr_file);

    static char buf[kMaxBuf] = {0};
    buf[0] = '\0';

    int i = 0;

    int c = 0;

    bool BufferOverflowStatus = false;

    while ((c = getc(ptr_file)) != '\n')
    {
        if (i < kMaxBuf - 1)
        {
            if (c != EOF)
            {
                buf[i++] = (char) c;
            }
            else
            {
                return kEofError;
            }
        }
        else
        {
            BufferOverflowStatus = true;
        }
    }

    if (buf[0] == '\0')
    {
        return kZeroStr;
    }

    if (BufferOverflowStatus)
    {
        return kBufferOverflowError;
    }

    if (i > 0)
    {
        buf[i] = '\0';
    }

    return ConvertBuf(buf, table, command_count);
}

InputResults ConvertBuf(char *buf,
                        int *table,
                        size_t command_count)
{
    CHECK(buf);
    CHECK(table);

    static char command[kMaxBuf] = {0};
    command[0] = '\0';

    bool is_one_word = CutSpaces(buf, command);

    if (is_one_word)
    {
        for (int i = 0; i < kCommandArraySize; ++i)
        {
            if (strcmp(command, CommandArray[i].command_name) == 0)
            {
                return CommandArray[i].result;
            }
        }
    }

    return ConvertBufToCoeffs(buf,
                              table,
                              command_count);
}

InputResults ConvertBufToCoeffs(char *buf,
                                int *table,
                                size_t command_count)
{
    CHECK(buf);
    CHECK(ptr_coefficients);

    char *number_end = nullptr;

    static int x_pos = 0;
    static int y_pos = 0;

    y_pos = strtod(buf, &number_end) - 1;

    if (buf != number_end)
    {
        buf = number_end;
        x_pos = strtod(buf, &number_end) - 1;
    }

    if (x_pos > command_count || y_pos > command_count)
    {
        return kInputError;
    }

    int input_copy = 0;

    if (buf != number_end)
    {
        buf = number_end;
        input_copy = strtod(buf, &number_end);
    }

    CHECK(x_pos <= command_count);
    CHECK(y_pos <= command_count);

    if (x_pos > y_pos)
    {
        int tmp = x_pos;

        x_pos = y_pos;

        y_pos = tmp;

        input_copy *= -1;
    }

    while (isspace(*number_end))
    {
        ++number_end;
    }

    if (x_pos == y_pos)
    {
        return kInputError;//dream about good error name and massage
    }

    if (*number_end == '\0' && buf[0] != '\0')
    {
        *(table + (y_pos) * (y_pos - 1) / 2 + x_pos) += input_copy;
        return kInputSuccess;
    }
    else
    {
        return kInputError;
    }
}

static bool CutSpaces(const char *buf, char *command)
{
    CHECK(buf);
    CHECK(command);

    int i = 0;

    while (isspace(buf[i]))
    {
        ++i;
    }

    int j = 0;

    while (!isspace(buf[i]) && buf[i] != '\0')
    {
        command[j++] = buf[i++];
    }

    command[j] = '\0';

    while (isspace(buf[i]))
    {
        ++i;
    }

    return buf[i] == '\0';
}

