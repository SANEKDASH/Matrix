#ifndef input
#define input

typedef enum
{
    kInputError,          //!< an unknown function has been introduced
    kInputSuccess,        //!< three coefficients were successfully written
    kBufferOverflowError, //!< buffer is full
    kEofError,            //!< ran into EOF
    kInputFileError,      //!< error while opening input file
    //kTestFileError,       //!< error while opening test file
    kHelp,                //!< the help command is entered
    kQuit,                //!< the quit command is entered
    kZeroStr,             //!< the null line is entered
    kPrint
} InputResults;

//! Command structure

typedef struct
{
    const char *command_name; //!< name of command
    InputResults result;      //!< is a constant corresponding to the command
    const char *help_text;    //!< command actions
} Command;

const int kCommandArraySize = 3;

const Command CommandArray[kCommandArraySize] = {
                                                "help" , kHelp , "invokes list of commands",
                                                "quit" , kQuit , "to shutdown the program",
                                                "print", kPrint, "to print tournament table"
                                                };


//! Writes the characters read from the file to the buffer, outputs a constant corresponding to the command written to the buffer.
//! @param ptr_file    pointer to a readable file.
//! @param ptr_coeffients    pointer to the structure of coefficients.
//!
//! @note if there are three coefficients in the buffer, they are written to the structure pointed to by ptr_coeffients.
//!
//! @see ConvertBuf() ConvertBufToCoeffs()input.h

InputResults GetInput(FILE *ptr_file,
                      int *table,
                      size_t command_count);

//! Checks whether the string written in the buffer is a command. Outputs the constant corresponding to the command.
//! @param buf    buffer
//! @param ptr_coeffients    pointer to the coefficient structure
//!
//! @note if there are three coefficients in the buffer, they are written to the structure pointed to by ptr_coeffients.
//!
//! @see ConvertBufToCoeffs() input.h

InputResults ConvertBuf(char *buf,
                        int *table,
                        size_t command_count);

//! Writes the values of the coefficients specified in the buffer to the coefficient structure
//!
//! @param buf    buffer
//! @param ptr_coeffients    pointer to the structure of coefficients
//!
//! @note if coefficients are written incorrectly in the buffer, returns the kInputError error
//!
//! @see input.h

InputResults ConvertBufToCoeffs(char *buf,
                                int *table,
                                size_t command_count);

InputResults GetMatrixSize(size_t *table_size);

#endif


