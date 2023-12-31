#include <stdio.h>
#include <stdlib.h>

#define DEBUG

#include "color_print.h"
#include "matrix.h"
#include "input.h"
#include "debug.h"

int main()
{
    //������� � ��������� �������
    printf("#/ Hello, this program helps coaches manage tournaments.\n"
           "#/ Write the count of teams below to start work.\n#/ ");

    size_t command_count = 0;

    InputResults status = kInputSuccess;

    while((status = GetMatrixSize(&command_count)) != kInputSuccess &&
                                            status != kQuit &&
                                            status != kInputFileError)
    {
        switch (status)
        {
            case kZeroStr:
            {
                printf("#/ ");

                break;
            }

            case kInputError:
            {
                ColorPrintf(kRed, "#/ Try to write the commands count correctly.\n");
                printf("#/ ");

                break;
            }

            case kBufferOverflowError:
            {
                printf("#/ Man, don't kid me please.\n");

                break;
            }

            case kHelp:

            case kPrint:

            case kEofError:

            case kInputFileError:

            case kQuit:

            case kInputSuccess:

            default:
            {
                printf("#/ DOOLBO@#!!!");

                CHECK(0);

                break;
            }
        }
    }
    printf("#/ Good. Now you can type 'help' command\n"
           "#/ to see the list of commands.\n#/ ");

    unsigned int number_of_meetings = (1 + command_count) * (command_count) / 2;

    int *table = (int*) calloc(number_of_meetings,
                               sizeof(int));

    MyMemset(table, number_of_meetings);


    while ((status = GetInput(stdin, table, command_count)) != kQuit &&
                                                     status != kEofError &&
                                                     status != kInputFileError)
    {
        switch (status)
        {
            case kZeroStr:
            {
                printf("#/ ");

                break;
            }

            case kInputSuccess:
            {
                ColorPrintf(kGreen, "#/ Data successfully saved!.\n");
                printf("#/ ");

                break;
            }

            case kPrint:
            {
                PrintTriangleMatrix(table, command_count);
                printf("#/ ");

                break;
            }

            case kInputError:
            {
                ColorPrintf(kRed, "#/ Try to type 'help' to see the list of commands.\n");
                printf("#/ ");

                break;
            }

            case kHelp:
            {
                ColorPrintf(kGold, "#/ 'team 1' 'team 2' 'team 1 score' - to save the score of team 1.\n");

                for (int i = 0; i < kCommandArraySize; ++i)
                {
                    ColorPrintf(kGold, "#/ '%s' - %s.\n", CommandArray[i].command_name,
                                                          CommandArray[i].help_text);
                }
                printf("#/ ");

                break;
            }

            case kBufferOverflowError:
            {
                printf("#/ Man, don't kid me please.\n");

                break;
            }

            case kEofError:

            case kInputFileError:

            case kQuit:

            default:
            {
                printf("#/ DOOLBO@#!!!");

                CHECK(0);

                break;
            }

        }
    }

    free(table);

    return 0;
}
