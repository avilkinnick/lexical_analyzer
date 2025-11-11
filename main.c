#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

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

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        fputs("Valid usage:\n", stderr);
        fputs("lexical_analyzer source_file.c\n", stderr);
        return EXIT_FAILURE;
    }

    const char* const absolute_source_file_path = argv[1];

    FILE* const file = fopen(absolute_source_file_path, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Failed to open %s\n", absolute_source_file_path);
        return EXIT_FAILURE;
    }

    fclose(file);

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
