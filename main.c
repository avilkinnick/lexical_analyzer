#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 128

typedef enum BufferState
{
    BUFFER_STATE_INITIAL,
    BUFFER_STATE_SEPARATOR,
    BUFFER_STATE_DIGIT,
    BUFFER_STATE_IDENTIFIER,
    BUFFER_STATE_INVALID
} BufferState;

// C language keywords (relevant for C17 standard)
static const char* const KEYWORDS[] = {
    "auto",     "break",   "case",     "char",    "const",
    "continue", "default", "do",       "double",  "else",
    "enum",     "extern",  "float",    "for",     "goto",
    "if",       "inline",  "int",      "long",    "register",
    "restrict", "return",  "short",    "signed",  "sizeof",
    "static",   "struct",  "switch",   "typedef", "union",
    "unsigned", "void",    "volatile", "while"
};

static int is_whitespace_character(const char ch);
static int is_separator(const char ch);
static int is_digit(const char ch);
static int is_uppercase_letter(const char ch);
static int is_lowercase_letter(const char ch);

static int compare_number(const int number1, const int number2);

static int binary_search_string(
    const char* const str,
    const char* const * const array,
    const int array_size
);

static int binary_search_number(
    const int number,
    const int * const array,
    const int array_size
);

FILE* file = NULL;

static void cleanup(void);

int main(int argc, char* argv[])
{
    atexit(cleanup);

    if (argc != 2)
    {
        fputs("Valid usage:\n", stderr);
        fputs("lexical_analyzer source_file.c\n", stderr);
        return EXIT_FAILURE;
    }

    const char* const absolute_source_file_path = argv[1];

    file = fopen(absolute_source_file_path, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Failed to open %s\n", absolute_source_file_path);
        return EXIT_FAILURE;
    }

    char buffer[MAX_BUFFER_SIZE] = "";
    int buffer_length = 0;
    BufferState buffer_state = BUFFER_STATE_INITIAL;

    char ch;
    while (fscanf(file, "%c", &ch) != EOF)
    {
        switch (buffer_state)
        {
            case BUFFER_STATE_INITIAL:
            {
                if (ch == '#')
                {
                    while (ch != '\n')
                    {
                        fscanf(file, "%c", &ch);
                    }
                }
                else if (is_separator(ch))
                {
                    buffer[buffer_length] = ch;
                    ++buffer_length;
                    buffer_state = BUFFER_STATE_SEPARATOR;
                }
                else if (is_digit(ch))
                {
                    buffer[buffer_length] = ch;
                    ++buffer_length;
                    buffer_state = BUFFER_STATE_DIGIT;
                }
                else if (is_uppercase_letter(ch) || is_lowercase_letter(ch) || ch == '_')
                {
                    buffer[buffer_length] = ch;
                    ++buffer_length;
                    buffer_state = BUFFER_STATE_IDENTIFIER;
                }

                break;
            }
            case BUFFER_STATE_SEPARATOR:
            {
                break;
            }
            case BUFFER_STATE_DIGIT:
            {
                break;
            }
            case BUFFER_STATE_IDENTIFIER:
            {
                if (is_whitespace_character(ch))
                {
                }
                else if (is_digit(ch) || is_uppercase_letter(ch) || is_lowercase_letter(ch) || ch == '_')
                {
                }

                break;
            }
            case BUFFER_STATE_INVALID:
            {
                break;
            }
        }
    }

    return EXIT_SUCCESS;
}

static int is_whitespace_character(const char ch)
{
    switch (ch)
    {
        case '\t': case '\n': case '\r': case ' ':
        {
            return 1;
        }
        default:
        {
            return 0;
        }
    }
}

static int is_separator(const char ch)
{
    switch (ch)
    {
        case '!': case '"': case '%': case '&': case '\'':
        case '(': case ')': case '*': case '+': case ',':
        case '-': case '.': case '/': case ':': case ';':
        case '<': case '=': case '>': case '?': case '[':
        case ']': case '{': case '|': case '}':
        {
            return 1;
        }
        default:
        {
            return 0;
        }
    }
}

static int is_digit(const char ch)
{
    return ch >= '0' && ch <= '9';
}

static int is_uppercase_letter(const char ch)
{
    return ch >= 'A' && ch <= 'Z';
}

static int is_lowercase_letter(const char ch)
{
    return ch >= 'a' && ch <= 'z';
}

static int compare_number(const int number1, const int number2)
{
    if (number1 < number2)
    {
        return -1;
    }
    else if (number1 == number2)
    {
        return 0;
    }
    else // (number1 > number2)
    {
        return 1;
    }
}

static int binary_search_string(const char* const str, const char* const * const array, const int array_size)
{
    int low_index = 0;
    int high_index = array_size - 1;

    while (low_index <= high_index)
    {
        const int middle_index = (low_index + high_index) / 2;

        const int compare_result = strcmp(str, array[middle_index]);
        if (compare_result == 0)
        {
            return middle_index;
        }
        else if (compare_result < 0)
        {
            high_index = middle_index - 1;
        }
        else // (compare_result > 0)
        {
            low_index = middle_index + 1;
        }
    }

    return -1;
}

static int binary_search_number(const int number, const int * const array, const int array_size)
{
    int low_index = 0;
    int high_index = array_size - 1;

    while (low_index <= high_index)
    {
        const int middle_index = (low_index + high_index) / 2;

        const int compare_result = compare_number(number, array[middle_index]);
        if (compare_result == 0)
        {
            return middle_index;
        }
        else if (compare_result < 0)
        {
            high_index = middle_index - 1;
        }
        else // (compare_result > 0)
        {
            low_index = middle_index + 1;
        }
    }

    return -1;
}

static void cleanup(void)
{
    if (file != NULL)
    {
        fclose(file);
    }
}
